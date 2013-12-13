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
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/HashingUnitGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/HashingUnitGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=ISR_Support.S C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_init.c C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_int.c C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_tasks.c C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/main.c C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/app.c ..\..\..\v0_70b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c ..\..\..\v0_70b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb.c ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb_device.c ..\..\..\v0_70b\framework\osal\osal.c ..\..\..\v0_70b\framework\osal\osal_freertos.c ..\..\..\v0_70b\framework\system\clk\src\sys_clk.c ..\..\..\v0_70b\framework\system\clk\src\sys_clk_pic32.c ..\..\..\v0_70b\framework\system\common\sys_buffer.c ..\..\..\v0_70b\framework\system\common\sys_queue.c ..\..\..\v0_70b\framework\system\int\src\sys_int_pic32.c ..\..\..\v0_70b\framework\system\ports\src\sys_ports.c ..\..\..\v0_70b\framework\system\tmr\src\sys_tmr.c ..\..\..\v0_70b\framework\system\wdt\src\sys_wdt.c ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device.c ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_hid.c ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\croutine.c ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\list.c ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\queue.c ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\tasks.c ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\timers.c ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\portable\MemMang\heap_3.c ../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c port_asm.S

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/ISR_Support.o ${OBJECTDIR}/_ext/1321821662/system_init.o ${OBJECTDIR}/_ext/1321821662/system_int.o ${OBJECTDIR}/_ext/1321821662/system_tasks.o ${OBJECTDIR}/_ext/1321821662/main.o ${OBJECTDIR}/_ext/1321821662/app.o ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o ${OBJECTDIR}/_ext/33171531/drv_usb.o ${OBJECTDIR}/_ext/33171531/drv_usb_device.o ${OBJECTDIR}/_ext/471554295/osal.o ${OBJECTDIR}/_ext/471554295/osal_freertos.o ${OBJECTDIR}/_ext/505637111/sys_clk.o ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o ${OBJECTDIR}/_ext/711893886/sys_buffer.o ${OBJECTDIR}/_ext/711893886/sys_queue.o ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o ${OBJECTDIR}/_ext/2101373095/sys_ports.o ${OBJECTDIR}/_ext/1551575698/sys_tmr.o ${OBJECTDIR}/_ext/855120028/sys_wdt.o ${OBJECTDIR}/_ext/297931189/usb_device.o ${OBJECTDIR}/_ext/297931189/usb_device_hid.o ${OBJECTDIR}/_ext/304019964/croutine.o ${OBJECTDIR}/_ext/304019964/list.o ${OBJECTDIR}/_ext/304019964/queue.o ${OBJECTDIR}/_ext/304019964/tasks.o ${OBJECTDIR}/_ext/304019964/timers.o ${OBJECTDIR}/_ext/976165375/heap_3.o ${OBJECTDIR}/_ext/1073948370/port.o ${OBJECTDIR}/port_asm.o
POSSIBLE_DEPFILES=${OBJECTDIR}/ISR_Support.o.d ${OBJECTDIR}/_ext/1321821662/system_init.o.d ${OBJECTDIR}/_ext/1321821662/system_int.o.d ${OBJECTDIR}/_ext/1321821662/system_tasks.o.d ${OBJECTDIR}/_ext/1321821662/main.o.d ${OBJECTDIR}/_ext/1321821662/app.o.d ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o.d ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o.d ${OBJECTDIR}/_ext/33171531/drv_usb.o.d ${OBJECTDIR}/_ext/33171531/drv_usb_device.o.d ${OBJECTDIR}/_ext/471554295/osal.o.d ${OBJECTDIR}/_ext/471554295/osal_freertos.o.d ${OBJECTDIR}/_ext/505637111/sys_clk.o.d ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o.d ${OBJECTDIR}/_ext/711893886/sys_buffer.o.d ${OBJECTDIR}/_ext/711893886/sys_queue.o.d ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o.d ${OBJECTDIR}/_ext/2101373095/sys_ports.o.d ${OBJECTDIR}/_ext/1551575698/sys_tmr.o.d ${OBJECTDIR}/_ext/855120028/sys_wdt.o.d ${OBJECTDIR}/_ext/297931189/usb_device.o.d ${OBJECTDIR}/_ext/297931189/usb_device_hid.o.d ${OBJECTDIR}/_ext/304019964/croutine.o.d ${OBJECTDIR}/_ext/304019964/list.o.d ${OBJECTDIR}/_ext/304019964/queue.o.d ${OBJECTDIR}/_ext/304019964/tasks.o.d ${OBJECTDIR}/_ext/304019964/timers.o.d ${OBJECTDIR}/_ext/976165375/heap_3.o.d ${OBJECTDIR}/_ext/1073948370/port.o.d ${OBJECTDIR}/port_asm.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/ISR_Support.o ${OBJECTDIR}/_ext/1321821662/system_init.o ${OBJECTDIR}/_ext/1321821662/system_int.o ${OBJECTDIR}/_ext/1321821662/system_tasks.o ${OBJECTDIR}/_ext/1321821662/main.o ${OBJECTDIR}/_ext/1321821662/app.o ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o ${OBJECTDIR}/_ext/33171531/drv_usb.o ${OBJECTDIR}/_ext/33171531/drv_usb_device.o ${OBJECTDIR}/_ext/471554295/osal.o ${OBJECTDIR}/_ext/471554295/osal_freertos.o ${OBJECTDIR}/_ext/505637111/sys_clk.o ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o ${OBJECTDIR}/_ext/711893886/sys_buffer.o ${OBJECTDIR}/_ext/711893886/sys_queue.o ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o ${OBJECTDIR}/_ext/2101373095/sys_ports.o ${OBJECTDIR}/_ext/1551575698/sys_tmr.o ${OBJECTDIR}/_ext/855120028/sys_wdt.o ${OBJECTDIR}/_ext/297931189/usb_device.o ${OBJECTDIR}/_ext/297931189/usb_device_hid.o ${OBJECTDIR}/_ext/304019964/croutine.o ${OBJECTDIR}/_ext/304019964/list.o ${OBJECTDIR}/_ext/304019964/queue.o ${OBJECTDIR}/_ext/304019964/tasks.o ${OBJECTDIR}/_ext/304019964/timers.o ${OBJECTDIR}/_ext/976165375/heap_3.o ${OBJECTDIR}/_ext/1073948370/port.o ${OBJECTDIR}/port_asm.o

# Source Files
SOURCEFILES=ISR_Support.S C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_init.c C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_int.c C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_tasks.c C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/main.c C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/app.c ..\..\..\v0_70b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c ..\..\..\v0_70b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb.c ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb_device.c ..\..\..\v0_70b\framework\osal\osal.c ..\..\..\v0_70b\framework\osal\osal_freertos.c ..\..\..\v0_70b\framework\system\clk\src\sys_clk.c ..\..\..\v0_70b\framework\system\clk\src\sys_clk_pic32.c ..\..\..\v0_70b\framework\system\common\sys_buffer.c ..\..\..\v0_70b\framework\system\common\sys_queue.c ..\..\..\v0_70b\framework\system\int\src\sys_int_pic32.c ..\..\..\v0_70b\framework\system\ports\src\sys_ports.c ..\..\..\v0_70b\framework\system\tmr\src\sys_tmr.c ..\..\..\v0_70b\framework\system\wdt\src\sys_wdt.c ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device.c ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_hid.c ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\croutine.c ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\list.c ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\queue.c ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\tasks.c ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\timers.c ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\portable\MemMang\heap_3.c ../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c port_asm.S


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/HashingUnitGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/ISR_Support.o: ISR_Support.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ISR_Support.o.d 
	@${RM} ${OBJECTDIR}/ISR_Support.o 
	@${RM} ${OBJECTDIR}/ISR_Support.o.ok ${OBJECTDIR}/ISR_Support.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ISR_Support.o.d" "${OBJECTDIR}/ISR_Support.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -MMD -MF "${OBJECTDIR}/ISR_Support.o.d"  -o ${OBJECTDIR}/ISR_Support.o ISR_Support.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/ISR_Support.o.asm.d",--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1
	
${OBJECTDIR}/port_asm.o: port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/port_asm.o.d 
	@${RM} ${OBJECTDIR}/port_asm.o 
	@${RM} ${OBJECTDIR}/port_asm.o.ok ${OBJECTDIR}/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/port_asm.o.d" "${OBJECTDIR}/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -MMD -MF "${OBJECTDIR}/port_asm.o.d"  -o ${OBJECTDIR}/port_asm.o port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/port_asm.o.asm.d",--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1
	
else
${OBJECTDIR}/ISR_Support.o: ISR_Support.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ISR_Support.o.d 
	@${RM} ${OBJECTDIR}/ISR_Support.o 
	@${RM} ${OBJECTDIR}/ISR_Support.o.ok ${OBJECTDIR}/ISR_Support.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ISR_Support.o.d" "${OBJECTDIR}/ISR_Support.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -MMD -MF "${OBJECTDIR}/ISR_Support.o.d"  -o ${OBJECTDIR}/ISR_Support.o ISR_Support.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/ISR_Support.o.asm.d",--gdwarf-2
	
${OBJECTDIR}/port_asm.o: port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/port_asm.o.d 
	@${RM} ${OBJECTDIR}/port_asm.o 
	@${RM} ${OBJECTDIR}/port_asm.o.ok ${OBJECTDIR}/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/port_asm.o.d" "${OBJECTDIR}/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -MMD -MF "${OBJECTDIR}/port_asm.o.d"  -o ${OBJECTDIR}/port_asm.o port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/port_asm.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1321821662/system_init.o: C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1321821662 
	@${RM} ${OBJECTDIR}/_ext/1321821662/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1321821662/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1321821662/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1321821662/system_init.o.d" -o ${OBJECTDIR}/_ext/1321821662/system_init.o C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_init.c   
	
${OBJECTDIR}/_ext/1321821662/system_int.o: C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1321821662 
	@${RM} ${OBJECTDIR}/_ext/1321821662/system_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1321821662/system_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1321821662/system_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1321821662/system_int.o.d" -o ${OBJECTDIR}/_ext/1321821662/system_int.o C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_int.c   
	
${OBJECTDIR}/_ext/1321821662/system_tasks.o: C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1321821662 
	@${RM} ${OBJECTDIR}/_ext/1321821662/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1321821662/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1321821662/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1321821662/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1321821662/system_tasks.o C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_tasks.c   
	
${OBJECTDIR}/_ext/1321821662/main.o: C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1321821662 
	@${RM} ${OBJECTDIR}/_ext/1321821662/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1321821662/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1321821662/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1321821662/main.o.d" -o ${OBJECTDIR}/_ext/1321821662/main.o C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/main.c   
	
${OBJECTDIR}/_ext/1321821662/app.o: C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1321821662 
	@${RM} ${OBJECTDIR}/_ext/1321821662/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1321821662/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1321821662/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1321821662/app.o.d" -o ${OBJECTDIR}/_ext/1321821662/app.o C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/app.c   
	
${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o: ..\..\..\v0_70b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/709546973 
	@${RM} ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o.d" -o ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o ..\..\..\v0_70b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c   
	
${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o: ..\..\..\v0_70b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1093147594 
	@${RM} ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o.d" -o ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o ..\..\..\v0_70b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c   
	
${OBJECTDIR}/_ext/33171531/drv_usb.o: ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/33171531 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb.o.d 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/33171531/drv_usb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/33171531/drv_usb.o.d" -o ${OBJECTDIR}/_ext/33171531/drv_usb.o ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb.c   
	
${OBJECTDIR}/_ext/33171531/drv_usb_device.o: ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/33171531 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/33171531/drv_usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/33171531/drv_usb_device.o.d" -o ${OBJECTDIR}/_ext/33171531/drv_usb_device.o ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb_device.c   
	
${OBJECTDIR}/_ext/471554295/osal.o: ..\..\..\v0_70b\framework\osal\osal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/471554295 
	@${RM} ${OBJECTDIR}/_ext/471554295/osal.o.d 
	@${RM} ${OBJECTDIR}/_ext/471554295/osal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/471554295/osal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/471554295/osal.o.d" -o ${OBJECTDIR}/_ext/471554295/osal.o ..\..\..\v0_70b\framework\osal\osal.c   
	
${OBJECTDIR}/_ext/471554295/osal_freertos.o: ..\..\..\v0_70b\framework\osal\osal_freertos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/471554295 
	@${RM} ${OBJECTDIR}/_ext/471554295/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/471554295/osal_freertos.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/471554295/osal_freertos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/471554295/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/471554295/osal_freertos.o ..\..\..\v0_70b\framework\osal\osal_freertos.c   
	
${OBJECTDIR}/_ext/505637111/sys_clk.o: ..\..\..\v0_70b\framework\system\clk\src\sys_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/505637111 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/505637111/sys_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/505637111/sys_clk.o.d" -o ${OBJECTDIR}/_ext/505637111/sys_clk.o ..\..\..\v0_70b\framework\system\clk\src\sys_clk.c   
	
${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o: ..\..\..\v0_70b\framework\system\clk\src\sys_clk_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/505637111 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o.d" -o ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o ..\..\..\v0_70b\framework\system\clk\src\sys_clk_pic32.c   
	
${OBJECTDIR}/_ext/711893886/sys_buffer.o: ..\..\..\v0_70b\framework\system\common\sys_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711893886 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711893886/sys_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/711893886/sys_buffer.o.d" -o ${OBJECTDIR}/_ext/711893886/sys_buffer.o ..\..\..\v0_70b\framework\system\common\sys_buffer.c   
	
${OBJECTDIR}/_ext/711893886/sys_queue.o: ..\..\..\v0_70b\framework\system\common\sys_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711893886 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711893886/sys_queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/711893886/sys_queue.o.d" -o ${OBJECTDIR}/_ext/711893886/sys_queue.o ..\..\..\v0_70b\framework\system\common\sys_queue.c   
	
${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o: ..\..\..\v0_70b\framework\system\int\src\sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1601261892 
	@${RM} ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o ..\..\..\v0_70b\framework\system\int\src\sys_int_pic32.c   
	
${OBJECTDIR}/_ext/2101373095/sys_ports.o: ..\..\..\v0_70b\framework\system\ports\src\sys_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2101373095 
	@${RM} ${OBJECTDIR}/_ext/2101373095/sys_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/2101373095/sys_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2101373095/sys_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/2101373095/sys_ports.o.d" -o ${OBJECTDIR}/_ext/2101373095/sys_ports.o ..\..\..\v0_70b\framework\system\ports\src\sys_ports.c   
	
${OBJECTDIR}/_ext/1551575698/sys_tmr.o: ..\..\..\v0_70b\framework\system\tmr\src\sys_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1551575698 
	@${RM} ${OBJECTDIR}/_ext/1551575698/sys_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1551575698/sys_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1551575698/sys_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1551575698/sys_tmr.o.d" -o ${OBJECTDIR}/_ext/1551575698/sys_tmr.o ..\..\..\v0_70b\framework\system\tmr\src\sys_tmr.c   
	
${OBJECTDIR}/_ext/855120028/sys_wdt.o: ..\..\..\v0_70b\framework\system\wdt\src\sys_wdt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/855120028 
	@${RM} ${OBJECTDIR}/_ext/855120028/sys_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/855120028/sys_wdt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/855120028/sys_wdt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/855120028/sys_wdt.o.d" -o ${OBJECTDIR}/_ext/855120028/sys_wdt.o ..\..\..\v0_70b\framework\system\wdt\src\sys_wdt.c   
	
${OBJECTDIR}/_ext/297931189/usb_device.o: ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/297931189 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/297931189/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/297931189/usb_device.o.d" -o ${OBJECTDIR}/_ext/297931189/usb_device.o ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device.c   
	
${OBJECTDIR}/_ext/297931189/usb_device_hid.o: ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/297931189 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device_hid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/297931189/usb_device_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/297931189/usb_device_hid.o.d" -o ${OBJECTDIR}/_ext/297931189/usb_device_hid.o ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_hid.c   
	
${OBJECTDIR}/_ext/304019964/croutine.o: ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/304019964 
	@${RM} ${OBJECTDIR}/_ext/304019964/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/304019964/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304019964/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/304019964/croutine.o.d" -o ${OBJECTDIR}/_ext/304019964/croutine.o ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\croutine.c   
	
${OBJECTDIR}/_ext/304019964/list.o: ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/304019964 
	@${RM} ${OBJECTDIR}/_ext/304019964/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/304019964/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304019964/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/304019964/list.o.d" -o ${OBJECTDIR}/_ext/304019964/list.o ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\list.c   
	
${OBJECTDIR}/_ext/304019964/queue.o: ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/304019964 
	@${RM} ${OBJECTDIR}/_ext/304019964/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/304019964/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304019964/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/304019964/queue.o.d" -o ${OBJECTDIR}/_ext/304019964/queue.o ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\queue.c   
	
${OBJECTDIR}/_ext/304019964/tasks.o: ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/304019964 
	@${RM} ${OBJECTDIR}/_ext/304019964/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/304019964/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304019964/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/304019964/tasks.o.d" -o ${OBJECTDIR}/_ext/304019964/tasks.o ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\tasks.c   
	
${OBJECTDIR}/_ext/304019964/timers.o: ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/304019964 
	@${RM} ${OBJECTDIR}/_ext/304019964/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/304019964/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304019964/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/304019964/timers.o.d" -o ${OBJECTDIR}/_ext/304019964/timers.o ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\timers.c   
	
${OBJECTDIR}/_ext/976165375/heap_3.o: ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\portable\MemMang\heap_3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/976165375 
	@${RM} ${OBJECTDIR}/_ext/976165375/heap_3.o.d 
	@${RM} ${OBJECTDIR}/_ext/976165375/heap_3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/976165375/heap_3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/976165375/heap_3.o.d" -o ${OBJECTDIR}/_ext/976165375/heap_3.o ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\portable\MemMang\heap_3.c   
	
${OBJECTDIR}/_ext/1073948370/port.o: ../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1073948370 
	@${RM} ${OBJECTDIR}/_ext/1073948370/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1073948370/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1073948370/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1073948370/port.o.d" -o ${OBJECTDIR}/_ext/1073948370/port.o ../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   
	
else
${OBJECTDIR}/_ext/1321821662/system_init.o: C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1321821662 
	@${RM} ${OBJECTDIR}/_ext/1321821662/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1321821662/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1321821662/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1321821662/system_init.o.d" -o ${OBJECTDIR}/_ext/1321821662/system_init.o C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_init.c   
	
${OBJECTDIR}/_ext/1321821662/system_int.o: C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1321821662 
	@${RM} ${OBJECTDIR}/_ext/1321821662/system_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1321821662/system_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1321821662/system_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1321821662/system_int.o.d" -o ${OBJECTDIR}/_ext/1321821662/system_int.o C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_int.c   
	
${OBJECTDIR}/_ext/1321821662/system_tasks.o: C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1321821662 
	@${RM} ${OBJECTDIR}/_ext/1321821662/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1321821662/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1321821662/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1321821662/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1321821662/system_tasks.o C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/system_tasks.c   
	
${OBJECTDIR}/_ext/1321821662/main.o: C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1321821662 
	@${RM} ${OBJECTDIR}/_ext/1321821662/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1321821662/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1321821662/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1321821662/main.o.d" -o ${OBJECTDIR}/_ext/1321821662/main.o C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/main.c   
	
${OBJECTDIR}/_ext/1321821662/app.o: C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1321821662 
	@${RM} ${OBJECTDIR}/_ext/1321821662/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1321821662/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1321821662/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1321821662/app.o.d" -o ${OBJECTDIR}/_ext/1321821662/app.o C:/microchip/harmony/v0_70b/apps/HashingUnitGen2.X/app.c   
	
${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o: ..\..\..\v0_70b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/709546973 
	@${RM} ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o.d" -o ${OBJECTDIR}/_ext/709546973/drv_spi_dynamic.o ..\..\..\v0_70b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c   
	
${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o: ..\..\..\v0_70b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1093147594 
	@${RM} ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o.d" -o ${OBJECTDIR}/_ext/1093147594/drv_tmr_dynamic.o ..\..\..\v0_70b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c   
	
${OBJECTDIR}/_ext/33171531/drv_usb.o: ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/33171531 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb.o.d 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/33171531/drv_usb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/33171531/drv_usb.o.d" -o ${OBJECTDIR}/_ext/33171531/drv_usb.o ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb.c   
	
${OBJECTDIR}/_ext/33171531/drv_usb_device.o: ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/33171531 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/33171531/drv_usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/33171531/drv_usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/33171531/drv_usb_device.o.d" -o ${OBJECTDIR}/_ext/33171531/drv_usb_device.o ..\..\..\v0_70b\framework\driver\usb\src\dynamic\drv_usb_device.c   
	
${OBJECTDIR}/_ext/471554295/osal.o: ..\..\..\v0_70b\framework\osal\osal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/471554295 
	@${RM} ${OBJECTDIR}/_ext/471554295/osal.o.d 
	@${RM} ${OBJECTDIR}/_ext/471554295/osal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/471554295/osal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/471554295/osal.o.d" -o ${OBJECTDIR}/_ext/471554295/osal.o ..\..\..\v0_70b\framework\osal\osal.c   
	
${OBJECTDIR}/_ext/471554295/osal_freertos.o: ..\..\..\v0_70b\framework\osal\osal_freertos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/471554295 
	@${RM} ${OBJECTDIR}/_ext/471554295/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/471554295/osal_freertos.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/471554295/osal_freertos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/471554295/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/471554295/osal_freertos.o ..\..\..\v0_70b\framework\osal\osal_freertos.c   
	
${OBJECTDIR}/_ext/505637111/sys_clk.o: ..\..\..\v0_70b\framework\system\clk\src\sys_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/505637111 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/505637111/sys_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/505637111/sys_clk.o.d" -o ${OBJECTDIR}/_ext/505637111/sys_clk.o ..\..\..\v0_70b\framework\system\clk\src\sys_clk.c   
	
${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o: ..\..\..\v0_70b\framework\system\clk\src\sys_clk_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/505637111 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o.d" -o ${OBJECTDIR}/_ext/505637111/sys_clk_pic32.o ..\..\..\v0_70b\framework\system\clk\src\sys_clk_pic32.c   
	
${OBJECTDIR}/_ext/711893886/sys_buffer.o: ..\..\..\v0_70b\framework\system\common\sys_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711893886 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711893886/sys_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/711893886/sys_buffer.o.d" -o ${OBJECTDIR}/_ext/711893886/sys_buffer.o ..\..\..\v0_70b\framework\system\common\sys_buffer.c   
	
${OBJECTDIR}/_ext/711893886/sys_queue.o: ..\..\..\v0_70b\framework\system\common\sys_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711893886 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/711893886/sys_queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711893886/sys_queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/711893886/sys_queue.o.d" -o ${OBJECTDIR}/_ext/711893886/sys_queue.o ..\..\..\v0_70b\framework\system\common\sys_queue.c   
	
${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o: ..\..\..\v0_70b\framework\system\int\src\sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1601261892 
	@${RM} ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1601261892/sys_int_pic32.o ..\..\..\v0_70b\framework\system\int\src\sys_int_pic32.c   
	
${OBJECTDIR}/_ext/2101373095/sys_ports.o: ..\..\..\v0_70b\framework\system\ports\src\sys_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2101373095 
	@${RM} ${OBJECTDIR}/_ext/2101373095/sys_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/2101373095/sys_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2101373095/sys_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/2101373095/sys_ports.o.d" -o ${OBJECTDIR}/_ext/2101373095/sys_ports.o ..\..\..\v0_70b\framework\system\ports\src\sys_ports.c   
	
${OBJECTDIR}/_ext/1551575698/sys_tmr.o: ..\..\..\v0_70b\framework\system\tmr\src\sys_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1551575698 
	@${RM} ${OBJECTDIR}/_ext/1551575698/sys_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1551575698/sys_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1551575698/sys_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1551575698/sys_tmr.o.d" -o ${OBJECTDIR}/_ext/1551575698/sys_tmr.o ..\..\..\v0_70b\framework\system\tmr\src\sys_tmr.c   
	
${OBJECTDIR}/_ext/855120028/sys_wdt.o: ..\..\..\v0_70b\framework\system\wdt\src\sys_wdt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/855120028 
	@${RM} ${OBJECTDIR}/_ext/855120028/sys_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/855120028/sys_wdt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/855120028/sys_wdt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/855120028/sys_wdt.o.d" -o ${OBJECTDIR}/_ext/855120028/sys_wdt.o ..\..\..\v0_70b\framework\system\wdt\src\sys_wdt.c   
	
${OBJECTDIR}/_ext/297931189/usb_device.o: ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/297931189 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/297931189/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/297931189/usb_device.o.d" -o ${OBJECTDIR}/_ext/297931189/usb_device.o ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device.c   
	
${OBJECTDIR}/_ext/297931189/usb_device_hid.o: ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/297931189 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/297931189/usb_device_hid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/297931189/usb_device_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/297931189/usb_device_hid.o.d" -o ${OBJECTDIR}/_ext/297931189/usb_device_hid.o ..\..\..\v0_70b\framework\usb\src\dynamic\usb_device_hid.c   
	
${OBJECTDIR}/_ext/304019964/croutine.o: ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/304019964 
	@${RM} ${OBJECTDIR}/_ext/304019964/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/304019964/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304019964/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/304019964/croutine.o.d" -o ${OBJECTDIR}/_ext/304019964/croutine.o ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\croutine.c   
	
${OBJECTDIR}/_ext/304019964/list.o: ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/304019964 
	@${RM} ${OBJECTDIR}/_ext/304019964/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/304019964/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304019964/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/304019964/list.o.d" -o ${OBJECTDIR}/_ext/304019964/list.o ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\list.c   
	
${OBJECTDIR}/_ext/304019964/queue.o: ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/304019964 
	@${RM} ${OBJECTDIR}/_ext/304019964/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/304019964/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304019964/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/304019964/queue.o.d" -o ${OBJECTDIR}/_ext/304019964/queue.o ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\queue.c   
	
${OBJECTDIR}/_ext/304019964/tasks.o: ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/304019964 
	@${RM} ${OBJECTDIR}/_ext/304019964/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/304019964/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304019964/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/304019964/tasks.o.d" -o ${OBJECTDIR}/_ext/304019964/tasks.o ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\tasks.c   
	
${OBJECTDIR}/_ext/304019964/timers.o: ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/304019964 
	@${RM} ${OBJECTDIR}/_ext/304019964/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/304019964/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304019964/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/304019964/timers.o.d" -o ${OBJECTDIR}/_ext/304019964/timers.o ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\timers.c   
	
${OBJECTDIR}/_ext/976165375/heap_3.o: ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\portable\MemMang\heap_3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/976165375 
	@${RM} ${OBJECTDIR}/_ext/976165375/heap_3.o.d 
	@${RM} ${OBJECTDIR}/_ext/976165375/heap_3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/976165375/heap_3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/976165375/heap_3.o.d" -o ${OBJECTDIR}/_ext/976165375/heap_3.o ..\..\..\v0_70b\third_party\rtos\FreeRTOSV7.6.0_PIC32\FreeRTOS\Source\portable\MemMang\heap_3.c   
	
${OBJECTDIR}/_ext/1073948370/port.o: ../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1073948370 
	@${RM} ${OBJECTDIR}/_ext/1073948370/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1073948370/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1073948370/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -fdata-sections -mno-float -I"../../framework" -I"../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/include" -I"." -MMD -MF "${OBJECTDIR}/_ext/1073948370/port.o.d" -o ${OBJECTDIR}/_ext/1073948370/port.o ../../third_party/rtos/FreeRTOSV7.6.0_PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/HashingUnitGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ..\\..\\bin\\framework\\peripheral\\PIC32MX250F128B_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)    -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/HashingUnitGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\bin\framework\peripheral\PIC32MX250F128B_peripherals.a          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=_min_heap_size=4096,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--warn-section-align
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/HashingUnitGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ..\\..\\bin\\framework\\peripheral\\PIC32MX250F128B_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/HashingUnitGen2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\bin\framework\peripheral\PIC32MX250F128B_peripherals.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=4096,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--warn-section-align
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/HashingUnitGen2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
