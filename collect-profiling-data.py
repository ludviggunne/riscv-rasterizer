#!/usr/bin/env python3

import sys
import json
import os

_start_indicator = "# PROFILE START"
_end_indicator = "# PROFILE END"

class ProfileWindow:
    def __init__(self, json_object):
        # Collect the data in to a Python object and do some calculations
        self.name = json_object["name"]
        self.runs = json_object["runs"]
        self.cycles = json_object["mcycle"]
        self.instrs = json_object["minstret"]
        self.mem_instrs = json_object["mhpmcounter3"]
        self.i_misses = json_object["mhpmcounter4"]
        self.d_misses = json_object["mhpmcounter5"]
        self.i_stalls = json_object["mhpmcounter6"]
        self.d_stalls = json_object["mhpmcounter7"]
        self.hzd_stalls = json_object["mhpmcounter8"]
        self.alu_stalls = json_object["mhpmcounter9"]
        self.exec_time = self.cycles / 30000000
        self.ipc = self.instrs / self.cycles
        self.d_miss_ratio = self.d_misses / self.mem_instrs
        self.d_hit_ratio = 1 - self.d_miss_ratio
        self.i_miss_ratio = self.i_misses / self.instrs
        self.i_hit_ratio = 1 - self.i_miss_ratio
        self.alu_stall_ratio = self.alu_stalls / self.cycles
        self.mem_intensity = self.mem_instrs / self.instrs
        self.hzd_stall_ratio = self.hzd_stalls / self.cycles
        self.all_misses = self.i_misses + self.d_misses

def die(msg):
    print(msg, file=sys.stderr)
    sys.exit(1)

def pretty_name(name):
    return (name[0].upper() + name[1:]).replace("_", " ")

def read_profile_data_from_open_file(file):
    raw_data = ""
    found_start = False

    # Extract the profiling data from input
    for line in file:
        if not found_start:
            if line.startswith(_start_indicator):
                found_start = True
            continue
        if line.startswith(_end_indicator):
            break
        raw_data += line

    json_data = json.loads(raw_data)
    data = []

    # Convert json to ProfileWindow
    for obj in json_data:
        data.append(ProfileWindow(obj))

    return data

def default_printer(data):

    if len(data) == 0:
        return

    frame_exec_time = None

    ipc_acc = 0
    dmiss_acc = 0
    imiss_acc = 0
    alustall_acc = 0
    hzdstall_acc = 0
    memint_acc = 0

    for window in data:
        if window.name == "frame":
            frame_exec_time = window.exec_time
        if frame_exec_time is None:
            die("error: first registered window needs name \"frame\"")

        print(f"{pretty_name(window.name)}:")
        print(f"    Number of runs:     {window.runs}")
        print(f"    Execution time:     {round(window.exec_time, 2)}s")
        print(f"    % of frame time:    {round(100 * window.exec_time / frame_exec_time, 1)}%")
        print(f"    IPC:                {round(window.ipc, 2)}")
        print(f"    D-cache miss ratio: {round(window.d_miss_ratio * 100, 1)}%")
        print(f"    I-cache miss ratio: {round(window.i_miss_ratio * 100, 1)}%")
        print(f"    ALU-stall ratio:    {round(window.alu_stall_ratio * 100, 1)}%")
        print(f"    Hazard-stall ratio: {round(window.hzd_stall_ratio * 100, 1)}%")
        print(f"    Memory intensity:   {round(window.mem_intensity * 100, 1)}%")
        print("")

        ipc_acc += window.ipc
        dmiss_acc += window.d_miss_ratio
        imiss_acc += window.i_miss_ratio
        alustall_acc += window.alu_stall_ratio
        hzdstall_acc += window.hzd_stall_ratio
        memint_acc += window.mem_intensity

    ipc_acc /= len(data)
    dmiss_acc /= len(data)
    imiss_acc /= len(data)
    alustall_acc /= len(data)
    hzdstall_acc /= len(data)
    memint_acc /= len(data)

    print(f"Average IPC:                {round(ipc_acc, 2)}")
    print(f"Average D-cache miss ratio: {round(dmiss_acc * 100, 1)}%")
    print(f"Average I-cache miss ratio: {round(imiss_acc * 100, 1)}%")
    print(f"Average ALU-stall ratio:    {round(alustall_acc * 100, 1)}%")
    print(f"Average Hazard-stall ratio: {round(hzdstall_acc * 100, 1)}%")
    print(f"Average Memory intensity:   {round(memint_acc * 100, 1)}%")

def save_latex_table(table, path):
    with open(path, "w") as file:
        outstr = "\\begin{tabular}{ | l | " + "c | " * (len(table[0]) - 1) + "}\n    \\hline\n"
        outstr += "".join(map(lambda row: "    " + " & ".join(map(lambda x: str(x), row)) + " \\\\\n    \\hline\n", table))
        outstr += "\n\\end{tabular}\n"
        file.write(outstr)

# Create table with a separate window on each row
# and metrics for columns
def create_table_layout_1(data):
    table = [list(map(lambda x: "\\textbf{" + x + "}",
            ["Window",
            "IPC",
            "D-cache miss ratio",
            "I-cache miss ratio",
            "Memory intensity"]))]
    for window in data:
        table.append([pretty_name(window.name),
                    round(window.ipc, 2),
                    str(round(100 * window.d_miss_ratio, 1)) + "\\%",
                    str(round(100 * window.i_miss_ratio, 1)) + "\\%",
                    str(round(100 * window.mem_intensity, 1)) + "\\%"])
    return table

sys.tracebacklimit = 0
data = read_profile_data_from_open_file(sys.stdin)
default_printer(data)
save_latex_table(create_table_layout_1(data), "table.tex")

# Saving this for later
# if len(sys.argv) < 2:
#     print("Usage: {sys.argv[0]} <table name>", file=sys.stderr)
#     sys.exit(1)

# table_name = sys.argv[1]
# table_path = os.path.join("tables", table_name)

# os.makedirs(table_path, exist_ok=True)

# for window in data:
    # with open(os.path.join(table_path, window.name)) as file:
