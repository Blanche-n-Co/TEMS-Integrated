#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TEMS-Integrated.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TEMS-Integrated.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=fcts/ADC/My_ADC.c fcts/Clock/My_CLOCK.c ARP.c Announce.c DNS.c ENC28J60.c Helpers.c ICMP.c IP.c PICDelay.c StackTsk.c TCP.c TCPPerformanceTest.c Tick.c UDP.c UDPPerformanceTest.c fcts/GSM/My_GSM.c fcts/i2c/i2c2ack.c fcts/i2c/i2c2clos.c fcts/i2c/i2c2dtrd.c fcts/i2c/i2c2eeap.c fcts/i2c/i2c2eebw.c fcts/i2c/i2c2eecr.c fcts/i2c/i2c2eepw.c fcts/i2c/i2c2eerr.c fcts/i2c/i2c2eesr.c fcts/i2c/i2c2gets.c fcts/i2c/i2c2idle.c fcts/i2c/i2c2nack.c fcts/i2c/i2c2open.c fcts/i2c/i2c2puts.c fcts/i2c/i2c2read.c fcts/i2c/i2c2rstr.c fcts/i2c/i2c2stop.c fcts/i2c/i2c2strt.c fcts/i2c/i2c2writ.c fcts/LCD/busyxlcd.c fcts/LCD/openxlcd.c fcts/LCD/putrxlcd.c fcts/LCD/putsxlcd.c fcts/LCD/readaddr.c fcts/LCD/readdata.c fcts/LCD/setcgram.c fcts/LCD/setddram.c fcts/LCD/wcmdxlcd.c fcts/LCD/writdata.c fcts/LCD/writeOnLCD.c fcts/LCD/delaysXLCD.c fcts/OS/hardware.c fcts/OS/My_TIMERS.c TIOS.c fcts/Temperature/1wire.c fcts/Temperature/ftoa.c fcts/Temperature/My_TEMP.c fcts/USART/My_USART.c Main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/fcts/ADC/My_ADC.o ${OBJECTDIR}/fcts/Clock/My_CLOCK.o ${OBJECTDIR}/ARP.o ${OBJECTDIR}/Announce.o ${OBJECTDIR}/DNS.o ${OBJECTDIR}/ENC28J60.o ${OBJECTDIR}/Helpers.o ${OBJECTDIR}/ICMP.o ${OBJECTDIR}/IP.o ${OBJECTDIR}/PICDelay.o ${OBJECTDIR}/StackTsk.o ${OBJECTDIR}/TCP.o ${OBJECTDIR}/TCPPerformanceTest.o ${OBJECTDIR}/Tick.o ${OBJECTDIR}/UDP.o ${OBJECTDIR}/UDPPerformanceTest.o ${OBJECTDIR}/fcts/GSM/My_GSM.o ${OBJECTDIR}/fcts/i2c/i2c2ack.o ${OBJECTDIR}/fcts/i2c/i2c2clos.o ${OBJECTDIR}/fcts/i2c/i2c2dtrd.o ${OBJECTDIR}/fcts/i2c/i2c2eeap.o ${OBJECTDIR}/fcts/i2c/i2c2eebw.o ${OBJECTDIR}/fcts/i2c/i2c2eecr.o ${OBJECTDIR}/fcts/i2c/i2c2eepw.o ${OBJECTDIR}/fcts/i2c/i2c2eerr.o ${OBJECTDIR}/fcts/i2c/i2c2eesr.o ${OBJECTDIR}/fcts/i2c/i2c2gets.o ${OBJECTDIR}/fcts/i2c/i2c2idle.o ${OBJECTDIR}/fcts/i2c/i2c2nack.o ${OBJECTDIR}/fcts/i2c/i2c2open.o ${OBJECTDIR}/fcts/i2c/i2c2puts.o ${OBJECTDIR}/fcts/i2c/i2c2read.o ${OBJECTDIR}/fcts/i2c/i2c2rstr.o ${OBJECTDIR}/fcts/i2c/i2c2stop.o ${OBJECTDIR}/fcts/i2c/i2c2strt.o ${OBJECTDIR}/fcts/i2c/i2c2writ.o ${OBJECTDIR}/fcts/LCD/busyxlcd.o ${OBJECTDIR}/fcts/LCD/openxlcd.o ${OBJECTDIR}/fcts/LCD/putrxlcd.o ${OBJECTDIR}/fcts/LCD/putsxlcd.o ${OBJECTDIR}/fcts/LCD/readaddr.o ${OBJECTDIR}/fcts/LCD/readdata.o ${OBJECTDIR}/fcts/LCD/setcgram.o ${OBJECTDIR}/fcts/LCD/setddram.o ${OBJECTDIR}/fcts/LCD/wcmdxlcd.o ${OBJECTDIR}/fcts/LCD/writdata.o ${OBJECTDIR}/fcts/LCD/writeOnLCD.o ${OBJECTDIR}/fcts/LCD/delaysXLCD.o ${OBJECTDIR}/fcts/OS/hardware.o ${OBJECTDIR}/fcts/OS/My_TIMERS.o ${OBJECTDIR}/TIOS.o ${OBJECTDIR}/fcts/Temperature/1wire.o ${OBJECTDIR}/fcts/Temperature/ftoa.o ${OBJECTDIR}/fcts/Temperature/My_TEMP.o ${OBJECTDIR}/fcts/USART/My_USART.o ${OBJECTDIR}/Main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/fcts/ADC/My_ADC.o.d ${OBJECTDIR}/fcts/Clock/My_CLOCK.o.d ${OBJECTDIR}/ARP.o.d ${OBJECTDIR}/Announce.o.d ${OBJECTDIR}/DNS.o.d ${OBJECTDIR}/ENC28J60.o.d ${OBJECTDIR}/Helpers.o.d ${OBJECTDIR}/ICMP.o.d ${OBJECTDIR}/IP.o.d ${OBJECTDIR}/PICDelay.o.d ${OBJECTDIR}/StackTsk.o.d ${OBJECTDIR}/TCP.o.d ${OBJECTDIR}/TCPPerformanceTest.o.d ${OBJECTDIR}/Tick.o.d ${OBJECTDIR}/UDP.o.d ${OBJECTDIR}/UDPPerformanceTest.o.d ${OBJECTDIR}/fcts/GSM/My_GSM.o.d ${OBJECTDIR}/fcts/i2c/i2c2ack.o.d ${OBJECTDIR}/fcts/i2c/i2c2clos.o.d ${OBJECTDIR}/fcts/i2c/i2c2dtrd.o.d ${OBJECTDIR}/fcts/i2c/i2c2eeap.o.d ${OBJECTDIR}/fcts/i2c/i2c2eebw.o.d ${OBJECTDIR}/fcts/i2c/i2c2eecr.o.d ${OBJECTDIR}/fcts/i2c/i2c2eepw.o.d ${OBJECTDIR}/fcts/i2c/i2c2eerr.o.d ${OBJECTDIR}/fcts/i2c/i2c2eesr.o.d ${OBJECTDIR}/fcts/i2c/i2c2gets.o.d ${OBJECTDIR}/fcts/i2c/i2c2idle.o.d ${OBJECTDIR}/fcts/i2c/i2c2nack.o.d ${OBJECTDIR}/fcts/i2c/i2c2open.o.d ${OBJECTDIR}/fcts/i2c/i2c2puts.o.d ${OBJECTDIR}/fcts/i2c/i2c2read.o.d ${OBJECTDIR}/fcts/i2c/i2c2rstr.o.d ${OBJECTDIR}/fcts/i2c/i2c2stop.o.d ${OBJECTDIR}/fcts/i2c/i2c2strt.o.d ${OBJECTDIR}/fcts/i2c/i2c2writ.o.d ${OBJECTDIR}/fcts/LCD/busyxlcd.o.d ${OBJECTDIR}/fcts/LCD/openxlcd.o.d ${OBJECTDIR}/fcts/LCD/putrxlcd.o.d ${OBJECTDIR}/fcts/LCD/putsxlcd.o.d ${OBJECTDIR}/fcts/LCD/readaddr.o.d ${OBJECTDIR}/fcts/LCD/readdata.o.d ${OBJECTDIR}/fcts/LCD/setcgram.o.d ${OBJECTDIR}/fcts/LCD/setddram.o.d ${OBJECTDIR}/fcts/LCD/wcmdxlcd.o.d ${OBJECTDIR}/fcts/LCD/writdata.o.d ${OBJECTDIR}/fcts/LCD/writeOnLCD.o.d ${OBJECTDIR}/fcts/LCD/delaysXLCD.o.d ${OBJECTDIR}/fcts/OS/hardware.o.d ${OBJECTDIR}/fcts/OS/My_TIMERS.o.d ${OBJECTDIR}/TIOS.o.d ${OBJECTDIR}/fcts/Temperature/1wire.o.d ${OBJECTDIR}/fcts/Temperature/ftoa.o.d ${OBJECTDIR}/fcts/Temperature/My_TEMP.o.d ${OBJECTDIR}/fcts/USART/My_USART.o.d ${OBJECTDIR}/Main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/fcts/ADC/My_ADC.o ${OBJECTDIR}/fcts/Clock/My_CLOCK.o ${OBJECTDIR}/ARP.o ${OBJECTDIR}/Announce.o ${OBJECTDIR}/DNS.o ${OBJECTDIR}/ENC28J60.o ${OBJECTDIR}/Helpers.o ${OBJECTDIR}/ICMP.o ${OBJECTDIR}/IP.o ${OBJECTDIR}/PICDelay.o ${OBJECTDIR}/StackTsk.o ${OBJECTDIR}/TCP.o ${OBJECTDIR}/TCPPerformanceTest.o ${OBJECTDIR}/Tick.o ${OBJECTDIR}/UDP.o ${OBJECTDIR}/UDPPerformanceTest.o ${OBJECTDIR}/fcts/GSM/My_GSM.o ${OBJECTDIR}/fcts/i2c/i2c2ack.o ${OBJECTDIR}/fcts/i2c/i2c2clos.o ${OBJECTDIR}/fcts/i2c/i2c2dtrd.o ${OBJECTDIR}/fcts/i2c/i2c2eeap.o ${OBJECTDIR}/fcts/i2c/i2c2eebw.o ${OBJECTDIR}/fcts/i2c/i2c2eecr.o ${OBJECTDIR}/fcts/i2c/i2c2eepw.o ${OBJECTDIR}/fcts/i2c/i2c2eerr.o ${OBJECTDIR}/fcts/i2c/i2c2eesr.o ${OBJECTDIR}/fcts/i2c/i2c2gets.o ${OBJECTDIR}/fcts/i2c/i2c2idle.o ${OBJECTDIR}/fcts/i2c/i2c2nack.o ${OBJECTDIR}/fcts/i2c/i2c2open.o ${OBJECTDIR}/fcts/i2c/i2c2puts.o ${OBJECTDIR}/fcts/i2c/i2c2read.o ${OBJECTDIR}/fcts/i2c/i2c2rstr.o ${OBJECTDIR}/fcts/i2c/i2c2stop.o ${OBJECTDIR}/fcts/i2c/i2c2strt.o ${OBJECTDIR}/fcts/i2c/i2c2writ.o ${OBJECTDIR}/fcts/LCD/busyxlcd.o ${OBJECTDIR}/fcts/LCD/openxlcd.o ${OBJECTDIR}/fcts/LCD/putrxlcd.o ${OBJECTDIR}/fcts/LCD/putsxlcd.o ${OBJECTDIR}/fcts/LCD/readaddr.o ${OBJECTDIR}/fcts/LCD/readdata.o ${OBJECTDIR}/fcts/LCD/setcgram.o ${OBJECTDIR}/fcts/LCD/setddram.o ${OBJECTDIR}/fcts/LCD/wcmdxlcd.o ${OBJECTDIR}/fcts/LCD/writdata.o ${OBJECTDIR}/fcts/LCD/writeOnLCD.o ${OBJECTDIR}/fcts/LCD/delaysXLCD.o ${OBJECTDIR}/fcts/OS/hardware.o ${OBJECTDIR}/fcts/OS/My_TIMERS.o ${OBJECTDIR}/TIOS.o ${OBJECTDIR}/fcts/Temperature/1wire.o ${OBJECTDIR}/fcts/Temperature/ftoa.o ${OBJECTDIR}/fcts/Temperature/My_TEMP.o ${OBJECTDIR}/fcts/USART/My_USART.o ${OBJECTDIR}/Main.o

# Source Files
SOURCEFILES=fcts/ADC/My_ADC.c fcts/Clock/My_CLOCK.c ARP.c Announce.c DNS.c ENC28J60.c Helpers.c ICMP.c IP.c PICDelay.c StackTsk.c TCP.c TCPPerformanceTest.c Tick.c UDP.c UDPPerformanceTest.c fcts/GSM/My_GSM.c fcts/i2c/i2c2ack.c fcts/i2c/i2c2clos.c fcts/i2c/i2c2dtrd.c fcts/i2c/i2c2eeap.c fcts/i2c/i2c2eebw.c fcts/i2c/i2c2eecr.c fcts/i2c/i2c2eepw.c fcts/i2c/i2c2eerr.c fcts/i2c/i2c2eesr.c fcts/i2c/i2c2gets.c fcts/i2c/i2c2idle.c fcts/i2c/i2c2nack.c fcts/i2c/i2c2open.c fcts/i2c/i2c2puts.c fcts/i2c/i2c2read.c fcts/i2c/i2c2rstr.c fcts/i2c/i2c2stop.c fcts/i2c/i2c2strt.c fcts/i2c/i2c2writ.c fcts/LCD/busyxlcd.c fcts/LCD/openxlcd.c fcts/LCD/putrxlcd.c fcts/LCD/putsxlcd.c fcts/LCD/readaddr.c fcts/LCD/readdata.c fcts/LCD/setcgram.c fcts/LCD/setddram.c fcts/LCD/wcmdxlcd.c fcts/LCD/writdata.c fcts/LCD/writeOnLCD.c fcts/LCD/delaysXLCD.c fcts/OS/hardware.c fcts/OS/My_TIMERS.c TIOS.c fcts/Temperature/1wire.c fcts/Temperature/ftoa.c fcts/Temperature/My_TEMP.c fcts/USART/My_USART.c Main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/TEMS-Integrated.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F46K22
MP_PROCESSOR_OPTION_LD=18f46k22
MP_LINKER_DEBUG_OPTION=  -u_DEBUGSTACK
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/fcts/ADC/My_ADC.o: fcts/ADC/My_ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/ADC 
	@${RM} ${OBJECTDIR}/fcts/ADC/My_ADC.o.d 
	@${RM} ${OBJECTDIR}/fcts/ADC/My_ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/ADC/My_ADC.o   fcts/ADC/My_ADC.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/ADC/My_ADC.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/ADC/My_ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/Clock/My_CLOCK.o: fcts/Clock/My_CLOCK.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/Clock 
	@${RM} ${OBJECTDIR}/fcts/Clock/My_CLOCK.o.d 
	@${RM} ${OBJECTDIR}/fcts/Clock/My_CLOCK.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/Clock/My_CLOCK.o   fcts/Clock/My_CLOCK.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/Clock/My_CLOCK.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/Clock/My_CLOCK.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ARP.o: ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ARP.o.d 
	@${RM} ${OBJECTDIR}/ARP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/ARP.o   ARP.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ARP.o 
	@${FIXDEPS} "${OBJECTDIR}/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Announce.o: Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Announce.o.d 
	@${RM} ${OBJECTDIR}/Announce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Announce.o   Announce.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Announce.o 
	@${FIXDEPS} "${OBJECTDIR}/Announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/DNS.o: DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/DNS.o.d 
	@${RM} ${OBJECTDIR}/DNS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/DNS.o   DNS.c 
	@${DEP_GEN} -d ${OBJECTDIR}/DNS.o 
	@${FIXDEPS} "${OBJECTDIR}/DNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ENC28J60.o: ENC28J60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ENC28J60.o.d 
	@${RM} ${OBJECTDIR}/ENC28J60.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/ENC28J60.o   ENC28J60.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ENC28J60.o 
	@${FIXDEPS} "${OBJECTDIR}/ENC28J60.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Helpers.o: Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Helpers.o.d 
	@${RM} ${OBJECTDIR}/Helpers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Helpers.o   Helpers.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ICMP.o: ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ICMP.o.d 
	@${RM} ${OBJECTDIR}/ICMP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/ICMP.o   ICMP.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ICMP.o 
	@${FIXDEPS} "${OBJECTDIR}/ICMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/IP.o: IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/IP.o.d 
	@${RM} ${OBJECTDIR}/IP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/IP.o   IP.c 
	@${DEP_GEN} -d ${OBJECTDIR}/IP.o 
	@${FIXDEPS} "${OBJECTDIR}/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PICDelay.o: PICDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/PICDelay.o.d 
	@${RM} ${OBJECTDIR}/PICDelay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PICDelay.o   PICDelay.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PICDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/PICDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/StackTsk.o: StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/StackTsk.o.d 
	@${RM} ${OBJECTDIR}/StackTsk.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/StackTsk.o   StackTsk.c 
	@${DEP_GEN} -d ${OBJECTDIR}/StackTsk.o 
	@${FIXDEPS} "${OBJECTDIR}/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/TCP.o: TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/TCP.o.d 
	@${RM} ${OBJECTDIR}/TCP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/TCP.o   TCP.c 
	@${DEP_GEN} -d ${OBJECTDIR}/TCP.o 
	@${FIXDEPS} "${OBJECTDIR}/TCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/TCPPerformanceTest.o: TCPPerformanceTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/TCPPerformanceTest.o.d 
	@${RM} ${OBJECTDIR}/TCPPerformanceTest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/TCPPerformanceTest.o   TCPPerformanceTest.c 
	@${DEP_GEN} -d ${OBJECTDIR}/TCPPerformanceTest.o 
	@${FIXDEPS} "${OBJECTDIR}/TCPPerformanceTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Tick.o: Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Tick.o.d 
	@${RM} ${OBJECTDIR}/Tick.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Tick.o   Tick.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UDP.o: UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/UDP.o.d 
	@${RM} ${OBJECTDIR}/UDP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UDP.o   UDP.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UDP.o 
	@${FIXDEPS} "${OBJECTDIR}/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UDPPerformanceTest.o: UDPPerformanceTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/UDPPerformanceTest.o.d 
	@${RM} ${OBJECTDIR}/UDPPerformanceTest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UDPPerformanceTest.o   UDPPerformanceTest.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UDPPerformanceTest.o 
	@${FIXDEPS} "${OBJECTDIR}/UDPPerformanceTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/GSM/My_GSM.o: fcts/GSM/My_GSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/GSM 
	@${RM} ${OBJECTDIR}/fcts/GSM/My_GSM.o.d 
	@${RM} ${OBJECTDIR}/fcts/GSM/My_GSM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/GSM/My_GSM.o   fcts/GSM/My_GSM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/GSM/My_GSM.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/GSM/My_GSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2ack.o: fcts/i2c/i2c2ack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2ack.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2ack.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2ack.o   fcts/i2c/i2c2ack.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2ack.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2ack.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2clos.o: fcts/i2c/i2c2clos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2clos.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2clos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2clos.o   fcts/i2c/i2c2clos.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2clos.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2clos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2dtrd.o: fcts/i2c/i2c2dtrd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2dtrd.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2dtrd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2dtrd.o   fcts/i2c/i2c2dtrd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2dtrd.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2dtrd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2eeap.o: fcts/i2c/i2c2eeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eeap.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eeap.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2eeap.o   fcts/i2c/i2c2eeap.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2eeap.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2eeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2eebw.o: fcts/i2c/i2c2eebw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eebw.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eebw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2eebw.o   fcts/i2c/i2c2eebw.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2eebw.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2eebw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2eecr.o: fcts/i2c/i2c2eecr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eecr.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eecr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2eecr.o   fcts/i2c/i2c2eecr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2eecr.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2eecr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2eepw.o: fcts/i2c/i2c2eepw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eepw.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eepw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2eepw.o   fcts/i2c/i2c2eepw.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2eepw.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2eepw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2eerr.o: fcts/i2c/i2c2eerr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eerr.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eerr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2eerr.o   fcts/i2c/i2c2eerr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2eerr.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2eerr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2eesr.o: fcts/i2c/i2c2eesr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eesr.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eesr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2eesr.o   fcts/i2c/i2c2eesr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2eesr.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2eesr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2gets.o: fcts/i2c/i2c2gets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2gets.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2gets.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2gets.o   fcts/i2c/i2c2gets.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2gets.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2gets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2idle.o: fcts/i2c/i2c2idle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2idle.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2idle.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2idle.o   fcts/i2c/i2c2idle.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2idle.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2idle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2nack.o: fcts/i2c/i2c2nack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2nack.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2nack.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2nack.o   fcts/i2c/i2c2nack.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2nack.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2nack.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2open.o: fcts/i2c/i2c2open.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2open.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2open.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2open.o   fcts/i2c/i2c2open.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2open.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2open.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2puts.o: fcts/i2c/i2c2puts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2puts.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2puts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2puts.o   fcts/i2c/i2c2puts.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2puts.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2puts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2read.o: fcts/i2c/i2c2read.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2read.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2read.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2read.o   fcts/i2c/i2c2read.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2read.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2read.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2rstr.o: fcts/i2c/i2c2rstr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2rstr.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2rstr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2rstr.o   fcts/i2c/i2c2rstr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2rstr.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2rstr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2stop.o: fcts/i2c/i2c2stop.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2stop.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2stop.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2stop.o   fcts/i2c/i2c2stop.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2stop.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2stop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2strt.o: fcts/i2c/i2c2strt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2strt.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2strt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2strt.o   fcts/i2c/i2c2strt.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2strt.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2strt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2writ.o: fcts/i2c/i2c2writ.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2writ.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2writ.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2writ.o   fcts/i2c/i2c2writ.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2writ.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2writ.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/busyxlcd.o: fcts/LCD/busyxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/busyxlcd.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/busyxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/busyxlcd.o   fcts/LCD/busyxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/busyxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/busyxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/openxlcd.o: fcts/LCD/openxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/openxlcd.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/openxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/openxlcd.o   fcts/LCD/openxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/openxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/openxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/putrxlcd.o: fcts/LCD/putrxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/putrxlcd.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/putrxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/putrxlcd.o   fcts/LCD/putrxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/putrxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/putrxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/putsxlcd.o: fcts/LCD/putsxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/putsxlcd.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/putsxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/putsxlcd.o   fcts/LCD/putsxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/putsxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/putsxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/readaddr.o: fcts/LCD/readaddr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/readaddr.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/readaddr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/readaddr.o   fcts/LCD/readaddr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/readaddr.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/readaddr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/readdata.o: fcts/LCD/readdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/readdata.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/readdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/readdata.o   fcts/LCD/readdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/readdata.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/readdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/setcgram.o: fcts/LCD/setcgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/setcgram.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/setcgram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/setcgram.o   fcts/LCD/setcgram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/setcgram.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/setcgram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/setddram.o: fcts/LCD/setddram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/setddram.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/setddram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/setddram.o   fcts/LCD/setddram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/setddram.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/setddram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/wcmdxlcd.o: fcts/LCD/wcmdxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/wcmdxlcd.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/wcmdxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/wcmdxlcd.o   fcts/LCD/wcmdxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/wcmdxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/wcmdxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/writdata.o: fcts/LCD/writdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/writdata.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/writdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/writdata.o   fcts/LCD/writdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/writdata.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/writdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/writeOnLCD.o: fcts/LCD/writeOnLCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/writeOnLCD.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/writeOnLCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/writeOnLCD.o   fcts/LCD/writeOnLCD.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/writeOnLCD.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/writeOnLCD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/delaysXLCD.o: fcts/LCD/delaysXLCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/delaysXLCD.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/delaysXLCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/delaysXLCD.o   fcts/LCD/delaysXLCD.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/delaysXLCD.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/delaysXLCD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/OS/hardware.o: fcts/OS/hardware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/OS 
	@${RM} ${OBJECTDIR}/fcts/OS/hardware.o.d 
	@${RM} ${OBJECTDIR}/fcts/OS/hardware.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/OS/hardware.o   fcts/OS/hardware.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/OS/hardware.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/OS/hardware.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/OS/My_TIMERS.o: fcts/OS/My_TIMERS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/OS 
	@${RM} ${OBJECTDIR}/fcts/OS/My_TIMERS.o.d 
	@${RM} ${OBJECTDIR}/fcts/OS/My_TIMERS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/OS/My_TIMERS.o   fcts/OS/My_TIMERS.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/OS/My_TIMERS.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/OS/My_TIMERS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/TIOS.o: TIOS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/TIOS.o.d 
	@${RM} ${OBJECTDIR}/TIOS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/TIOS.o   TIOS.c 
	@${DEP_GEN} -d ${OBJECTDIR}/TIOS.o 
	@${FIXDEPS} "${OBJECTDIR}/TIOS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/Temperature/1wire.o: fcts/Temperature/1wire.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/Temperature 
	@${RM} ${OBJECTDIR}/fcts/Temperature/1wire.o.d 
	@${RM} ${OBJECTDIR}/fcts/Temperature/1wire.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/Temperature/1wire.o   fcts/Temperature/1wire.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/Temperature/1wire.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/Temperature/1wire.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/Temperature/ftoa.o: fcts/Temperature/ftoa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/Temperature 
	@${RM} ${OBJECTDIR}/fcts/Temperature/ftoa.o.d 
	@${RM} ${OBJECTDIR}/fcts/Temperature/ftoa.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/Temperature/ftoa.o   fcts/Temperature/ftoa.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/Temperature/ftoa.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/Temperature/ftoa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/Temperature/My_TEMP.o: fcts/Temperature/My_TEMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/Temperature 
	@${RM} ${OBJECTDIR}/fcts/Temperature/My_TEMP.o.d 
	@${RM} ${OBJECTDIR}/fcts/Temperature/My_TEMP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/Temperature/My_TEMP.o   fcts/Temperature/My_TEMP.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/Temperature/My_TEMP.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/Temperature/My_TEMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/USART/My_USART.o: fcts/USART/My_USART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/USART 
	@${RM} ${OBJECTDIR}/fcts/USART/My_USART.o.d 
	@${RM} ${OBJECTDIR}/fcts/USART/My_USART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/USART/My_USART.o   fcts/USART/My_USART.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/USART/My_USART.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/USART/My_USART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Main.o   Main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/fcts/ADC/My_ADC.o: fcts/ADC/My_ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/ADC 
	@${RM} ${OBJECTDIR}/fcts/ADC/My_ADC.o.d 
	@${RM} ${OBJECTDIR}/fcts/ADC/My_ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/ADC/My_ADC.o   fcts/ADC/My_ADC.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/ADC/My_ADC.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/ADC/My_ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/Clock/My_CLOCK.o: fcts/Clock/My_CLOCK.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/Clock 
	@${RM} ${OBJECTDIR}/fcts/Clock/My_CLOCK.o.d 
	@${RM} ${OBJECTDIR}/fcts/Clock/My_CLOCK.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/Clock/My_CLOCK.o   fcts/Clock/My_CLOCK.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/Clock/My_CLOCK.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/Clock/My_CLOCK.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ARP.o: ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ARP.o.d 
	@${RM} ${OBJECTDIR}/ARP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/ARP.o   ARP.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ARP.o 
	@${FIXDEPS} "${OBJECTDIR}/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Announce.o: Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Announce.o.d 
	@${RM} ${OBJECTDIR}/Announce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Announce.o   Announce.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Announce.o 
	@${FIXDEPS} "${OBJECTDIR}/Announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/DNS.o: DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/DNS.o.d 
	@${RM} ${OBJECTDIR}/DNS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/DNS.o   DNS.c 
	@${DEP_GEN} -d ${OBJECTDIR}/DNS.o 
	@${FIXDEPS} "${OBJECTDIR}/DNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ENC28J60.o: ENC28J60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ENC28J60.o.d 
	@${RM} ${OBJECTDIR}/ENC28J60.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/ENC28J60.o   ENC28J60.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ENC28J60.o 
	@${FIXDEPS} "${OBJECTDIR}/ENC28J60.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Helpers.o: Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Helpers.o.d 
	@${RM} ${OBJECTDIR}/Helpers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Helpers.o   Helpers.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ICMP.o: ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ICMP.o.d 
	@${RM} ${OBJECTDIR}/ICMP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/ICMP.o   ICMP.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ICMP.o 
	@${FIXDEPS} "${OBJECTDIR}/ICMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/IP.o: IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/IP.o.d 
	@${RM} ${OBJECTDIR}/IP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/IP.o   IP.c 
	@${DEP_GEN} -d ${OBJECTDIR}/IP.o 
	@${FIXDEPS} "${OBJECTDIR}/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PICDelay.o: PICDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/PICDelay.o.d 
	@${RM} ${OBJECTDIR}/PICDelay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PICDelay.o   PICDelay.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PICDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/PICDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/StackTsk.o: StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/StackTsk.o.d 
	@${RM} ${OBJECTDIR}/StackTsk.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/StackTsk.o   StackTsk.c 
	@${DEP_GEN} -d ${OBJECTDIR}/StackTsk.o 
	@${FIXDEPS} "${OBJECTDIR}/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/TCP.o: TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/TCP.o.d 
	@${RM} ${OBJECTDIR}/TCP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/TCP.o   TCP.c 
	@${DEP_GEN} -d ${OBJECTDIR}/TCP.o 
	@${FIXDEPS} "${OBJECTDIR}/TCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/TCPPerformanceTest.o: TCPPerformanceTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/TCPPerformanceTest.o.d 
	@${RM} ${OBJECTDIR}/TCPPerformanceTest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/TCPPerformanceTest.o   TCPPerformanceTest.c 
	@${DEP_GEN} -d ${OBJECTDIR}/TCPPerformanceTest.o 
	@${FIXDEPS} "${OBJECTDIR}/TCPPerformanceTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Tick.o: Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Tick.o.d 
	@${RM} ${OBJECTDIR}/Tick.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Tick.o   Tick.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UDP.o: UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/UDP.o.d 
	@${RM} ${OBJECTDIR}/UDP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UDP.o   UDP.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UDP.o 
	@${FIXDEPS} "${OBJECTDIR}/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UDPPerformanceTest.o: UDPPerformanceTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/UDPPerformanceTest.o.d 
	@${RM} ${OBJECTDIR}/UDPPerformanceTest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UDPPerformanceTest.o   UDPPerformanceTest.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UDPPerformanceTest.o 
	@${FIXDEPS} "${OBJECTDIR}/UDPPerformanceTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/GSM/My_GSM.o: fcts/GSM/My_GSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/GSM 
	@${RM} ${OBJECTDIR}/fcts/GSM/My_GSM.o.d 
	@${RM} ${OBJECTDIR}/fcts/GSM/My_GSM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/GSM/My_GSM.o   fcts/GSM/My_GSM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/GSM/My_GSM.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/GSM/My_GSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2ack.o: fcts/i2c/i2c2ack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2ack.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2ack.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2ack.o   fcts/i2c/i2c2ack.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2ack.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2ack.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2clos.o: fcts/i2c/i2c2clos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2clos.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2clos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2clos.o   fcts/i2c/i2c2clos.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2clos.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2clos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2dtrd.o: fcts/i2c/i2c2dtrd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2dtrd.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2dtrd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2dtrd.o   fcts/i2c/i2c2dtrd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2dtrd.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2dtrd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2eeap.o: fcts/i2c/i2c2eeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eeap.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eeap.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2eeap.o   fcts/i2c/i2c2eeap.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2eeap.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2eeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2eebw.o: fcts/i2c/i2c2eebw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eebw.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eebw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2eebw.o   fcts/i2c/i2c2eebw.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2eebw.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2eebw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2eecr.o: fcts/i2c/i2c2eecr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eecr.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eecr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2eecr.o   fcts/i2c/i2c2eecr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2eecr.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2eecr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2eepw.o: fcts/i2c/i2c2eepw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eepw.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eepw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2eepw.o   fcts/i2c/i2c2eepw.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2eepw.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2eepw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2eerr.o: fcts/i2c/i2c2eerr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eerr.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eerr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2eerr.o   fcts/i2c/i2c2eerr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2eerr.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2eerr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2eesr.o: fcts/i2c/i2c2eesr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eesr.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2eesr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2eesr.o   fcts/i2c/i2c2eesr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2eesr.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2eesr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2gets.o: fcts/i2c/i2c2gets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2gets.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2gets.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2gets.o   fcts/i2c/i2c2gets.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2gets.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2gets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2idle.o: fcts/i2c/i2c2idle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2idle.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2idle.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2idle.o   fcts/i2c/i2c2idle.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2idle.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2idle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2nack.o: fcts/i2c/i2c2nack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2nack.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2nack.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2nack.o   fcts/i2c/i2c2nack.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2nack.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2nack.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2open.o: fcts/i2c/i2c2open.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2open.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2open.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2open.o   fcts/i2c/i2c2open.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2open.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2open.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2puts.o: fcts/i2c/i2c2puts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2puts.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2puts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2puts.o   fcts/i2c/i2c2puts.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2puts.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2puts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2read.o: fcts/i2c/i2c2read.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2read.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2read.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2read.o   fcts/i2c/i2c2read.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2read.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2read.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2rstr.o: fcts/i2c/i2c2rstr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2rstr.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2rstr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2rstr.o   fcts/i2c/i2c2rstr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2rstr.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2rstr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2stop.o: fcts/i2c/i2c2stop.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2stop.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2stop.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2stop.o   fcts/i2c/i2c2stop.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2stop.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2stop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2strt.o: fcts/i2c/i2c2strt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2strt.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2strt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2strt.o   fcts/i2c/i2c2strt.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2strt.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2strt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/i2c/i2c2writ.o: fcts/i2c/i2c2writ.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/i2c 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2writ.o.d 
	@${RM} ${OBJECTDIR}/fcts/i2c/i2c2writ.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/i2c/i2c2writ.o   fcts/i2c/i2c2writ.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/i2c/i2c2writ.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/i2c/i2c2writ.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/busyxlcd.o: fcts/LCD/busyxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/busyxlcd.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/busyxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/busyxlcd.o   fcts/LCD/busyxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/busyxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/busyxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/openxlcd.o: fcts/LCD/openxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/openxlcd.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/openxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/openxlcd.o   fcts/LCD/openxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/openxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/openxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/putrxlcd.o: fcts/LCD/putrxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/putrxlcd.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/putrxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/putrxlcd.o   fcts/LCD/putrxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/putrxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/putrxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/putsxlcd.o: fcts/LCD/putsxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/putsxlcd.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/putsxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/putsxlcd.o   fcts/LCD/putsxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/putsxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/putsxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/readaddr.o: fcts/LCD/readaddr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/readaddr.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/readaddr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/readaddr.o   fcts/LCD/readaddr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/readaddr.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/readaddr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/readdata.o: fcts/LCD/readdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/readdata.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/readdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/readdata.o   fcts/LCD/readdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/readdata.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/readdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/setcgram.o: fcts/LCD/setcgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/setcgram.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/setcgram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/setcgram.o   fcts/LCD/setcgram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/setcgram.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/setcgram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/setddram.o: fcts/LCD/setddram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/setddram.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/setddram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/setddram.o   fcts/LCD/setddram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/setddram.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/setddram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/wcmdxlcd.o: fcts/LCD/wcmdxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/wcmdxlcd.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/wcmdxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/wcmdxlcd.o   fcts/LCD/wcmdxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/wcmdxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/wcmdxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/writdata.o: fcts/LCD/writdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/writdata.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/writdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/writdata.o   fcts/LCD/writdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/writdata.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/writdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/writeOnLCD.o: fcts/LCD/writeOnLCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/writeOnLCD.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/writeOnLCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/writeOnLCD.o   fcts/LCD/writeOnLCD.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/writeOnLCD.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/writeOnLCD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/LCD/delaysXLCD.o: fcts/LCD/delaysXLCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/LCD 
	@${RM} ${OBJECTDIR}/fcts/LCD/delaysXLCD.o.d 
	@${RM} ${OBJECTDIR}/fcts/LCD/delaysXLCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/LCD/delaysXLCD.o   fcts/LCD/delaysXLCD.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/LCD/delaysXLCD.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/LCD/delaysXLCD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/OS/hardware.o: fcts/OS/hardware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/OS 
	@${RM} ${OBJECTDIR}/fcts/OS/hardware.o.d 
	@${RM} ${OBJECTDIR}/fcts/OS/hardware.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/OS/hardware.o   fcts/OS/hardware.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/OS/hardware.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/OS/hardware.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/OS/My_TIMERS.o: fcts/OS/My_TIMERS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/OS 
	@${RM} ${OBJECTDIR}/fcts/OS/My_TIMERS.o.d 
	@${RM} ${OBJECTDIR}/fcts/OS/My_TIMERS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/OS/My_TIMERS.o   fcts/OS/My_TIMERS.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/OS/My_TIMERS.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/OS/My_TIMERS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/TIOS.o: TIOS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/TIOS.o.d 
	@${RM} ${OBJECTDIR}/TIOS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/TIOS.o   TIOS.c 
	@${DEP_GEN} -d ${OBJECTDIR}/TIOS.o 
	@${FIXDEPS} "${OBJECTDIR}/TIOS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/Temperature/1wire.o: fcts/Temperature/1wire.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/Temperature 
	@${RM} ${OBJECTDIR}/fcts/Temperature/1wire.o.d 
	@${RM} ${OBJECTDIR}/fcts/Temperature/1wire.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/Temperature/1wire.o   fcts/Temperature/1wire.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/Temperature/1wire.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/Temperature/1wire.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/Temperature/ftoa.o: fcts/Temperature/ftoa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/Temperature 
	@${RM} ${OBJECTDIR}/fcts/Temperature/ftoa.o.d 
	@${RM} ${OBJECTDIR}/fcts/Temperature/ftoa.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/Temperature/ftoa.o   fcts/Temperature/ftoa.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/Temperature/ftoa.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/Temperature/ftoa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/Temperature/My_TEMP.o: fcts/Temperature/My_TEMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/Temperature 
	@${RM} ${OBJECTDIR}/fcts/Temperature/My_TEMP.o.d 
	@${RM} ${OBJECTDIR}/fcts/Temperature/My_TEMP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/Temperature/My_TEMP.o   fcts/Temperature/My_TEMP.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/Temperature/My_TEMP.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/Temperature/My_TEMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fcts/USART/My_USART.o: fcts/USART/My_USART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/fcts/USART 
	@${RM} ${OBJECTDIR}/fcts/USART/My_USART.o.d 
	@${RM} ${OBJECTDIR}/fcts/USART/My_USART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fcts/USART/My_USART.o   fcts/USART/My_USART.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fcts/USART/My_USART.o 
	@${FIXDEPS} "${OBJECTDIR}/fcts/USART/My_USART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"TCPIP Stack" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Main.o   Main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/TEMS-Integrated.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_ICD3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/TEMS-Integrated.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/TEMS-Integrated.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/TEMS-Integrated.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
