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
ifeq "$(wildcard nbproject/Makefile-local-pic32mx_default.mk)" "nbproject/Makefile-local-pic32mx_default.mk"
include nbproject/Makefile-local-pic32mx_default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=pic32mx_default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/sample.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/sample.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/system_config/pic32mx_default/system_init.c ../src/system_config/pic32mx_default/system_int.c ../src/system_config/pic32mx_default/system_tasks.c ../src/app.c ../src/main.c ../../../../../framework/driver/usart/src/dynamic/drv_usart_dynamic.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1693412961/system_init.o ${OBJECTDIR}/_ext/1693412961/system_int.o ${OBJECTDIR}/_ext/1693412961/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/821589181/drv_usart_dynamic.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1693412961/system_init.o.d ${OBJECTDIR}/_ext/1693412961/system_int.o.d ${OBJECTDIR}/_ext/1693412961/system_tasks.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/821589181/drv_usart_dynamic.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1693412961/system_init.o ${OBJECTDIR}/_ext/1693412961/system_int.o ${OBJECTDIR}/_ext/1693412961/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/821589181/drv_usart_dynamic.o

# Source Files
SOURCEFILES=../src/system_config/pic32mx_default/system_init.c ../src/system_config/pic32mx_default/system_int.c ../src/system_config/pic32mx_default/system_tasks.c ../src/app.c ../src/main.c ../../../../../framework/driver/usart/src/dynamic/drv_usart_dynamic.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-pic32mx_default.mk dist/${CND_CONF}/${IMAGE_TYPE}/sample.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1693412961/system_init.o: ../src/system_config/pic32mx_default/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1693412961 
	@${RM} ${OBJECTDIR}/_ext/1693412961/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1693412961/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1693412961/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"../src" -I"../../../../../framework" -I"../src/system_config/pic32mx_default" -Wall -MMD -MF "${OBJECTDIR}/_ext/1693412961/system_init.o.d" -o ${OBJECTDIR}/_ext/1693412961/system_init.o ../src/system_config/pic32mx_default/system_init.c   
	
${OBJECTDIR}/_ext/1693412961/system_int.o: ../src/system_config/pic32mx_default/system_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1693412961 
	@${RM} ${OBJECTDIR}/_ext/1693412961/system_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1693412961/system_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1693412961/system_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"../src" -I"../../../../../framework" -I"../src/system_config/pic32mx_default" -Wall -MMD -MF "${OBJECTDIR}/_ext/1693412961/system_int.o.d" -o ${OBJECTDIR}/_ext/1693412961/system_int.o ../src/system_config/pic32mx_default/system_int.c   
	
${OBJECTDIR}/_ext/1693412961/system_tasks.o: ../src/system_config/pic32mx_default/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1693412961 
	@${RM} ${OBJECTDIR}/_ext/1693412961/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1693412961/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1693412961/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"../src" -I"../../../../../framework" -I"../src/system_config/pic32mx_default" -Wall -MMD -MF "${OBJECTDIR}/_ext/1693412961/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1693412961/system_tasks.o ../src/system_config/pic32mx_default/system_tasks.c   
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"../src" -I"../../../../../framework" -I"../src/system_config/pic32mx_default" -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"../src" -I"../../../../../framework" -I"../src/system_config/pic32mx_default" -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/821589181/drv_usart_dynamic.o: ../../../../../framework/driver/usart/src/dynamic/drv_usart_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/821589181 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/821589181/drv_usart_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"../src" -I"../../../../../framework" -I"../src/system_config/pic32mx_default" -Wall -MMD -MF "${OBJECTDIR}/_ext/821589181/drv_usart_dynamic.o.d" -o ${OBJECTDIR}/_ext/821589181/drv_usart_dynamic.o ../../../../../framework/driver/usart/src/dynamic/drv_usart_dynamic.c   
	
else
${OBJECTDIR}/_ext/1693412961/system_init.o: ../src/system_config/pic32mx_default/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1693412961 
	@${RM} ${OBJECTDIR}/_ext/1693412961/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1693412961/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1693412961/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"../src" -I"../../../../../framework" -I"../src/system_config/pic32mx_default" -Wall -MMD -MF "${OBJECTDIR}/_ext/1693412961/system_init.o.d" -o ${OBJECTDIR}/_ext/1693412961/system_init.o ../src/system_config/pic32mx_default/system_init.c   
	
${OBJECTDIR}/_ext/1693412961/system_int.o: ../src/system_config/pic32mx_default/system_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1693412961 
	@${RM} ${OBJECTDIR}/_ext/1693412961/system_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1693412961/system_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1693412961/system_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"../src" -I"../../../../../framework" -I"../src/system_config/pic32mx_default" -Wall -MMD -MF "${OBJECTDIR}/_ext/1693412961/system_int.o.d" -o ${OBJECTDIR}/_ext/1693412961/system_int.o ../src/system_config/pic32mx_default/system_int.c   
	
${OBJECTDIR}/_ext/1693412961/system_tasks.o: ../src/system_config/pic32mx_default/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1693412961 
	@${RM} ${OBJECTDIR}/_ext/1693412961/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1693412961/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1693412961/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"../src" -I"../../../../../framework" -I"../src/system_config/pic32mx_default" -Wall -MMD -MF "${OBJECTDIR}/_ext/1693412961/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1693412961/system_tasks.o ../src/system_config/pic32mx_default/system_tasks.c   
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"../src" -I"../../../../../framework" -I"../src/system_config/pic32mx_default" -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"../src" -I"../../../../../framework" -I"../src/system_config/pic32mx_default" -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/821589181/drv_usart_dynamic.o: ../../../../../framework/driver/usart/src/dynamic/drv_usart_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/821589181 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/821589181/drv_usart_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"../src" -I"../../../../../framework" -I"../src/system_config/pic32mx_default" -Wall -MMD -MF "${OBJECTDIR}/_ext/821589181/drv_usart_dynamic.o.d" -o ${OBJECTDIR}/_ext/821589181/drv_usart_dynamic.o ../../../../../framework/driver/usart/src/dynamic/drv_usart_dynamic.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/sample.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../bin/framework/peripheral/PIC32MX795F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)    -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/sample.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\bin\framework\peripheral\PIC32MX795F512L_peripherals.a          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/sample.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../bin/framework/peripheral/PIC32MX795F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/sample.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\bin\framework\peripheral\PIC32MX795F512L_peripherals.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/sample.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/pic32mx_default
	${RM} -r dist/pic32mx_default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
