# Microsoft Developer Studio Project File - Name="GameInput" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GameInput - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GameInput.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GameInput.mak" CFG="GameInput - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GameInput - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GameInput - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GameInput - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Distributes/GameInput.exe"

!ELSEIF  "$(CFG)" == "GameInput - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"Distributes/GameInput.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "GameInput - Win32 Release"
# Name "GameInput - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CaptureDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Includes\EditEx.cpp
# End Source File
# Begin Source File

SOURCE=.\GameData.cpp
# End Source File
# Begin Source File

SOURCE=.\GameDetailDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GameInput.cpp
# End Source File
# Begin Source File

SOURCE=.\GameInput.rc
# End Source File
# Begin Source File

SOURCE=.\GameManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Includes\HotKeyCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\HotkeyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Includes\Ini.cpp
# End Source File
# Begin Source File

SOURCE=.\Includes\InputSimulate.cpp
# End Source File
# Begin Source File

SOURCE=.\Includes\ListCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\NameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SchemeData.cpp
# End Source File
# Begin Source File

SOURCE=.\SchemeListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Includes\SystemTray.cpp
# End Source File
# Begin Source File

SOURCE=.\Includes\TrayFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Includes\WinAppEx.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Includes\ArrayEx.h
# End Source File
# Begin Source File

SOURCE=.\CaptureDlg.h
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditDlg.h
# End Source File
# Begin Source File

SOURCE=.\Includes\EditEx.h
# End Source File
# Begin Source File

SOURCE=.\GameData.h
# End Source File
# Begin Source File

SOURCE=.\GameDetailDlg.h
# End Source File
# Begin Source File

SOURCE=.\GameDlg.h
# End Source File
# Begin Source File

SOURCE=.\GameInput.h
# End Source File
# Begin Source File

SOURCE=.\GameManager.h
# End Source File
# Begin Source File

SOURCE=.\Includes\HotKeyCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\HotkeyDlg.h
# End Source File
# Begin Source File

SOURCE=.\Includes\Ini.h
# End Source File
# Begin Source File

SOURCE=.\Includes\InputSimulate.h
# End Source File
# Begin Source File

SOURCE=.\Includes\ListCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\NameDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SchemeData.h
# End Source File
# Begin Source File

SOURCE=.\SchemeListDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Includes\SystemTray.h
# End Source File
# Begin Source File

SOURCE=.\Includes\TrayFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\Includes\WinAppEx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\GameInput.ico
# End Source File
# Begin Source File

SOURCE=.\res\GameInput.rc2
# End Source File
# Begin Source File

SOURCE=.\res\tray.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
