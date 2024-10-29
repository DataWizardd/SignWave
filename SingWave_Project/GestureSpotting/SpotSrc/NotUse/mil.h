/***************************************************************************/
/*

    Filename:  MIL.H
    Owner   :  Matrox Imaging dept.
    Rev     :  $Revision:   1.0  $
    Content :  This file contains the defines necessary to use the
	       Matrox Imaging Library (MIL) C user interface.

    COPYRIGHT (c) 1993  Matrox Electronic Systems Ltd.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MIL_H
#define __MIL_H 


/***************************************************************************/
/* DEFAULT SETUP FLAG */

/* include set-up instructions (if not specified) */
#ifndef M_MIL_USE_SETUP
#include "milsetup.h"
#endif

/***************************************************************************/
/* FUNCTION ARGUMENT DECLARATIONS */

/* MIL buffer identifier type */
typedef long MIL_ID;

/* general default parameters (bit encoded) */
#define M_NULL                        0x00000000L
#define M_FALSE                       0L
#define M_TRUE                        1L
#define M_NO                          0L
#define M_YES                         1L
#define M_OFF                         0L
#define M_ON                          1L
#define M_DEFAULT                     0x10000000L
#define M_QUIET                       0x08000000L
#define M_VALID                       0x00000001L
#define M_INVALID                     -1L
#define M_CLEAR                       0x00000001L
#define M_NO_CLEAR                    0x00000002L
#define M_LUT_OFFSET                  0x80000000L
#define M_EXTENDED                    0x80000000L  // Special parameter routed directly to the driver

/* buffer ID offset for defaults */
#define M_ID_OFFSET_OF_DEFAULT_KERNEL 0x00100000L

#define M_UNSIGNED                    0x00000000L
#define M_SIGNED                      0x10000000L

/* buffer attributes */
#define M_NO_ATTR                     0x0000
#define M_IN                          0x0001
#define M_OUT                         0x0002

#define M_IMAGE                       0x00000004L
#define M_GRAB                        0x00000008L
#define M_PROC                        0x00000010L
#define M_DISP                        0x00000020L
#define M_GRAPH                       0x00000040L
#define M_OVR                         0x00000080L
#define M_LUT                         0x00000100L
#define M_KERNEL                      0x00000200L
#define M_STRUCT_ELEMENT              0x00000400L
#define M_ARRAY                       0x00000800L
#define M_BINARY                      0x00001000L
#define M_HIST_LIST                   0x00002000L
#define M_PROJ_LIST                   0x00004000L
#define M_EVENT_LIST                  0x00008000L
#define M_EXTREME_LIST                0x00010000L
#define M_COUNT_LIST                  0x00020000L
#define M_FILE_FORMAT                 0x00040000L
#define M_WARP_COEFFICIENT            0x00080000L
#define M_DIGITIZER                   0x00100000L
#define M_DISPLAY                     0x00200000L
#define M_APPLICATION                 0x00400000L
#define M_SYSTEM                      0x00800000L
#define M_GRAPHIC_CONTEXT             0x01000000L
#define M_CALL_CONTEXT                0x02000000L
#define M_ERROR_CONTEXT               0x04000000L
#define M_OVERSCAN_BUFFER             0x08000000L
#define M_USER_HOST_POINTER           0x10000000L
#define M_USER_ATTRIBUTE              0x20000000L
#define M_EXTENDED_ATTRIBUTE          M_EXTENDED

#define M_USER_OBJECT_1               (M_USER_ATTRIBUTE | 0x00010000L)
#define M_USER_OBJECT_2               (M_USER_ATTRIBUTE | 0x00020000L)
#define M_BLOB_OBJECT                 (M_USER_ATTRIBUTE | 0x00040000L)
#define M_PAT_OBJECT                  (M_USER_ATTRIBUTE | 0x00080000L)
#define M_OCR_OBJECT                  (M_USER_ATTRIBUTE | 0x00100000L)
#define M_MEAS_OBJECT                 (M_USER_ATTRIBUTE | 0x00200000L)
#define M_FREE_OBJECT_1               (M_USER_ATTRIBUTE | 0x00400000L)
#define M_FREE_OBJECT_2               (M_USER_ATTRIBUTE | 0x00800000L)
#define M_FREE_OBJECT_3               (M_USER_ATTRIBUTE | 0x01000000L)
#define M_FREE_OBJECT_4               (M_USER_ATTRIBUTE | 0x02000000L)
#define M_FREE_OBJECT_5               (M_USER_ATTRIBUTE | 0x04000000L)
#define M_FREE_OBJECT_6               (M_USER_ATTRIBUTE | 0x08000000L)
#define M_USER_DEFINE_LOW_ATTRIBUTE   0x0000FFFFL

#define M_HOOK_CONTEXT                (M_EXTENDED_ATTRIBUTE | 0x00000001L)
#define M_ON_BOARD                    (M_EXTENDED_ATTRIBUTE | 0x00040000L)
#define M_OFF_BOARD                   (M_EXTENDED_ATTRIBUTE | 0x00080000L)
#define M_AS_SPECIFIED                (M_EXTENDED_ATTRIBUTE | 0x00100000L)

#define M_SYSTEM_ALLOCATED            0x00000001L
#define M_USER_ALLOCATED              0xFFFFFFFEL

/************************************************************************
 * Msysxxxx() defines
 ************************************************************************/
/* MsysControl() */
#define M_PROCESSING_SYSTEM                     12L
#define M_PCI_LATENCY                           (M_EXTENDED_ATTRIBUTE | 0x00000001L) 
#define M_FAST_PCI_TO_MEM                       (M_EXTENDED_ATTRIBUTE | 0x00000002L) 
#define M_CHECK_FIELD_DROPPED                   (M_EXTENDED_ATTRIBUTE | 0x00000003L) 

#define M_RGB555_BUFFER_ALLOCATION              (M_EXTENDED_ATTRIBUTE | 0x00000100L)
#define M_PSEUDO_LIVE_VIDEO_ON_MGA              (M_EXTENDED_ATTRIBUTE | 0x00000200L)
#define M_LIVE_VIDEO                            (M_EXTENDED_ATTRIBUTE | 0x00000400L)
#define M_GRAB_BY_DISPLAY_CAPTURE               (M_EXTENDED_ATTRIBUTE | 0x00000800L)
#define M_ALLOC_BUF_RGB888_AS_RGB555            (M_EXTENDED_ATTRIBUTE | 0x00001000L)
#define M_PSEUDO_LIVE_GRAB_WHEN_OVERLAPPED      (M_EXTENDED_ATTRIBUTE | 0x00002000L)
#define M_SWITCH_TO_PSEUDO_WHEN_OVERLAPPED      (M_EXTENDED_ATTRIBUTE | 0x00002000L)
#define M_STOP_LIVE_GRAB_WHEN_MENU              (M_EXTENDED_ATTRIBUTE | 0x00004000L)
#define M_STOP_LIVE_GRAB_WHEN_INACTIVE          (M_EXTENDED_ATTRIBUTE | 0x00008000L)
#define M_DMA_ENABLE                            (M_EXTENDED_ATTRIBUTE | 0x00010000L)
#define M_DMA_DISABLE                           (M_EXTENDED_ATTRIBUTE | 0x00020000L)
#define M_LAST_GRAB_IN_ACTUAL_BUFFER            (M_EXTENDED_ATTRIBUTE | 0x00010000L)
#define M_STOP_LIVE_GRAB_WHEN_DISABLED          (M_EXTENDED_ATTRIBUTE | 0x00020000L)
#define M_COLOR_DISP_UPDATE_DURING_LIVE_GRAB    (M_EXTENDED_ATTRIBUTE | 0x00040000L)
#define M_NO_GRAB_WHEN_NO_INPUT_SIGNAL          (M_EXTENDED_ATTRIBUTE | 0x00100000L)
#define M_LIVE_GRAB_WHEN_DISPLAY_DOES_NOT_MATCH (M_EXTENDED_ATTRIBUTE | 0x00200000L)
#define M_FORCE_PSEUDO_IN_NON_PULSAR_DISPLAYS   (M_EXTENDED_ATTRIBUTE | 0x00400000L)
#define M_LIVE_GRAB_TRACK                       (M_EXTENDED_ATTRIBUTE | 0x00800000L)

/* MsysAlloc() */
#define M_SYSTEM_HOST_TYPE     9L
#define M_SYSTEM_MAGIC_TYPE    10L
#define M_SYSTEM_IP8_TYPE      11L
#define M_SYSTEM_IMAGE_TYPE    12L
#define M_SYSTEM_VGA_TYPE      13L
#define M_SYSTEM_COMET_TYPE    14L
#define M_SYSTEM_METEOR_TYPE   15L
#define M_SYSTEM_PULSAR_TYPE   16L
#define M_SYSTEM_GENESIS_TYPE  17L

/* MilInter */
#define M_SYSTEM_HOST_PTR     (M_SYSTEM_HOST_TYPE    +  50L)
#define M_SYSTEM_MAGIC_PTR    (M_SYSTEM_MAGIC_TYPE   +  50L)
#define M_SYSTEM_IP8_PTR      (M_SYSTEM_IP8_TYPE     +  50L)
#define M_SYSTEM_IMAGE_PTR    (M_SYSTEM_IMAGE_TYPE   +  50L)
#define M_SYSTEM_VGA_PTR      (M_SYSTEM_VGA_TYPE     +  50L)
#define M_SYSTEM_COMET_PTR    (M_SYSTEM_COMET_TYPE   +  50L)
#define M_SYSTEM_METEOR_PTR   (M_SYSTEM_METEOR_TYPE  +  50L)
#define M_SYSTEM_PULSAR_PTR   (M_SYSTEM_PULSAR_TYPE  +  50L)
#define M_SYSTEM_GENESIS_PTR  (M_SYSTEM_GENESYS_TYPE +  50L)


#define M_DEFAULT_HOST                0x10000001L

#define M_COMPLETE                    0x00000000L
#define M_PARTIAL                     0x00000001L
#define M_WINDOWS                     0x00000002L
#define M_DISP_WAIT_SELECT            0x00000004L
#define M_DISP_TEXT_SAVE              0x00000008L
#define M_NO_INTERRUPT                0x00010000L
#define M_NO_FIELD_START_INTERRUPT    0x00020000L
#define M_DISP_NO_WAIT_SELECT         0x00040000L
#define M_USE_DMA_FOR_PROC_BUF        (M_EXTENDED_ATTRIBUTE|0x00000010L)
#define M_USE_DMA_FOR_DISP_BUF        (M_EXTENDED_ATTRIBUTE|0x00000020L)
#define M_USE_DMA_FOR_GRAB_BUF        (M_EXTENDED_ATTRIBUTE|0x00000040L)
#define M_USE_DMA                     (M_USE_DMA_FOR_PROC_BUF | \
                                       M_USE_DMA_FOR_DISP_BUF | \
                                       M_USE_DMA_FOR_GRAB_BUF)

/*Reserve next 8 bits for DMA  from   0x00000100L   */
/*Size at allocation                  0x00000200L   */
/*                                    0x00000400L   */
/*                                    0x00000800L   */
/*                                    0x00001000L   */
/*                                    0x00002000L   */
/*                                    0x00004000L   */
/*                             to     0x00008000L   */
#define M_DMA_MEM_MASK                0x0000FF00L
#define M_PRE_ALLOC_DMA_MEM           0x00000080L

#if M_MIL_USE_DOS
   #define M_DMA_BLOCK_SIZE           64L
#endif
   
#if (!M_MIL_USE_DOS)
	#define M_DMA_BLOCK_SIZE           256L
#endif

#define M_DMA_BUF_SIZE(Val)           (((((Val+255L)/256L) << 8) & M_DMA_MEM_MASK) | M_PRE_ALLOC_DMA_MEM)

/************************************************************************/

/* MdispAlloc for VGA system */
#define M_WINDOW_NO_MENUBAR           0x00000010L
#define M_WINDOW_NO_TITLEBAR          0x00000020L
#define M_WINDOW_NO_KEY               0x00000040L
#define M_WINDOW_MAXIMIZE             0x00000080L
#define M_WINDOW_USE_FORMAT           0x00000100L
#define M_PALETTE_MIL                 0x00000000L
#define M_PALETTE_WINDOWS             0x00000200L
#define M_PALETTE_COLLAPSE            0x00000000L
#define M_PALETTE_NOCOLLAPSE          0x00100000L
#define M_ZOOM_ENHANCED               0x00000000L
#define M_ZOOM_BASIC                  0x00000400L
#define M_DISPLAY_8_BASIC             0x00000000L
#define M_DISPLAY_8_ENHANCED          0x00000800L
#define M_DISPLAY_24_ENHANCED         0x00000000L
#define M_DISPLAY_24_BASIC            0x00001000L
#define M_DISPLAY_24_WINDOWS          0x00002000L
#define M_DISPLAY_ENHANCED            (M_DISPLAY_8_ENHANCED+M_DISPLAY_24_ENHANCED)
#define M_DISPLAY_BASIC               (M_DISPLAY_8_BASIC+M_DISPLAY_24_BASIC)
#define M_DISPLAY_WINDOWS             (M_DISPLAY_8_BASIC+M_DISPLAY_24_WINDOWS)
#define M_WINDOW_NO_SYSBUTTON         0x00004000L
#define M_WINDOW_NO_MINBUTTON         0x00008000L
#define M_WINDOW_NO_MAXBUTTON         0x00010000L
#define M_COLORTABLE_RGB              0x00000000L
#define M_COLORTABLE_INDEX            0x00020000L

/* MdispAlloc for Pulsar system */
#define M_WINDOWED                    0x01000000L
#define M_NON_WINDOWED                0x02000000L


#define M_AUTOMATIC                   0xffffffffL
#define M_DEV0                        0L
#define M_DEV1                        1L
#define M_DEV2                        2L
#define M_DEV3                        3L
#define M_DEV4                        4L
#define M_DEV5                        5L
#define M_DEV6                        6L
#define M_DEV7                        7L
#define M_DEV8                        8L
#define M_DEV9                        9L
#define M_DEV10                       10L
#define M_DEV11                       11L
#define M_DEV12                       12L
#define M_DEV13                       13L
#define M_DEV14                       14L
#define M_DEV15                       15L
#define M_NODE0                       0x00010000L
#define M_NODE1                       0x00020000L
#define M_NODE2                       0x00040000L
#define M_NODE3                       0x00080000L
#define M_NODE4                       0x00100000L
#define M_NODE5                       0x00200000L
#define M_NODE6                       0x00400000L
#define M_NODE7                       0x00800000L
#define M_NODE8                       0x01000000L
#define M_NODE9                       0x02000000L
#define M_NODE10                      0x04000000L
#define M_NODE11                      0x08000000L
#define M_NODE12                      0x10000000L
#define M_NODE13                      0x20000000L
#define M_NODE14                      0x40000000L
#define M_NODE15                      0x80000000L

/* MsysInquire() */
#define M_NUMBER_DIGITIZER         119L
#define M_NUMBER_DISPLAY           122L
#define M_OWNER_SYSTEM             124L

/************************************************************************
 * Mdigxxxx() defines
 ************************************************************************/

/* MdigAlloc() */
#define M_DIGITIZER_COLOR          (M_EXTENDED_ATTRIBUTE | 0x00000001L)
#define M_DIGITIZER_MONO           (M_EXTENDED_ATTRIBUTE | 0x00000002L)

/* MdigChannel() */
#define M_CH0                  0L
#define M_CH1                  1L
#define M_CH2                  2L
#define M_CH3                  3L
#define M_CH4                  4L
#define M_CH5                  5L
#define M_CH6                  6L
#define M_CH7                  7L
#define M_RCA                  M_CH0
#define M_RGB                  (M_EXTENDED_ATTRIBUTE | M_CH4)
#define M_YC                   (M_EXTENDED_ATTRIBUTE | M_CH5)
#define M_TUNER_CHANNEL        (M_EXTENDED_ATTRIBUTE | 0x00000100L)
#define M_TUNER_BAND           (M_EXTENDED_ATTRIBUTE | 0x00000200L)
#define M_CABLE                0x10000L
#define M_REGULAR              0x20000L

/* MdigReference() */
#define M_BLACK                    0L
#define M_WHITE                    1L
#define M_BLACK_REF                0L
#define M_WHITE_REF                1L
#define M_CH0_REF                  0x01000000L
#define M_CH1_REF                  0x02000000L
#define M_CH2_REF                  0x04000000L
#define M_CH3_REF                  0x08000000L
#define M_CH4_REF                  0x00100000L
#define M_CH5_REF                  0x00200000L
#define M_CH6_REF                  0x00400000L
#define M_CH7_REF                  0x00800000L
#define M_ALL_REF                  (M_CH0_REF|M_CH1_REF|M_CH2_REF|M_CH3_REF|M_CH4_REF|M_CH5_REF|M_CH6_REF|M_CH7_REF)
#define M_MIN_LEVEL                0L
#define M_MAX_LEVEL                255L
#define M_HUE_REF                  (M_EXTENDED_ATTRIBUTE | 1L)    
#define M_SATURATION_REF           (M_EXTENDED_ATTRIBUTE | 2L)    
#define M_CONTRAST_REF             (M_EXTENDED_ATTRIBUTE | 3L)
#define M_BRIGHTNESS_REF           (M_EXTENDED_ATTRIBUTE | 4L)

/* MdigInquire() and partially MdigControl()*/
#define M_DIG_TYPE                     300L
#define M_DIG_NUMBER                   301L
#define M_DIG_FORMAT                   302L
#define M_DIG_CHANNEL                  303L
#define M_DIG_INIT_FLAG                304L
#define M_DIG_LUT                      305L
#define M_DIG_REF_BLACK                306L
#define M_DIG_REF_WHITE                307L
#define M_DIG_GRAB_SUBSAMPLE_X         308L
#define M_DIG_GRAB_SUBSAMPLE_Y         309L
#define M_DIG_GRAB_MODE                310L
#define M_DIG_GRAB_FRAME_NUM           311L
#define M_DIG_GRAB_FIELD_NUM           312L
#define M_DIG_GRAB_SCALE_X             313L
#define M_DIG_GRAB_SCALE_Y             314L
#define M_DIG_CHANNEL_NUM              315L
#define M_GRAB_INPUT_GAIN              316L
#define M_HOOK_PRIORITY                317L
#define M_DIG_NATIVE_ID                          (M_EXTENDED_ATTRIBUTE | 0x00040000L)
#define M_DESTRUCTIVE_GRAB_IN_PROGRESS           (M_EXTENDED_ATTRIBUTE | 0x00000001L)
#define M_DIG_HUE_REF                            (M_EXTENDED_ATTRIBUTE | 4L)
#define M_DIG_SATURATION_REF                     (M_EXTENDED_ATTRIBUTE | 5L)
#define M_DIG_BRIGHTNESS_REF                     (M_EXTENDED_ATTRIBUTE | 6L)
#define M_DIG_CONTRAST_REF                       (M_EXTENDED_ATTRIBUTE | 7L)
#define M_VCR_INPUT_TYPE                         (M_EXTENDED_ATTRIBUTE | 16L)
#define M_GRAB_START_MODE                        (M_EXTENDED_ATTRIBUTE | 19L)
#define M_GRAB_END_HANDLER_PTR                   (M_EXTENDED_ATTRIBUTE | 20L)
#define M_GRAB_END_HANDLER_USER_PTR              (M_EXTENDED_ATTRIBUTE | 21L)
#define M_GRAB_FIELD_END_HANDLER_PTR             (M_EXTENDED_ATTRIBUTE | 22L)
#define M_GRAB_FIELD_END_HANDLER_USER_PTR        (M_EXTENDED_ATTRIBUTE | 23L)
#define M_GRAB_FIELD_END_ODD_HANDLER_PTR         (M_EXTENDED_ATTRIBUTE | 24L)
#define M_GRAB_FIELD_END_ODD_HANDLER_USER_PTR    (M_EXTENDED_ATTRIBUTE | 25L)
#define M_GRAB_FIELD_END_EVEN_HANDLER_PTR        (M_EXTENDED_ATTRIBUTE | 26L)
#define M_GRAB_FIELD_END_EVEN_HANDLER_USER_PTR   (M_EXTENDED_ATTRIBUTE | 27L)
#define M_GRAB_FRAME_END_HANDLER_PTR             (M_EXTENDED_ATTRIBUTE | 28L)
#define M_GRAB_FRAME_END_HANDLER_USER_PTR        (M_EXTENDED_ATTRIBUTE | 29L)
#define M_FIELD_START_HANDLER_PTR                (M_EXTENDED_ATTRIBUTE | 30L)
#define M_FIELD_START_HANDLER_USER_PTR           (M_EXTENDED_ATTRIBUTE | 31L)
#define M_FIELD_START_ODD_HANDLER_PTR            (M_EXTENDED_ATTRIBUTE | 32L)
#define M_FIELD_START_ODD_HANDLER_USER_PTR       (M_EXTENDED_ATTRIBUTE | 33L)
#define M_FIELD_START_EVEN_HANDLER_PTR           (M_EXTENDED_ATTRIBUTE | 34L)
#define M_FIELD_START_EVEN_HANDLER_USER_PTR      (M_EXTENDED_ATTRIBUTE | 35L)  
#define M_GRAB_WINDOWS_RANGE                     (M_EXTENDED_ATTRIBUTE | 41L)  
#define M_DIG_SOURCE_SIZE_X                      (M_EXTENDED_ATTRIBUTE | 42L)  
#define M_DIG_SOURCE_SIZE_Y                      (M_EXTENDED_ATTRIBUTE | 43L)  
#define M_DIG_SOURCE_OFFSET_X                    (M_EXTENDED_ATTRIBUTE | 44L)  
#define M_DIG_SOURCE_OFFSET_Y                    (M_EXTENDED_ATTRIBUTE | 45L) 
#define M_DIG_INPUT_SIGNAL_PRESENT               (M_EXTENDED_ATTRIBUTE | 47L)
#define M_DIG_INPUT_SIGNAL_SOURCE                (M_EXTENDED_ATTRIBUTE | 48L)
#define M_GRAB_TRIGGER_MODE                      (M_EXTENDED_ATTRIBUTE | 52L) 
#define M_GRAB_FIELD_END_ODD_THREAD_ID           (M_EXTENDED_ATTRIBUTE | 53L)
#define M_GRAB_FIELD_END_EVEN_THREAD_ID          (M_EXTENDED_ATTRIBUTE | 54L)
#define M_FIELD_START_THREAD_ID                  (M_EXTENDED_ATTRIBUTE | 55L)
#define M_GRAB_FIELD_END_ODD_THREAD_HANDLE       (M_EXTENDED_ATTRIBUTE | 56L)
#define M_GRAB_FIELD_END_EVEN_THREAD_HANDLE      (M_EXTENDED_ATTRIBUTE | 57L)
#define M_FIELD_START_THREAD_HANDLE              (M_EXTENDED_ATTRIBUTE | 58L)
#define M_GRAB_EXPOSURE_MODE                     (M_EXTENDED_ATTRIBUTE | 59L) 
#define M_GRAB_TRIGGER_SOURCE                    (M_EXTENDED_ATTRIBUTE | 60L)
#define M_GRAB_EXPOSURE_TIME                     (M_EXTENDED_ATTRIBUTE | 61L)
#define M_GRAB_TRIGGER                           (M_EXTENDED_ATTRIBUTE | 62L)
#define M_GRAB_EXPOSURE_TIME_DELAY               (M_EXTENDED_ATTRIBUTE | 63L)
#define M_GRAB_EXPOSURE_TIME_WAIT                (M_EXTENDED_ATTRIBUTE | 64L)
#define M_START_EXPOSURE                         (M_EXTENDED_ATTRIBUTE | 65L)
#define M_DIG_USER_BIT                           (M_EXTENDED_ATTRIBUTE | 80L)
#define M_DIG_USER_BIT0                          (M_EXTENDED_ATTRIBUTE | 80L)
#define M_DIG_USER_BIT1                          (M_EXTENDED_ATTRIBUTE | 80L)+1L
#define M_DIG_USER_BIT2                          (M_EXTENDED_ATTRIBUTE | 80L)+2L
#define M_DIG_USER_BIT3                          (M_EXTENDED_ATTRIBUTE | 80L)+3L
#define M_DIG_USER_BIT4                          (M_EXTENDED_ATTRIBUTE | 80L)+4L
#define M_DIG_USER_BIT5                          (M_EXTENDED_ATTRIBUTE | 80L)+5L
#define M_DIG_USER_BIT6                          (M_EXTENDED_ATTRIBUTE | 80L)+6L
#define M_DIG_USER_BIT7                          (M_EXTENDED_ATTRIBUTE | 80L)+7L
#define M_DIG_USER_BIT8                          (M_EXTENDED_ATTRIBUTE | 80L)+8L
#define M_DIG_USER_BIT9                          (M_EXTENDED_ATTRIBUTE | 80L)+9L
#define M_DIG_USER_BIT10                         (M_EXTENDED_ATTRIBUTE | 80L)+10L
#define M_DIG_USER_BIT11                         (M_EXTENDED_ATTRIBUTE | 80L)+11L
#define M_DIG_USER_BIT12                         (M_EXTENDED_ATTRIBUTE | 80L)+12L
#define M_DIG_USER_BIT13                         (M_EXTENDED_ATTRIBUTE | 80L)+13L
#define M_DIG_USER_BIT14                         (M_EXTENDED_ATTRIBUTE | 80L)+14L
#define M_DIG_USER_BIT15                         (M_EXTENDED_ATTRIBUTE | 80L)+15L
#define M_DIG_USER_BIT16                         (M_EXTENDED_ATTRIBUTE | 80L)+16L
#define M_DIG_USER_BIT17                         (M_EXTENDED_ATTRIBUTE | 80L)+17L
#define M_DIG_USER_BIT18                         (M_EXTENDED_ATTRIBUTE | 80L)+18L
#define M_DIG_USER_BIT19                         (M_EXTENDED_ATTRIBUTE | 80L)+19L
#define M_DIG_USER_BIT20                         (M_EXTENDED_ATTRIBUTE | 80L)+20L
#define M_DIG_USER_BIT21                         (M_EXTENDED_ATTRIBUTE | 80L)+21L
#define M_DIG_USER_BIT22                         (M_EXTENDED_ATTRIBUTE | 80L)+22L
#define M_DIG_USER_BIT23                         (M_EXTENDED_ATTRIBUTE | 80L)+23L
#define M_DIG_USER_BIT24                         (M_EXTENDED_ATTRIBUTE | 80L)+24L
#define M_DIG_USER_BIT25                         (M_EXTENDED_ATTRIBUTE | 80L)+25L
#define M_DIG_USER_BIT26                         (M_EXTENDED_ATTRIBUTE | 80L)+26L
#define M_DIG_USER_BIT27                         (M_EXTENDED_ATTRIBUTE | 80L)+27L
#define M_DIG_USER_BIT28                         (M_EXTENDED_ATTRIBUTE | 80L)+28L
#define M_DIG_USER_BIT29                         (M_EXTENDED_ATTRIBUTE | 80L)+29L
#define M_DIG_USER_BIT30                         (M_EXTENDED_ATTRIBUTE | 80L)+30L
#define M_DIG_USER_BIT31                         (M_EXTENDED_ATTRIBUTE | 80L)+31L
#define M_DIG_USER_BIT32                         (M_EXTENDED_ATTRIBUTE | 80L)+32L

/* MdigControl() */

/* Control type */
#define M_GRAB_SUBSAMPLE_X         1L
#define M_GRAB_SUBSAMPLE_Y         2L
#define M_GRAB_SUBSAMPLE           3L
#define M_GRAB_MODE                4L
#define M_GRAB_FRAME_NUM           5L
#define M_GRAB_FIELD_NUM           6L
#define M_GRAB_SCALE_X             7L
#define M_GRAB_SCALE_Y             8L
#define M_GRAB_SCALE               9L
#define M_GRAB_WRITE_FORMAT       10L         
#define M_GRAB_ON_ONE_LINE        11L         
#define M_GRAB_LUT_PALETTE        13L

/* Control Values */
#define M_FILL_DESTINATION       -1.0 
#define M_FILL_DISPLAY           -2.0 
#define M_SYNCHRONOUS              1L
#define M_ASYNCHRONOUS             2L
#define M_EDGE_RISING              0L
#define M_EDGE_FALLING             1L
#define M_LEVEL_LOW                2L
#define M_LEVEL_HIGH               3L
#define M_HARDWARE_PORT0           0x0100L    /* Bitfield value */
#define M_HARDWARE_PORT1           0x0200L    /* Bitfield value */
#define M_HARDWARE_PORT_CAMERA     5L 
#define M_SOFTWARE                 4L

#define M_LUT_PALETTE0             0L         
#define M_LUT_PALETTE1             1L
#define M_LUT_PALETTE2             2L
#define M_LUT_PALETTE3             3L
#define M_LUT_PALETTE4             4L
#define M_LUT_PALETTE5             5L
#define M_LUT_PALETTE6             6L
#define M_LUT_PALETTE7             7L
#define M_GAIN0                   10L
#define M_GAIN1                   11L
#define M_GAIN2                   12L
#define M_GAIN3                   13L

/* MdigGrabWait() */
#define M_GRAB_END                 1L
#define M_GRAB_NEXT_FRAME          2L
#define M_GRAB_NEXT_FIELD          3L

/* MdigHookFunction() */
#define M_GRAB_FIELD_END_ODD    (M_EXTENDED_ATTRIBUTE | 1L)
#define M_GRAB_FIELD_END_EVEN   (M_EXTENDED_ATTRIBUTE | 2L)
#define M_GRAB_FIELD_END        (M_EXTENDED_ATTRIBUTE | 3L)
#define M_GRAB_FRAME_END        (M_EXTENDED_ATTRIBUTE | 4L)
#define M_FIELD_START           (M_EXTENDED_ATTRIBUTE | 5L)
#define M_FIELD_START_ODD       (M_EXTENDED_ATTRIBUTE | 6L)
#define M_FIELD_START_EVEN      (M_EXTENDED_ATTRIBUTE | 7L)


/************************************************************************
 * Mdispxxxx() defines
 ************************************************************************/


/* MdispInquire() */
#define M_DISP_PAN_X            201L
#define M_DISP_PAN_Y            202L
#define M_DISP_ZOOM_X           203L
#define M_DISP_SELECT           204L
#define M_DISP_ZOOM_Y           205L
#define M_DISP_LUT              206L
#define M_DISP_NUMBER           207L
#define M_DISP_FORMAT           208L
#define M_DISP_INIT_FLAG        209L
#define M_DISP_KEY_MODE         210L
#define M_DISP_KEY_CONDITION    211L
#define M_DISP_KEY_MASK         212L
#define M_DISP_KEY_COLOR        213L
#define M_DISP_KEY_SUPPORTED    500L
#define M_DISP_MODE             501L
#define M_DISP_OVR_BUF_ID       502L
#define M_DISP_OVR_WRITE        503L
#define M_DISP_HARDWARE_PAN     504L
#define M_DISP_HARDWARE_ZOOM    505L
#define M_DISP_VGA_BUF_ID       506L
#define M_DISP_BUF_WRITE        507L
#define M_DISP_BUF_ID           508L
#define M_DISP_BUF_SURFACE      509L
#define M_DISP_NATIVE_ID        (M_EXTENDED_ATTRIBUTE | 0x00040000L)

/* MdispControl() */
#define M_DISP_OVR_WRITE        503L
#define M_DISP_HARDWARE_PAN     504L
#define M_DISP_HARDWARE_ZOOM    505L
#define M_DISP_BUF_WRITE        507L

/* MdispLut() */
#define M_PSEUDO               (M_LUT_OFFSET + 8L)

/* MDispOverlayKey() */
#define M_KEY_ON_COLOR         1L
#define M_KEY_OFF              2L
#define M_KEY_ALWAYS           3L

/************************************************************************
 * Mgenxxxx() defines
 ************************************************************************/

/* MgenLutFunction() */
#define M_LOG     0x00000000L
#define M_EXP     0x00000001L
#define M_SIN     0x00000002L
#define M_COS     0x00000003L
#define M_TAN     0x00000004L
#define M_QUAD    0x00000005L

/************************************************************************
 * Mimxxxx() defines
 ************************************************************************/

/* MimGetResult() */
#define M_VALUE         0L
#define M_POSITION_X    3L
#define M_POSITION_Y    4L
#define M_NB_EVENT      5L

/* MimInquire () */
#define M_RESULT_SIZE   0L
#define M_RESULT_TYPE   1L

/* MimFindExtreme() */
#define M_MAX_VALUE     1L
#define M_MIN_VALUE     2L

/* MimArith() */
#define M_CONSTANT    0x8000L
#define M_FIXED_POINT 0x4000L
#define M_ADD         0x0000L
#define M_ADD_CONST   (M_ADD | M_CONSTANT)
#define M_SUB         0x0001L
#define M_SUB_CONST   (M_SUB | M_CONSTANT)
#define M_NEG_SUB     0x000AL
#define M_CONST_SUB   (M_NEG_SUB | M_CONSTANT)
#define M_SUB_ABS     0x0011L
#define M_MIN         0x0012L
#define M_MIN_CONST   (M_MIN | M_CONSTANT)
#define M_MAX         0x0013L
#define M_MAX_CONST   (M_MAX | M_CONSTANT)
#define M_OR          0x0016L
#define M_OR_CONST    (M_OR  | M_CONSTANT)
#define M_AND         0x0017L
#define M_AND_CONST   (M_AND | M_CONSTANT)
#define M_XOR         0x0018L
#define M_XOR_CONST   (M_XOR | M_CONSTANT)
#define M_NOR         0x0019L
#define M_NOR_CONST   (M_NOR | M_CONSTANT)
#define M_NAND        0x001AL
#define M_NAND_CONST  (M_NAND | M_CONSTANT)
#define M_XNOR        0x001BL
#define M_XNOR_CONST  (M_XNOR | M_CONSTANT)
#define M_NOT         0x0014L
#define M_NEG         0x0023L
#define M_ABS         0x000CL
#define M_PASS        0x0002L
#define M_CONST_PASS  (M_PASS | M_CONSTANT)
#define M_MULT        0x0100L
#define M_MULT_CONST  (M_MULT | M_CONSTANT)
#define M_DIV         0x0101L
#define M_DIV_CONST   (M_DIV | M_CONSTANT)
#define M_INV_DIV     0x0102L
#define M_CONST_DIV   (M_INV_DIV | M_CONSTANT)

/* MimBinarize(), MimClip(), MimLocateEvent() */
#define M_IN_RANGE         1L
#define M_OUT_RANGE        2L
#define M_EQUAL            3L
#define M_NOT_EQUAL        4L
#define M_GREATER          5L
#define M_LESS             6L
#define M_GREATER_OR_EQUAL 7L
#define M_LESS_OR_EQUAL    8L

/* MimConvolve() */
#define M_SMOOTH           (M_ID_OFFSET_OF_DEFAULT_KERNEL +  0L)
#define M_LAPLACIAN_EDGE   (M_ID_OFFSET_OF_DEFAULT_KERNEL +  1L)
#define M_LAPLACIAN_EDGE2  (M_ID_OFFSET_OF_DEFAULT_KERNEL +  2L)
#define M_SHARPEN          (M_ID_OFFSET_OF_DEFAULT_KERNEL +  3L)
#define M_SHARPEN2         (M_ID_OFFSET_OF_DEFAULT_KERNEL +  4L)
#define M_HORIZ_EDGE       (M_ID_OFFSET_OF_DEFAULT_KERNEL +  5L)
#define M_VERT_EDGE        (M_ID_OFFSET_OF_DEFAULT_KERNEL +  6L)
#define M_EDGE_DETECT      (M_ID_OFFSET_OF_DEFAULT_KERNEL +  7L)
#define M_EDGE_DETECT2     (M_ID_OFFSET_OF_DEFAULT_KERNEL +  8L)
#define M_OVERSCAN_DISABLE (M_ID_OFFSET_OF_DEFAULT_KERNEL >> 1L)

/* MimRank() */
#define M_MEDIAN          0x10000L
#define M_3X3_RECT        (M_ID_OFFSET_OF_DEFAULT_KERNEL + 20L)
#define M_3X3_CROSS       (M_ID_OFFSET_OF_DEFAULT_KERNEL + 21L)

/* MimMorphic(), ... */
#define M_ERODE           1L
#define M_DILATE          2L
#define M_THIN            3L
#define M_THICK           4L
#define M_HIT_OR_MISS     5L
#define M_MATCH           6L
#define M_CLOSE           10L
#define M_OPEN            11L

/* MimThin() */
#define M_TO_SKELETON     -1L

/* MimThick() */
#define M_TO_IDEMPOTENCE  M_TO_SKELETON

/* MimDistance() */
#define M_CHAMFER_3_4     0x01
#define M_CITY_BLOCK      0x02
#define M_FORWARD         0x01
#define M_BACKWARD        0x02
#define M_OVERSCAN_TO_DO  0x04
#define M_BOTH            0x07

/* MimProject() */
#define M_0_DEGREE         0.0
#define M_90_DEGREE       90.0
#define M_180_DEGREE     180.0
#define M_270_DEGREE     270.0

/* MimTranslate() and MimRotate() */
#define M_OVERSCAN_ENABLE   0x00000000L
#define M_INTERPOLATE       0x00000004L
#define M_BILINEAR          0x00000008L
#define M_BICUBIC           0x00000010L
#define M_AVERAGE           0x00000020L
#define M_NEAREST_NEIGHBOR  0x00000040L
#define M_OVERSCAN_CLEAR    0x00000080L

/* MimAverage */
#define M_NORMAL          1L
#define M_WEIGHTED        2L
#define M_CONTINUOUS     -1L
#define M_SINGLE         -2L

/* MimResize */
#define M_FILL_DESTINATION -1.0 // DO NOT MODIFY, WITHOUT CODE MODIFICATION

/* MimHistogramEqualize() */
#define M_UNIFORM         1
#define M_EXPONENTIAL     2
#define M_RAYLEIGH        3
#define M_HYPER_CUBE_ROOT 4
#define M_HYPER_LOG       5

/* MimConvert() */
#define M_RGB_TO_HLS      1
#define M_RGB_TO_L        2
#define M_HLS_TO_RGB      3
#define M_L_TO_RGB        4

/************************************************************************
 * Mbufxxxx() defines
 ************************************************************************/

/* MbufGetColor(), MbufPutColor() and MbufChildColor() */

#define M_ALL_BAND           -1L
#define M_RED                -2L
#define M_GREEN              -3L
#define M_BLUE               -4L
#define M_HUE              M_RED
#define M_SATURATION     M_GREEN
#define M_LUMINANCE       M_BLUE

#define M_SINGLE_BAND         1L
#define M_RGB24_PACKED        2L
#define M_RGB32_PACKED        3L
#define M_PLANAR              4L
#define M_BGR24_PACKED        5L                           // Windows+DOS VGA
#define M_BGR16_PACKED        6L                           // Windows+DOS VGA
#define M_NODIBFLIP           128L                         // Windows VGA
#define M_DIB_BGR24_PACKED    (M_BGR24_PACKED+M_NODIBFLIP) // Windows VGA
#define M_DIB_BGR16_PACKED    (M_BGR16_PACKED+M_NODIBFLIP) // Windows VGA
#define M_BGR32_PACKED_ATI   17

/* MbufGet..(), MbufPut..() and MbufChild..() */
#define M_ALL_BITS           -1L
#define M_DONT_CARE  0x80000000L

/* MbufImport(), MbufExport() */
#define M_RESTORE             0L
#define M_LOAD                1L

#define M_MIL                 0L
#define M_RAW                 1L
#define M_TIFF                2L
#define M_GIF                 3L


/* MbufControlNeighborhood() */
#define M_ABSOLUTE_VALUE         50L
#define M_NORMALIZATION_FACTOR   52L
#define M_OVERSCAN               53L
#define M_OVERSCAN_REPLACE_VALUE 54L
#define M_OFFSET_CENTER_X        55L
#define M_OFFSET_CENTER_Y        56L
#define M_ENABLE                 -9997L
#define M_DISABLE                -9999L
#define M_TRANSPARENT            0x01000059L
#define M_REPLACE                0x01000060L
#define M_MIRROR                 0x01000061L
#define M_REPLACE_MAX            0x01000063L
#define M_REPLACE_MIN            0x01000064L

/* MbufInquire() */
#define M_SIZE_X                   3L
#define M_SIZE_Y                   4L
#define M_SIZE_Z                   5L
#define M_SIZE_BAND                6L
#define M_SIZE_TIME                7L
#define M_TYPE                     8L
#define M_ATTRIBUTE                9L
#define M_SIZE_BIT                 10L
#define M_SIGN                     11L
#define M_INTER_SYSTEM_ID          29L
#define M_PARENT_ID                30L
#define M_ANCESTOR_ID              31L
#define M_PARENT_OFFSET_X          32L
#define M_PARENT_OFFSET_Y          33L
#define M_ANCESTOR_OFFSET_X        34L
#define M_ANCESTOR_OFFSET_Y        35L
#define M_PARENT_OFFSET_BAND       37L
#define M_ANCESTOR_OFFSET_BAND     38L
#define M_NB_CHILD                 39L
#define M_MODIFICATION_COUNT       40L
#define M_HOST_ADDRESS             41L
#define M_ANCESTOR_SIZE_X          42L
#define M_HOST_ADDRESS_FAR         43L
#define M_SIZE_BAND_LUT            44L
#define M_ASSOCIATED_LUT           45L
#define M_CURRENT_BUF_ID           46L
#define M_BUF_ASSOCIATED_BUFFER_ID 47L
#define M_BUF_NATIVE_ID            (M_EXTENDED_ATTRIBUTE | 0x00040000L)
#define M_FORMAT                   (M_EXTENDED_ATTRIBUTE | 0x00000005L)
#define M_PHYSICAL_ADDRESS         (M_EXTENDED_ATTRIBUTE | 0x00000006L)
#define M_VALID_GRAB_BUFFER        (M_EXTENDED_ATTRIBUTE | 0x00000007L)
#define M_VALID_GRAB_BUFFER_OFFSET (M_EXTENDED_ATTRIBUTE | 0x00000008L)
#define M_LOW_LEVEL_BUFFER_ID      (M_EXTENDED_ATTRIBUTE | 0x00000009L)

/* MbufDiskInquire() */
#define M_LUT_PRESENT              47L
#define M_ASPECT_RATIO             48L


/* Lattice values */
#define M_4_CONNECTED           0x10L
#define M_8_CONNECTED           0x20L

/* Data types for results */
#define M_TYPE_CHAR          0x10000L
#define M_TYPE_SHORT         0x20000L
#define M_TYPE_LONG          0x40000L
#define M_TYPE_FLOAT         0x80000L
#define M_TYPE_DOUBLE       0x100000L
#define M_TYPE_PTR          0x200000L
#define M_TYPE_MIL_ID       0x400000L
#define M_TYPE_STRING       0x800000L
#define M_TYPE_STRING_PTR   0x800000L
#define M_TYPE_ASCII        0x800000L
#define M_TYPE_BINARY      0x1000000L
#define M_TYPE_HEX         0x2000000L


/* Bit encoded image types */
#define M_GREYSCALE  0x0200L
#define M_GRAYSCALE  0x0200L

/* MbufInquire() on Magic and Meteor */
#define M_DMA_READ_HOST_ID            (M_EXTENDED_ATTRIBUTE | 0x00000002L)
#define M_HOST_ID                      M_DMA_READ_HOST_ID
#define M_DMA_BUFFER                  (M_EXTENDED_ATTRIBUTE | 0x00000003L)
#define M_DMA_BUFFER_PTR              (M_EXTENDED_ATTRIBUTE | 0x00000004L)
#define M_DMA_BUFFER_PHYSICAL_PTR     (M_EXTENDED_ATTRIBUTE | 0x00000005L)

/************************************************************************
 * Mgraxxxx() defines
 ************************************************************************/

/* Used by MgraFont() */
#define M_FONT_DEFAULT_SMALL        MgraFontGetSmall()
#define M_FONT_DEFAULT_MEDIUM       MgraFontGetMedium()
#define M_FONT_DEFAULT_LARGE        MgraFontGetLarge()
#define M_FONT_DEFAULT              M_FONT_DEFAULT_SMALL
#define M_FONT_DEFAULT_SMALL_VALUE  0L
#define M_FONT_DEFAULT_MEDIUM_VALUE 1L
#define M_FONT_DEFAULT_LARGE_VALUE  2L
#define M_FONT_DEFAULT_VALUE        M_FONT_DEFAULT_SMALL_VALUE

/* Used by MgraInquire() */
#define M_GRAPHIC_POSITION_X 3L
#define M_GRAPHIC_POSITION_Y 4L
#define M_COLOR              5L
#define M_BACKCOLOR          6L
#define M_FONT               7L
#define M_FONT_X_SCALE       8L
#define M_FONT_Y_SCALE       9L
#define M_THICKNESS          10L
#define M_OWNER_APPLICATION  11L


/* Used by MgraControl() */
#define M_BACKGROUND_MODE        12L
#define M_OPAQUE                 0x01000058L
#define M_TRANSPARENT            0x01000059L

/************************************************************************
 * Mnatxxxx() defines
 ************************************************************************/

/* Used by MnatEnter/LeaveNativeMode() */
#define M_NAT_NULL                    0x0L
#define M_NAT_PROC                    0x1L
#define M_NAT_GRAPH                   0x2L
#define M_NAT_DISP                    0x4L
#define M_NAT_GRAB                    0x8L
#define M_NAT_ACCESS                  0x10L
#define M_NAT_ALL                     0x1fL

/* Used by MnatAccessSystemInfo */
#define M_READ                        1
#define M_WRITE                       2
#define M_RDWR                        3
#define M_MODULE_NAT                  0

/************************************************************************
 * Misxxxx() defines
 ************************************************************************/

/* Used by MisNatGetLocGraph() */
#define M_ORG                         1L
#define M_SURF                        2L

/************************************************************************
 * Mappxxxx() defines
 ************************************************************************/

/* MappGetErrorxxx() */
#define M_NO_ERROR               0L
#define M_CURRENT                1L
#define M_CURRENT_FCT            2L
#define M_CURRENT_SUB_NB         3L
#define M_CURRENT_SUB            4L
#define M_CURRENT_SUB_1          4L
#define M_CURRENT_SUB_2          5L
#define M_CURRENT_SUB_3          6L
#define M_GLOBAL                 7L
#define M_GLOBAL_FCT             8L
#define M_GLOBAL_SUB_NB          9L
#define M_GLOBAL_SUB             10L
#define M_GLOBAL_SUB_1           10L
#define M_GLOBAL_SUB_2           11L
#define M_GLOBAL_SUB_3           12L
#define M_INTERNAL               13L
#define M_INTERNAL_FCT           14L
#define M_INTERNAL_SUB_NB        15L
#define M_INTERNAL_SUB           16L
#define M_INTERNAL_SUB_1         16L
#define M_INTERNAL_SUB_2         17L
#define M_INTERNAL_SUB_3         18L
#define M_PARAM_NB               19L
#define M_FATAL                  40L
#define M_BUFFER_ID              41L
#define M_REGION_OFFSET_X        42L
#define M_REGION_OFFSET_Y        43L
#define M_REGION_SIZE_X          44L
#define M_REGION_SIZE_Y          45L
#define M_MODIFIED_BUFFER        0x02000000L
#define M_UNHOOK                 0x04000000L
#define M_PARAM_VALUE            0x08000000L
#define M_PARAM_TYPE             0x10000000L
#define M_MESSAGE                0x20000000L
#define M_ERROR                  0x40000000L
#define M_NATIVE_ERROR           0x80000000L
#define M_ERROR_CURRENT          (M_ERROR|M_CURRENT)
#define M_ERROR_GLOBAL           (M_ERROR|M_GLOBAL)
#define M_ERROR_FATAL            (M_ERROR|M_FATAL)
#define M_ERROR_HANDLER_PTR      (M_EXTENDED_ATTRIBUTE | 0x00000008L)
#define M_ERROR_HANDLER_USER_PTR (M_EXTENDED_ATTRIBUTE | 0x00000009L)
#define M_IRQ_CONTROL            (M_EXTENDED_ATTRIBUTE | 0x0000000AL)

#define M_FUNCTION_NAME_SIZE  32L
#define M_ERROR_FUNCTION_NAME_SIZE M_FUNCTION_NAME_SIZE
#define M_ERROR_MESSAGE_SIZE  128L

#define M_NBFCTNAMEMAX         180  /* max number of function codes     */
#define M_NBERRMSGMAX           60  /* max number of error messages     */
#define M_NBSUBERRMSGMAX        10  /* max number of sub error messages */

#define M_FUNC_ERROR      (M_NBERRMSGMAX+1L) /* M_MFUNC error numbers   */

/* MappHookFunction() */
#define M_TRACE_START         1L
#define M_TRACE_END           2L

/* MappControl() */
#define M_PARAMETER_CHECK        1L
#define M_TRACE                  3L
#define M_PARAMETER              4L
#define M_MEMORY                 5L
#define M_PROCESSING             6L
#define M_PRINT_DISABLE          0L
#define M_PRINT_ENABLE           1L
#define M_CHECK_DISABLE          2L
#define M_CHECK_ENABLE           3L
#define M_COMPENSATION_DISABLE   4L
#define M_COMPENSATION_ENABLE    5L

/* MappInquire() */
#define M_VERSION                          1L
#define M_OBJECT_TYPE                      0x80000000L
#define M_LAST_PLATFORM_USE                7L
#define M_CURRENT_ERROR_HANDLER_PTR        8L
#define M_CURRENT_ERROR_HANDLER_USER_PTR   9L
#define M_GLOBAL_ERROR_HANDLER_PTR         10L
#define M_GLOBAL_ERROR_HANDLER_USER_PTR    11L
#define M_FATAL_ERROR_HANDLER_PTR          12L
#define M_FATAL_ERROR_HANDLER_USER_PTR     13L
#define M_TRACE_START_HANDLER_PTR          14L
#define M_TRACE_START_HANDLER_USER_PTR     15L
#define M_TRACE_END_HANDLER_PTR            16L
#define M_TRACE_END_HANDLER_USER_PTR       17L
#define M_MODIFIED_BUFFER_HANDLER_PTR      0x10000000L   // Must not interfere with M_ERROR
#define M_MODIFIED_BUFFER_HANDLER_USER_PTR 0x20000000L   // Must not interfere with M_ERROR


/* MappModify() */
#define M_SWAP_ID                1L

/************************************************************************
 * Msysxxxx() defines
 ************************************************************************/

/* MsysInquire() */
#define M_SYS_TYPE_PTR              1L                                         
#define M_SYS_NUMBER                2L                                         
#define M_SYS_INIT_FLAG             3L                                         
#define M_SYS_DISPLAY_NUM           4L                                         
#define M_SYS_DISPLAY_TYPE          5L                                         
#define M_SYS_DIGITIZER_NUM         6L                                         
#define M_SYS_DIGITIZER_TYPE        7L                                         
#define M_SYS_PROCESSOR_NUM         8L                                         
#define M_SYS_PROCESSOR_TYPE        9L                                         
#define M_SYS_TYPE                  10L                                        
#define M_PROCESSING_SYSTEM_TYPE    13L                                        
#define M_SYS_DISPLAY_LIST          14L                                        
#define M_SYS_NATIVE_ID             (M_EXTENDED_ATTRIBUTE | 0x00040000L)
#define M_SYS_TUNER_NUM             (M_EXTENDED_ATTRIBUTE | 36L)               
#define M_SYS_TUNER_TYPE            (M_EXTENDED_ATTRIBUTE | 37L)               
#define M_SYS_RGB_MODULE_NUM        (M_EXTENDED_ATTRIBUTE | 38L)               
#define M_SYS_RGB_MODULE_TYPE       (M_EXTENDED_ATTRIBUTE | 39L)
#define M_SYS_BOARD_TYPE            (M_EXTENDED_ATTRIBUTE | 40L)
#define M_LOW_LEVEL_SYSTEM_ID       (M_EXTENDED_ATTRIBUTE | 48L)
#define M_ON_BOARD_MEM_ADRS         (M_EXTENDED_ATTRIBUTE | 51L)
#define M_SYS_BOARD_REVISION        (M_EXTENDED_ATTRIBUTE | 52L)
#define M_SYS_DUAL_SCREEN_MODE      15L
#define M_ON_BOARD_VGA_ADRS         16L

/************************************************************************
 * MmeasFindMarker() anbd binary functions in BLOB module.
 ************************************************************************/
#define M_LENGTH                  48L


/************************************************************************
 * MmeasFindMarker(), MmeasCalculate(), MmeasGetResult(), MpatGetResult().
 ************************************************************************/
#define M_ANGLE        5L


/************************************************************************
 * MpatGetResult(), MmeasSetMarker()
 ************************************************************************/
#define M_ORIENTATION  7L

/************************************************************************
 * MblobControl() and/or MblobInquire() values and MmeasControl()
 ************************************************************************/
#define M_PIXEL_ASPECT_RATIO       5L

/************************************************************************
 * MfuncPrintMessage() defines
 ************************************************************************/
#define M_RESP_YES              1L
#define M_RESP_NO               2L
#define M_RESP_CANCEL           4L
#define M_RESP_YES_NO           (M_RESP_YES|M_RESP_NO)
#define M_RESP_YES_NO_CANCEL    (M_RESP_YES|M_RESP_NO|M_RESP_CANCEL)

/************************************************************************
 * Mfile() defines
 ************************************************************************/

#define M_NO_MEMORY             1L

/************************************************************************/
/* MIL OPTIONAL COMPILE DEFINES prefixes */

#if M_MIL_USE_DOS
// Much more to define for MS-DOS library generation under MSC or BC
   #define MCTYPE                         // Class header type
   #define MFTYPE                         // Exported Function type (16 bits)
   #define MFTYPE32                       // Exported Function type (32 bits)
   #define MFCTYPE                        // Exported C Function type (16 bits)
   #define MFCTYPE32                      // Exported C Function type (32 bits)
   #define MFTYPEHT                       // Non Exported Function type
   #define MPTYPE                         // Pointer and Reference type
   #define MFINLINE      inline           // Inline function type
   #define MHUGETYPE     huge             // To force HUGE pointers
   #define MFARTYPE      far              // To force FAR type pointers
   #define MINTFTYPE     MFTYPE           // Interrupt Function type (16 bits)   
#endif

#if M_MIL_USE_WINDOWS
// Much more to define for MS-WINDOWS 3.1 library generation under MSC or BC
   #ifdef _MSC_VER
      #define MCTYPE     far                 // Class header type on MSC
   #endif
   #ifdef __TURBOC__
      #define MCTYPE     huge                // Class header type on BC
   #endif
   #define MFTYPE        far pascal _export  // Exported Function type (16 bits)
   #define MFTYPE32                          // Exported Function type (32 bits)
   #define MFCTYPE       far _export         // Exported C Function type (16 bits)
   #define MFCTYPE32                         // Exported C Function type (32 bits)
   #define MFTYPEHT      far pascal          // Non Exported Function type
   #define MPTYPE        far                 // Pointer and Reference type
   #define MFINLINE      inline              // Inline function type
   #define MHUGETYPE     huge                // To force HUGE pointers
   #define MFARTYPE      far                 // To force FAR type pointers
   #define MINTFTYPE     far pascal _loadds  // Interrupt Function type (16 bits)   
#endif

#if M_MIL_USE_PHARLAP_LIB
// Much more to define for PHARLAP library generation under MSC or BC
   #define MCTYPE                         // Class header type
   #define MFTYPE                         // Exported Function type (16 bits)
   #define MFTYPE32                       // Exported Function type (32 bits)
   #define MFCTYPE                        // Exported C Function type (16 bits)
   #define MFCTYPE32                      // Exported C Function type (32 bits)
   #define MFTYPEHT                       // Non Exported Function type
   #define MPTYPE                         // Pointer and Reference type
   #define MFINLINE      inline           // Inline function type
   #define MHUGETYPE     huge             // To force HUGE pointers
   #define MFARTYPE      far              // To force FAR type pointers
   #define MINTFTYPE     MFTYPE           // Interrupt Function type (16 bits)   
#endif

#if M_MIL_USE_DOS_32
// Much more to define for MS-DOS library generation under DOS_32
   #define MCTYPE                         // Class header type on DOS_32
   #define MFTYPE        cdecl            // Exported Function type (16 bits)
   #define MFTYPE32                       // Exported Function type (32 bits)
   #define MFCTYPE       cdecl            // Exported C Function type (16 bits)
   #define MFCTYPE32                      // Exported C Function type (32 bits)
   #define MFTYPEHT                       // Non Exported Function type
   #define MPTYPE                         // Pointer and Reference type
   #define MFINLINE      inline           // Inline function type
   #define MHUGETYPE                      // To force HUGE pointers
   #define MFARTYPE                       // To force FAR type pointers
   #define MINTFTYPE     MFTYPE           // Interrupt Function type (16 bits)   
#endif

#if M_MIL_USE_NT_DOS
// Much more to define for MS-DOS library generation under NT
   #define MCTYPE                        // Class header type on NT
   #ifdef _MSC_VER
      #define MFTYPE    _stdcall              // Exported Function type (32 bits)
      #define MFTYPE32  __declspec(dllexport) // Exported Function type (32 bits)
      #define MFCTYPE   _stdcall              // Exported C Function type (32 bits)
      #define MFCTYPE32 __declspec(dllexport) // Exported C Function type (32 bits)
   #endif
   #ifdef __TURBOC__
      #define MFTYPE    _stdcall _export      // Exported Function type (32 bits)
      #define MFTYPE32                        // Not used
      #define MFCTYPE   _stdcall _export      // Exported C Function type (32 bits)
      #define MFCTYPE32                       // Not used
   #endif
   #define MFTYPEHT      _stdcall        // Non Exported Function type
   #define MPTYPE                        // Pointer and Reference type
   #define MFINLINE      inline          // Inline function type
   #define MHUGETYPE                     // To force HUGE pointers
   #define MFARTYPE                      // To force FAR type pointers
   #define MINTFTYPE     MFTYPE          // Interrupt Function type (16 bits)   
#endif

#if M_MIL_USE_NT_WINDOWS
// Much more to define for MS-WINDOWS NT 3.1 library generation under NT
   #define MCTYPE                          // Class header type on NT
   #ifdef _MSC_VER
      #ifdef WINDOWS_95_DRIVER_COMPILATION
         #define MFTYPE    _stdcall              // Exported Function type (32 bits)
         #define MFTYPE32                        // Exported Function type (32 bits)
         #define MFCTYPE   _stdcall              // Exported C Function type (32 bits)
         #define MFCTYPE32                       // Exported C Function type (32 bits)
      #else
         #define MFTYPE    _stdcall              // Exported Function type (32 bits)
         #define MFTYPE32  __declspec(dllexport) // Exported Function type (32 bits)
         #define MFCTYPE   _stdcall              // Exported C Function type (32 bits)
         #define MFCTYPE32 __declspec(dllexport) // Exported C Function type (32 bits)
      #endif
   #endif
   #ifdef __TURBOC__
      #define MFTYPE    _stdcall _export      // Exported Function type (32 bits)
      #define MFTYPE32                        // Not used
      #define MFCTYPE   _stdcall _export      // Exported C Function type (32 bits)
      #define MFCTYPE32                       // Not used
   #endif
   #define MFTYPEHT    _stdcall            // Non Exported Function type
   #define MPTYPE                          // Pointer and Reference type
   #define MFINLINE    inline              // Inline function type
   #define MHUGETYPE                       // To force HUGE pointers
   #define MFARTYPE                        // To force FAR type pointers
   #define MINTFTYPE   _stdcall            // Interrupt Function type (16 bits)   
#endif

/************************************************************************/
/* MIL error messages */
#if M_MIL_USE_ERROR_MESSAGE
#include "milerr.h"
#endif

/************************************************************************/
/* MIL command decoder functions */
#include "mildec.h"

/************************************************************************/
/* MIL library prototypes */
#include "milproto.h"

/************************************************************************/
/* MIL native mode defines prototypes */
#if M_MIL_USE_NATIVE
#include "milnat.h"
#endif

/************************************************************************/
/* MIL blob package defines prototypes */
#if M_MIL_USE_BLOB
#include "milblob.h"
#endif

/************************************************************************/
/* MIL pat package defines prototypes */
#if M_MIL_USE_PAT
#include "milpat.h"
#endif

/************************************************************************/
/* MIL ocr package defines prototypes */
#if M_MIL_USE_OCR
#include "milocr.h"
#endif

/************************************************************************/
/* MIL meas package defines prototypes */
#if M_MIL_USE_MEAS
#include "milmeas.h"
#endif

/************************************************************************/
/* MIL Meteor specific defines */
#if M_MIL_USE_METEOR
#include "meteor.h"
#endif

/************************************************************************/
/* MIL Pulsar specific defines */
#if M_MIL_USE_PULSAR
#include "pulsar.h"
#endif

/************************************************************************/
/* Windows extensions */
#if (defined(_INC_WINDOWS) || defined(_WINDOWS_) || defined(__WINDOWS_H))
   #include "mwinext.h"
#endif

/************************************************************************/
/* Alias for Obsoleted function in rev 2.1 */
#define MnatHostBufCreate2d     MnatBufCreate2d
#define MnatHostBufCreateColor  MnatBufCreateColor
#define MnatHostBufDestroy      MnatBufDestroy

/************************************************************************/
/* Alias for Obsoleted function in rev 3.0 */
#define MnatHostBufGetPointer   MnatBufGetPointer
#define MnatHostBufGetPitch     MnatBufGetPitch  

#endif
