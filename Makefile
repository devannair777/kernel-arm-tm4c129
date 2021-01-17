#******************************************************************************
#
# GNU GPLv2 License
#
#******************************************************************************

#
# Defines the part type that this project uses.
#
PART=TM4C1294NCPDT
BIN=${COMPILER}/main.axf
LDNAME=main.ld

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
