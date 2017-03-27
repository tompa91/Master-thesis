#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.arm.elf.M3{1,0,16.9,0
#
ifeq (,$(MK_NOGENDEPS))
-include package/cfg/appBLE_UartLog_pem3.oem3.dep
package/cfg/appBLE_UartLog_pem3.oem3.dep: ;
endif

package/cfg/appBLE_UartLog_pem3.oem3: | .interfaces
package/cfg/appBLE_UartLog_pem3.oem3: package/cfg/appBLE_UartLog_pem3.c package/cfg/appBLE_UartLog_pem3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem3 $< ...
	$(ti.targets.arm.elf.M3.rootDir)/bin/armcl -c  -mv7M3 --code_state=16 -me -O4 --opt_for_speed=0 --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Profiles" --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Application" --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/ICallBLE" --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Startup" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/DevInfo" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/ProjectZero/CC26xx/Source/Application" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/uart_log" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/applib/heap" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/services/sdata" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/Roles/CC26xx" --include_path="C:/ti/tirex-content/tirtos_simplelink_2_13_00_06/products/cc26xxware_2_21_01_15600" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/controller/CC26xx/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/hci" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/host" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/target/CC2650TIRTOS" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/target/_common/cc26xx" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/icall/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/osal/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/services/saddr" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/ICall/Include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/Roles" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/common/cc26xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --define=CC26XX --define=CC26XXWARE --define=USE_ICALL --define=xdc_runtime_Assert_DISABLE_ALL --define=Xxdc_runtime_Log_DISABLE_ALL --define=POWER_SAVING --define=DEBUG --define=HEAPMGR_SIZE=3000 --define=ICALL_MAX_NUM_ENTITIES=6 --define=ICALL_RAM0_ADDR=0x200043E8 --define=ICALL_STACK0_ADDR=0x0000E000 --define=MAX_NUM_BLE_CONNS=1 --define=ccs --define=GAPROLE_TASK_STACK_SIZE=520 --define=ICALL_MAX_NUM_TASKS=3 --define=xdc_FILE="""" --define=UARTLOG_NUM_EVT_BUF=32 -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi   -qq -pdsw225 -ms --fp_mode=strict --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3   -Dxdc_cfg__xheader__='"configPkg/package/cfg/appBLE_UartLog_pem3.h"'  -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_16_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/cfg -fr=./package/cfg -fc $<
	$(MKDEP) -a $@.dep -p package/cfg -s oem3 $< -C   -mv7M3 --code_state=16 -me -O4 --opt_for_speed=0 --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Profiles" --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Application" --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/ICallBLE" --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Startup" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/DevInfo" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/ProjectZero/CC26xx/Source/Application" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/uart_log" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/applib/heap" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/services/sdata" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/Roles/CC26xx" --include_path="C:/ti/tirex-content/tirtos_simplelink_2_13_00_06/products/cc26xxware_2_21_01_15600" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/controller/CC26xx/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/hci" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/host" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/target/CC2650TIRTOS" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/target/_common/cc26xx" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/icall/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/osal/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/services/saddr" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/ICall/Include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/Roles" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/common/cc26xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --define=CC26XX --define=CC26XXWARE --define=USE_ICALL --define=xdc_runtime_Assert_DISABLE_ALL --define=Xxdc_runtime_Log_DISABLE_ALL --define=POWER_SAVING --define=DEBUG --define=HEAPMGR_SIZE=3000 --define=ICALL_MAX_NUM_ENTITIES=6 --define=ICALL_RAM0_ADDR=0x200043E8 --define=ICALL_STACK0_ADDR=0x0000E000 --define=MAX_NUM_BLE_CONNS=1 --define=ccs --define=GAPROLE_TASK_STACK_SIZE=520 --define=ICALL_MAX_NUM_TASKS=3 --define=xdc_FILE="""" --define=UARTLOG_NUM_EVT_BUF=32 -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi   -qq -pdsw225 -ms --fp_mode=strict --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3   -Dxdc_cfg__xheader__='"configPkg/package/cfg/appBLE_UartLog_pem3.h"'  -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_16_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/cfg -fr=./package/cfg
	-@$(FIXDEP) $@.dep $@.dep
	
package/cfg/appBLE_UartLog_pem3.oem3: export C_DIR=
package/cfg/appBLE_UartLog_pem3.oem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/;$(PATH)
package/cfg/appBLE_UartLog_pem3.oem3: Path:=$(ti.targets.arm.elf.M3.rootDir)/bin/;$(PATH)

package/cfg/appBLE_UartLog_pem3.sem3: | .interfaces
package/cfg/appBLE_UartLog_pem3.sem3: package/cfg/appBLE_UartLog_pem3.c package/cfg/appBLE_UartLog_pem3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem3 -n $< ...
	$(ti.targets.arm.elf.M3.rootDir)/bin/armcl -c -n -s --symdebug:none -mv7M3 --code_state=16 -me -O4 --opt_for_speed=0 --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Profiles" --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Application" --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/ICallBLE" --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Startup" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/DevInfo" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/ProjectZero/CC26xx/Source/Application" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/uart_log" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/applib/heap" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/services/sdata" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/Roles/CC26xx" --include_path="C:/ti/tirex-content/tirtos_simplelink_2_13_00_06/products/cc26xxware_2_21_01_15600" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/controller/CC26xx/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/hci" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/host" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/target/CC2650TIRTOS" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/target/_common/cc26xx" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/icall/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/osal/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/services/saddr" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/ICall/Include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/Roles" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/common/cc26xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --define=CC26XX --define=CC26XXWARE --define=USE_ICALL --define=xdc_runtime_Assert_DISABLE_ALL --define=Xxdc_runtime_Log_DISABLE_ALL --define=POWER_SAVING --define=DEBUG --define=HEAPMGR_SIZE=3000 --define=ICALL_MAX_NUM_ENTITIES=6 --define=ICALL_RAM0_ADDR=0x200043E8 --define=ICALL_STACK0_ADDR=0x0000E000 --define=MAX_NUM_BLE_CONNS=1 --define=ccs --define=GAPROLE_TASK_STACK_SIZE=520 --define=ICALL_MAX_NUM_TASKS=3 --define=xdc_FILE="""" --define=UARTLOG_NUM_EVT_BUF=32 -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi   -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3   -Dxdc_cfg__xheader__='"configPkg/package/cfg/appBLE_UartLog_pem3.h"'  -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_16_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/cfg -fr=./package/cfg -fc $<
	$(MKDEP) -a $@.dep -p package/cfg -s oem3 $< -C  -n -s --symdebug:none -mv7M3 --code_state=16 -me -O4 --opt_for_speed=0 --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Profiles" --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Application" --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/ICallBLE" --include_path="C:/Users/Tom/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Startup" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/DevInfo" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/ProjectZero/CC26xx/Source/Application" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/uart_log" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/applib/heap" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/services/sdata" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/Roles/CC26xx" --include_path="C:/ti/tirex-content/tirtos_simplelink_2_13_00_06/products/cc26xxware_2_21_01_15600" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/controller/CC26xx/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/hci" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/host" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/target/CC2650TIRTOS" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/target/_common/cc26xx" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/icall/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/osal/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/services/saddr" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/ICall/Include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/Roles" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/common/cc26xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --define=CC26XX --define=CC26XXWARE --define=USE_ICALL --define=xdc_runtime_Assert_DISABLE_ALL --define=Xxdc_runtime_Log_DISABLE_ALL --define=POWER_SAVING --define=DEBUG --define=HEAPMGR_SIZE=3000 --define=ICALL_MAX_NUM_ENTITIES=6 --define=ICALL_RAM0_ADDR=0x200043E8 --define=ICALL_STACK0_ADDR=0x0000E000 --define=MAX_NUM_BLE_CONNS=1 --define=ccs --define=GAPROLE_TASK_STACK_SIZE=520 --define=ICALL_MAX_NUM_TASKS=3 --define=xdc_FILE="""" --define=UARTLOG_NUM_EVT_BUF=32 -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi   -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3   -Dxdc_cfg__xheader__='"configPkg/package/cfg/appBLE_UartLog_pem3.h"'  -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_16_9_0 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/cfg -fr=./package/cfg
	-@$(FIXDEP) $@.dep $@.dep
	
package/cfg/appBLE_UartLog_pem3.sem3: export C_DIR=
package/cfg/appBLE_UartLog_pem3.sem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/;$(PATH)
package/cfg/appBLE_UartLog_pem3.sem3: Path:=$(ti.targets.arm.elf.M3.rootDir)/bin/;$(PATH)

clean,em3 ::
	-$(RM) package/cfg/appBLE_UartLog_pem3.oem3
	-$(RM) package/cfg/appBLE_UartLog_pem3.sem3

appBLE_UartLog.pem3: package/cfg/appBLE_UartLog_pem3.oem3 package/cfg/appBLE_UartLog_pem3.mak

clean::
	-$(RM) package/cfg/appBLE_UartLog_pem3.mak
