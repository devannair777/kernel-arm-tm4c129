###Setting up a gcc environment for kernel development of 
###TM4C1294NCPDT (NON-CMSIS)
###Install gcc-arm-none-eabi compiler
sudo apt install gcc-arm-none-eabi

###Install lm4f flash tools
git clone https://github.com/utzig/lm4tools.git
sudo apt-get install libcap-dev
###Install pkg-config if it is not already present
###Change the Makefile build for lm4flash to have appropriate cflags for
###libusb-dev1.0 header files
cd lm4tools/lm4flash
make
##The make output
#cc -Wall -I/usr/include/libusb-1.0  lm4flash.c -L/usr/lib/x86_64-linux-gnu -lusb-1.0  -o lm4flash
## pkg-config --cflags libusb-1.0
#-I/usr/include/libusb-1.0
## pkg-config --libs libusb-1.0
#-L/usr/lib/x86_64-linux-gnu -lusb-1.0
sudo cp lm4tools/lm4flash/lm4flash /usr/bin/

###Remove the lm4tools git repository
rm -rf lm4tools

###Optionally install cross-compiler for ARM-Linux environment
###sudo apt-get install gcc-arm-linux-gnueabi g++-arm-linux-gnueabi
###To view the disassembly of the compiled and linked (.axf) code
###arm-none-eabi-objdump -d gcc/main.axf
###To view the symbol table of the compiled and linked (.axf) code
###arm-none-eabi-objdump -t gcc/main.axf
###To flash the compiled binaries into the dev-board
###lm4flash -v gcc/blinky.bin
###For openocd debugging with gdb
###Download and install openocd, GNU-gdb
###Use the startup script for the EK-TM4C129x board
###openocd -f openocd/tcl/board/ti_ek-tm4c1294xl.cfg

##Use Serial Communication(Doesnt work with wsl), install cu with
#apt install cu
##Check the device ID of the ICDI with dmesg as
#dmesg | egrep --color 'serial|ttyS'
##OR
#ls /dev/tty*
##Call-up to the serial device with cu as
## cu -l /dev/<device-id> -s <baud-rate>
#E.g. cu -l /dev/ttyS0 -s 9600  
##To exit enter tilde dot (~.).
