#!/usr/bin/env bash
PORT=${PORT:-/dev/ttyACM0}
sudo picocom -b9600 -d8 -p1 --imap lfcrlf $PORT
