#!/usr/bin/env bash
dtekv-run rast.bin | tee $(tty) | collect-profiling-data.py > profiling-data.tex.in
