#******************************************************************************
#
# GNU GPLv2 License
#
#******************************************************************************


BIN=${COMPILER}/main.axf
LDNAME=tm4c129.ld
LISTDIR=Listing

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
# The default rule.
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
	@mkdir -p ${COMPILER}/${LISTDIR}


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
	${PREFIX}-objdump -s ${BIN} 
	${PREFIX}-objdump -h ${BIN}


#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
