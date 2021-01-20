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
