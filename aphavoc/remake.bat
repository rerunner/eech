@echo off
SET EECH_ROOTDIR=e:\Work\eech-new

	cd %EECH_ROOTDIR%\aphavoc

	del *.exe

	del *.lnk

	del *.pch
	
	del project.map
	
	del project.sym

	cd %EECH_ROOTDIR%\aphavoc\source

	del /s *.obj

	cd %EECH_ROOTDIR%\modules

	del /s *.obj

	cd %EECH_ROOTDIR%\aphavoc
