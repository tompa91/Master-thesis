# invoke SourceDir generated makefile for appBLE_UartLog.pem3
appBLE_UartLog.pem3: .libraries,appBLE_UartLog.pem3
.libraries,appBLE_UartLog.pem3: package/cfg/appBLE_UartLog_pem3.xdl
	$(MAKE) -f C:\ti\tirex-content\simplelink\ble_cc26xx_2_01_00_44423_cloud\Projects\ble\ProjectZero\CC26xx\CCS\Config/src/makefile.libs

clean::
	$(MAKE) -f C:\ti\tirex-content\simplelink\ble_cc26xx_2_01_00_44423_cloud\Projects\ble\ProjectZero\CC26xx\CCS\Config/src/makefile.libs clean

