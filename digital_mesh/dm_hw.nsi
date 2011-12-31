; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "Dightal Mesh Homework"
!define PRODUCT_VERSION "1.3"
!define PRODUCT_PUBLISHER "Damody & peefly"
!define PRODUCT_WEB_SITE "http://code.google.com/p/dm-hw"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\hw1.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_STARTMENU_REGVAL "NSIS:StartMenuDir"

SetCompressor lzma

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "publish\feline.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Language Selection Dialog Settings
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "publish\NewBSD.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Start menu page
var ICONS_GROUP
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Dightal Mesh Homework"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_STARTMENU_REGVAL}"
!insertmacro MUI_PAGE_STARTMENU Application $ICONS_GROUP
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\hw1.exe"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "Japanese"
!insertmacro MUI_LANGUAGE "SimpChinese"
!insertmacro MUI_LANGUAGE "TradChinese"

; Reserve files
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "$PROGRAMFILES\Dightal Mesh Homework"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "publish\zlib1.dll"
  File "publish\uninstall.bat"
  File "publish\feline.ico"
  File "publish\ot12-OpenThreads.dll"
  File "publish\osg80-osgWidget.dll"
  File "publish\osg80-osgVolume.dll"
  File "publish\osg80-osgViewer.dll"
  File "publish\osg80-osgUtil.dll"
  File "publish\osg80-osgText.dll"
  File "publish\osg80-osgTerrain.dll"
  File "publish\osg80-osgSim.dll"
  File "publish\osg80-osgShadow.dll"
  File "publish\osg80-osgPresentation.dll"
  File "publish\osg80-osgParticle.dll"
  File "publish\osg80-osgManipulator.dll"
  File "publish\osg80-osgGA.dll"
  File "publish\osg80-osgFX.dll"
  File "publish\osg80-osgDB.dll"
  File "publish\osg80-osgd.dll"
  File "publish\osg80-osgAnimation.dll"
  File "publish\osg80-osg.dll"
  File "publish\NewBSD.txt"
  File "publish\libpng13.dll"
  File "publish\libexpat.dll"
  File "publish\Interop.digital_meshLib.dll"
  File "publish\install.bat"
  File "publish\hw1.exe"
  File "publish\glut32.dll"
  File "publish\gdal18.dll"
  File "publish\freetype6.dll"
  File "publish\digital_mesh.dll"

; Shortcuts
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  CreateDirectory "$SMPROGRAMS\$ICONS_GROUP"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Dightal Mesh Homework.lnk" "$INSTDIR\hw1.exe" """$INSTDIR\feline.ico"""
  CreateShortCut "$SMPROGRAMS\lic.lnk" "$INSTDIR\lic.exe"
  CreateShortCut "$DESKTOP\Dightal Mesh Homework.lnk" "$INSTDIR\hw1.exe" """$INSTDIR\feline.ico"""
  CreateShortCut "$DESKTOP\lic.lnk" "$INSTDIR\lic.exe"
  !insertmacro MUI_STARTMENU_WRITE_END
  Exec '$INSTDIR\install.bat'
SectionEnd

Section "LIC" SEC02
  File "publish\LIC.exe"

; Shortcuts
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -AdditionalIcons
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk" "$INSTDIR\uninst.exe"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\hw1.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\hw1.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地從你的電腦移除。"
FunctionEnd

Function un.onInit
!insertmacro MUI_UNGETLANGUAGE
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "你確定要完全移除 $(^Name) ，其及所有的元件？" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Exec '$INSTDIR\uninstall.bat'
  !insertmacro MUI_STARTMENU_GETFOLDER "Application" $ICONS_GROUP
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\LIC.exe"
  Delete "$INSTDIR\digital_mesh.dll"
  Delete "$INSTDIR\freetype6.dll"
  Delete "$INSTDIR\gdal18.dll"
  Delete "$INSTDIR\glut32.dll"
  Delete "$INSTDIR\hw1.exe"
  Delete "$INSTDIR\install.bat"
  Delete "$INSTDIR\feline.ico"
  Delete "$INSTDIR\Interop.digital_meshLib.dll"
  Delete "$INSTDIR\libexpat.dll"
  Delete "$INSTDIR\libpng13.dll"
  Delete "$INSTDIR\NewBSD.txt"
  Delete "$INSTDIR\osg80-osg.dll"
  Delete "$INSTDIR\osg80-osgAnimation.dll"
  Delete "$INSTDIR\osg80-osgd.dll"
  Delete "$INSTDIR\osg80-osgDB.dll"
  Delete "$INSTDIR\osg80-osgFX.dll"
  Delete "$INSTDIR\osg80-osgGA.dll"
  Delete "$INSTDIR\osg80-osgManipulator.dll"
  Delete "$INSTDIR\osg80-osgParticle.dll"
  Delete "$INSTDIR\osg80-osgPresentation.dll"
  Delete "$INSTDIR\osg80-osgShadow.dll"
  Delete "$INSTDIR\osg80-osgSim.dll"
  Delete "$INSTDIR\osg80-osgTerrain.dll"
  Delete "$INSTDIR\osg80-osgText.dll"
  Delete "$INSTDIR\osg80-osgUtil.dll"
  Delete "$INSTDIR\osg80-osgViewer.dll"
  Delete "$INSTDIR\osg80-osgVolume.dll"
  Delete "$INSTDIR\osg80-osgWidget.dll"
  Delete "$INSTDIR\ot12-OpenThreads.dll"
  Delete "$INSTDIR\uninstall.bat"
  Delete "$INSTDIR\zlib1.dll"

  Delete "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\Website.lnk"
  Delete "$DESKTOP\Dightal Mesh Homework.lnk"
  Delete "$DESKTOP\lic.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\Dightal Mesh Homework.lnk"
  Delete "$SMPROGRAMS\lic.lnk"

  RMDir "$SMPROGRAMS\$ICONS_GROUP"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd