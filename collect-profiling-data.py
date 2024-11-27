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
    for window in data:
        print(f'{window.name.replace("_", " ")}:')
        print(f"    Number of runs:     {window.runs}")
        print(f"    Execution time:     {round(window.exec_time, 2)}s")
        print(f"    IPC:                {round(window.ipc, 2)}")
        print(f"    D-cache miss ratio: {round(window.d_miss_ratio * 100, 1)}%")
        print(f"    I-cache miss ratio: {round(window.i_miss_ratio * 100, 1)}%")
        print(f"    ALU-stall ratio:    {round(window.alu_stall_ratio * 100, 1)}%")
        print(f"    Hazard-stall ratio: {round(window.hzd_stall_ratio * 100, 1)}%")
        print(f"    Memory intensity:   {round(window.mem_intensity * 100, 1)}%")
        print("")

sys.tracebacklimit = 0
data = read_profile_data_from_open_file(sys.stdin)
default_printer(data)

# Saving this for later
# if len(sys.argv) < 2:
#     print("Usage: {sys.argv[0]} <table name>", file=sys.stderr)
#     sys.exit(1)

# table_name = sys.argv[1]
# table_path = os.path.join("tables", table_name)

# os.makedirs(table_path, exist_ok=True)

# for window in data:
    # with open(os.path.join(table_path, window.name)) as file:
