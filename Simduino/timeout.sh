#!/bin/sh

trap 'kill -INT -$pid' INT
timeout -s 2 $@ &
pid=$!
wait $pid
