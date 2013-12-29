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
ifeq "$(wildcard nbproject/Makefile-local-CondoUnit.mk)" "nbproject/Makefile-local-CondoUnit.mk"
include nbproject/Makefile-local-CondoUnit.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=CondoUnit
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_init.c C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_int.c C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_tasks.c C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/main.c C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/app.c bsp_sys_init.c ..\..\..\v0_70b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c ..\..\..\v0_70b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb.c ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb_device.c ..\..\..\v0_70b\framework\system\clk\src\sys_clk.c ..\..\..\v0_70b\framework\system\clk\src\sys_clk_pic32.c ..\..\..\v0_70b\framework\system\common\sys_buffer.c ..\..\..\v0_70b\framework\system\common\sys_queue.c ..\..\..\v0_70b\framework\system\int\src\sys_int_pic32.c ..\..\..\v0_70b\framework\system\ports\src\sys_ports.c ..\..\..\v0_70b\framework\system\tmr\src\sys_tmr.c ..\..\..\v0_70b\framework\system\wdt\src\sys_wdt.c ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device.c ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_cdc.c ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_cdc_acm.c config_performance.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1900764991/system_init.o ${OBJECTDIR}/_ext/1900764991/system_int.o ${OBJECTDIR}/_ext/1900764991/system_tasks.o ${OBJECTDIR}/_ext/1900764991/main.o ${OBJECTDIR}/_ext/1900764991/app.o ${OBJECTDIR}/bsp_sys_init.o ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o ${OBJECTDIR}/_ext/33171531/drv_usb.o ${OBJECTDIR}/_ext/33171531/drv_usb_device.o ${OBJECTDIR}/_ext/505637111/sys_clk.o ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o ${OBJECTDIR}/_ext/711893886/sys_buffer.o ${OBJECTDIR}/_ext/711893886/sys_queue.o ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o ${OBJECTDIR}/_ext/2101373095/sys_ports.o ${OBJECTDIR}/_ext/1551575698/sys_tmr.o ${OBJECTDIR}/_ext/855120028/sys_wdt.o ${OBJECTDIR}/_ext/297931189/usb_device.o ${OBJECTDIR}/_ext/297931189/usb_device_cdc.o ${OBJECTDIR}/_ext/297931189/usb_device_cdc_acm.o ${OBJECTDIR}/config_performance.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1900764991/system_init.o.d ${OBJECTDIR}/_ext/1900764991/system_int.o.d ${OBJECTDIR}/_ext/1900764991/system_tasks.o.d ${OBJECTDIR}/_ext/1900764991/main.o.d ${OBJECTDIR}/_ext/1900764991/app.o.d ${OBJECTDIR}/bsp_sys_init.o.d ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o.d ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o.d ${OBJECTDIR}/_ext/33171531/drv_usb.o.d ${OBJECTDIR}/_ext/33171531/drv_usb_device.o.d ${OBJECTDIR}/_ext/505637111/sys_clk.o.d ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o.d ${OBJECTDIR}/_ext/711893886/sys_buffer.o.d ${OBJECTDIR}/_ext/711893886/sys_queue.o.d ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o.d ${OBJECTDIR}/_ext/2101373095/sys_ports.o.d ${OBJECTDIR}/_ext/1551575698/sys_tmr.o.d ${OBJECTDIR}/_ext/855120028/sys_wdt.o.d ${OBJECTDIR}/_ext/297931189/usb_device.o.d ${OBJECTDIR}/_ext/297931189/usb_device_cdc.o.d ${OBJECTDIR}/_ext/297931189/usb_device_cdc_acm.o.d ${OBJECTDIR}/config_performance.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1900764991/system_init.o ${OBJECTDIR}/_ext/1900764991/system_int.o ${OBJECTDIR}/_ext/1900764991/system_tasks.o ${OBJECTDIR}/_ext/1900764991/main.o ${OBJECTDIR}/_ext/1900764991/app.o ${OBJECTDIR}/bsp_sys_init.o ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o ${OBJECTDIR}/_ext/33171531/drv_usb.o ${OBJECTDIR}/_ext/33171531/drv_usb_device.o ${OBJECTDIR}/_ext/505637111/sys_clk.o ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o ${OBJECTDIR}/_ext/711893886/sys_buffer.o ${OBJECTDIR}/_ext/711893886/sys_queue.o ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o ${OBJECTDIR}/_ext/2101373095/sys_ports.o ${OBJECTDIR}/_ext/1551575698/sys_tmr.o ${OBJECTDIR}/_ext/855120028/sys_wdt.o ${OBJECTDIR}/_ext/297931189/usb_device.o ${OBJECTDIR}/_ext/297931189/usb_device_cdc.o ${OBJECTDIR}/_ext/297931189/usb_device_cdc_acm.o ${OBJECTDIR}/config_performance.o

# Source Files
SOURCEFILES=C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_init.c C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_int.c C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_tasks.c C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/main.c C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/app.c bsp_sys_init.c ..\..\..\v0_70b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c ..\..\..\v0_70b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb.c ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb_device.c ..\..\..\v0_70b\framework\system\clk\src\sys_clk.c ..\..\..\v0_70b\framework\system\clk\src\sys_clk_pic32.c ..\..\..\v0_70b\framework\system\common\sys_buffer.c ..\..\..\v0_70b\framework\system\common\sys_queue.c ..\..\..\v0_70b\framework\system\int\src\sys_int_pic32.c ..\..\..\v0_70b\framework\system\ports\src\sys_ports.c ..\..\..\v0_70b\framework\system\tmr\src\sys_tmr.c ..\..\..\v0_70b\framework\system\wdt\src\sys_wdt.c ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device.c ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_cdc.c ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_cdc_acm.c config_performance.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-CondoUnit.mk dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX250F128B
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
${OBJECTDIR}/_ext/1900764991/system_init.o: C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1900764991 
	@${RM} ${OBJECTDIR}/_ext/1900764991/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1900764991/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1900764991/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1900764991/system_init.o.d" -o ${OBJECTDIR}/_ext/1900764991/system_init.o C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_init.c   
	
${OBJECTDIR}/_ext/1900764991/system_int.o: C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1900764991 
	@${RM} ${OBJECTDIR}/_ext/1900764991/system_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1900764991/system_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1900764991/system_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1900764991/system_int.o.d" -o ${OBJECTDIR}/_ext/1900764991/system_int.o C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_int.c   
	
${OBJECTDIR}/_ext/1900764991/system_tasks.o: C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1900764991 
	@${RM} ${OBJECTDIR}/_ext/1900764991/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1900764991/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1900764991/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1900764991/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1900764991/system_tasks.o C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_tasks.c   
	
${OBJECTDIR}/_ext/1900764991/main.o: C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1900764991 
	@${RM} ${OBJECTDIR}/_ext/1900764991/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1900764991/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1900764991/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1900764991/main.o.d" -o ${OBJECTDIR}/_ext/1900764991/main.o C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/main.c   
	
${OBJECTDIR}/_ext/1900764991/app.o: C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1900764991 
	@${RM} ${OBJECTDIR}/_ext/1900764991/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1900764991/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1900764991/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1900764991/app.o.d" -o ${OBJECTDIR}/_ext/1900764991/app.o C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/app.c   
	
${OBJECTDIR}/bsp_sys_init.o: bsp_sys_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/bsp_sys_init.o.d 
	@${RM} ${OBJECTDIR}/bsp_sys_init.o 
	@${FIXDEPS} "${OBJECTDIR}/bsp_sys_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/bsp_sys_init.o.d" -o ${OBJECTDIR}/bsp_sys_init.o bsp_sys_init.c   
	
${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o: ..\..\..\v0_70b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/709546973 
	@${RM} ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o.d" -o ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o ..\..\..\v0_70b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c   
	
${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o: ..\..\..\v0_70b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1093147594 
	@${RM} ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o.d" -o ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o ..\..\..\v0_70b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c   
	
${OBJECTDIR}/_ext/33171531/drv_usb.o: ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/33171531 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb.o.d 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/33171531/drv_usb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/33171531/drv_usb.o.d" -o ${OBJECTDIR}/_ext/33171531/drv_usb.o ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb.c   
	
${OBJECTDIR}/_ext/33171531/drv_usb_device.o: ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/33171531 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/33171531/drv_usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/33171531/drv_usb_device.o.d" -o ${OBJECTDIR}/_ext/33171531/drv_usb_device.o ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb_device.c   
	
${OBJECTDIR}/_ext/505637111/sys_clk.o: ..\..\..\v0_70b\framework\system\clk\src\sys_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/505637111 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/505637111/sys_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/505637111/sys_clk.o.d" -o ${OBJECTDIR}/_ext/505637111/sys_clk.o ..\..\..\v0_70b\framework\system\clk\src\sys_clk.c   
	
${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o: ..\..\..\v0_70b\framework\system\clk\src\sys_clk_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/505637111 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o.d" -o ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o ..\..\..\v0_70b\framework\system\clk\src\sys_clk_pic32.c   
	
${OBJECTDIR}/_ext/711893886/sys_buffer.o: ..\..\..\v0_70b\framework\system\common\sys_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711893886 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711893886/sys_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/711893886/sys_buffer.o.d" -o ${OBJECTDIR}/_ext/711893886/sys_buffer.o ..\..\..\v0_70b\framework\system\common\sys_buffer.c   
	
${OBJECTDIR}/_ext/711893886/sys_queue.o: ..\..\..\v0_70b\framework\system\common\sys_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711893886 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711893886/sys_queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/711893886/sys_queue.o.d" -o ${OBJECTDIR}/_ext/711893886/sys_queue.o ..\..\..\v0_70b\framework\system\common\sys_queue.c   
	
${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o: ..\..\..\v0_70b\framework\system\int\src\sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1601261892 
	@${RM} ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o ..\..\..\v0_70b\framework\system\int\src\sys_int_pic32.c   
	
${OBJECTDIR}/_ext/2101373095/sys_ports.o: ..\..\..\v0_70b\framework\system\ports\src\sys_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2101373095 
	@${RM} ${OBJECTDIR}/_ext/2101373095/sys_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/2101373095/sys_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2101373095/sys_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/2101373095/sys_ports.o.d" -o ${OBJECTDIR}/_ext/2101373095/sys_ports.o ..\..\..\v0_70b\framework\system\ports\src\sys_ports.c   
	
${OBJECTDIR}/_ext/1551575698/sys_tmr.o: ..\..\..\v0_70b\framework\system\tmr\src\sys_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1551575698 
	@${RM} ${OBJECTDIR}/_ext/1551575698/sys_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1551575698/sys_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1551575698/sys_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1551575698/sys_tmr.o.d" -o ${OBJECTDIR}/_ext/1551575698/sys_tmr.o ..\..\..\v0_70b\framework\system\tmr\src\sys_tmr.c   
	
${OBJECTDIR}/_ext/855120028/sys_wdt.o: ..\..\..\v0_70b\framework\system\wdt\src\sys_wdt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/855120028 
	@${RM} ${OBJECTDIR}/_ext/855120028/sys_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/855120028/sys_wdt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/855120028/sys_wdt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/855120028/sys_wdt.o.d" -o ${OBJECTDIR}/_ext/855120028/sys_wdt.o ..\..\..\v0_70b\framework\system\wdt\src\sys_wdt.c   
	
${OBJECTDIR}/_ext/297931189/usb_device.o: ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/297931189 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/297931189/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/297931189/usb_device.o.d" -o ${OBJECTDIR}/_ext/297931189/usb_device.o ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device.c   
	
${OBJECTDIR}/_ext/297931189/usb_device_cdc.o: ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/297931189 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/297931189/usb_device_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/297931189/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/297931189/usb_device_cdc.o ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_cdc.c   
	
${OBJECTDIR}/_ext/297931189/usb_device_cdc_acm.o: ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_cdc_acm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/297931189 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device_cdc_acm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/297931189/usb_device_cdc_acm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/297931189/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/297931189/usb_device_cdc_acm.o ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_cdc_acm.c   
	
${OBJECTDIR}/config_performance.o: config_performance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/config_performance.o.d 
	@${RM} ${OBJECTDIR}/config_performance.o 
	@${FIXDEPS} "${OBJECTDIR}/config_performance.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/config_performance.o.d" -o ${OBJECTDIR}/config_performance.o config_performance.c   
	
else
${OBJECTDIR}/_ext/1900764991/system_init.o: C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1900764991 
	@${RM} ${OBJECTDIR}/_ext/1900764991/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1900764991/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1900764991/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1900764991/system_init.o.d" -o ${OBJECTDIR}/_ext/1900764991/system_init.o C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_init.c   
	
${OBJECTDIR}/_ext/1900764991/system_int.o: C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1900764991 
	@${RM} ${OBJECTDIR}/_ext/1900764991/system_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1900764991/system_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1900764991/system_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1900764991/system_int.o.d" -o ${OBJECTDIR}/_ext/1900764991/system_int.o C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_int.c   
	
${OBJECTDIR}/_ext/1900764991/system_tasks.o: C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1900764991 
	@${RM} ${OBJECTDIR}/_ext/1900764991/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1900764991/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1900764991/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1900764991/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1900764991/system_tasks.o C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/system_tasks.c   
	
${OBJECTDIR}/_ext/1900764991/main.o: C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1900764991 
	@${RM} ${OBJECTDIR}/_ext/1900764991/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1900764991/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1900764991/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1900764991/main.o.d" -o ${OBJECTDIR}/_ext/1900764991/main.o C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/main.c   
	
${OBJECTDIR}/_ext/1900764991/app.o: C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1900764991 
	@${RM} ${OBJECTDIR}/_ext/1900764991/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1900764991/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1900764991/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1900764991/app.o.d" -o ${OBJECTDIR}/_ext/1900764991/app.o C:/microchip/harmony/v0_70b/apps/Harmony4AvalonGen2.X/app.c   
	
${OBJECTDIR}/bsp_sys_init.o: bsp_sys_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/bsp_sys_init.o.d 
	@${RM} ${OBJECTDIR}/bsp_sys_init.o 
	@${FIXDEPS} "${OBJECTDIR}/bsp_sys_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/bsp_sys_init.o.d" -o ${OBJECTDIR}/bsp_sys_init.o bsp_sys_init.c   
	
${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o: ..\..\..\v0_70b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/709546973 
	@${RM} ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o.d" -o ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o ..\..\..\v0_70b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c   
	
${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o: ..\..\..\v0_70b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1093147594 
	@${RM} ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o.d" -o ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o ..\..\..\v0_70b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c   
	
${OBJECTDIR}/_ext/33171531/drv_usb.o: ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/33171531 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb.o.d 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/33171531/drv_usb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/33171531/drv_usb.o.d" -o ${OBJECTDIR}/_ext/33171531/drv_usb.o ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb.c   
	
${OBJECTDIR}/_ext/33171531/drv_usb_device.o: ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/33171531 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/33171531/drv_usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/33171531/drv_usb_device.o.d" -o ${OBJECTDIR}/_ext/33171531/drv_usb_device.o ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb_device.c   
	
${OBJECTDIR}/_ext/505637111/sys_clk.o: ..\..\..\v0_70b\framework\system\clk\src\sys_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/505637111 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/505637111/sys_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/505637111/sys_clk.o.d" -o ${OBJECTDIR}/_ext/505637111/sys_clk.o ..\..\..\v0_70b\framework\system\clk\src\sys_clk.c   
	
${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o: ..\..\..\v0_70b\framework\system\clk\src\sys_clk_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/505637111 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o.d" -o ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o ..\..\..\v0_70b\framework\system\clk\src\sys_clk_pic32.c   
	
${OBJECTDIR}/_ext/711893886/sys_buffer.o: ..\..\..\v0_70b\framework\system\common\sys_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711893886 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711893886/sys_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/711893886/sys_buffer.o.d" -o ${OBJECTDIR}/_ext/711893886/sys_buffer.o ..\..\..\v0_70b\framework\system\common\sys_buffer.c   
	
${OBJECTDIR}/_ext/711893886/sys_queue.o: ..\..\..\v0_70b\framework\system\common\sys_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711893886 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711893886/sys_queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/711893886/sys_queue.o.d" -o ${OBJECTDIR}/_ext/711893886/sys_queue.o ..\..\..\v0_70b\framework\system\common\sys_queue.c   
	
${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o: ..\..\..\v0_70b\framework\system\int\src\sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1601261892 
	@${RM} ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o ..\..\..\v0_70b\framework\system\int\src\sys_int_pic32.c   
	
${OBJECTDIR}/_ext/2101373095/sys_ports.o: ..\..\..\v0_70b\framework\system\ports\src\sys_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2101373095 
	@${RM} ${OBJECTDIR}/_ext/2101373095/sys_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/2101373095/sys_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2101373095/sys_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/2101373095/sys_ports.o.d" -o ${OBJECTDIR}/_ext/2101373095/sys_ports.o ..\..\..\v0_70b\framework\system\ports\src\sys_ports.c   
	
${OBJECTDIR}/_ext/1551575698/sys_tmr.o: ..\..\..\v0_70b\framework\system\tmr\src\sys_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1551575698 
	@${RM} ${OBJECTDIR}/_ext/1551575698/sys_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1551575698/sys_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1551575698/sys_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/1551575698/sys_tmr.o.d" -o ${OBJECTDIR}/_ext/1551575698/sys_tmr.o ..\..\..\v0_70b\framework\system\tmr\src\sys_tmr.c   
	
${OBJECTDIR}/_ext/855120028/sys_wdt.o: ..\..\..\v0_70b\framework\system\wdt\src\sys_wdt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/855120028 
	@${RM} ${OBJECTDIR}/_ext/855120028/sys_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/855120028/sys_wdt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/855120028/sys_wdt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/855120028/sys_wdt.o.d" -o ${OBJECTDIR}/_ext/855120028/sys_wdt.o ..\..\..\v0_70b\framework\system\wdt\src\sys_wdt.c   
	
${OBJECTDIR}/_ext/297931189/usb_device.o: ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/297931189 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/297931189/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/297931189/usb_device.o.d" -o ${OBJECTDIR}/_ext/297931189/usb_device.o ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device.c   
	
${OBJECTDIR}/_ext/297931189/usb_device_cdc.o: ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/297931189 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/297931189/usb_device_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/297931189/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/297931189/usb_device_cdc.o ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_cdc.c   
	
${OBJECTDIR}/_ext/297931189/usb_device_cdc_acm.o: ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_cdc_acm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/297931189 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device_cdc_acm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/297931189/usb_device_cdc_acm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/_ext/297931189/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/297931189/usb_device_cdc_acm.o ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_cdc_acm.c   
	
${OBJECTDIR}/config_performance.o: config_performance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/config_performance.o.d 
	@${RM} ${OBJECTDIR}/config_performance.o 
	@${FIXDEPS} "${OBJECTDIR}/config_performance.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -I"." -I"../../framework" -I"../../framework/system" -MMD -MF "${OBJECTDIR}/config_performance.o.d" -o ${OBJECTDIR}/config_performance.o config_performance.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ..\\..\\bin\\framework\\peripheral\\PIC32MX250F128B_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -o dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\bin\framework\peripheral\PIC32MX250F128B_peripherals.a       -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--warn-section-align
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ..\\..\\bin\\framework\\peripheral\\PIC32MX250F128B_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -o dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\bin\framework\peripheral\PIC32MX250F128B_peripherals.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--warn-section-align
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/CondoUnit
	${RM} -r dist/CondoUnit

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
