#!/bin/sh
# Written by Uwe Hermann <uwe@hermann-uwe.de>, released as public domain.
# Edited by Travis Wiens

TARGET=arm-eabi			 # Or: TARGET=arm-none-elf
PREFIX=/usr/local/arm # Install location of your final toolchain
PARALLEL=""			 # Or: PARALLEL=""

BINUTILS=binutils-2.20.1
GCC=gcc-4.4.3
NEWLIB=newlib-1.18.0
GDB=gdb-7.1

export PATH="$PATH:$PREFIX/bin"

mkdir build

aria2c -s 20 http://ftp.gnu.org/gnu/binutils/$BINUTILS.tar.bz2
tar xfvj $BINUTILS.tar.bz2 
cd build
../$BINUTILS/configure --target=$TARGET --prefix=$PREFIX --enable-interwork --enable-multilib --with-gnu-as --with-gnu-ld --disable-nls --with-float=soft --disable-werror
make $PARALLEL all
make install
cd ..
#rm -rf build/* $BINUTILS $BINUTILS.tar.bz2

aria2c -s 20 ftp://ftp.gnu.org/gnu/gcc/$GCC/$GCC.tar.bz2
tar xfvj $GCC.tar.bz2 
cd build
../$GCC/configure --target=$TARGET --prefix=$PREFIX --enable-interwork --enable-multilib --enable-languages="c,c++" --with-newlib --without-headers --disable-shared --with-gnu-as --with-gnu-ld --with-float=soft --disable-werror
make $PARALLEL all-gcc
make install-gcc
cd ..
#rm -rf build/* $GCC.tar.bz2

aria2c -s 20 ftp://sources.redhat.com/pub/newlib/$NEWLIB.tar.gz
tar xfvz $NEWLIB.tar.gz
cd build
../$NEWLIB/configure --target=$TARGET --prefix=$PREFIX --enable-interwork --enable-multilib --with-gnu-as --with-gnu-ld --disable-nls --with-float=soft --disable-werror
make $PARALLEL
make install
cd ..
#rm -rf build/* $NEWLIB $NEWLIB.tar.gz

# Yes, you need to build gcc again!
cd build
../$GCC/configure --target=$TARGET --prefix=$PREFIX --enable-interwork --enable-multilib --enable-languages="c,c++" --with-newlib --disable-shared --with-gnu-as --with-gnu-ld --with-float=soft --disable-werror
make $PARALLEL
make install
cd ..
#rm -rf build/* $GCC

aria2c -s 20 ftp://ftp.gnu.org/gnu/gdb/$GDB.tar.bz2
tar xfvj $GDB.tar.bz2
cd build
../$GDB/configure --target=$TARGET --prefix=$PREFIX --enable-interwork --enable-multilib --disable-werror
make $PARALLEL
make install
cd ..
#rm -rf build $GDB $GDB.tar.bz2

sudo ln -s $PREFIX/bin/arm-eabi* /usr/bin

cd ..
mkdir Sam_I_Am
cd Sam_I_Am
aria2c -s 20 http://claymore.engineer.gvsu.edu/%7Esteriana/Software/Sam_I_Am-0.3.tar.gz
tar xfvz Sam_I_Am-0.3.tar.gz
cd Sam_I_Am-0.3
python setup.py install
cd ..
echo "
open /dev/ttyUSB0
version
set readallow 0 0x300000
set ramwriteallow 0x202000 57344
set flashwriteallow 0x100000 0x40000
" >> .samiamrc
cp .samiamrc ~/

rm /usr/bin/Sam_I_Am
echo "
#!/bin/sh
python /usr/local/lib/python2.6/dist-packages/Sam_I_Am/samiam.py $*
" >> /usr/bin/Sam_I_Am
chmod a=rx /usr/bin/Sam_I_Am

sudo modprobe usbserial vendor=0x3eb product=0x6124
#this fails on kernel 2.6.28-11-generic, upgrade to latest prerelease


#install sam7utils
cd ..
aria2c -s 20 http://oss.tekno.us/sam7utils/sam7utils-0.2.1.tar.gz
tar xfvz sam7utils-0.2.1.tar.gz
cd sam7utils-0.2.1
./configure
make
make install
ln -s /dev/ttyUSB0 /dev/at91_0


