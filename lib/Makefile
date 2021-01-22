ODIR=obj
LIBS=$(shell find . -name '*.c')
LIBFILES=$(notdir ${LIBS})
LIB_OBJS=$(patsubst %.c,${ODIR}/%.o,$(LIBFILES))
IDIR=../inc
#
# The flags passed to the compiler.
#
CFLAGS=-mthumb             \
       ${CPU}              \
       ${FPU}              \
       -ffunction-sections \
       -fdata-sections     \
       -MD                 \
       -std=c99            \
       -Wall               \
       -pedantic           \
       -DPART_${PART}      \
       -c


all: ${LIB_OBJS}
#	echo "At all" $^

clean: 
	@rm  ${ODIR}/* 

${ODIR}/%.o:
	@echo  " CC	$(shell find . -name ${notdir ${@:.o=.c}}) ";
	@arm-none-eabi-gcc ${CFLAGS} -o $@ -I${IDIR} $(shell find . -name ${notdir ${@:.o=.c}})
	@rm ${ODIR}/*.d