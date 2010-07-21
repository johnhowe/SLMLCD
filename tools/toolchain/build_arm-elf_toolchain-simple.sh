#!/bin/bash

BINUTILS=binutils-2.20.1
GCC=gcc-4.5.0
NEWLIB=newlib-1.18.0
GDB=gdb-7.1


apt-get install --force-yes build-essential gcc-multilib texinfo libgmp3-dev libmpfr-dev libmpc-dev libexpat1-dev libncurses5-dev openocd aria2 

mkdir build
cd build

echo "http://ftp.gnu.org/gnu/binutils/$BINUTILS.tar.bz2
http://ftp.gnu.org/gnu/gcc/gcc-4.5.0/gcc-4.5.0.tar.bz2
ftp://sources.redhat.com/pub/newlib/newlib-1.18.0.tar.gz
http://ftp.gnu.org/gnu/gdb/gdb-7.1.tar.bz2" >> sourceURLs
aria2c -s 20 -i sourceURLs && 
rm sourceURLs

tar -xjf $BINUTILS.tar.bz2
tar -xvf $GCC.tar.bz2
tar -xvf $NEWLIB.tar.gz
tar -xvf $GDB.tar.bz2

# BINUTILS
cd $BINUTILS
./configure --target=arm-elf --prefix=/usr/local --enable-interwork --enable-multilib --with-float=soft --disable-werror
make all && make install

# GCC (part 1)
cd ../$GCC
./configure --target=arm-elf --prefix=/usr/local --enable-interwork --enable-multilib --with-float=soft --disable-werror --enable-languages="c,c++" --with-newlib --with-headers=../newlib-1.18.0/newlib/libc/include
make all-gcc && make install-gcc

# NEWLIB
cd ../$NEWLIB
./configure --target=arm-elf --prefix=/usr/local --enable-interwork --enable-multilib --with-float=soft --disable-werror
make all && make install

# GCC (part 2)
cd ../$GCC
make all && make install

# GDB
cd ../$GDB
./configure --target=arm-elf --prefix=/usr/local --enable-interwork --enable-multilib --with-float=soft --disable-werror
make all && make install
