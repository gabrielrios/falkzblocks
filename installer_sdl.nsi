;--------------------------------
;Include Modern UI

  !include "MUI.nsh"

;--------------------------------
;General

  ;Name and file
  Name "Falkz Blocks"
  OutFile "falkzblocks_installer.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\falkzblocks"

  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\falkzblocks" ""

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "LICENSE"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES

  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH
;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "falkzblocks" SecApp

  SetOutPath $INSTDIR\img
  File "img\*.*"
  SetOutPath $INSTDIR\data
  File "data\*.*"
  SetOutPath $INSTDIR
  File "bin\Release\*.*"
  FIle "C:\SDL\bin\*.dll"

  ;Store installation folder
  WriteRegStr HKCU "Software\falkzblocks" "" $INSTDIR

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  CreateShortCut "$INSTDIR\falkzblocks.lnk" "$INSTDIR\falkzblocks.exe"

  SetOutPath "$SMPROGRAMS\falkzblocks\"
  CopyFiles "$INSTDIR\falkzblocks.lnk" "$SMPROGRAMS\falkzblocks\"
  CopyFiles "$INSTDIR\falkzblocks.lnk" "$DESKTOP\"
  Delete "$INSTDIR\falkzblocks.lnk"
  CreateShortCut "$SMPROGRAMS\falkzblocks\Uninstall.lnk" "$INSTDIR\Uninstall.exe"

SectionEnd


;--------------------------------
;Uninstaller Section

Section "Uninstall"

  Delete "$INSTDIR\*.*"

  Delete "$DESKTOP\falkzblocks.lnk"
  Delete "$SMPROGRAMS\falkzblocks\falkzblocks.lnk"
  Delete "$SMPROGRAMS\falkzblocks\Uninstall.lnk"

  RMDir  "$SMPROGRAMS\falkzblocks\"

  RMDir /r "$INSTDIR\img\"
  RMDir /r "$INSTDIR\data\"


  RMDir "$INSTDIR"

  DeleteRegKey /ifempty HKCU "Software\falkzblocks"

SectionEnd
