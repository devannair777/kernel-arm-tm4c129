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
BIN=${COMPILER}/main.axf

#
# The base directory for TivaWare.
#
ROOT=.

#
# Include the common make definitions.
#
include makedefs

#
# Where to find header files that do not live in the source directory.
#
IPATH=inc

#
# The default rule, which causes the blinky example to be built.
#
all: ${COMPILER}
all: ${BIN}

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

#
# The rule to create the target & object directories.
#
${COMPILER}:
	@mkdir -p ${COMPILER}
	@mkdir -p ${COMPILER}/${ODIR}


#
# Rules for building the kernel
#

${BIN}: ${OBJS}
SCATTERgcc_main=main.ld
ENTRY_main=ResetISR

# Flash the binary
flash:
	lm4flash -v gcc/main.bin

# Show Assembly
assembly:
	${PREFIX}-objdump -d ${BIN}

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
