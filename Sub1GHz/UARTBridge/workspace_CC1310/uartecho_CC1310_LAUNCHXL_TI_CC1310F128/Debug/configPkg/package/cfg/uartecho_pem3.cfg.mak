# invoke SourceDir generated makefile for uartecho.pem3
uartecho.pem3: .libraries,uartecho.pem3
.libraries,uartecho.pem3: package/cfg/uartecho_pem3.xdl
	$(MAKE) -f C:\Users\Tom\workspace_v7_27\uartecho_CC1310_LAUNCHXL_TI_CC1310F128/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\Tom\workspace_v7_27\uartecho_CC1310_LAUNCHXL_TI_CC1310F128/src/makefile.libs clean

