/***************************************************************************/
/*

    Filename:  MILMEAS.H
    Owner   :  Matrox Imaging dept.
    Rev     :  $Revision:   1.0  $
    Content :  This file contains the defines for the MIL measurement
               module. (Mmeas...).

    COPYRIGHT (c) 1993  Matrox Electronic Systems Ltd.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MILMEAS_H__
#define __MILMEAS_H__

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
{
#endif


/********************************************************************
 * CAPI defines
 ********************************************************************/

/* MmeasAllocMarker */
#define M_POINT                     1L
#define M_EDGE                      2L
#define M_STRIPE                    3L

/* MmeasAllocResult */
#define M_CALCULATE                 1L

/* MmeasSetMarker */
/* #define M_POSITION_X             3L (already defined in mil.h) */
/* #define M_POSITION_Y             4L (already defined in mil.h) */
/* #define M_ORIENTATION            7L (already defined in milpat.h) */
         #define M_VERTICAL         1L
         #define M_HORIZONTAL       2L
         #define M_ANY              0x11000000L
#define M_WIDTH_VARIATION           8L
#define M_BOX_SIZE                  9L
#define M_BOX_ORIGIN                10L
#define M_BOX_CENTER                11L
#define M_BOX_ANGLE                 12L
#define M_BOX_FIRST_CENTER          13L
#define M_BOX_SECOND_CENTER         14L
#define M_NUMBER                    15L
/* #define M_WIDTH                 512L  (already defined below) */
#define M_NUMBER_MIN                17L
#define M_NUMBER_MAX                18L
#define M_SPACING                   19L
#define M_DEBUG_FLAG                21L
#define M_MARKER_REFERENCE          22L
#define M_POSITION                  64L
#define M_CONTRAST                 128L
#define M_CONTRAST_VARIATION       256L
#define M_POLARITY                2048L
         #define M_POSITIVE   2L
         #define M_NEGATIVE  -2L  /*Must be the additive inverse of M_POSITIVE*/
         #define M_OPPOSITE   3L
         #define M_SAME       4L
         /* #define M_ANY   0x11000000L (already defined above) */

/* MmeasControl */
/* #define M_PIXEL_ASPECT_RATIO       5L  (already defined in milblob.h) */
#define M_ZERO_OFFSET_X                131L
#define M_ZERO_OFFSET_Y                132L
#define M_SPEED                        129L
#define M_ACCURACY                     130L
#define M_EDGE_FORCE_FACTOR            133L
#define M_EDGE_SENSITIVITY_FACTOR      137L
#define M_ANGLE_PRECISION_NB_LINES     134L
#define M_ANGLE_BOX_OF_INTEREST_SIZE   134L
#define M_PIXEL_ASPECT_RATIO_INPUT     135L
#define M_PIXEL_ASPECT_RATIO_OUTPUT    136L
         /* #define M_NORMAL 1L (already defined in mil.h) */
         #define M_CORRECTED  2L

/* MmeasInquire */
/* All of the above (MmeasSetMarker() and MmeasControl()) */
#define M_MARKER_TYPE              100L
/* #define M_RESULT_TYPE             1L (already defined in mil.h) */
#define M_CONTROL_FLAG             102L
/* #define M_TYPE_LONG         0x40000L (already defined in mil.h) */


/* MmeasFindMarker (!!!BitField!!!) */
/* #define M_POSITION            0x0040L (already defined above) */
#define M_POSITION_VARIATION     0x1000L
/* #define M_POLARITY            0x0800L (already defined above) */
/* #define M_CONTRAST            0x0080L (already defined above) */
#define M_WIDTH                  0x0200L
/* #define M_WIDTH_VARIATION     0x0008L (already defined above) */
/* #define M_LENGTH              0x0030L (already defined in milblob.h) */
/* #define M_ANGLE               0x0005L (already defined in milpat.h) */
#define M_LINE_EQUATION          0x0400L

/* MmeasCalculate (!!!BitField!!!) */
#define M_DISTANCE                0x002L
/* #define M_LINE_EQUATION        0x400L (already defined */
/* #define M_ANGLE                0x005L (already defined in milpat.h) */

/* MmeasGetResult */
#define M_VALID_FLAG                 1L
/* #define M_SCORE                   2L (already defined in milpat.h) */
/* #define M_POSITION_X              3L (already defined in mil.h) */
/* #define M_POSITION_Y              4L (already defined in mil.h) */
/* #define M_POSITION               64L (already defined above) */
/* #define M_WIDTH                 512L (already defined above) */
/* #define M_WIDTH_VARIATION         8L (already defined above) */
/* #define M_CONTRAST              128L (already defined above) */
/* (!!! BitField !!!) */
#define M_EDGE_FIRST               0x00100000L
#define M_EDGE_SECOND              0x00200000L
/* #define M_TYPE_LONG             0x00040000L (already defined in mil.h) */
/* #define M_POSITION_VARIATION       0x1000L (already defined above) */

#define M_DISTANCE_X                 1L
#define M_DISTANCE_Y                 3L
/* #define M_DISTANCE                2L (already defined above) */
/* #define M_ANGLE                   5L (already defined in milpat.h) */

/* #define M_LINE_EQUATION        1024L (already defined above) */
#define M_LINE_EQUATION_SLOPE     1025L
#define M_LINE_EQUATION_INTERCEPT 1026L

/* Other defines are in MIL.H */

/********************************************************************
 * Utility defines
 ********************************************************************/

#define M_INFINITE_SLOPE    (1.0E+300)

/********************************************************************
 * Function prototypes
 ********************************************************************/

MFTYPE32 MIL_ID MFTYPE MmeasAllocMarker  (MIL_ID SystemId,
                                          long   MarkerType,
                                          long   ControlFlag,
                                          MIL_ID *MarkerIdPtr);
MFTYPE32 MIL_ID MFTYPE MmeasAllocResult  (MIL_ID SystemId,
                                          long   ResultBufferType,
                                          MIL_ID MPTYPE *ResultIdPtr);
MFTYPE32 MIL_ID MFTYPE MmeasAllocContext (MIL_ID SystemId,
                                          long   ControlFlag,
                                          MIL_ID *ContextId);
MFTYPE32 void   MFTYPE MmeasFree         (MIL_ID MarkerOrResultIdOrContextId);
MFTYPE32 void   MFTYPE MmeasSaveMarker   (char   *FileName,
                                          MIL_ID MarkerId,
                                          long   ControlFlag);
MFTYPE32 MIL_ID MFTYPE MmeasRestoreMarker(char   *FileName,
                                          MIL_ID SystemId,
                                          long   ControlFlag,
                                          MIL_ID *MarkerIdPtr);
MFTYPE32 void   MFTYPE MmeasSetMarker    (MIL_ID MarkerId,
                                          long   Parameter,
                                          double FirstValue,
                                          double SecondValue);
MFTYPE32 void   MFTYPE MmeasFindMarker   (MIL_ID ContextId,
                                          MIL_ID ImageId,
                                          MIL_ID MarkerId,
                                          long   MeasurementList);
MFTYPE32 void   MFTYPE MmeasCalculate    (MIL_ID ContextID,
                                          MIL_ID Marker1Id,
                                          MIL_ID Marker2Id,
                                          MIL_ID ResultId,
                                          long   MeasurementList);
MFTYPE32 void   MFTYPE MmeasGetResult    (MIL_ID MarkerOrResultId,
                                          long   ResultType,
                                          void   *FirstResultPtr,
                                          void   *SecondResultPtr);
MFTYPE32 long   MFTYPE MmeasInquire      (MIL_ID MarkerIdOrResultIdOrContextId,
                                          long   ParamToInquire,
                                          void   *FirstValuePtr,
                                          void   *SecondValuePtr);
MFTYPE32 void   MFTYPE MmeasControl      (MIL_ID ContextId,
                                          long   ControlType,
                                          double Value);


/* C++ directive if needed */
#ifdef __cplusplus
}
#endif

#endif /* __MILMEAS_H__ */
