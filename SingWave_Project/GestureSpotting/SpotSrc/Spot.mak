# Microsoft Developer Studio Generated NMAKE File, Based on Spot.dsp
!IF "$(CFG)" == ""
CFG=Spot - Win32 Release
!MESSAGE No configuration specified. Defaulting to Spot - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Spot - Win32 Release" && "$(CFG)" != "Spot - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Spot - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Spot.exe"

!ELSE 

ALL : "$(OUTDIR)\Spot.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Cdhmm.obj"
	-@erase "$(INTDIR)\CFlist.obj"
	-@erase "$(INTDIR)\Cfvec.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\Cmatrix.obj"
	-@erase "$(INTDIR)\Cmgvq.obj"
	-@erase "$(INTDIR)\CMyMIL.obj"
	-@erase "$(INTDIR)\Cstroke.obj"
	-@erase "$(INTDIR)\Cvq.obj"
	-@erase "$(INTDIR)\CVScore.obj"
	-@erase "$(INTDIR)\DocMisc.obj"
	-@erase "$(INTDIR)\DoHmm.obj"
	-@erase "$(INTDIR)\GestureDoc.obj"
	-@erase "$(INTDIR)\GestureView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Makemeta.obj"
	-@erase "$(INTDIR)\MyHand.obj"
	-@erase "$(INTDIR)\PrefixDlg.obj"
	-@erase "$(INTDIR)\Spot.obj"
	-@erase "$(INTDIR)\Spot.pch"
	-@erase "$(INTDIR)\Spot.res"
	-@erase "$(INTDIR)\SpotDoc.obj"
	-@erase "$(INTDIR)\SpotUtil.obj"
	-@erase "$(INTDIR)\SpotView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Spot.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "C:\MIL\INCLUDE" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "MORE_MODEL" /Fp"$(INTDIR)\Spot.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x412 /fo"$(INTDIR)\Spot.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Spot.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=milhost.lib milvga.lib mil.lib milmet.lib miltiff.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Spot.pdb" /machine:I386\
 /out:"$(OUTDIR)\Spot.exe" /libpath:"C:\mil\library\winnt\msc\dll" 
LINK32_OBJS= \
	"$(INTDIR)\Cdhmm.obj" \
	"$(INTDIR)\CFlist.obj" \
	"$(INTDIR)\Cfvec.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\Cmatrix.obj" \
	"$(INTDIR)\Cmgvq.obj" \
	"$(INTDIR)\CMyMIL.obj" \
	"$(INTDIR)\Cstroke.obj" \
	"$(INTDIR)\Cvq.obj" \
	"$(INTDIR)\CVScore.obj" \
	"$(INTDIR)\DocMisc.obj" \
	"$(INTDIR)\DoHmm.obj" \
	"$(INTDIR)\GestureDoc.obj" \
	"$(INTDIR)\GestureView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Makemeta.obj" \
	"$(INTDIR)\MyHand.obj" \
	"$(INTDIR)\PrefixDlg.obj" \
	"$(INTDIR)\Spot.obj" \
	"$(INTDIR)\Spot.res" \
	"$(INTDIR)\SpotDoc.obj" \
	"$(INTDIR)\SpotUtil.obj" \
	"$(INTDIR)\SpotView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\utils.obj"

"$(OUTDIR)\Spot.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Spot.exe"

!ELSE 

ALL : "$(OUTDIR)\Spot.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Cdhmm.obj"
	-@erase "$(INTDIR)\CFlist.obj"
	-@erase "$(INTDIR)\Cfvec.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\Cmatrix.obj"
	-@erase "$(INTDIR)\Cmgvq.obj"
	-@erase "$(INTDIR)\CMyMIL.obj"
	-@erase "$(INTDIR)\Cstroke.obj"
	-@erase "$(INTDIR)\Cvq.obj"
	-@erase "$(INTDIR)\CVScore.obj"
	-@erase "$(INTDIR)\DocMisc.obj"
	-@erase "$(INTDIR)\DoHmm.obj"
	-@erase "$(INTDIR)\GestureDoc.obj"
	-@erase "$(INTDIR)\GestureView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Makemeta.obj"
	-@erase "$(INTDIR)\MyHand.obj"
	-@erase "$(INTDIR)\PrefixDlg.obj"
	-@erase "$(INTDIR)\Spot.obj"
	-@erase "$(INTDIR)\Spot.pch"
	-@erase "$(INTDIR)\Spot.res"
	-@erase "$(INTDIR)\SpotDoc.obj"
	-@erase "$(INTDIR)\SpotUtil.obj"
	-@erase "$(INTDIR)\SpotView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Spot.exe"
	-@erase "$(OUTDIR)\Spot.ilk"
	-@erase "$(OUTDIR)\Spot.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "C:\MIL\INCLUDE" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "MORE_MODEL"\
 /Fp"$(INTDIR)\Spot.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x412 /fo"$(INTDIR)\Spot.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Spot.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=milhost.lib milvga.lib mil.lib milmet.lib miltiff.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Spot.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)\Spot.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Cdhmm.obj" \
	"$(INTDIR)\CFlist.obj" \
	"$(INTDIR)\Cfvec.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\Cmatrix.obj" \
	"$(INTDIR)\Cmgvq.obj" \
	"$(INTDIR)\CMyMIL.obj" \
	"$(INTDIR)\Cstroke.obj" \
	"$(INTDIR)\Cvq.obj" \
	"$(INTDIR)\CVScore.obj" \
	"$(INTDIR)\DocMisc.obj" \
	"$(INTDIR)\DoHmm.obj" \
	"$(INTDIR)\GestureDoc.obj" \
	"$(INTDIR)\GestureView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Makemeta.obj" \
	"$(INTDIR)\MyHand.obj" \
	"$(INTDIR)\PrefixDlg.obj" \
	"$(INTDIR)\Spot.obj" \
	"$(INTDIR)\Spot.res" \
	"$(INTDIR)\SpotDoc.obj" \
	"$(INTDIR)\SpotUtil.obj" \
	"$(INTDIR)\SpotView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\utils.obj"

"$(OUTDIR)\Spot.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "Spot - Win32 Release" || "$(CFG)" == "Spot - Win32 Debug"
SOURCE=.\Cdhmm.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_CDHMM=\
	".\Cdhmm.h"\
	".\Cstroke.h"\
	".\CVScore.h"\
	".\GestureDoc.h"\
	".\Spot.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Cdhmm.obj" : $(SOURCE) $(DEP_CPP_CDHMM) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_CDHMM=\
	".\Cdhmm.h"\
	".\Cstroke.h"\
	".\CVScore.h"\
	".\GestureDoc.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Cdhmm.obj" : $(SOURCE) $(DEP_CPP_CDHMM) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\CFlist.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_CFLIS=\
	".\CFlist.h"\
	".\Spot.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\CFlist.obj" : $(SOURCE) $(DEP_CPP_CFLIS) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_CFLIS=\
	".\CFlist.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\CFlist.obj" : $(SOURCE) $(DEP_CPP_CFLIS) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\Cfvec.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_CFVEC=\
	".\Cfvec.h"\
	".\Spot.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Cfvec.obj" : $(SOURCE) $(DEP_CPP_CFVEC) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_CFVEC=\
	".\Cfvec.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Cfvec.obj" : $(SOURCE) $(DEP_CPP_CFVEC) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_CHILD=\
	".\ChildFrm.h"\
	".\Spot.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_CHILD=\
	".\ChildFrm.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\Cmatrix.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_CMATR=\
	".\Cmatrix.h"\
	".\Spot.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Cmatrix.obj" : $(SOURCE) $(DEP_CPP_CMATR) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_CMATR=\
	".\Cmatrix.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Cmatrix.obj" : $(SOURCE) $(DEP_CPP_CMATR) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\Cmgvq.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_CMGVQ=\
	".\CFlist.h"\
	".\Cfvec.h"\
	".\Cmgvq.h"\
	".\Cvq.h"\
	".\Spot.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Cmgvq.obj" : $(SOURCE) $(DEP_CPP_CMGVQ) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_CMGVQ=\
	".\CFlist.h"\
	".\Cfvec.h"\
	".\Cmgvq.h"\
	".\Cvq.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Cmgvq.obj" : $(SOURCE) $(DEP_CPP_CMGVQ) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\CMyMIL.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_CMYMI=\
	".\CMyMIL.h"\
	".\Cstroke.h"\
	".\GestureDoc.h"\
	".\MyHand.h"\
	".\Spot.h"\
	".\SpotDoc.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\CMyMIL.obj" : $(SOURCE) $(DEP_CPP_CMYMI) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_CMYMI=\
	".\CMyMIL.h"\
	".\Cstroke.h"\
	".\GestureDoc.h"\
	".\MyHand.h"\
	".\Spot.h"\
	".\SpotDoc.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\CMyMIL.obj" : $(SOURCE) $(DEP_CPP_CMYMI) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\Cstroke.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_CSTRO=\
	".\CFlist.h"\
	".\Cfvec.h"\
	".\Cstroke.h"\
	".\GestureDoc.h"\
	".\PrefixDlg.h"\
	".\Spot.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Cstroke.obj" : $(SOURCE) $(DEP_CPP_CSTRO) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_CSTRO=\
	".\CFlist.h"\
	".\Cfvec.h"\
	".\Cstroke.h"\
	".\GestureDoc.h"\
	".\PrefixDlg.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Cstroke.obj" : $(SOURCE) $(DEP_CPP_CSTRO) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\Cvq.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_CVQ_C=\
	".\CFlist.h"\
	".\Cfvec.h"\
	".\Cvq.h"\
	".\Spot.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Cvq.obj" : $(SOURCE) $(DEP_CPP_CVQ_C) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_CVQ_C=\
	".\CFlist.h"\
	".\Cfvec.h"\
	".\Cvq.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Cvq.obj" : $(SOURCE) $(DEP_CPP_CVQ_C) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\CVScore.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_CVSCO=\
	".\Cdhmm.h"\
	".\Cstroke.h"\
	".\CVScore.h"\
	".\Spot.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\CVScore.obj" : $(SOURCE) $(DEP_CPP_CVSCO) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_CVSCO=\
	".\Cdhmm.h"\
	".\Cstroke.h"\
	".\CVScore.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\CVScore.obj" : $(SOURCE) $(DEP_CPP_CVSCO) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\DocMisc.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_DOCMI=\
	".\Cdhmm.h"\
	".\CFlist.h"\
	".\Cfvec.h"\
	".\Cmgvq.h"\
	".\Cvq.h"\
	".\GestureDoc.h"\
	".\Spot.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\DocMisc.obj" : $(SOURCE) $(DEP_CPP_DOCMI) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_DOCMI=\
	".\Cdhmm.h"\
	".\CFlist.h"\
	".\Cfvec.h"\
	".\Cmgvq.h"\
	".\Cvq.h"\
	".\GestureDoc.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\DocMisc.obj" : $(SOURCE) $(DEP_CPP_DOCMI) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\DoHmm.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_DOHMM=\
	".\Cdhmm.h"\
	".\CFlist.h"\
	".\Cfvec.h"\
	".\Cmgvq.h"\
	".\Cstroke.h"\
	".\Cvq.h"\
	".\CVScore.h"\
	".\GestureDoc.h"\
	".\GestureView.h"\
	".\Spot.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\DoHmm.obj" : $(SOURCE) $(DEP_CPP_DOHMM) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_DOHMM=\
	".\Cdhmm.h"\
	".\CFlist.h"\
	".\Cfvec.h"\
	".\Cmgvq.h"\
	".\Cstroke.h"\
	".\Cvq.h"\
	".\CVScore.h"\
	".\GestureDoc.h"\
	".\GestureView.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\DoHmm.obj" : $(SOURCE) $(DEP_CPP_DOHMM) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\GestureDoc.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_GESTU=\
	".\Cdhmm.h"\
	".\CFlist.h"\
	".\Cfvec.h"\
	".\Cmgvq.h"\
	".\Cvq.h"\
	".\CVScore.h"\
	".\GestureDoc.h"\
	".\GestureView.h"\
	".\Spot.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\GestureDoc.obj" : $(SOURCE) $(DEP_CPP_GESTU) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_GESTU=\
	".\Cdhmm.h"\
	".\CFlist.h"\
	".\Cfvec.h"\
	".\Cmgvq.h"\
	".\Cvq.h"\
	".\CVScore.h"\
	".\GestureDoc.h"\
	".\GestureView.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\GestureDoc.obj" : $(SOURCE) $(DEP_CPP_GESTU) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\GestureView.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_GESTUR=\
	".\Cdhmm.h"\
	".\CFlist.h"\
	".\Cfvec.h"\
	".\Cmgvq.h"\
	".\Cstroke.h"\
	".\Cvq.h"\
	".\GestureDoc.h"\
	".\GestureView.h"\
	".\Spot.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\GestureView.obj" : $(SOURCE) $(DEP_CPP_GESTUR) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_GESTUR=\
	".\Cdhmm.h"\
	".\CFlist.h"\
	".\Cfvec.h"\
	".\Cmgvq.h"\
	".\Cstroke.h"\
	".\Cvq.h"\
	".\GestureDoc.h"\
	".\GestureView.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\GestureView.obj" : $(SOURCE) $(DEP_CPP_GESTUR) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\Spot.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\Makemeta.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_MAKEM=\
	".\Spot.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Makemeta.obj" : $(SOURCE) $(DEP_CPP_MAKEM) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_MAKEM=\
	".\Spot.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Makemeta.obj" : $(SOURCE) $(DEP_CPP_MAKEM) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\MyHand.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_MYHAN=\
	".\CMyMIL.h"\
	".\Cstroke.h"\
	".\MyHand.h"\
	".\Spot.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\MyHand.obj" : $(SOURCE) $(DEP_CPP_MYHAN) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_MYHAN=\
	".\CMyMIL.h"\
	".\Cstroke.h"\
	".\MyHand.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	{$(INCLUDE)}"sys\timeb.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\MyHand.obj" : $(SOURCE) $(DEP_CPP_MYHAN) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\PrefixDlg.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_PREFI=\
	".\PrefixDlg.h"\
	".\Spot.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\PrefixDlg.obj" : $(SOURCE) $(DEP_CPP_PREFI) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_PREFI=\
	".\PrefixDlg.h"\
	".\Spot.h"\
	".\StdAfx.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\PrefixDlg.obj" : $(SOURCE) $(DEP_CPP_PREFI) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\Spot.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_SPOT_=\
	".\ChildFrm.h"\
	".\CMyMIL.h"\
	".\GestureDoc.h"\
	".\GestureView.h"\
	".\MainFrm.h"\
	".\MyHand.h"\
	".\Spot.h"\
	".\SpotDoc.h"\
	".\SpotView.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Spot.obj" : $(SOURCE) $(DEP_CPP_SPOT_) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_SPOT_=\
	".\ChildFrm.h"\
	".\CMyMIL.h"\
	".\GestureDoc.h"\
	".\GestureView.h"\
	".\MainFrm.h"\
	".\MyHand.h"\
	".\Spot.h"\
	".\SpotDoc.h"\
	".\SpotView.h"\
	".\StdAfx.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\Spot.obj" : $(SOURCE) $(DEP_CPP_SPOT_) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\Spot.rc
DEP_RSC_SPOT_R=\
	".\res\Gesture.ico"\
	".\res\Spot.ico"\
	".\res\Spot.rc2"\
	".\res\SpotDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\Spot.res" : $(SOURCE) $(DEP_RSC_SPOT_R) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\SpotDoc.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_SPOTD=\
	".\CMyMIL.h"\
	".\MyHand.h"\
	".\Spot.h"\
	".\SpotDoc.h"\
	".\SpotView.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\SpotDoc.obj" : $(SOURCE) $(DEP_CPP_SPOTD) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_SPOTD=\
	".\CMyMIL.h"\
	".\MyHand.h"\
	".\Spot.h"\
	".\SpotDoc.h"\
	".\SpotView.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\SpotDoc.obj" : $(SOURCE) $(DEP_CPP_SPOTD) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\SpotUtil.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_SPOTU=\
	".\Spot.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\SpotUtil.obj" : $(SOURCE) $(DEP_CPP_SPOTU) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_SPOTU=\
	".\Spot.h"\
	".\StdAfx.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\SpotUtil.obj" : $(SOURCE) $(DEP_CPP_SPOTU) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\SpotView.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_SPOTV=\
	".\CMyMIL.h"\
	".\Cstroke.h"\
	".\GestureDoc.h"\
	".\MyHand.h"\
	".\Spot.h"\
	".\SpotDoc.h"\
	".\SpotView.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\SpotView.obj" : $(SOURCE) $(DEP_CPP_SPOTV) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_SPOTV=\
	".\CMyMIL.h"\
	".\Cstroke.h"\
	".\GestureDoc.h"\
	".\MyHand.h"\
	".\Spot.h"\
	".\SpotDoc.h"\
	".\SpotView.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\SpotView.obj" : $(SOURCE) $(DEP_CPP_SPOTV) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Spot - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "C:\MIL\INCLUDE" /D "NDEBUG" /D "WIN32"\
 /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "MORE_MODEL" /Fp"$(INTDIR)\Spot.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Spot.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "C:\MIL\INCLUDE" /D "_DEBUG"\
 /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "MORE_MODEL"\
 /Fp"$(INTDIR)\Spot.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Spot.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\utils.cpp

!IF  "$(CFG)" == "Spot - Win32 Release"

DEP_CPP_UTILS=\
	".\CMyMIL.h"\
	".\GestureDoc.h"\
	".\GestureView.h"\
	".\Spot.h"\
	".\SpotDoc.h"\
	".\SpotView.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	

"$(INTDIR)\utils.obj" : $(SOURCE) $(DEP_CPP_UTILS) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ELSEIF  "$(CFG)" == "Spot - Win32 Debug"

DEP_CPP_UTILS=\
	".\CMyMIL.h"\
	".\GestureDoc.h"\
	".\GestureView.h"\
	".\Spot.h"\
	".\SpotDoc.h"\
	".\SpotView.h"\
	".\StdAfx.h"\
	".\utils.h"\
	".\values.h"\
	"c:\mil\include\meteor.h"\
	"c:\mil\include\mil.h"\
	"c:\mil\include\mildec.h"\
	"c:\mil\include\milerr.h"\
	"c:\mil\include\milnat.h"\
	"c:\mil\include\milproto.h"\
	"c:\mil\include\milsetup.h"\
	"c:\mil\include\mwinmil.h"\
	{$(INCLUDE)}"sys\timeb.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\utils.obj" : $(SOURCE) $(DEP_CPP_UTILS) "$(INTDIR)"\
 "$(INTDIR)\Spot.pch"


!ENDIF 


!ENDIF 

