#!/bin/bash
if [ `pidof openocd` ] ; then killall openocd ; fi

openocd -f ../tools/openocd/openocd.cfg > /dev/null 2>&1 & 
echo "Starting OpenOCD daemon..."

sleep 3

echo "Opening telnet connection to OpenOCD"
( 
    echo halt
    sleep 0.5
    echo flash write_bank 0 main.bin 0x0
    sleep 0.5
    echo reset
    sleep 0.5
    echo shutdown
) | telnet localhost 4444

sleep 1
if [ `pidof openocd` ] ; then killall openocd ; fi




