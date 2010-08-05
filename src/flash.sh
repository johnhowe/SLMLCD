#!/bin/bash
if [ `pidof openocd` ] ; then killall openocd ; fi

openocd -f ../tools/openocd/openocd.cfg & 

sleep 3

( 
    echo halt
    sleep 2
    echo flash write_bank 0 main.bin 0x0
    sleep 2
    echo reset
    sleep 2
    echo shutdown
) | telnet localhost 4444

sleep 1
if [ `pidof openocd` ] ; then killall openocd ; fi




