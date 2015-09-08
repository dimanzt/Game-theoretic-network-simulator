@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by MANET.HPJ. >"hlp\MANET.hm"
echo. >>"hlp\MANET.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\MANET.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\MANET.hm"
echo. >>"hlp\MANET.hm"
echo // Prompts (IDP_*) >>"hlp\MANET.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\MANET.hm"
echo. >>"hlp\MANET.hm"
echo // Resources (IDR_*) >>"hlp\MANET.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\MANET.hm"
echo. >>"hlp\MANET.hm"
echo // Dialogs (IDD_*) >>"hlp\MANET.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\MANET.hm"
echo. >>"hlp\MANET.hm"
echo // Frame Controls (IDW_*) >>"hlp\MANET.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\MANET.hm"
REM -- Make help for Project MANET


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\MANET.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\MANET.hlp" goto :Error
if not exist "hlp\MANET.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\MANET.hlp" Debug
if exist Debug\nul copy "hlp\MANET.cnt" Debug
if exist Release\nul copy "hlp\MANET.hlp" Release
if exist Release\nul copy "hlp\MANET.cnt" Release
echo.
goto :done

:Error
echo hlp\MANET.hpj(1) : error: Problem encountered creating help file

:done
echo.
