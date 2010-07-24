#!/bin/bash
killall openocd
openocd -f ../tools/openocd/openocd.cfg & 
sleep 1
( 
echo halt
sleep 1
echo flash write_bank 0 main.bin 0x0
sleep 1
echo reset
sleep 1
echo shutdown
) | telnet localhost 4444

#sleep 5
#killall openocd

