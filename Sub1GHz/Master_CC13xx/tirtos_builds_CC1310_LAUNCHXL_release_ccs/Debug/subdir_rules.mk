################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
build-1317695535:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-1317695535-inproc

build-1317695535-inproc: ../release.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"/opt/ti/xdctools_3_32_01_22_core/xs" --xdcpath="/home/mike/ti/tirex-content/simplelink_cc13x0_sdk_1_00_00_13/source;/home/mike/ti/tirex-content/simplelink_cc13x0_sdk_1_00_00_13/kernel/tirtos/packages;/opt/ti/ccsv7/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M3 -p ti.platforms.simplelink:CC1310F128 -r release -c "/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS" --compileOptions " -DDEVICE_FAMILY=cc13x0 " "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: build-1317695535
configPkg/compiler.opt: build-1317695535
configPkg/: build-1317695535


