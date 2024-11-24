#!/usr/bin/env bash
# Sets up a serial monitor on port `PORT`
PORT=${PORT:-/dev/ttyACM0}
sudo picocom -b9600 -d8 -p1 --imap lfcrlf $PORT
