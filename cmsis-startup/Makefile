#******************************************************************************
#
# Makefile - Rules for building the blinky example.
#
# Copyright (c) 2013-2014 Texas Instruments Incorporated.  All rights reserved.
# Software License Agreement
# 
# Texas Instruments (TI) is supplying this software for use solely and
# exclusively on TI's microcontroller products. The software is owned by
# TI and/or its suppliers, and is protected under applicable copyright
# laws. You may not combine this software with "viral" open-source
# software in order to form a larger program.
# 
# THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
# NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
# NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
# CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
# DAMAGES, FOR ANY REASON WHATSOEVER.
# 
# This is part of revision 2.1.0.12573 of the EK-TM4C1294XL Firmware Package.
#
#******************************************************************************

#
# Defines the part type that this project uses.
#
PART=TM4C1294NCPDT
#
# The base directory for TivaWare.
#
ROOT=.

IPATH=../inc

#
# Include the common make definitions.
#
include makedefs


#
# The default rule, which causes the blinky example to be built.
#
#build: main.o
#build: startup_tm4c129.o
#build: main.axf

SCATTERgcc_main=tm4c129.ld


#
# The rule to clean out all the build products.
#

clean:
	@rm *.d
	@rm *.o
	@rm *.axf
	@rm *.bin

#
# Show Assembly
#

assembly: startup_tm4c129.o
assembly: main.axf
main.axf: main.o 
assembly:
	${PREFIX}-objdump -s main.axf
	${PREFIX}-objdump -t main.axf
	@rm *.d
	@rm *.o
	@rm *.axf
	@rm *.bin



test:
	@echo ${LIBGCC} 
	@echo ${LIBC} 
	@echo ${LIBM} 
#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
