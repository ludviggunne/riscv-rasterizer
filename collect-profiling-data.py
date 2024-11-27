#!/usr/bin/env python3

import sys
import json
import pprint

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
    for line in sys.stdin:
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

sys.tracebacklimit = 0
for window in read_profile_data_from_open_file(sys.stdin):
    pprint.pp(window)
