#!/usr/bin/env bash
tty=`tty`
dtekv-run build/dtekv/rast.bin | tee ${tty} | ./collect-profiling-data.py
