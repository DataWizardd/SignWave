# Microsoft Developer Studio Project File - Name="Spot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Spot - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Spot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Spot.mak" CFG="Spot - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Spot - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Spot - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Spot - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "C:\MIL\INCLUDE" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "MORE_MODEL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 milhost.lib milvga.lib mil.lib milmet.lib miltiff.lib /nologo /subsystem:windows /machine:I386 /libpath:"C:\mil\library\winnt\msc\dll"

!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "C:\MIL\INCLUDE" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "MORE_MODEL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 milhost.lib milvga.lib mil.lib milmet.lib miltiff.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"C:\mil\library\winnt\msc\dll"

!ENDIF 

# Begin Target

# Name "Spot - Win32 Release"
# Name "Spot - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Cdhmm.cpp
# End Source File
# Begin Source File

SOURCE=.\CFlist.cpp
# End Source File
# Begin Source File

SOURCE=.\Cfvec.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmatrix.cpp
# End Source File
# Begin Source File

SOURCE=.\Cmgvq.cpp
# End Source File
# Begin Source File

SOURCE=.\CMyMIL.cpp
# End Source File
# Begin Source File

SOURCE=.\Cstroke.cpp
# End Source File
# Begin Source File

SOURCE=.\Cvq.cpp
# End Source File
# Begin Source File

SOURCE=.\CVScore.cpp
# End Source File
# Begin Source File

SOURCE=.\DocMisc.cpp
# End Source File
# Begin Source File

SOURCE=.\DoHmm.cpp
# End Source File
# Begin Source File

SOURCE=.\GestureDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\GestureView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Makemeta.cpp
# End Source File
# Begin Source File

SOURCE=.\MyHand.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefixDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\Spot.cpp
# End Source File
# Begin Source File

SOURCE=.\Spot.rc

!IF  "$(CFG)" == "Spot - Win32 Release"

!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SpotDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SpotUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\SpotView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\utils.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Cdhmm.h
# End Source File
# Begin Source File

SOURCE=.\CFlist.h
# End Source File
# Begin Source File

SOURCE=.\Cfvec.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\Cmatrix.h
# End Source File
# Begin Source File

SOURCE=.\Cmgvq.h
# End Source File
# Begin Source File

SOURCE=.\CMyMIL.h
# End Source File
# Begin Source File

SOURCE=.\Cstroke.h
# End Source File
# Begin Source File

SOURCE=.\Cvq.h
# End Source File
# Begin Source File

SOURCE=.\CVScore.h
# End Source File
# Begin Source File

SOURCE=.\GestureDoc.h
# End Source File
# Begin Source File

SOURCE=.\GestureView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyHand.h
# End Source File
# Begin Source File

SOURCE=.\PrefixDlg.h
# End Source File
# Begin Source File

SOURCE=.\Spot.h
# End Source File
# Begin Source File

SOURCE=.\SpotDoc.h
# End Source File
# Begin Source File

SOURCE=.\SpotView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\utils.h
# End Source File
# Begin Source File

SOURCE=.\values.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Gesture.ico
# End Source File
# Begin Source File

SOURCE=.\res\Spot.ico
# End Source File
# Begin Source File

SOURCE=.\res\Spot.rc2
# End Source File
# Begin Source File

SOURCE=.\res\SpotDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
