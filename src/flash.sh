#!/bin/bash
if [ `pidof openocd` ] ; then killall openocd ; fi

openocd -f ../tools/openocd/openocd.cfg & 

sleep 0.5
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

