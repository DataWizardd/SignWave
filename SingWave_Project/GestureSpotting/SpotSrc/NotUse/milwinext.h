/***************************************************************************/
/*

    Filename:  MWINEXT.H
    Owner   :  Matrox Imaging dept.
    Rev     :  $Revision:   1.0  $
    Content :  This file contains the defines necessary to use the
               Matrox Imaging Library (MIL) VGA extention

    COPYRIGHT (c) 1993  Matrox Electronic Systems Ltd.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MWINEXT_H
#define __MWINEXT_H

/**************************************************************************/
/* VGA SPECIFIC FUNCTION SET                                              */
/**************************************************************************/


#if !defined(__MIL_H) || !defined(WINVER)

 #error 'mil.h' and 'windows.h' must be included before 'mwinext.h'.

#else

 /* C++ directive if needed */
 #ifdef __cplusplus
 extern "C"
 {
 #endif

 /* Defines for the ModificationType of the hook function */
 #define M_NOT_MODIFIED                0 /* No changed at all              */
 #define M_MODIFIED_LUT                1 /* Disp lut is changed            */
 #define M_MODIFIED_DIB                2 /* Disp buffer data is changed    */
 #define M_MODIFIED_ZOOM               3 /* Disp is zoomed                 */
 #define M_MODIFIED_PAN                4 /* Disp is panned                 */
 #define M_MODIFIED_DIB_CREATION       5 /* Disp receives a new buffer ID  */
 #define M_MODIFIED_DIB_DESTRUCTION    6 /* Disp receives a buffer ID 0    */
 #define M_MODIFIED_WINDOW_CREATION    7 /* Wnd is created                 */
 #define M_MODIFIED_WINDOW_DESTRUCTION 8 /* Wnd is destroyed               */
 #define M_MODIFIED_WINDOW_LOCATION    9 /* Wnd size is changed            */
 #define M_MODIFIED_WINDOW_OVERLAP    11 /* Wnd overlap is changed         */
 #define M_MODIFIED_WINDOW_ICONIZED   12 /* Wnd is changed to iconic state */
 #define M_MODIFIED_WINDOW_ZOOM       13 /* Wnd is zoomed                  */
 #define M_MODIFIED_WINDOW_PAN        14 /* Wnd is panned                  */
 #define M_MODIFIED_WINDOW_MENU       15 /* Wnd menu pulled-down           */
 #define M_MODIFIED_WINDOW_PAINT      16 /* Wnd is painted with image      */
 #define M_MODIFIED_WINDOW_ACTIVE     17 /* Wnd activation state changed   */
 #define M_MODIFIED_WINDOW_ENABLE     18 /* Wnd enable state changed       */

 /* M_MODIFIED_WINDOW_MENU hook defines */
 #define M_MODIFIED_SYS_MENU             0x100
 #define M_MODIFIED_APP_MENU             0x200
 #define M_MODIFIED_USER_APP_MENU      0x10000L 
 #define M_MODIFIED_RESTORE_MENUITEM       0x1
 #define M_MODIFIED_MOVE_MENUITEM          0x2
 #define M_MODIFIED_SIZE_MENUITEM          0x3
 #define M_MODIFIED_MINIMIZE_MENUITEM      0x4
 #define M_MODIFIED_MAXIMIZE_MENUITEM      0x5
 #define M_MODIFIED_CLOSE_MENUITEM         0x6
 #define M_MODIFIED_TASKLIST_MENUITEM      0x7
 #define M_MODIFIED_MENUBAR_MENUITEM       0x8
 #define M_MODIFIED_TITLEOFF_MENUITEM      0x9
 #define M_MODIFIED_ZOOMIN_MENUITEM        0xA
 #define M_MODIFIED_ZOOMOUT_MENUITEM       0xB
 #define M_MODIFIED_NOZOOM_MENUITEM        0xC

 /* M_MODIFIED_WINDOW_ACTIVE & M_MODIFIED_WINDOW_ENABLE hook defines */
 #define M_MODIFIED_STATE_FROM_WINDOW   0x00000000
 #define M_MODIFIED_STATE_FROM_PARENT   0x00000010
 #define M_MODIFIED_OFF                 0x00000000
 #define M_MODIFIED_ON                  0x00000001

 /* MvgaDispControl() */
 #define M_DISP_WINDOW_CONTROL_ERROR               -1
 #define M_DISP_WINDOW_ZOOM                        1
 #define M_DISP_WINDOW_RESIZE                      2
 #define M_DISP_WINDOW_OVERLAP                     3
 #define M_DISP_WINDOW_SCROLLBAR                   4
 #define M_DISP_WINDOW_UPDATE                      5
 #define M_DISP_WINDOW_PROTECT_AREA                6
 #define M_DISP_WINDOW_TITLE_BAR                   7
 #define M_DISP_WINDOW_MENU_BAR                    8
 #define M_DISP_WINDOW_CHANGE_TITLE_BAR            9
 #define M_DISP_WINDOW_CHANGE_MENU_BAR             10
 #define M_DISP_WINDOW_MOVE                        11
 #define M_DISP_WINDOW_SYSBUTTON                   12
 #define M_DISP_WINDOW_MINBUTTON                   13
 #define M_DISP_WINDOW_MAXBUTTON                   14
 #define M_DISP_WINDOW_COLOR                       15
 #define M_DISP_WINDOW_CHANGE_COLOR                16
 #define M_DISP_WINDOW_PALETTE                     17
 #define M_DISP_WINDOW_PALETTE_WINDOWS             18
 #define M_DISP_WINDOW_PALETTE_NOCOLLAPSE          19
 #define M_DISP_WINDOW_PALETTE_BACKGROUND          20
 #define M_DISP_WINDOW_PALETTE_AUTO                21
 #define M_DISP_WINDOW_ERASE_BACKGROUND            22
 #define M_DISP_WINDOW_AUTO_UPDATE                 23
 #define M_DISP_WINDOW_UPDATE_WITH_MESSAGE         24
 #define M_DISP_WINDOW_SNAP_X                      25
 #define M_DISP_WINDOW_SNAP_Y                      26
 #define M_DISP_WINDOW_UPDATE_REGION               27
 #define M_DISP_WINDOW_UPDATE_ONLY_INVALID_BORDER  28 
 #define M_DISP_WINDOW_UPDATE_KEEP_PALETTE_ALIVE   29
 #define M_DISP_WINDOW_UPDATE_USE_BEGINPAINT       30
 #define M_DISP_WINDOW_UPDATE_USE_ERASEBKGND       31
 #define M_DISP_WINDOW_MANUAL_UPDATE               32
 #define M_DISP_WINDOW_DO_PAINT                    33
 #define M_DISP_WINDOW_ACTIVATE_DELAY              34

 #define M_FULL_SIZE                      0
 #define M_NORMAL_SIZE                    1

 /* MvgaDispInquire() */
 /* These defines must be exclusive with 'mil.h' MdispInquire defines */
 /* Also all MvgaDispControl() defines are valid for the inquire      */
 #define M_DISP_WINDOW_HANDLE                  214L
 #define M_DISP_WINDOW_OFFSET_X                215L
 #define M_DISP_WINDOW_OFFSET_Y                216L
 #define M_DISP_WINDOW_SIZE_X                  217L
 #define M_DISP_WINDOW_SIZE_Y                  218L
 #define M_DISP_WINDOW_PAN_X                   219L
 #define M_DISP_WINDOW_PAN_Y                   220L
 #define M_DISP_WINDOW_ZOOM_X                  221L
 #define M_DISP_WINDOW_ZOOM_Y                  222L
 #define M_DISP_WINDOW_TITLE_NAME              223L
 #define M_DISP_HOOK_MODIFIED_DIB_PTR          230L
 #define M_DISP_HOOK_MODIFIED_DIB_USER_PTR     234L
 #define M_DISP_HOOK_MODIFIED_WINDOW_PTR       240L
 #define M_DISP_HOOK_MODIFIED_WINDOW_USER_PTR  244L
 #define M_DISP_WINDOW_APPFRAME_HANDLE         248L
 #define M_DISP_WINDOW_MDICLIENT_HANDLE        250L
 #define M_DISP_WINDOW_MDIFRAME_HANDLE         252L
 #define M_DISP_VISIBLE_OFFSET_X               260L
 #define M_DISP_VISIBLE_OFFSET_Y               262L
 #define M_DISP_VISIBLE_SIZE_X                 264L
 #define M_DISP_VISIBLE_SIZE_Y                 266L
 #define M_DISP_WINDOW_DIB_HANDLE              267L
 #define M_DISP_WINDOW_DISPLAY_DIB_HANDLE      268L
 #define M_DISP_WINDOW_ACTIVE                  269L
 #define M_DISP_WINDOW_ENABLE                  270L
 #define M_DISP_HOOK_MESSAGE_LOOP_PTR          271L
 #define M_DISP_HOOK_MESSAGE_LOOP_USER_PTR     272L
 #define M_DISP_PALETTE_HANDLE                 273L

 /* Defines for the HookTypeFlag of the hook function */
 /* These defines are bit encoded */

  /* For buffer DIB modification  */
  #define M_HOOK_MODIFIED_DIB     0x00000010
  /* For disp window modification */
  #define M_HOOK_MODIFIED_WINDOW  0x00000020
  /* For disp window modification */
  #define M_HOOK_MESSAGE_LOOP     0x00000040
  /* For hook after modification  */
  #define M_HOOK_AFTER            0x00000001
  /* For hook before modification */
  #define M_HOOK_BEFORE           0x00000002


 typedef struct
 {
 LPBITMAPINFO DIBHeaderPtr;          /* pointer to the DIB header          */
 UINT         DIBColorUse;           /* color usage of DIB header          */
 LPSTR        DIBDataPtr;            /* pointer to the DIB data            */
 LPLOGPALETTE DIBPalettePtr;         /* pointer to the DIB palette         */
 HPALETTE     DIBPaletteHdl;         /* handle to the DIB palette          */
 HBITMAP      DIBBitmapHdl;          /* handle to DIB bitmap               */
 LPBITMAPINFO DIBDisplayHeaderPtr;   /* pointer to the display DIB header  */
 UINT         DIBDisplayColorUse;    /* color usage of display DIB header  */
 LPSTR        DIBDisplayDataPtr;     /* pointer to the display DIB data    */
 LPLOGPALETTE DIBDisplayPalettePtr;  /* pointer to the display DIB palette */
 HPALETTE     DIBDisplayPaletteHdl;  /* handle to the display DIB palette  */
 HBITMAP      DIBDisplayBitmapHdl;   /* handle to the display DIB bitmap   */
 MIL_ID       MilVgaBufferId;        /* MIL ID of the MIL VGA buffer       */
 MIL_ID       MilVgaDisplayId;       /* MIL ID of the MIL VGA display      */
 long         VgaDriverBufferId;     /* Reserved                           */
 long         VgaDriverDisplayId;    /* Reserved                           */
 long         VgaDriverSystemId;     /* Reserved                           */
 long         ModificationHookType;  /* Type of hook on modification       */
 long         ModificationType;      /* Type of modification to buffer     */
 long         ModificationOffsetX;   /* Offset x of modification in buffer */
 long         ModificationOffsetY;   /* Offset y of modification in buffer */
 long         ModificationSizeX;     /* Size x of modification in buffer   */
 long         ModificationSizeY;     /* Size y of modification in buffer   */
 long         ModificationZoomX;     /* Zoom x of modification in buffer   */
 long         ModificationZoomY;     /* Zoom y of modification in buffer   */
 long         ModificationPanX;      /* Pan x of modification in buffer    */
 long         ModificationPanY;      /* Pan y of modification in buffer    */
 LPVOID       ExpansionPtr;          /* Reserved                           */
 } M_DIB_INFO;

 typedef struct
 {
 HWND         WindowHandle;          /* Window hdl associated to display   */
 LPBITMAPINFO DIBHeaderPtr;          /* pointer to the DIB header          */
 UINT         DIBColorUse;           /* color usage of DIB header          */
 LPSTR        DIBDataPtr;            /* pointer to the DIB data            */
 LPLOGPALETTE DIBPalettePtr;         /* pointer to the DIB palette         */
 HPALETTE     DIBPaletteHdl;         /* handle to the DIB palette          */
 HBITMAP      DIBBitmapHdl;          /* handle to DIB bitmap               */
 LPBITMAPINFO DIBDisplayHeaderPtr;   /* pointer to the display DIB header  */
 UINT         DIBDisplayColorUse;    /* color usage of display DIB header  */
 LPSTR        DIBDisplayDataPtr;     /* pointer to the display DIB data    */
 LPLOGPALETTE DIBDisplayPalettePtr;  /* pointer to the display DIB palette */
 HPALETTE     DIBDisplayPaletteHdl;  /* handle to the display DIB palette  */
 HBITMAP      DIBDisplayBitmapHdl;   /* handle to the display DIB bitmap   */
 MIL_ID       MilVgaBufferId;        /* MIL ID of the MIL VGA buffer       */
 MIL_ID       MilVgaDisplayId;       /* MIL ID of the MIL VGA display      */
 long         VgaDriverBufferId;     /* Reserved                           */
 long         VgaDriverDisplayId;    /* Reserved                           */
 long         VgaDriverSystemId;     /* Reserved                           */
 long         ModificationHookType;  /* Type of hook on modification       */
 long         ModificationType;      /* Type of modification to buffer     */
 long         ModificationOffsetX;   /* Offset x of modified window        */
 long         ModificationOffsetY;   /* Offset y of modified window        */
 long         ModificationSizeX;     /* Size x of modified window          */
 long         ModificationSizeY;     /* Size y of modified window          */
 long         ModificationZoomX;     /* Zoom x of modified window          */
 long         ModificationZoomY;     /* Zoom y of modified window          */
 long         ModificationPanX;      /* Pan x of modified window           */
 long         ModificationPanY;      /* Pan x of modified window           */
 long         ModificationMenu;      /* Menu that is used by user          */
 long         ModificationValue;     /* Optional value for modification    */
 long         VisibleOffsetX;        /* Offset x of visible rect. of wnd   */
 long         VisibleOffsetY;        /* Offset y of visible rect. of wnd   */
 long         VisibleSizeX;          /* Size x of visible rect. of wnd     */
 long         VisibleSizeY;          /* Size y of visible rect. of wnd     */
 LPVOID       ExpansionPtr;          /* Reserved                           */
 long         ExpansionFlag;         /* Reserved                           */
 long         ReservedValue1;        /* Reserved                           */
 long         ReservedValue2;        /* Reserved                           */
 long         ReservedValue3;        /* Reserved                           */
 long         ReservedValue4;        /* Reserved                           */
 } M_WINDOW_INFO;
 
 typedef struct
 {
 HWND         WindowHandle;          /* Window hdl associated to display   */
 UINT         message;               /* Window message                     */
 WPARAM       wParam;                /* Window message wParam              */
 LPARAM       lParam;                /* Window message lParam              */
 MIL_ID       MilVgaBufferId;        /* MIL ID of the MIL VGA buffer       */
 MIL_ID       MilVgaDisplayId;       /* MIL ID of the MIL VGA display      */
 long         VgaDriverBufferId;     /* Reserved                           */
 long         VgaDriverDisplayId;    /* Reserved                           */
 long         VgaDriverSystemId;     /* Reserved                           */
 long         ModificationHookType;  /* Type of hook on modification       */
 } M_WINDOW_MSG_INFO;
 
 typedef struct
 {                  
 LPVOID     SrcRegionDataPtr;
 LPVOID     DstRegionDataPtr;
 } M_UPDATE_REGION_LIST;
 

 typedef MFTYPE32 long (MFTYPE MPTYPE *MVGADIBHOOKFCTPTR)
                              (M_DIB_INFO MPTYPE *ModifiedVgaBufferInfoPtr,
                              void MPTYPE *ExtraUserInfoPtr);

 typedef MFTYPE32 long (MFTYPE MPTYPE *MVGAWINHOOKFCTPTR)
                              (M_WINDOW_INFO MPTYPE *ModifiedVgaWindowInfoPtr,
                              void MPTYPE *ExtraUserInfoPtr);

 typedef MFTYPE32 long (MFTYPE MPTYPE *MVGAWINMSGHOOKFCTPTR)
                              (M_WINDOW_MSG_INFO MPTYPE *ModifiedVgaWindowMsgInfoPtr,
                              void MPTYPE *ExtraUserInfoPtr);

 typedef void MPTYPE *MVGAHOOKFCTPTR;

 /* To get a DIB info structure to display a VGA windows buffer */
 MFTYPE32 M_DIB_INFO MPTYPE * MFTYPE MvgaDispAllocDIBInfo(
                                 MIL_ID MilVgaDisplayId,
                                 MIL_ID MilVgaBufferId);


 /* To free a DIB info structure from a display a VGA windows buffer */
 MFTYPE32 void MFTYPE MvgaDispFreeDIBInfo(
                                 MIL_ID MilVgaDisplayId,
                                 MIL_ID MilVgaBufferId);


 /* To hook a user function that will handle display refresh */
 MFTYPE32 MVGAHOOKFCTPTR MFTYPE MvgaHookModifiedDIB(
                                 MIL_ID MilVgaDisplayId,
                                 MVGAHOOKFCTPTR FctPtr,
                                 void MPTYPE *ExtraUserInfoPtr);

 /* To hook a user function for modification of MIL VGA object */
 MFTYPE32 MVGAHOOKFCTPTR MFTYPE MvgaHookModified(
                                 MIL_ID MilVgaDisplayId,
                                 long HookTypeFlag,
                                 MVGAHOOKFCTPTR FctPtr,
                                 void MPTYPE *ExtraUserInfoPtr);

 /* To display a buffer in a display window creates by the user */
 MFTYPE32 void MFTYPE MvgaDispSelectClientArea(
                                 MIL_ID MilVgaDisplayId,
                                 MIL_ID MilVgaBufferId,
                                 HWND ClientWindowHandle);


 /* To undisplay a buffer from a display window created by user */
 MFTYPE32 void MFTYPE MvgaDispDeselectClientArea(
                                 MIL_ID MilVgaDisplayId,
                                 MIL_ID MilVgaBufferId,
                                 HWND ClientWindowHandle);

 MFTYPE32 void MFTYPE MvgaDispControl(
                                 MIL_ID MilVgaDisplayId,
                                 long ControlType,
                                 long ControlState);

 MFTYPE32 long MFTYPE MvgaDispInquire(
                                 MIL_ID MilVgaDisplayId,
                                 long InquireType,
                                 long MPTYPE *TargetVarPtr);

 MFTYPE32 void MFTYPE MvgaDispCapture(
                                 MIL_ID MilVgaDisplayId,
                                 long OffsetX,
                                 long OffsetY,
                                 long SizeX,
                                 long SizeY,
                                 long DestOffsetX,
                                 long DestOffsetY);

 MFTYPE32 void MFTYPE MvgaDispProtectArea(
                                 MIL_ID MilVgaDisplayId,
                                 long OffsetX,
                                 long OffsetY,
                                 long SizeX,
                                 long SizeY);

 MFTYPE32 void MFTYPE MvgaDispSetTitleName(
                                 MIL_ID MilVgaDisplayId,
                                 char *TitleName);

 /* C++ directive if needed */
 #ifdef __cplusplus
 }
 #endif

#endif
#endif
