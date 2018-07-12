;NSIS Modern User Interface
;Repeater install script
;Written by Jonathan Naylor

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;Configuration

  ;General
  Name "ircDDB Gateway 20180627"
  OutFile "ircDDBGateway64-20180627.exe"

  ;Folder selection page
  InstallDir "$PROGRAMFILES64\ircDDBGateway"
 
   ;Request application privileges for Windows Vista
  RequestExecutionLevel admin
 
;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "COPYING.txt"
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Repeater Program Files" SecProgram

  SetOutPath "$INSTDIR"
  
  File "x64\Release\ircDDBGateway.exe"
  File "x64\Release\ircDDBGatewayConfig.exe"
  File "x64\Release\RemoteControl.exe"
  File "x64\Release\StarNetServer.exe"
  File "x64\Release\TextTransmit.exe"
  File "x64\Release\TimerControl.exe"
  File "x64\Release\TimeServer.exe"
  File "x64\Release\VoiceTransmit.exe"
  File "C:\wxWidgets-3.0.4\lib\vc_x64_dll\wxbase30u_vc_x64_custom.dll"
  File "C:\wxWidgets-3.0.4\lib\vc_x64_dll\wxmsw30u_adv_vc_x64_custom.dll"
  File "C:\wxWidgets-3.0.4\lib\vc_x64_dll\wxmsw30u_core_vc_x64_custom.dll"
  File "CHANGES.txt"
  File "COPYING.txt"
  File "Data\CCS_Hosts.txt"
  File "Data\DCS_Hosts.txt"
  File "Data\DExtra_Hosts.txt"
  File "Data\DPlus_Hosts.txt"
  File "Data\TIME_de_DE.ambe"
  File "Data\TIME_de_DE.indx"
  File "Data\TIME_en_GB.ambe"
  File "Data\TIME_en_GB.indx"
  File "Data\TIME_en_US.ambe"
  File "Data\TIME_en_US.indx"
  File "Data\TIME_fr_FR.ambe"
  File "Data\TIME_fr_FR.indx"
  File "Data\TIME_se_SE.ambe"
  File "Data\TIME_se_SE.indx"
  File "Data\de_DE.ambe"
  File "Data\de_DE.indx"
  File "Data\dk_DK.ambe"
  File "Data\dk_DK.indx"
  File "Data\en_GB.ambe"
  File "Data\en_GB.indx"
  File "Data\en_US.ambe"
  File "Data\en_US.indx"
  File "Data\es_ES.ambe"
  File "Data\es_ES.indx"
  File "Data\fr_FR.ambe"
  File "Data\fr_FR.indx"
  File "Data\it_IT.ambe"
  File "Data\it_IT.indx"
  File "Data\no_NO.ambe"
  File "Data\no_NO.indx"
  File "Data\pl_PL.ambe"
  File "Data\pl_PL.indx"
  File "Data\se_SE.ambe"
  File "Data\se_SE.indx"

  ;Create start menu entry
  CreateDirectory "$SMPROGRAMS\ircDDBGateway"
  CreateShortCut "$SMPROGRAMS\ircDDBGateway\ircDDB Gateway.lnk"        "$INSTDIR\ircDDBGateway.exe"
  CreateShortCut "$SMPROGRAMS\ircDDBGateway\ircDDB Gateway Config.lnk" "$INSTDIR\ircDDBGatewayConfig.exe"
  CreateShortCut "$SMPROGRAMS\ircDDBGateway\Remote Control.lnk"        "$INSTDIR\RemoteControl.exe"
  CreateShortCut "$SMPROGRAMS\ircDDBGateway\StarNet Server.lnk"        "$INSTDIR\StarNetServer.exe"
  CreateShortCut "$SMPROGRAMS\ircDDBGateway\Timer Control.lnk"         "$INSTDIR\TimerControl.exe"
  CreateShortCut "$SMPROGRAMS\ircDDBGateway\Time Server.lnk"           "$INSTDIR\TimeServer.exe"
  CreateShortCut "$SMPROGRAMS\ircDDBGateway\Changes.lnk"               "$INSTDIR\CHANGES.txt"
  CreateShortCut "$SMPROGRAMS\ircDDBGateway\Licence.lnk"               "$INSTDIR\COPYING.txt"
  CreateShortCut "$SMPROGRAMS\ircDDBGateway\Uninstall.lnk"             "$INSTDIR\Uninstall.exe"

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  Delete "$INSTDIR\*.*"
  RMDir  "$INSTDIR"

  Delete "$SMPROGRAMS\ircDDBGateway\*.*"
  RMDir  "$SMPROGRAMS\ircDDBGateway"

  DeleteRegKey /ifempty HKCU "Software\G4KLX\IRCDDB Gateway"
  DeleteRegKey /ifempty HKCU "Software\G4KLX\Remote Control"
  DeleteRegKey /ifempty HKCU "Software\G4KLX\StarNet Server"
  DeleteRegKey /ifempty HKCU "Software\G4KLX\Timer Control"
  DeleteRegKey /ifempty HKCU "Software\G4KLX\Time Server"

SectionEnd
