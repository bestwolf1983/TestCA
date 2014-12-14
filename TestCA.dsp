# Microsoft Developer Studio Project File - Name="TestCA" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TestCA - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestCA.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestCA.mak" CFG="TestCA - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestCA - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TestCA - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestCA - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "TestCA - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TestCA - Win32 Release"
# Name "TestCA - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cell.cpp
# End Source File
# Begin Source File

SOURCE=.\changeable_cell.cpp
# End Source File
# Begin Source File

SOURCE=.\changeable_lane.cpp
# End Source File
# Begin Source File

SOURCE=.\Detector.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogRun.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCar.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgD.cpp
# End Source File
# Begin Source File

SOURCE=.\lane.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Saved_Cell.cpp
# End Source File
# Begin Source File

SOURCE=.\Saved_Lane.cpp
# End Source File
# Begin Source File

SOURCE=.\simworld.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Strategy.cpp
# End Source File
# Begin Source File

SOURCE=.\TestCA.cpp
# End Source File
# Begin Source File

SOURCE=.\TestCA.rc
# End Source File
# Begin Source File

SOURCE=.\TestCADoc.cpp
# End Source File
# Begin Source File

SOURCE=.\TestCAView.cpp
# End Source File
# Begin Source File

SOURCE=.\UIConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\Vehicle.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\cell.h
# End Source File
# Begin Source File

SOURCE=.\changeable_cell.h
# End Source File
# Begin Source File

SOURCE=.\changeable_lane.h
# End Source File
# Begin Source File

SOURCE=.\Detector.h
# End Source File
# Begin Source File

SOURCE=.\DialogRun.h
# End Source File
# Begin Source File

SOURCE=.\DlgCar.h
# End Source File
# Begin Source File

SOURCE=.\DlgD.h
# End Source File
# Begin Source File

SOURCE=.\DlgDistSet.h
# End Source File
# Begin Source File

SOURCE=.\DlgTimeSet.h
# End Source File
# Begin Source File

SOURCE=.\lane.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Saved_Cell.h
# End Source File
# Begin Source File

SOURCE=.\Saved_Lane.h
# End Source File
# Begin Source File

SOURCE=.\simworld.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Strategy.h
# End Source File
# Begin Source File

SOURCE=.\TestCA.h
# End Source File
# Begin Source File

SOURCE=.\TestCADoc.h
# End Source File
# Begin Source File

SOURCE=.\TestCAView.h
# End Source File
# Begin Source File

SOURCE=.\UIConfig.h
# End Source File
# Begin Source File

SOURCE=.\Vehicle.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TestCA.ico
# End Source File
# Begin Source File

SOURCE=.\res\TestCA.rc2
# End Source File
# Begin Source File

SOURCE=.\res\TestCADoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section TestCA : {72ADFD78-2C39-11D0-9903-00A0C91BC942}
# 	1:10:IDB_SPLASH:102
# 	2:21:SplashScreenInsertKey:4.0
# End Section
