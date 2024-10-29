/***************************************************************************/
/*

    Filename:  MILBLOB.H
    Owner   :  Matrox Imaging dept.
    Rev     :  $Revision:   1.0  $
    Content :  This file contains the defines for the MIL blob
               analysis module. (Mblob...).

    COPYRIGHT (c) 1993  Matrox Electronic Systems Ltd.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MILBLOB_H__
#define __MILBLOB_H__

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
{
#endif

/* Binary only */

#define M_LABEL_VALUE              1L
#define M_AREA                     2L
#define M_PERIMETER                3L
#define M_FERET_X                  4L
#define M_FERET_Y                  5L
#define M_BOX_X_MIN                6L
#define M_BOX_Y_MIN                7L
#define M_BOX_X_MAX                8L
#define M_BOX_Y_MAX                9L
#define M_FIRST_POINT_X           10L
#define M_FIRST_POINT_Y           11L
#define M_AXIS_PRINCIPAL_LENGTH   12L
#define M_AXIS_SECONDARY_LENGTH   13L
#define M_FERET_MIN_DIAMETER      14L
#define M_FERET_MIN_ANGLE         15L
#define M_FERET_MAX_DIAMETER      16L
#define M_FERET_MAX_ANGLE         17L
#define M_FERET_MEAN_DIAMETER     18L
#define M_CONVEX_AREA             19L
#define M_CONVEX_PERIMETER        20L
#define M_X_MIN_AT_Y_MIN          21L
#define M_X_MAX_AT_Y_MAX          22L
#define M_Y_MIN_AT_X_MAX          23L
#define M_Y_MAX_AT_X_MIN          24L
#define M_COMPACTNESS             25L
#define M_NUMBER_OF_HOLES         26L
#define M_FERET_ELONGATION        27L
#define M_ROUGHNESS               28L
#define M_EULER_NUMBER            47L
#define M_BREADTH                 49L
#define M_ELONGATION              50L
#define M_INTERCEPT_0             51L
#define M_INTERCEPT_45            52L
#define M_INTERCEPT_90            53L
#define M_INTERCEPT_135           54L
#define M_NUMBER_OF_RUNS          55L
#define M_GENERAL_FERET        0x400L

/* Greyscale only (ie, trivial for binary) */

#define M_SUM_PIXEL               29L
#define M_MIN_PIXEL               30L
#define M_MAX_PIXEL               31L
#define M_MEAN_PIXEL              32L
#define M_SIGMA_PIXEL             33L
#define M_SUM_PIXEL_SQUARED       46L

/* Binary or greyscale (might want both for a greyscale image) */

#define M_CENTER_OF_GRAVITY_X     34L
#define M_CENTER_OF_GRAVITY_Y     35L
#define M_MOMENT_X0_Y1            36L
#define M_MOMENT_X1_Y0            37L
#define M_MOMENT_X1_Y1            38L
#define M_MOMENT_X0_Y2            39L
#define M_MOMENT_X2_Y0            40L
#define M_MOMENT_CENTRAL_X1_Y1    41L
#define M_MOMENT_CENTRAL_X0_Y2    42L
#define M_MOMENT_CENTRAL_X2_Y0    43L
#define M_AXIS_PRINCIPAL_ANGLE    44L
#define M_AXIS_SECONDARY_ANGLE    45L
#define M_GENERAL_MOMENT       0x800L

/* General moment type */

#define M_ORDINARY             0x400L
#define M_CENTRAL              0x800L

/* Short cuts for enabling multiple features */

#define M_ALL_FEATURES         0x100L   /* All except general Feret */
#define M_BOX                  0x101L
#define M_CONTACT_POINTS       0x102L
#define M_CENTER_OF_GRAVITY    0x103L
#define M_NO_FEATURES          0x104L   /* Still do label and area */

/* MblobControl() and/or MblobInquire() values */

#define M_BLOB_IDENTIFICATION      2L
#define M_LATTICE                  3L
#define M_FOREGROUND_VALUE         4L
#define M_NUMBER_OF_FERETS         6L
#define M_RESET                    9L
#define M_IDENTIFIER_TYPE         15L
#define M_MAX_LABEL               16L

/* Blob identification values */

#define M_WHOLE_IMAGE              1L
#define M_INDIVIDUAL               2L
#define M_LABELLED                 4L

/* Foreground values */

#define M_NONZERO               0x80L
#define M_ZERO                 0x100L
#define M_NON_ZERO          M_NONZERO

/* Conditional test not in MIL.H */

#define M_ALWAYS              0L

/* MblobReconstruct() defines */

#define M_RECONSTRUCT_FROM_SEED     1L
#define M_ERASE_BORDER_BLOBS        2L
#define M_FILL_HOLES                3L
#define M_EXTRACT_HOLES             4L
#define M_SEED_PIXELS_ALL_IN_BLOBS  1L
#define M_FOREGROUND_ZERO           2L

/* Miscellaneous */

#define M_ALL_BLOBS            0x105L
#define M_INCLUDED_BLOBS       0x106L
#define M_EXCLUDED_BLOBS       0x107L
#define M_INCLUDE                  1L
#define M_EXCLUDE                  2L
#define M_DELETE                   3L
#define M_MIN_FERETS               2L
#define M_MAX_FERETS              64L
#define M_INCLUDE_ONLY         0x101L
#define M_EXCLUDE_ONLY         0x102L

/* Other defines are in MIL.H */


/********************************************************************
 * Error codes
 ********************************************************************/

#define M_BLOB_RESULT_ID_ERROR         (2000+M_FUNC_ERROR)
#define M_BLOB_FEATURE_ID_ERROR        (2001+M_FUNC_ERROR)
                                      
/* Memory errors */
#define M_BLOB_MEMORY_ERROR            (2050+M_FUNC_ERROR)
#define M_BLOB_NO_IDS_ERROR            (2051+M_FUNC_ERROR)

/* Processing errors */
#define M_BLOB_PARAMETER_ERROR         (2100+M_FUNC_ERROR)
#define M_BLOB_NOT_AVAILABLE_ERROR     (2101+M_FUNC_ERROR)
#define M_BLOB_INTERNAL_ERROR          (2102+M_FUNC_ERROR)
#define M_BLOB_TOO_COMPLEX_ERROR       (2103+M_FUNC_ERROR)
#define M_BLOB_HW_LIMITATION_ERROR     (2104+M_FUNC_ERROR)
#define M_BLOB_LIMITATION_ERROR        (2105+M_FUNC_ERROR)


/********************************************************************
 * Function prototypes
 ********************************************************************/

MFTYPE32 MIL_ID MFTYPE MblobAllocFeatureList(MIL_ID SystemId,MIL_ID MPTYPE *FeatureListPtr);
MFTYPE32 MIL_ID MFTYPE MblobAllocResult(MIL_ID SystemId, MIL_ID MPTYPE *BlobResIdPtr);
MFTYPE32 void MFTYPE MblobCalculate(MIL_ID BlobIdentImageId, MIL_ID GreyImageId,
              MIL_ID FeatureListId, MIL_ID BlobResId);
MFTYPE32 void MFTYPE MblobControl(MIL_ID BlobResId, long ProcMode, double Value);
MFTYPE32 void MFTYPE MblobFill(MIL_ID BlobResId, MIL_ID TargetImageId, long Mode,
              long Value);
MFTYPE32 void MFTYPE MblobFree(MIL_ID BlobResId);
MFTYPE32 long MFTYPE MblobGetLabel(MIL_ID BlobResId, long XPos, long YPos,
              long MPTYPE *BlobLabelPtr);
MFTYPE32 long MFTYPE MblobGetNumber(MIL_ID BlobResId, long MPTYPE *CountPtr);
MFTYPE32 void MFTYPE MblobGetResult(MIL_ID BlobResId, long Feature,
              void MPTYPE *TargetArrayPtr);
MFTYPE32 void MFTYPE MblobGetResultSingle(MIL_ID BlobResId, long BlobLabel,
              long Feature, void MPTYPE *ValuePtr);
MFTYPE32 void MFTYPE MblobGetRuns(MIL_ID BlobResId, long BlobLabel, long ArrayType,
              void MPTYPE *RunXPtr, void MPTYPE *RunYPtr, void MPTYPE *RunLengthPtr);
MFTYPE32 void MFTYPE MblobInquire(MIL_ID BlobResId, long ProcMode, void MPTYPE *ValuePtr);
MFTYPE32 void MFTYPE MblobLabel(MIL_ID BlobResId, MIL_ID TargetImageId, long Mode);
MFTYPE32 void MFTYPE MblobSelect(MIL_ID BlobResId, long Operation, long Feature,
              long Condition, double CondLow, double CondHigh);
MFTYPE32 void MFTYPE MblobSelectFeature(MIL_ID FeatureListId, long Feature);
MFTYPE32 void MFTYPE MblobSelectFeret(MIL_ID FeatureListId, double Angle);
MFTYPE32 void MFTYPE MblobSelectMoment(MIL_ID FeatureListId, long MomType,
              long XMomOrder, long YMomOrder);
MFTYPE32 void MFTYPE MblobReconstruct(MIL_ID srce_image_id, MIL_ID seed_image_id,
              MIL_ID dest_image_id, long operation, long mode);

/* C++ directive if needed */
#ifdef __cplusplus
}
#endif

#endif /* __MILBLOB_H__ */
