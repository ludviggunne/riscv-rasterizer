#!/usr/bin/env bash
tty=`tty`
dtekv-run build/dtekv/rast.bin | tee ${tty} | $(dirname $BASH_SOURCE)/collect_profiling_data.py
