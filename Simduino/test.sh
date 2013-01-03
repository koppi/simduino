#!/bin/sh

export SDL_VIDEO_WINDOW_POS="535,38"

resize.sh 6 37 520 250

record-desktop.sh &
rpid=$!

trap 'kill -INT -$pid' INT
timeout -s 2 $@ &
tpid=$!
wait $tpid
wait $rpid

