################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Utils/uart_logs.obj: C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/uart_log/uart_logs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M3 --code_state=16 -me -O3 --opt_for_speed=0 --include_path="C:/Users/Tom/test3/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Profiles" --include_path="C:/Users/Tom/test3/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Application" --include_path="C:/Users/Tom/test3/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/ICallBLE" --include_path="C:/Users/Tom/test3/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Startup" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/DevInfo" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/ProjectZero/CC26xx/Source/Application" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/uart_log" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/applib/heap" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/services/sdata" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/Roles/CC26xx" --include_path="C:/ti/tirex-content/tirtos_simplelink_2_13_00_06/products/cc26xxware_2_21_01_15600" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/controller/CC26xx/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/hci" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/host" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/target/CC2650TIRTOS" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/target/_common/cc26xx" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/icall/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/osal/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/services/saddr" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/ICall/Include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/Roles" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/common/cc26xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --define=CC26XX --define=CC26XXWARE --define=USE_ICALL --define=xdc_runtime_Assert_DISABLE_ALL --define=Xxdc_runtime_Log_DISABLE_ALL --define=POWER_SAVING --define=DEBUG --define=HEAPMGR_SIZE=3000 --define=ICALL_MAX_NUM_ENTITIES=6 --define=ICALL_RAM0_ADDR=0x200043E8 --define=ICALL_STACK0_ADDR=0x0000E000 --define=MAX_NUM_BLE_CONNS=1 --define=ccs --define=GAPROLE_TASK_STACK_SIZE=520 --define=ICALL_MAX_NUM_TASKS=3 --define=xdc_FILE="\"uart_logs.c\"" --define=UARTLOG_NUM_EVT_BUF=32 -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="Utils/uart_logs.d" --obj_directory="Utils" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Utils/util.obj: C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/common/cc26xx/util.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M3 --code_state=16 -me -O3 --opt_for_speed=0 --include_path="C:/Users/Tom/test3/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Profiles" --include_path="C:/Users/Tom/test3/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Application" --include_path="C:/Users/Tom/test3/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/ICallBLE" --include_path="C:/Users/Tom/test3/workspace_v7_17/ProjectZeroApp_CC2650LAUNCHXL/Startup" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/DevInfo" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/ProjectZero/CC26xx/Source/Application" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/uart_log" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/applib/heap" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/services/sdata" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/Roles/CC26xx" --include_path="C:/ti/tirex-content/tirtos_simplelink_2_13_00_06/products/cc26xxware_2_21_01_15600" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/controller/CC26xx/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/hci" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/host" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/ble/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/target/CC2650TIRTOS" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/hal/target/_common/cc26xx" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/icall/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/osal/include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Components/services/saddr" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/ICall/Include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Include" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/Profiles/Roles" --include_path="C:/ti/tirex-content/simplelink/ble_cc26xx_2_01_00_44423_cloud/Projects/ble/common/cc26xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --define=CC26XX --define=CC26XXWARE --define=USE_ICALL --define=xdc_runtime_Assert_DISABLE_ALL --define=Xxdc_runtime_Log_DISABLE_ALL --define=POWER_SAVING --define=DEBUG --define=HEAPMGR_SIZE=3000 --define=ICALL_MAX_NUM_ENTITIES=6 --define=ICALL_RAM0_ADDR=0x200043E8 --define=ICALL_STACK0_ADDR=0x0000E000 --define=MAX_NUM_BLE_CONNS=1 --define=ccs --define=GAPROLE_TASK_STACK_SIZE=520 --define=ICALL_MAX_NUM_TASKS=3 --define=xdc_FILE="\"util.c\"" --define=UARTLOG_NUM_EVT_BUF=32 -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="Utils/util.d" --obj_directory="Utils" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


