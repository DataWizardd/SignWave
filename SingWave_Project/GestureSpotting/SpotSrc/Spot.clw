; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSpotApp
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Spot.h"
LastPage=0

ClassCount=8
Class1=CSpotApp
Class2=CSpotDoc
Class3=CSpotView
Class4=CMainFrame

ResourceCount=9
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_SPOTTYPE
Class5=CAboutDlg
Class6=CChildFrame
Resource4=IDD_ABOUTHMM (English (U.S.))
Resource5=IDD_ABOUTBOX (English (U.S.))
Resource6=IDR_GESTTYPE (English (U.S.))
Class7=CGestureDoc
Class8=CGestureView
Resource7=IDR_MAINFRAME (English (U.S.))
Resource8=IDD_PREFIXDLG
Resource9=IDR_SPOTTYPE (English (U.S.))

[CLS:CSpotApp]
Type=0
HeaderFile=Spot.h
ImplementationFile=Spot.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=IDM_SET_TRIANGLEDATA

[CLS:CSpotDoc]
Type=0
HeaderFile=SpotDoc.h
ImplementationFile=SpotDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=IDM_SET_ALPHADATA

[CLS:CSpotView]
Type=0
HeaderFile=SpotView.h
ImplementationFile=SpotView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=IDM_CHECK_FRAME_RATE

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M

[CLS:CAboutDlg]
Type=0
HeaderFile=Spot.cpp
ImplementationFile=Spot.cpp
Filter=D
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7
Command3=ID_FILE_MRU_FILE1

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=8
Command8=ID_APP_ABOUT

[MNU:IDR_SPOTTYPE]
Type=1
Class=CSpotView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_WINDOW_NEW
CommandCount=18
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command15=ID_WINDOW_CASCADE
Command16=ID_WINDOW_TILE_HORZ
Command17=ID_WINDOW_ARRANGE
Command18=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
CommandCount=13
Command4=ID_EDIT_UNDO
Command13=ID_PREV_PANE


[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Command1=IDM_EDIT_SAVE_STROKE
Command2=IDM_CLEAR_DISPLAY
Command3=IDM_PREV10_STROKE
Command4=IDM_PREV10_DUMP_FILE
Command5=IDM_NEXT10_STROKE
Command6=IDM_NEXT10_DUMP_FILE
Command7=IDM_EDIT_NEXT_STROKE
Command8=IDM_NEXT_DUMP_FILE
Command9=ID_FILE_OPEN
Command10=IDM_EDIT_PREV_STROKE
Command11=IDM_PREV_DUMP_FILE
Command12=ID_FILE_SAVE
Command13=IDM_DISPLAY_FRAME
Command14=IDM_START_CAPTURE
Command15=ID_NEXT_PANE
Command16=ID_PREV_PANE
CommandCount=16

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_SPOTTYPE (English (U.S.))]
Type=1
Class=CSpotView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=IDM_NEXT_DUMP_FILE
Command9=IDM_PREV_DUMP_FILE
Command10=IDM_NEXT10_DUMP_FILE
Command11=IDM_PREV10_DUMP_FILE
Command12=IDM_START_GRAB
Command13=IDM_FINISH_GRAB
Command14=IDM_COUNT_LABEL
Command15=IDM_SAVE_SNAP_FRAME
Command16=IDM_DISPLAY_FRAME
Command17=IDM_GEN_LASTDATA
Command18=IDM_GEN_FIRSTDATA
Command19=IDM_GEN_NEXTDATA
Command20=IDM_GEN_PREVDATA
Command21=IDM_GEN_QUITDATA
Command22=IDM_GEN_BYEDATA
Command23=IDM_GEN_CIRCLEDATA
Command24=IDM_GEN_TRIANGLEDATA
Command25=IDM_GEN_SAWDATA
Command26=IDM_GEN_ALPHADATA
Command27=IDM_GEN_THRESHOLDDATA
Command28=IDM_GEN_TESTDATA
Command29=IDM_GEN_CUR_FEATURE
Command30=IDM_GENERATE_ALL_FEATURE
Command31=IDM_RECOG_TEST_DATA
Command32=IDM_GEN_TEST_RESULT
Command33=IDM_SET_LASTDATA
Command34=IDM_SET_FIRSTDATA
Command35=IDM_SET_NEXTDATA
Command36=IDM_SET_PREVDATA
Command37=IDM_SET_QUITDATA
Command38=IDM_SET_BYEDATA
Command39=IDM_SET_CIRCLEDATA
Command40=IDM_SET_TRIANGLEDATA
Command41=IDM_SET_SAWDATA
Command42=IDM_SET_ALPHADATA
Command43=IDM_SET_THRESHOLDDATA
Command44=IDM_SET_TESTDATA
Command45=ID_DISP_CONTINUOUS
Command46=ID_DISP_BY_FRAME
Command47=IDM_TRACK_HAND
Command48=IDM_RECOG_HAND_GESTURE
Command49=IDM_CHECK_FRAME_RATE
Command50=IDM_DUMP_FRAME
Command51=ID_AUTOSAVE
Command52=IDM_LABELLING
Command53=ID_SHOW_GRAY
Command54=ID_GET_Y
Command55=ID_GET_I
Command56=ID_WINDOW_NEW
Command57=ID_WINDOW_CASCADE
Command58=ID_WINDOW_TILE_HORZ
Command59=ID_WINDOW_ARRANGE
Command60=ID_VIEW_STATUS_BAR
Command61=ID_VIEW_TOOLBAR
Command62=ID_APP_ABOUT
CommandCount=62

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_DISP_CONTINUOUS
Command5=ID_DISP_BY_FRAME
Command6=IDM_DUMP_FRAME
Command7=ID_AUTOSAVE
Command8=IDM_RECOG_HAND_GESTURE
Command9=IDM_START_GRAB
Command10=IDM_FINISH_GRAB
Command11=IDM_DISPLAY_FRAME
Command12=ID_APP_ABOUT
CommandCount=12

[CLS:CGestureDoc]
Type=0
HeaderFile=GestureDoc.h
ImplementationFile=GestureDoc.cpp
BaseClass=CDocument
Filter=N
LastObject=IDM_REDUCEDTHRESHOLD
VirtualFilter=DC

[CLS:CGestureView]
Type=0
HeaderFile=GestureView.h
ImplementationFile=GestureView.cpp
BaseClass=CView
Filter=C
LastObject=CGestureView

[MNU:IDR_GESTTYPE (English (U.S.))]
Type=1
Class=CGestureDoc
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=IDM_MAKE_LIST_FILE
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=IDM_INIT_MODEL
Command10=IDM_DO_ALL
Command11=ID_HMM_TRAIN
Command12=IDM_MODEL_LAST
Command13=IDM_MODEL_FIRST
Command14=IDM_MODEL_NEXT
Command15=IDM_MODEL_PREV
Command16=IDM_MODEL_QUIT
Command17=IDM_MODEL_BYE
Command18=IDM_MODEL_CIRCLE
Command19=IDM_MODEL_TRIANGLE
Command20=IDM_MODEL_SAW
Command21=IDM_MODEL_ALPHA
Command22=IDM_MODEL_THRESHOLD
Command23=IDM_MAKE_THRESHOLD_MODEL
Command24=IDM_UNITE_MODEL
Command25=IDM_TRAIN_THRESHOLD
Command26=IDM_LOAD_THRESHOLD_HMM
Command27=IDM_MAKE_NORMAL_VQ
Command28=IDM_LEARN_VQ
Command29=IDM_VECTOR_QUANTIZE
Command30=IDM_SINGLE_TRANS
Command31=IDM_ONLINE_TEST
Command32=ID_HMM_TEST
Command33=IDM_TEST_LAST
Command34=IDM_TEST_FIRST
Command35=IDM_TEST_NEXT
Command36=IDM_TEST_PREV
Command37=IDM_TEST_QUIT
Command38=IDM_TEST_BYE
Command39=IDM_TEST_CIRCLE
Command40=IDM_TEST_TRIANGLE
Command41=IDM_TEST_SAW
Command42=IDM_TEST_ALPHA
Command43=IDM_TEST_THRESHOLD
Command44=IDM_TEST_UNITED
Command45=IDM_TEST_TRAIN_DATA
Command46=IDM_IMMEDIATE_RECOG
Command47=IDM_SHOW_MATCH
Command48=IDM_SHOW_RECOGNITION
Command49=IDM_MAKE_METAFILE
Command50=IDM_START_CAPTURE
Command51=IDM_CLEAR_DISPLAY
Command52=IDM_EDIT_STROKE
Command53=IDM_EDIT_NEXT_STROKE
Command54=IDM_EDIT_PREV_STROKE
Command55=IDM_NEXT10_STROKE
Command56=IDM_PREV10_STROKE
Command57=IDM_EDIT_CHANGE_STROKE
Command58=IDM_EDIT_SAVE_STROKE
Command59=IDM_RESAVE_ALL
Command60=IDM_START_RECOGNIZE
Command61=ID_HMM_ASCII
Command62=IDM_REDUCEDTHRESHOLD
Command63=ID_WINDOW_NEW
Command64=ID_WINDOW_CASCADE
Command65=ID_WINDOW_TILE_HORZ
Command66=ID_WINDOW_ARRANGE
Command67=ID_VIEW_STATUS_BAR
Command68=ID_VIEW_TOOLBAR
Command69=ID_APP_ABOUT
CommandCount=69

[DLG:IDD_PREFIXDLG]
Type=1
ControlCount=6
Control1=IDC_PREFIX,edit,1350631552
Control2=IDC_NUMBER,edit,1350639744
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTHMM (English (U.S.))]
Type=1
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

