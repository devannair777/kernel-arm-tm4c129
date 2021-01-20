#******************************************************************************
#
# GNU GPLv2 License
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

IPATH=.

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
	@rm *.o
	@rm *.d
	@rm *.axf
	@rm *.bin

#
# Show Assembly
#

main.axf: main.o startup_tm4c129.o

assembly:
	@echo "Complete Sector View";
	@${PREFIX}-objdump -s main.axf
	@echo "Disassembly";
	@${PREFIX}-objdump -d main.axf
	
test:
	@echo ${LIBGCC_DIR}	
	@echo ${LIBC_DIR}
	@echo ${LIBC}	

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
