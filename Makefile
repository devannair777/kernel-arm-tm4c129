#******************************************************************************
#
# GNU GPLv2 License
#
#******************************************************************************

LDNAME=tm4c129.ld
SRCDIR=src
ODIR=obj
LIBDIR=lib
LISTDIR=listing
TARGETDIR=bin
BIN=${COMPILER}/${TARGETDIR}/main.axf

# The base directory for TivaWare.

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

DEPS=${SRC_OBJS} 

ifdef LIB
DEPS+=${LIB_OBJS}
endif

all:clean ${COMPILER} ${BIN}
${BIN}: ${DEPS}

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
	@mkdir -p ${COMPILER}/${TARGETDIR}
	@mkdir -p ${COMPILER}/${LISTDIR}

# Flash the binary
flash: ${BIN}
	lm4flash -v ${^:.axf=.bin}

# Show Assembly

assembly:
	@${PREFIX}-objdump -d ${BIN} > ${COMPILER}/${LISTDIR}/disassembly 
	@${PREFIX}-objdump -s ${BIN} > ${COMPILER}/${LISTDIR}/entire 
	@${PREFIX}-objdump -h ${BIN} > ${COMPILER}/${LISTDIR}/sectors 
	@echo Check ${COMPILER}/${LISTDIR} for files ...


#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
