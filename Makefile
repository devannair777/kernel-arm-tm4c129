#******************************************************************************
#
# GNU GPLv2 License
#
#******************************************************************************

LDNAME=tm4c129.ld
SRCDIR=src
ODIR=obj
LIBDIR=lib
LIB_AR=ar/*.a
LISTDIR=listing
TARGETDIR=bin
BIN=$(COMPILER)/$(TARGETDIR)/main.axf

# The base directory for TivaWare.

ROOT=.

#
# Include the common make definitions.
#
include makedefs
#
# Where to find header files that do not live in the source directory.
#
QPC:=qpc
QP_PORT_DIR=$(QPC)/ports/ucos-ii
IPATH=inc:\
		$(QPC)/include:\
		$(QPC)/src:\
		$(QP_PORT_DIR):\
		$(QPC)/3rd_party/ucos-ii/Source:\
		$(QPC)/3rd_party/ucos-ii/Ports/ARM-Cortex-M/ARMv7-M/GNU:\
		$(QPC)/3rd_party/CMSIS/Include:\
		$(QPC)/3rd_party/ek-tm4c123gxl
#
# The default rule.
#


${BIN}: ${DEPS}

#all: ${COMPILER} ${DEPS}


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
#
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


##### Defns for RTEF Integration ##### 

VPATH = \
	$(SRCDIR) \
	$(SRCDIR)/bootloader \
	$(SRCDIR)/imu \
	$(SRCDIR)/rom_modules \
	$(SRCDIR)/test \
	$(QPC)/src/qf \
	$(QPC)/src/qs \
	$(QP_PORT_DIR) \
	$(QPC)/3rd_party/ucos-ii/Source \
	$(QPC)/3rd_party/ucos-ii/Ports/ARM-Cortex-M/ARMv7-M \
	$(QPC)/3rd_party/ucos-ii/Ports/ARM-Cortex-M/ARMv7-M/GNU \
	
QP_SRCS := \
	qep_hsm.c \
	qep_msm.c \
	qf_act.c \
	qf_defer.c \
	qf_dyn.c \
	qf_ps.c \
	qf_qact.c \
	qf_qeq.c \
	qf_qmact.c \
	qf_time.c \
	qf_port.c

RTOS_SRCS := \
	os_core.c \
	os_flag.c \
	os_mbox.c \
	os_mem.c \
	os_mutex.c \
	os_q.c \
	os_sem.c \
	os_task.c \
	os_time.c \
	os_tmr.c \
	os_cpu_c.c\
	os_dbg.c 

QS_SRCS := \
	qs.c \
	qs_rx.c \
	qs_fp.c

ASM_SRCS := \
	os_cpu_a.s
	
Q_SRCS += $(QP_SRCS)
Q_SRCS += $(RTOS_SRCS)
Q_SRCS += $(QS_SRCS)

QSRCS_OBJS:=$(patsubst %.c,%.o,$(Q_SRCS))
QSRCS_OBJS_EXT:=$(addprefix $(COMPILER)/$(ODIR)/,${QSRCS_OBJS})

ASM_OBJS:=$(patsubst %.s,%.o,$(ASM_SRCS))
ASM_OBJS_EXT:=$(addprefix $(COMPILER)/$(ODIR)/,${ASM_OBJS})

SRCS=$(notdir $(shell find $(SRCDIR) -name '*.c'))
SRC_OBJS=$(patsubst %.c,%.o,$(SRCS))
SRC_OBJS_EXT:=$(addprefix $(COMPILER)/$(ODIR)/,${SRC_OBJS})

echotest:
	@echo ${ASM_OBJS_EXT}

qpc: ${COMPILER} ${QSRCS_OBJS_EXT} 

srcs: ${COMPILER} ${SRC_OBJS_EXT}

asms: ${COMPILER} ${ASM_OBJS_EXT}

all: ${COMPILER} ${BIN}

${BIN}: ${ASM_OBJS_EXT} ${SRC_OBJS_EXT} ${QSRCS_OBJS_EXT}
	@${CC} ${CFLAGS} -D${COMPILER} $(QPC)/include/qstamp.c -o $(COMPILER)/$(ODIR)/qstamp.o
	${LD} ${LDFLAGS}  $^ $(COMPILER)/$(ODIR)/qstamp.o ${LIBDIR}/${LIB_AR} -T ${LDNAME}  -o $@  
	@${OBJCOPY} -O binary $@ ${@:.axf=.bin}	

$(COMPILER)/$(ODIR)/%.o : %.c
	@echo "CC	$<"
	@${CC} ${CFLAGS} -D${COMPILER} $< -o $@
	@rm ${COMPILER}/${ODIR}/*.d

$(COMPILER)/$(ODIR)/%.o : %.s
	@echo "AS	$<"
	@${AS} ${AFLAGS} $< -o $@
	@rm ./-Iinc





