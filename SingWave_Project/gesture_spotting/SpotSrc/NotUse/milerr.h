/***************************************************************************/
/*

    Filename:  MILERR.H
    Owner   :  Matrox Imaging dept.
    Rev     :  $Revision:   1.0  $
    Content :  This file contains the defines that are used by the
               mil functions to generate error codes and messages that
               will be used by the MIL Application Error Logging and
               other error related functions.

    COPYRIGHT (c) 1993  Matrox Electronic Systems Ltd.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MILERR_H
#define __MILERR_H

/*
First line is the error code.
Second line is the error message for this code.
Other 9 lines are optional sub-messages with more detailed information.

------------------------------------------------------------------------
-                                                                      -
-  WARNING: Strings (including the NULL character at the end) should   -
-           never be longer than M_ERROR_MESSAGE_SIZE (128L).          -
-           No checking is done anywhere in the code to ensure this.   -
-                                                                      -
------------------------------------------------------------------------
*/


#if (M_MIL_USE_DOS || M_MIL_USE_PHARLAP_LIB) && defined(__TURBOC__)
  #define NO_MSG             "Null."    /* empty error message          */
  #define NO_SUBMSG          "Null."    /* empty sub-error message      */
  #define NO_FCTNAME         "Null."    /* empty function name          */
#else
  #define NO_MSG             (char *)0  /* empty error message          */
  #define NO_SUBMSG          (char *)0  /* empty sub-error message      */
  #define NO_FCTNAME         (char *)0  /* empty function name          */
#endif

/* LIST OF ERROR CODES AND MESSAGES */

#define M_NULL_ERROR             0L
#define M_ERR_0_MSG              "Null."
#define M_ERR_0_SUBMSG_1         "Null."
#define M_ERR_0_SUBMSG_2         "Null."
#define M_ERR_0_SUBMSG_3         "Null."
#define M_ERR_0_SUBMSG_4         "Null."
#define M_ERR_0_SUBMSG_5         "Null."
#define M_ERR_0_SUBMSG_6         "Null."
#define M_ERR_0_SUBMSG_7         "Null."
#define M_ERR_0_SUBMSG_8         "Null."
#define M_ERR_0_SUBMSG_9         "Null."

#define M_XX1XX_ERROR            1L
#define M_ERR_1_MSG              NO_MSG
#define M_ERR_1_SUBMSG_1         NO_SUBMSG
#define M_ERR_1_SUBMSG_2         NO_SUBMSG
#define M_ERR_1_SUBMSG_3         NO_SUBMSG
#define M_ERR_1_SUBMSG_4         NO_SUBMSG
#define M_ERR_1_SUBMSG_5         NO_SUBMSG
#define M_ERR_1_SUBMSG_6         NO_SUBMSG
#define M_ERR_1_SUBMSG_7         NO_SUBMSG
#define M_ERR_1_SUBMSG_8         NO_SUBMSG
#define M_ERR_1_SUBMSG_9         NO_SUBMSG

#define M_XX2XX_ERROR            2L
#define M_ERR_2_MSG              NO_MSG
#define M_ERR_2_SUBMSG_1         NO_SUBMSG
#define M_ERR_2_SUBMSG_2         NO_SUBMSG
#define M_ERR_2_SUBMSG_3         NO_SUBMSG
#define M_ERR_2_SUBMSG_4         NO_SUBMSG
#define M_ERR_2_SUBMSG_5         NO_SUBMSG
#define M_ERR_2_SUBMSG_6         NO_SUBMSG
#define M_ERR_2_SUBMSG_7         NO_SUBMSG
#define M_ERR_2_SUBMSG_8         NO_SUBMSG
#define M_ERR_2_SUBMSG_9         NO_SUBMSG

#define M_XX3XX_ERROR            3L
#define M_ERR_3_MSG              NO_SUBMSG
#define M_ERR_3_SUBMSG_1         NO_SUBMSG
#define M_ERR_3_SUBMSG_2         NO_SUBMSG
#define M_ERR_3_SUBMSG_3         NO_SUBMSG
#define M_ERR_3_SUBMSG_4         NO_SUBMSG
#define M_ERR_3_SUBMSG_5         NO_SUBMSG
#define M_ERR_3_SUBMSG_6         NO_SUBMSG
#define M_ERR_3_SUBMSG_7         NO_SUBMSG
#define M_ERR_3_SUBMSG_8         NO_SUBMSG
#define M_ERR_3_SUBMSG_9         NO_SUBMSG

#define M_XX4XX_ERROR            4L
#define M_ERR_4_MSG              NO_MSG
#define M_ERR_4_SUBMSG_1         NO_SUBMSG
#define M_ERR_4_SUBMSG_2         NO_SUBMSG
#define M_ERR_4_SUBMSG_3         NO_SUBMSG
#define M_ERR_4_SUBMSG_4         NO_SUBMSG
#define M_ERR_4_SUBMSG_5         NO_SUBMSG
#define M_ERR_4_SUBMSG_6         NO_SUBMSG
#define M_ERR_4_SUBMSG_7         NO_SUBMSG
#define M_ERR_4_SUBMSG_8         NO_SUBMSG
#define M_ERR_4_SUBMSG_9         NO_SUBMSG

#define M_XX5XX_ERROR            5L
#define M_ERR_5_MSG              NO_SUBMSG
#define M_ERR_5_SUBMSG_1         NO_SUBMSG
#define M_ERR_5_SUBMSG_2         NO_SUBMSG
#define M_ERR_5_SUBMSG_3         NO_SUBMSG
#define M_ERR_5_SUBMSG_4         NO_SUBMSG
#define M_ERR_5_SUBMSG_5         NO_SUBMSG
#define M_ERR_5_SUBMSG_6         NO_SUBMSG
#define M_ERR_5_SUBMSG_7         NO_SUBMSG
#define M_ERR_5_SUBMSG_8         NO_SUBMSG
#define M_ERR_5_SUBMSG_9         NO_SUBMSG

#define M_INVALID_PARAM_ERROR    6L
#define M_ERR_6_MSG              "Invalid parameter."
#define M_ERR_6_SUBMSG_1         "Bad parameter value."
#define M_ERR_6_SUBMSG_2         "One parameter does not reside within the buffer's limits."
#define M_ERR_6_SUBMSG_3         "Pointer must be non-null."
#define M_ERR_6_SUBMSG_4         "Parameter 1 not in supported list."
#define M_ERR_6_SUBMSG_5         "Parameter 2 not in supported list."
#define M_ERR_6_SUBMSG_6         "No graphic text font selected."
#define M_ERR_6_SUBMSG_7         "Cannot allocate kernel deeper than 8 bits."
#define M_ERR_6_SUBMSG_8         "Result buffer too small to hold result."
#define M_ERR_6_SUBMSG_9         "Scale factors out of supported range."

#define M_OVERSCAN_ERROR         7L
#define M_ERR_7_MSG              "Overscan processing error."
#define M_ERR_7_SUBMSG_1         "Cannot allocate temporary buffer in memory."
#define M_ERR_7_SUBMSG_2         "Buffer too small to perform the selected overscan"
#define M_ERR_7_SUBMSG_3         NO_SUBMSG
#define M_ERR_7_SUBMSG_4         NO_SUBMSG
#define M_ERR_7_SUBMSG_5         NO_SUBMSG
#define M_ERR_7_SUBMSG_6         NO_SUBMSG
#define M_ERR_7_SUBMSG_7         NO_SUBMSG
#define M_ERR_7_SUBMSG_8         NO_SUBMSG
#define M_ERR_7_SUBMSG_9         NO_SUBMSG

#define M_ALLOC_ERROR            8L
#define M_ERR_8_MSG              "Allocation error."
#define M_ERR_8_SUBMSG_1         "Not enough memory to allocate application."
#define M_ERR_8_SUBMSG_2         "Application already exists for this task."
#define M_ERR_8_SUBMSG_3         "Cannot allocate temporary buffer in memory."
#define M_ERR_8_SUBMSG_4         "Not enough memory to allocate buffer."
#define M_ERR_8_SUBMSG_5         "Cannot allocate system."
#define M_ERR_8_SUBMSG_6         "Cannot allocate digitizer."
#define M_ERR_8_SUBMSG_7         "Cannot allocate display."
#define M_ERR_8_SUBMSG_8         "Not enough host memory to allocate buffer."
#define M_ERR_8_SUBMSG_9         "Buffer type not supported."

#define M_CHILD_ERROR            9L
#define M_ERR_9_MSG              "Child allocation error."
#define M_ERR_9_SUBMSG_1         NO_SUBMSG
#define M_ERR_9_SUBMSG_2         NO_SUBMSG
#define M_ERR_9_SUBMSG_3         "Not enough memory to allocate child buffer."
#define M_ERR_9_SUBMSG_4         "Cannot allocate temporary child buffer in memory."
#define M_ERR_9_SUBMSG_5         NO_SUBMSG
#define M_ERR_9_SUBMSG_6         NO_SUBMSG
#define M_ERR_9_SUBMSG_7         NO_SUBMSG
#define M_ERR_9_SUBMSG_8         NO_SUBMSG
#define M_ERR_9_SUBMSG_9         NO_SUBMSG

#define M_ACCESS_ERROR           10L
#define M_ERR_10_MSG             "Buffer access error."
#define M_ERR_10_SUBMSG_1        "Cannot M_RESTORE a M_RAW file format buffer."
#define M_ERR_10_SUBMSG_2        "Cannot export buffer."
#define M_ERR_10_SUBMSG_3        "Source buffer must be a M_IMAGE buffer."
#define M_ERR_10_SUBMSG_4        "Cannot import buffer."
#define M_ERR_10_SUBMSG_5        "Cannot restore buffer."
#define M_ERR_10_SUBMSG_6        NO_SUBMSG
#define M_ERR_10_SUBMSG_7        NO_SUBMSG
#define M_ERR_10_SUBMSG_8        NO_SUBMSG
#define M_ERR_10_SUBMSG_9        NO_SUBMSG

#define M_DISPLAY_ERROR          11L
#define M_ERR_11_MSG             "Display error."
#define M_ERR_11_SUBMSG_1        "Display and buffer must belong to same system."
#define M_ERR_11_SUBMSG_2        "Display Lut dimensions are not compatible with the user Lut."
#define M_ERR_11_SUBMSG_3        "Cannot associate a M_PSEUDO Lut with a monochrome display."
#define M_ERR_11_SUBMSG_4        "Zoom factors must be between -16 and 16 inclusive (except 0)."
#define M_ERR_11_SUBMSG_5        "Buffer not currently selected on display."
#define M_ERR_11_SUBMSG_6        NO_SUBMSG
#define M_ERR_11_SUBMSG_7        NO_SUBMSG
#define M_ERR_11_SUBMSG_8        NO_SUBMSG
#define M_ERR_11_SUBMSG_9        NO_SUBMSG

#define M_XX12XX_ERROR           12L
#define M_ERR_12_MSG             NO_MSG
#define M_ERR_12_SUBMSG_1        NO_SUBMSG
#define M_ERR_12_SUBMSG_2        NO_SUBMSG
#define M_ERR_12_SUBMSG_3        NO_SUBMSG
#define M_ERR_12_SUBMSG_4        NO_SUBMSG
#define M_ERR_12_SUBMSG_5        NO_SUBMSG
#define M_ERR_12_SUBMSG_6        NO_SUBMSG
#define M_ERR_12_SUBMSG_7        NO_SUBMSG
#define M_ERR_12_SUBMSG_8        NO_SUBMSG
#define M_ERR_12_SUBMSG_9        NO_SUBMSG

#define M_DIGITIZER_ERROR        13L
#define M_ERR_13_MSG             NO_MSG
#define M_ERR_13_SUBMSG_1        NO_SUBMSG
#define M_ERR_13_SUBMSG_2        NO_SUBMSG
#define M_ERR_13_SUBMSG_3        NO_SUBMSG
#define M_ERR_13_SUBMSG_4        NO_SUBMSG
#define M_ERR_13_SUBMSG_5        NO_SUBMSG
#define M_ERR_13_SUBMSG_6        NO_SUBMSG
#define M_ERR_13_SUBMSG_7        NO_SUBMSG
#define M_ERR_13_SUBMSG_8        NO_SUBMSG
#define M_ERR_13_SUBMSG_9        NO_SUBMSG

#define M_XX14XX_ERROR           14L
#define M_ERR_14_MSG             NO_MSG
#define M_ERR_14_SUBMSG_1        NO_SUBMSG
#define M_ERR_14_SUBMSG_2        NO_SUBMSG
#define M_ERR_14_SUBMSG_3        NO_SUBMSG
#define M_ERR_14_SUBMSG_4        NO_SUBMSG
#define M_ERR_14_SUBMSG_5        NO_SUBMSG
#define M_ERR_14_SUBMSG_6        NO_SUBMSG
#define M_ERR_14_SUBMSG_7        NO_SUBMSG
#define M_ERR_14_SUBMSG_8        NO_SUBMSG
#define M_ERR_14_SUBMSG_9        NO_SUBMSG

#define M_XX15XX_ERROR           15L
#define M_ERR_15_MSG             NO_MSG
#define M_ERR_15_SUBMSG_1        NO_SUBMSG
#define M_ERR_15_SUBMSG_2        NO_SUBMSG
#define M_ERR_15_SUBMSG_3        NO_SUBMSG
#define M_ERR_15_SUBMSG_4        NO_SUBMSG
#define M_ERR_15_SUBMSG_5        NO_SUBMSG
#define M_ERR_15_SUBMSG_6        NO_SUBMSG
#define M_ERR_15_SUBMSG_7        NO_SUBMSG
#define M_ERR_15_SUBMSG_8        NO_SUBMSG
#define M_ERR_15_SUBMSG_9        NO_SUBMSG

#define M_XX16XX_ERROR           16L
#define M_ERR_16_MSG             NO_MSG
#define M_ERR_16_SUBMSG_1        NO_SUBMSG
#define M_ERR_16_SUBMSG_2        NO_SUBMSG
#define M_ERR_16_SUBMSG_3        NO_SUBMSG
#define M_ERR_16_SUBMSG_4        NO_SUBMSG
#define M_ERR_16_SUBMSG_5        NO_SUBMSG
#define M_ERR_16_SUBMSG_6        NO_SUBMSG
#define M_ERR_16_SUBMSG_7        NO_SUBMSG
#define M_ERR_16_SUBMSG_8        NO_SUBMSG
#define M_ERR_16_SUBMSG_9        NO_SUBMSG

#define M_XX17XX_ERROR           17L
#define M_ERR_17_MSG             NO_MSG
#define M_ERR_17_SUBMSG_1        NO_SUBMSG
#define M_ERR_17_SUBMSG_2        NO_SUBMSG
#define M_ERR_17_SUBMSG_3        NO_SUBMSG
#define M_ERR_17_SUBMSG_4        NO_SUBMSG
#define M_ERR_17_SUBMSG_5        NO_SUBMSG
#define M_ERR_17_SUBMSG_6        NO_SUBMSG
#define M_ERR_17_SUBMSG_7        NO_SUBMSG
#define M_ERR_17_SUBMSG_8        NO_SUBMSG
#define M_ERR_17_SUBMSG_9        NO_SUBMSG

#define M_XX18XX_ERROR           18L
#define M_ERR_18_MSG             NO_MSG
#define M_ERR_18_SUBMSG_1        NO_SUBMSG
#define M_ERR_18_SUBMSG_2        NO_SUBMSG
#define M_ERR_18_SUBMSG_3        NO_SUBMSG
#define M_ERR_18_SUBMSG_4        NO_SUBMSG
#define M_ERR_18_SUBMSG_5        NO_SUBMSG
#define M_ERR_18_SUBMSG_6        NO_SUBMSG
#define M_ERR_18_SUBMSG_7        NO_SUBMSG
#define M_ERR_18_SUBMSG_8        NO_SUBMSG
#define M_ERR_18_SUBMSG_9        NO_SUBMSG

#define M_XX19XX_ERROR           19L
#define M_ERR_19_MSG             NO_MSG
#define M_ERR_19_SUBMSG_1        NO_SUBMSG
#define M_ERR_19_SUBMSG_2        NO_SUBMSG
#define M_ERR_19_SUBMSG_3        NO_SUBMSG
#define M_ERR_19_SUBMSG_4        NO_SUBMSG
#define M_ERR_19_SUBMSG_5        NO_SUBMSG
#define M_ERR_19_SUBMSG_6        NO_SUBMSG
#define M_ERR_19_SUBMSG_7        NO_SUBMSG
#define M_ERR_19_SUBMSG_8        NO_SUBMSG
#define M_ERR_19_SUBMSG_9        NO_SUBMSG

#define M_TIFF_ERROR             20L
#define M_ERR_20_MSG             "TIFF file access error."
#define M_ERR_20_SUBMSG_1        "Cannot open file."
#define M_ERR_20_SUBMSG_2        "Cannot close file."
#define M_ERR_20_SUBMSG_3        "Cannot read file."
#define M_ERR_20_SUBMSG_4        "Cannot read file."
#define M_ERR_20_SUBMSG_5        "Cannot write to file."
#define M_ERR_20_SUBMSG_6        "Cannot allocate temporary buffer in memory."
#define M_ERR_20_SUBMSG_7        "The image file does not conform to the TIFF 6.0 specification."
#define M_ERR_20_SUBMSG_8        "Wrong Byte Order, Only INTEL Byte Ordering supported."
#define M_ERR_20_SUBMSG_9        "Not a TIFF file."

#define M_MIL_FILE_ERROR         21L
#define M_ERR_21_MSG             "MIL file access error."
#define M_ERR_21_SUBMSG_1        "Cannot open file."
#define M_ERR_21_SUBMSG_2        "Cannot close file."
#define M_ERR_21_SUBMSG_3        "Cannot read file."
#define M_ERR_21_SUBMSG_4        "Cannot read file."
#define M_ERR_21_SUBMSG_5        "Cannot write to file."
#define M_ERR_21_SUBMSG_6        "Cannot allocate temporary buffer in memory."
#define M_ERR_21_SUBMSG_7        "The image file does not conform to the TIFF 6.0 specification."
#define M_ERR_21_SUBMSG_8        "Wrong Byte Order, Only INTEL Byte Ordering supported."
#define M_ERR_21_SUBMSG_9        "Not a MIL file."

#define M_MIL_FILE_ERROR_2       22L
#define M_ERR_22_MSG             "MIL file access error."
#define M_ERR_22_SUBMSG_1        "Only 8, 16 or 32 BitsPerSample supported."
#define M_ERR_22_SUBMSG_2        "Only Compression type 1 supported."
#define M_ERR_22_SUBMSG_3        "PhotometricInterp incompatible with SamplePerPixel."
#define M_ERR_22_SUBMSG_4        "Only PlanarConfiguration 2 supported for multi-band images."
#define M_ERR_22_SUBMSG_5        "Up to 8 Samples Per Pixel supported."
#define M_ERR_22_SUBMSG_6        "Only identical BitsPerSample for every sample supported."
#define M_ERR_22_SUBMSG_7        "Cannot seek in file."
#define M_ERR_22_SUBMSG_8        "Bad file format detected."
#define M_ERR_22_SUBMSG_9        NO_SUBMSG

#define M_MIL_FILE_ERROR_3       23L
#define M_ERR_23_MSG             "MIL file access error."
#define M_ERR_23_SUBMSG_1        "Invalid parameter detected."
#define M_ERR_23_SUBMSG_2        "Missing information in file."
#define M_ERR_23_SUBMSG_3        "Bad size information detected in file."
#define M_ERR_23_SUBMSG_4        "Bad identification information detected in file."
#define M_ERR_23_SUBMSG_5        "Invalid data information detected in file."
#define M_ERR_23_SUBMSG_6        "Unexpected internal error."
#define M_ERR_23_SUBMSG_7        NO_SUBMSG
#define M_ERR_23_SUBMSG_8        NO_SUBMSG
#define M_ERR_23_SUBMSG_9        NO_SUBMSG

#define M_XX24XX_ERROR           24L
#define M_ERR_24_MSG             NO_MSG
#define M_ERR_24_SUBMSG_1        NO_SUBMSG
#define M_ERR_24_SUBMSG_2        NO_SUBMSG
#define M_ERR_24_SUBMSG_3        NO_SUBMSG
#define M_ERR_24_SUBMSG_4        NO_SUBMSG
#define M_ERR_24_SUBMSG_5        NO_SUBMSG
#define M_ERR_24_SUBMSG_6        NO_SUBMSG
#define M_ERR_24_SUBMSG_7        NO_SUBMSG
#define M_ERR_24_SUBMSG_8        NO_SUBMSG
#define M_ERR_24_SUBMSG_9        NO_SUBMSG

#define M_XX25XX_ERROR           25L
#define M_ERR_25_MSG             NO_MSG
#define M_ERR_25_SUBMSG_1        NO_SUBMSG
#define M_ERR_25_SUBMSG_2        NO_SUBMSG
#define M_ERR_25_SUBMSG_3        NO_SUBMSG
#define M_ERR_25_SUBMSG_4        NO_SUBMSG
#define M_ERR_25_SUBMSG_5        NO_SUBMSG
#define M_ERR_25_SUBMSG_6        NO_SUBMSG
#define M_ERR_25_SUBMSG_7        NO_SUBMSG
#define M_ERR_25_SUBMSG_8        NO_SUBMSG
#define M_ERR_25_SUBMSG_9        NO_SUBMSG

#define M_BUFFER_FREE_ERROR      26L
#define M_ERR_26_MSG             "Buffer free operation error."
#define M_ERR_26_SUBMSG_1        "Buffer still has child(ren) associated with it."
#define M_ERR_26_SUBMSG_2        "Use MnatBufDestroy() on this kind of buffer."
#define M_ERR_26_SUBMSG_3        "User attempting to free a system allocated buffer."
#define M_ERR_26_SUBMSG_4        "Internal error, internal function attempting to free a user allocated buffer."
#define M_ERR_26_SUBMSG_5        NO_SUBMSG
#define M_ERR_26_SUBMSG_6        NO_SUBMSG
#define M_ERR_26_SUBMSG_7        NO_SUBMSG
#define M_ERR_26_SUBMSG_8        NO_SUBMSG
#define M_ERR_26_SUBMSG_9        NO_SUBMSG

#define M_SYSTEM_FREE_ERROR      27L
#define M_ERR_27_MSG             "System free operation error."
#define M_ERR_27_SUBMSG_1        "System still has buffer(s) associated with it."
#define M_ERR_27_SUBMSG_2        "System still has display(s) associated with it."
#define M_ERR_27_SUBMSG_3        "System still has digitizer(s) associated with it."
#define M_ERR_27_SUBMSG_4        NO_SUBMSG
#define M_ERR_27_SUBMSG_5        NO_SUBMSG
#define M_ERR_27_SUBMSG_6        NO_SUBMSG
#define M_ERR_27_SUBMSG_7        NO_SUBMSG
#define M_ERR_27_SUBMSG_8        NO_SUBMSG
#define M_ERR_27_SUBMSG_9        NO_SUBMSG

#define M_FUNCTION_START_ERROR   28L
#define M_ERR_28_MSG             "Function start error."
#define M_ERR_28_SUBMSG_1        "No application allocated yet, allocate one."
#define M_ERR_28_SUBMSG_2        NO_SUBMSG
#define M_ERR_28_SUBMSG_3        NO_SUBMSG
#define M_ERR_28_SUBMSG_4        NO_SUBMSG
#define M_ERR_28_SUBMSG_5        NO_SUBMSG
#define M_ERR_28_SUBMSG_6        NO_SUBMSG
#define M_ERR_28_SUBMSG_7        NO_SUBMSG
#define M_ERR_28_SUBMSG_8        NO_SUBMSG
#define M_ERR_28_SUBMSG_9        NO_SUBMSG

#define M_COMMAND_DECODER_ERROR  29L
#define M_ERR_29_MSG             "System command error."
#define M_ERR_29_SUBMSG_1        "Requested operation not supported."
#define M_ERR_29_SUBMSG_2        "Operation execution failed."
#define M_ERR_29_SUBMSG_3        NO_SUBMSG
#define M_ERR_29_SUBMSG_4        NO_SUBMSG
#define M_ERR_29_SUBMSG_5        NO_SUBMSG
#define M_ERR_29_SUBMSG_6        NO_SUBMSG
#define M_ERR_29_SUBMSG_7        NO_SUBMSG
#define M_ERR_29_SUBMSG_8        NO_SUBMSG
#define M_ERR_29_SUBMSG_9        NO_SUBMSG

#define M_LABELLING_ERROR        30L
#define M_ERR_30_MSG             "Labelling error."
#define M_ERR_30_SUBMSG_1        "Maximum number of labels reached."
#define M_ERR_30_SUBMSG_2        "Should use a buffer of greater bit depth."
#define M_ERR_30_SUBMSG_3        NO_SUBMSG
#define M_ERR_30_SUBMSG_4        NO_SUBMSG
#define M_ERR_30_SUBMSG_5        NO_SUBMSG
#define M_ERR_30_SUBMSG_6        NO_SUBMSG
#define M_ERR_30_SUBMSG_7        NO_SUBMSG
#define M_ERR_30_SUBMSG_8        NO_SUBMSG
#define M_ERR_30_SUBMSG_9        NO_SUBMSG

#define M_FILE_ERROR             31L
#define M_ERR_31_MSG             "File access error."
#define M_ERR_31_SUBMSG_1        "Cannot open output file."
#define M_ERR_31_SUBMSG_2        "Cannot write to file."
#define M_ERR_31_SUBMSG_3        "Cannot open input file."
#define M_ERR_31_SUBMSG_4        "Cannot read file."
#define M_ERR_31_SUBMSG_5        NO_SUBMSG
#define M_ERR_31_SUBMSG_6        NO_SUBMSG
#define M_ERR_31_SUBMSG_7        NO_SUBMSG
#define M_ERR_31_SUBMSG_8        NO_SUBMSG
#define M_ERR_31_SUBMSG_9        "Not a MIL file."

#define M_APP_FREE_ERROR         32L
#define M_ERR_32_MSG             "Application free operation error."
#define M_ERR_32_SUBMSG_1        "Application still has system(s) associated with it."
#define M_ERR_32_SUBMSG_2        "Default host system still has buffer(s) associated with it"
#define M_ERR_32_SUBMSG_3        NO_SUBMSG
#define M_ERR_32_SUBMSG_4        NO_SUBMSG
#define M_ERR_32_SUBMSG_5        NO_SUBMSG
#define M_ERR_32_SUBMSG_6        NO_SUBMSG
#define M_ERR_32_SUBMSG_7        NO_SUBMSG
#define M_ERR_32_SUBMSG_8        NO_SUBMSG
#define M_ERR_32_SUBMSG_9        NO_SUBMSG

#define M_TIFF_ERROR_2           33L
#define M_ERR_33_MSG             "TIFF File access error."
#define M_ERR_33_SUBMSG_1        "Only 8, 16 or 32 BitsPerSample supported."
#define M_ERR_33_SUBMSG_2        "Only Compression type 1 supported."
#define M_ERR_33_SUBMSG_3        "PhotometricInterp incompatible with SamplePerPixel."
#define M_ERR_33_SUBMSG_4        "Only PlanarConfiguration 2 supported for multi-band images."
#define M_ERR_33_SUBMSG_5        "Up to 8 Samples Per Pixel supported."
#define M_ERR_33_SUBMSG_6        "Only identical BitsPerSample for every sample supported."
#define M_ERR_33_SUBMSG_7        NO_SUBMSG
#define M_ERR_33_SUBMSG_8        NO_SUBMSG
#define M_ERR_33_SUBMSG_9        NO_SUBMSG

#define M_PROCESSING_ERROR       34L
#define M_ERR_34_MSG             "Processing error."
#define M_ERR_34_SUBMSG_1        "All buffers do not have the same working system."
#define M_ERR_34_SUBMSG_2        "Cannot find any working system between buffers."
#define M_ERR_34_SUBMSG_3        "Cannot process a HOST buffer as a whole and a temporary buffer."
#define M_ERR_34_SUBMSG_4        "Source buffers cannot overlap destination buffer."
#define M_ERR_34_SUBMSG_5        "No processor on target processing system."
#define M_ERR_34_SUBMSG_6        NO_SUBMSG
#define M_ERR_34_SUBMSG_7        NO_SUBMSG
#define M_ERR_34_SUBMSG_8        NO_SUBMSG
#define M_ERR_34_SUBMSG_9        "Not enough memory or system limitation, cannot process buffer."

#define M_INVALID_ID             35L
#define M_ERR_35_MSG             "Invalid MIL ID."
#define M_ERR_35_SUBMSG_1        "Invalid parameter 1."
#define M_ERR_35_SUBMSG_2        "Invalid parameter 2."
#define M_ERR_35_SUBMSG_3        "Invalid parameter 3."
#define M_ERR_35_SUBMSG_4        "Invalid parameter 4."
#define M_ERR_35_SUBMSG_5        "Invalid parameter 5."
#define M_ERR_35_SUBMSG_6        "Invalid parameter 6."
#define M_ERR_35_SUBMSG_7        "Invalid parameter 7."
#define M_ERR_35_SUBMSG_8        "Invalid parameter 8."
#define M_ERR_35_SUBMSG_9        "Invalid parameter 9."

#define M_INVALID_NATURE         36L
#define M_ERR_36_MSG             "Inappropriate MIL ID."
#define M_ERR_36_SUBMSG_1        "Invalid parameter 1."
#define M_ERR_36_SUBMSG_2        "Invalid parameter 2."
#define M_ERR_36_SUBMSG_3        "Invalid parameter 3."
#define M_ERR_36_SUBMSG_4        "Invalid parameter 4."
#define M_ERR_36_SUBMSG_5        "Invalid parameter 5."
#define M_ERR_36_SUBMSG_6        "Invalid parameter 6."
#define M_ERR_36_SUBMSG_7        "Invalid parameter 7."
#define M_ERR_36_SUBMSG_8        "Invalid parameter 8."
#define M_ERR_36_SUBMSG_9        "Invalid parameter 9."

#define M_INVALID_PARAM_ERROR_2  37L
#define M_ERR_37_MSG             "Invalid parameter."
#define M_ERR_37_SUBMSG_1        "For this operation, you should supply a LUT buffer with at least 512 entries."
#define M_ERR_37_SUBMSG_2        "For this operation the grab mode must be asynchronous."
#define M_ERR_37_SUBMSG_3        "This type of conversion requires two 3 band buffers."
#define M_ERR_37_SUBMSG_4        "This type of conversion requires a 3 band source buffer."
#define M_ERR_37_SUBMSG_5        "This type of conversion requires a 3 band destination buffer."
#define M_ERR_37_SUBMSG_6        "Invalid interpolation type specified."
#define M_ERR_37_SUBMSG_7        "Specified center is outside buffer."
#define M_ERR_37_SUBMSG_8        "Image buffer must be 8 bit monochrome for this operation."
#define M_ERR_37_SUBMSG_9        "Look up table must be 1 or 3 bands, 8 bits deep and have an X size of 256 or more."

#define M_INVALID_ATTRIBUTE      38L
#define M_ERR_38_MSG             "Invalid attributes."
#define M_ERR_38_SUBMSG_1        "Invalid parameter 1."
#define M_ERR_38_SUBMSG_2        "Invalid parameter 2."
#define M_ERR_38_SUBMSG_3        "Invalid parameter 3."
#define M_ERR_38_SUBMSG_4        "Invalid parameter 4."
#define M_ERR_38_SUBMSG_5        "Invalid parameter 5."
#define M_ERR_38_SUBMSG_6        "Invalid parameter 6."
#define M_ERR_38_SUBMSG_7        "Invalid parameter 7."
#define M_ERR_38_SUBMSG_8        "Invalid parameter 8."
#define M_ERR_38_SUBMSG_9        "Invalid parameter 9."

#define M_CALL_CONTEXT_ERROR     39L
#define M_ERR_39_MSG             "Call context error"
#define M_ERR_39_SUBMSG_1        "Cannot allocate temporary buffer in memory."
#define M_ERR_39_SUBMSG_2        NO_SUBMSG
#define M_ERR_39_SUBMSG_3        NO_SUBMSG
#define M_ERR_39_SUBMSG_4        NO_SUBMSG
#define M_ERR_39_SUBMSG_5        NO_SUBMSG
#define M_ERR_39_SUBMSG_6        NO_SUBMSG
#define M_ERR_39_SUBMSG_7        NO_SUBMSG
#define M_ERR_39_SUBMSG_8        NO_SUBMSG
#define M_ERR_39_SUBMSG_9        NO_SUBMSG

#define M_DRIVER_OBSOLETE        40L
#define M_ERR_40_MSG             "MIL driver obsolete."
#define M_ERR_40_SUBMSG_1        "Version must be 2.0 or higher."
#define M_ERR_40_SUBMSG_2        NO_SUBMSG
#define M_ERR_40_SUBMSG_3        NO_SUBMSG
#define M_ERR_40_SUBMSG_4        NO_SUBMSG
#define M_ERR_40_SUBMSG_5        NO_SUBMSG
#define M_ERR_40_SUBMSG_6        NO_SUBMSG
#define M_ERR_40_SUBMSG_7        NO_SUBMSG
#define M_ERR_40_SUBMSG_8        NO_SUBMSG
#define M_ERR_40_SUBMSG_9        NO_SUBMSG

#define M_INVALID_PARAM_ERROR_3  41L
#define M_ERR_41_MSG             "Invalid parameter."
#define M_ERR_41_SUBMSG_1        "Parameter 1 not in supported list."
#define M_ERR_41_SUBMSG_2        "Parameter 2 not in supported list."
#define M_ERR_41_SUBMSG_3        "Parameter 3 not in supported list."
#define M_ERR_41_SUBMSG_4        "Parameter 4 not in supported list."
#define M_ERR_41_SUBMSG_5        "Parameter 5 not in supported list."
#define M_ERR_41_SUBMSG_6        "Parameter 6 not in supported list."
#define M_ERR_41_SUBMSG_7        "Parameter 7 not in supported list."
#define M_ERR_41_SUBMSG_8        "Parameter 8 not in supported list."
#define M_ERR_41_SUBMSG_9        "Parameter 9 not in supported list."

#define M_ALLOC_ERROR_2          42L
#define M_ERR_42_MSG             "Allocation error."
#define M_ERR_42_SUBMSG_1        "Not enough host memory to do operation."
#define M_ERR_42_SUBMSG_2        NO_SUBMSG
#define M_ERR_42_SUBMSG_3        NO_SUBMSG
#define M_ERR_42_SUBMSG_4        NO_SUBMSG
#define M_ERR_42_SUBMSG_5        NO_SUBMSG
#define M_ERR_42_SUBMSG_6        NO_SUBMSG
#define M_ERR_42_SUBMSG_7        NO_SUBMSG
#define M_ERR_42_SUBMSG_8        NO_SUBMSG
#define M_ERR_42_SUBMSG_9        NO_SUBMSG

#define M_XX43XX_ERROR           43L
#define M_ERR_43_MSG             NO_MSG
#define M_ERR_43_SUBMSG_1        NO_SUBMSG
#define M_ERR_43_SUBMSG_2        NO_SUBMSG
#define M_ERR_43_SUBMSG_3        NO_SUBMSG
#define M_ERR_43_SUBMSG_4        NO_SUBMSG
#define M_ERR_43_SUBMSG_5        NO_SUBMSG
#define M_ERR_43_SUBMSG_6        NO_SUBMSG
#define M_ERR_43_SUBMSG_7        NO_SUBMSG
#define M_ERR_43_SUBMSG_8        NO_SUBMSG
#define M_ERR_43_SUBMSG_9        NO_SUBMSG

#define M_XX44XX_ERROR           44L
#define M_ERR_44_MSG             NO_MSG
#define M_ERR_44_SUBMSG_1        NO_SUBMSG
#define M_ERR_44_SUBMSG_2        NO_SUBMSG
#define M_ERR_44_SUBMSG_3        NO_SUBMSG
#define M_ERR_44_SUBMSG_4        NO_SUBMSG
#define M_ERR_44_SUBMSG_5        NO_SUBMSG
#define M_ERR_44_SUBMSG_6        NO_SUBMSG
#define M_ERR_44_SUBMSG_7        NO_SUBMSG
#define M_ERR_44_SUBMSG_8        NO_SUBMSG
#define M_ERR_44_SUBMSG_9        NO_SUBMSG

#define M_XX45XX_ERROR           45L
#define M_ERR_45_MSG             NO_MSG
#define M_ERR_45_SUBMSG_1        NO_SUBMSG
#define M_ERR_45_SUBMSG_2        NO_SUBMSG
#define M_ERR_45_SUBMSG_3        NO_SUBMSG
#define M_ERR_45_SUBMSG_4        NO_SUBMSG
#define M_ERR_45_SUBMSG_5        NO_SUBMSG
#define M_ERR_45_SUBMSG_6        NO_SUBMSG
#define M_ERR_45_SUBMSG_7        NO_SUBMSG
#define M_ERR_45_SUBMSG_8        NO_SUBMSG
#define M_ERR_45_SUBMSG_9        NO_SUBMSG

#define M_XX46XX_ERROR           46L
#define M_ERR_46_MSG             NO_MSG
#define M_ERR_46_SUBMSG_1        NO_SUBMSG
#define M_ERR_46_SUBMSG_2        NO_SUBMSG
#define M_ERR_46_SUBMSG_3        NO_SUBMSG
#define M_ERR_46_SUBMSG_4        NO_SUBMSG
#define M_ERR_46_SUBMSG_5        NO_SUBMSG
#define M_ERR_46_SUBMSG_6        NO_SUBMSG
#define M_ERR_46_SUBMSG_7        NO_SUBMSG
#define M_ERR_46_SUBMSG_8        NO_SUBMSG
#define M_ERR_46_SUBMSG_9        NO_SUBMSG

#define M_XX47XX_ERROR           47L
#define M_ERR_47_MSG             NO_MSG
#define M_ERR_47_SUBMSG_1        NO_SUBMSG
#define M_ERR_47_SUBMSG_2        NO_SUBMSG
#define M_ERR_47_SUBMSG_3        NO_SUBMSG
#define M_ERR_47_SUBMSG_4        NO_SUBMSG
#define M_ERR_47_SUBMSG_5        NO_SUBMSG
#define M_ERR_47_SUBMSG_6        NO_SUBMSG
#define M_ERR_47_SUBMSG_7        NO_SUBMSG
#define M_ERR_47_SUBMSG_8        NO_SUBMSG
#define M_ERR_47_SUBMSG_9        NO_SUBMSG

#define M_XX48XX_ERROR           48L
#define M_ERR_48_MSG             NO_MSG
#define M_ERR_48_SUBMSG_1        NO_SUBMSG
#define M_ERR_48_SUBMSG_2        NO_SUBMSG
#define M_ERR_48_SUBMSG_3        NO_SUBMSG
#define M_ERR_48_SUBMSG_4        NO_SUBMSG
#define M_ERR_48_SUBMSG_5        NO_SUBMSG
#define M_ERR_48_SUBMSG_6        NO_SUBMSG
#define M_ERR_48_SUBMSG_7        NO_SUBMSG
#define M_ERR_48_SUBMSG_8        NO_SUBMSG
#define M_ERR_48_SUBMSG_9        NO_SUBMSG

#define M_XX49XX_ERROR           49L
#define M_ERR_49_MSG             NO_MSG
#define M_ERR_49_SUBMSG_1        NO_SUBMSG
#define M_ERR_49_SUBMSG_2        NO_SUBMSG
#define M_ERR_49_SUBMSG_3        NO_SUBMSG
#define M_ERR_49_SUBMSG_4        NO_SUBMSG
#define M_ERR_49_SUBMSG_5        NO_SUBMSG
#define M_ERR_49_SUBMSG_6        NO_SUBMSG
#define M_ERR_49_SUBMSG_7        NO_SUBMSG
#define M_ERR_49_SUBMSG_8        NO_SUBMSG
#define M_ERR_49_SUBMSG_9        NO_SUBMSG

#define M_XX50XX_ERROR           50L
#define M_ERR_50_MSG             NO_MSG
#define M_ERR_50_SUBMSG_1        NO_SUBMSG
#define M_ERR_50_SUBMSG_2        NO_SUBMSG
#define M_ERR_50_SUBMSG_3        NO_SUBMSG
#define M_ERR_50_SUBMSG_4        NO_SUBMSG
#define M_ERR_50_SUBMSG_5        NO_SUBMSG
#define M_ERR_50_SUBMSG_6        NO_SUBMSG
#define M_ERR_50_SUBMSG_7        NO_SUBMSG
#define M_ERR_50_SUBMSG_8        NO_SUBMSG
#define M_ERR_50_SUBMSG_9        NO_SUBMSG

#define M_XX51XX_ERROR           51L
#define M_ERR_51_MSG             NO_MSG
#define M_ERR_51_SUBMSG_1        NO_SUBMSG
#define M_ERR_51_SUBMSG_2        NO_SUBMSG
#define M_ERR_51_SUBMSG_3        NO_SUBMSG
#define M_ERR_51_SUBMSG_4        NO_SUBMSG
#define M_ERR_51_SUBMSG_5        NO_SUBMSG
#define M_ERR_51_SUBMSG_6        NO_SUBMSG
#define M_ERR_51_SUBMSG_7        NO_SUBMSG
#define M_ERR_51_SUBMSG_8        NO_SUBMSG
#define M_ERR_51_SUBMSG_9        NO_SUBMSG

#define M_XX52XX_ERROR           52L
#define M_ERR_52_MSG             NO_MSG
#define M_ERR_52_SUBMSG_1        NO_SUBMSG
#define M_ERR_52_SUBMSG_2        NO_SUBMSG
#define M_ERR_52_SUBMSG_3        NO_SUBMSG
#define M_ERR_52_SUBMSG_4        NO_SUBMSG
#define M_ERR_52_SUBMSG_5        NO_SUBMSG
#define M_ERR_52_SUBMSG_6        NO_SUBMSG
#define M_ERR_52_SUBMSG_7        NO_SUBMSG
#define M_ERR_52_SUBMSG_8        NO_SUBMSG
#define M_ERR_52_SUBMSG_9        NO_SUBMSG

#define M_XX53XX_ERROR           53L
#define M_ERR_53_MSG             NO_MSG
#define M_ERR_53_SUBMSG_1        NO_SUBMSG
#define M_ERR_53_SUBMSG_2        NO_SUBMSG
#define M_ERR_53_SUBMSG_3        NO_SUBMSG
#define M_ERR_53_SUBMSG_4        NO_SUBMSG
#define M_ERR_53_SUBMSG_5        NO_SUBMSG
#define M_ERR_53_SUBMSG_6        NO_SUBMSG
#define M_ERR_53_SUBMSG_7        NO_SUBMSG
#define M_ERR_53_SUBMSG_8        NO_SUBMSG
#define M_ERR_53_SUBMSG_9        NO_SUBMSG

#define M_XX54XX_ERROR           54L
#define M_ERR_54_MSG             NO_MSG
#define M_ERR_54_SUBMSG_1        NO_SUBMSG
#define M_ERR_54_SUBMSG_2        NO_SUBMSG
#define M_ERR_54_SUBMSG_3        NO_SUBMSG
#define M_ERR_54_SUBMSG_4        NO_SUBMSG
#define M_ERR_54_SUBMSG_5        NO_SUBMSG
#define M_ERR_54_SUBMSG_6        NO_SUBMSG
#define M_ERR_54_SUBMSG_7        NO_SUBMSG
#define M_ERR_54_SUBMSG_8        NO_SUBMSG
#define M_ERR_54_SUBMSG_9        NO_SUBMSG

#define M_XX55XX_ERROR           55L
#define M_ERR_55_MSG             NO_MSG
#define M_ERR_55_SUBMSG_1        NO_SUBMSG
#define M_ERR_55_SUBMSG_2        NO_SUBMSG
#define M_ERR_55_SUBMSG_3        NO_SUBMSG
#define M_ERR_55_SUBMSG_4        NO_SUBMSG
#define M_ERR_55_SUBMSG_5        NO_SUBMSG
#define M_ERR_55_SUBMSG_6        NO_SUBMSG
#define M_ERR_55_SUBMSG_7        NO_SUBMSG
#define M_ERR_55_SUBMSG_8        NO_SUBMSG
#define M_ERR_55_SUBMSG_9        NO_SUBMSG

#define M_XX56XX_ERROR           56L
#define M_ERR_56_MSG             NO_MSG
#define M_ERR_56_SUBMSG_1        NO_SUBMSG
#define M_ERR_56_SUBMSG_2        NO_SUBMSG
#define M_ERR_56_SUBMSG_3        NO_SUBMSG
#define M_ERR_56_SUBMSG_4        NO_SUBMSG
#define M_ERR_56_SUBMSG_5        NO_SUBMSG
#define M_ERR_56_SUBMSG_6        NO_SUBMSG
#define M_ERR_56_SUBMSG_7        NO_SUBMSG
#define M_ERR_56_SUBMSG_8        NO_SUBMSG
#define M_ERR_56_SUBMSG_9        NO_SUBMSG

#define M_XX57XX_ERROR           57L
#define M_ERR_57_MSG             NO_MSG
#define M_ERR_57_SUBMSG_1        NO_SUBMSG
#define M_ERR_57_SUBMSG_2        NO_SUBMSG
#define M_ERR_57_SUBMSG_3        NO_SUBMSG
#define M_ERR_57_SUBMSG_4        NO_SUBMSG
#define M_ERR_57_SUBMSG_5        NO_SUBMSG
#define M_ERR_57_SUBMSG_6        NO_SUBMSG
#define M_ERR_57_SUBMSG_7        NO_SUBMSG
#define M_ERR_57_SUBMSG_8        NO_SUBMSG
#define M_ERR_57_SUBMSG_9        NO_SUBMSG

#define M_XX58XX_ERROR           58L
#define M_ERR_58_MSG             NO_MSG
#define M_ERR_58_SUBMSG_1        NO_SUBMSG
#define M_ERR_58_SUBMSG_2        NO_SUBMSG
#define M_ERR_58_SUBMSG_3        NO_SUBMSG
#define M_ERR_58_SUBMSG_4        NO_SUBMSG
#define M_ERR_58_SUBMSG_5        NO_SUBMSG
#define M_ERR_58_SUBMSG_6        NO_SUBMSG
#define M_ERR_58_SUBMSG_7        NO_SUBMSG
#define M_ERR_58_SUBMSG_8        NO_SUBMSG
#define M_ERR_58_SUBMSG_9        NO_SUBMSG

#define M_XX59XX_ERROR           59L
#define M_ERR_59_MSG             NO_MSG
#define M_ERR_59_SUBMSG_1        NO_SUBMSG
#define M_ERR_59_SUBMSG_2        NO_SUBMSG
#define M_ERR_59_SUBMSG_3        NO_SUBMSG
#define M_ERR_59_SUBMSG_4        NO_SUBMSG
#define M_ERR_59_SUBMSG_5        NO_SUBMSG
#define M_ERR_59_SUBMSG_6        NO_SUBMSG
#define M_ERR_59_SUBMSG_7        NO_SUBMSG
#define M_ERR_59_SUBMSG_8        NO_SUBMSG
#define M_ERR_59_SUBMSG_9        NO_SUBMSG



/* LIST FUNCTION NAMES AND MESSAGES */


/* MIM */

#define M_NO_FUNCTION               0L
#define M_FCT_0_NAME                ""

#define M_MIMSTARTOPCODE            1L
#define M_MIMALLOCRESULT            1L
#define M_FCT_1_NAME                "MimAllocResult"
#define M_MIMARITH                  2L
#define M_FCT_2_NAME                "MimArith"
#define M_FCT_3                     3L
#define M_FCT_3_NAME                NO_FCTNAME
#define M_MIMBINARIZE               4L
#define M_FCT_4_NAME                "MimBinarize"
#define M_MIMCLIP                   5L
#define M_FCT_5_NAME                "MimClip"
#define M_MIMCLOSE                  6L
#define M_FCT_6_NAME                "MimClose"
#define M_MIMCONNECTMAP             7L
#define M_FCT_7_NAME                "MimConnectMap"
#define M_MIMCONVOLVE               8L
#define M_FCT_8_NAME                "MimConvolve"
#define M_MIMCOUNTDIFFERENCE        9L
#define M_FCT_9_NAME                "MimCountDifference"
#define M_MIMDILATE                10L
#define M_FCT_10_NAME              "MimDilate"
#define M_MIMERODE                 11L
#define M_FCT_11_NAME              "MimErode"
#define M_MIMFINDEXTREME           12L
#define M_FCT_12_NAME              "MimFindExtreme"
#define M_MIMFREE                  13L
#define M_FCT_13_NAME              "MimFree"
#define M_MIMGETRESULT1D           14L
#define M_FCT_14_NAME              "MimGetResult1d"
#define M_MIMHISTOGRAM             15L
#define M_FCT_15_NAME              "MimHistogram"
#define M_MIMHISTOGRAMEQUALIZE     16L
#define M_FCT_16_NAME              "MimHistogramEqualize"
#define M_MIMLABEL                 17L
#define M_FCT_17_NAME              "MimLabel"
#define M_MIMLOCATEEVENT           18L
#define M_FCT_18_NAME              "MimLocateEvent"
#define M_MIMLUTMAP                19L
#define M_FCT_19_NAME              "MimLutMap"
#define M_MIMMORPHIC               20L
#define M_FCT_20_NAME              "MimMorphic"
#define M_MIMOPEN                  21L
#define M_FCT_21_NAME              "MimOpen"
#define M_MIMPROJECT               22L
#define M_FCT_22_NAME              "MimProject"
#define M_MIMRANK                  23L
#define M_FCT_23_NAME              "MimRank"
#define M_MIMRESIZE                24L
#define M_FCT_24_NAME              "MimResize"
#define M_MIMROTATE                25L
#define M_FCT_25_NAME              "MimRotate"
#define M_MIMSHIFT                 26L
#define M_FCT_26_NAME              "MimShift"
#define M_MIMTHIN                  27L
#define M_FCT_27_NAME              "MimThin"
#define M_MIMTRANSLATE             28L
#define M_FCT_28_NAME              "MimTranslate"
#define M_MIMGETRESULT             29L
#define M_FCT_29_NAME              "MimGetResult"
#define M_MIMINQUIRE               30L
#define M_FCT_30_NAME              "MimInquire"
#define M_MIMCONVERT               31L
#define M_FCT_31_NAME              "MimConvert"
#define M_MIMTHICK                 32L
#define M_FCT_32_NAME              "MimThick"
#define M_MIMDISTANCE              33L
#define M_FCT_33_NAME              "MimDistance"
#define M_FCT_34                   34L
#define M_FCT_34_NAME              NO_FCTNAME
#define M_FCT_35                   35L
#define M_FCT_35_NAME              NO_FCTNAME
#define M_FCT_36                   36L
#define M_FCT_36_NAME              NO_FCTNAME
#define M_FCT_37                   37L
#define M_FCT_37_NAME              NO_FCTNAME
#define M_FCT_38                   38L
#define M_FCT_38_NAME              NO_FCTNAME
#define M_FCT_39                   39L
#define M_FCT_39_NAME              NO_FCTNAME
#define M_FCT_40                   40L
#define M_FCT_40_NAME              NO_FCTNAME
#define M_FCT_41                   41L
#define M_FCT_41_NAME              NO_FCTNAME
#define M_FCT_42                   42L
#define M_FCT_42_NAME              NO_FCTNAME
#define M_FCT_43                   43L
#define M_FCT_43_NAME              NO_FCTNAME
#define M_FCT_44                   44L
#define M_FCT_44_NAME              NO_FCTNAME
#define M_FCT_45                   45L
#define M_FCT_45_NAME              NO_FCTNAME
#define M_FCT_46                   46L
#define M_FCT_46_NAME              NO_FCTNAME
#define M_FCT_47                   47L
#define M_FCT_47_NAME              NO_FCTNAME
#define M_MIMENDOPCODE             47L

/* MGRA */
#define M_MGRASTARTOPCODE          48L
#define M_MGRAARC                  48L
#define M_FCT_48_NAME              "MgraArc"
#define M_MGRAARCFILL              49L
#define M_FCT_49_NAME              "MgraArcFill"
#define M_MGRABACKCOLOR            50L
#define M_FCT_50_NAME              "MgraBackColor"
#define M_MGRAFILL                 51L
#define M_FCT_51_NAME              "MgraFill"
#define M_MGRACLEAR                52L
#define M_FCT_52_NAME              "MgraClear"
#define M_MGRACOLOR                53L
#define M_FCT_53_NAME              "MgraColor"
#define M_MGRADOT                  54L
#define M_FCT_54_NAME              "MgraDot"
#define M_MGRAFONT                 55L
#define M_FCT_55_NAME              "MgraFont"
#define M_MGRAFONTSCALE            56L
#define M_FCT_56_NAME              "MgraFontScale"
#define M_MGRAINQUIRE              57L
#define M_FCT_57_NAME              "MgraInquire"
#define M_MGRALINE                 58L
#define M_FCT_58_NAME              "MgraLine"
#define M_MGRARECT                 59L
#define M_FCT_59_NAME              "MgraRect"
#define M_MGRARECTFILL             60L
#define M_FCT_60_NAME              "MgraRectFill"
#define M_MGRATEXT                 61L
#define M_FCT_61_NAME              "MgraText"
#define M_MGRAALLOC                62L
#define M_FCT_62_NAME              "MgraAlloc"
#define M_MGRAFREE                 63L
#define M_FCT_63_NAME              "MgraFree"
#define M_MGRACONTROL              64L
#define M_FCT_64_NAME              "MgraControl"
#define M_FCT_65                   65L
#define M_FCT_65_NAME              NO_FCTNAME
#define M_FCT_66                   66L
#define M_FCT_66_NAME              NO_FCTNAME
#define M_FCT_67                   67L
#define M_FCT_67_NAME              NO_FCTNAME
#define M_FCT_68                   68L
#define M_FCT_68_NAME              NO_FCTNAME
#define M_FCT_69                   69L
#define M_FCT_69_NAME              NO_FCTNAME
#define M_FCT_70                   70L
#define M_FCT_70_NAME              NO_FCTNAME
#define M_MGRAENDOPCODE            70L

/* MGEN */

#define M_MGENSTARTOPCODE          71L
#define M_MGENLUTFUNCTION          71L
#define M_FCT_71_NAME              "MgenLutFunction"
#define M_MGENLUTRAMP              72L
#define M_FCT_72_NAME              "MgenLutRamp"
#define M_FCT_73                   73L
#define M_FCT_73_NAME              NO_FCTNAME
#define M_FCT_74                   74L
#define M_FCT_74_NAME              NO_FCTNAME
#define M_FCT_75                   75L
#define M_FCT_75_NAME              NO_FCTNAME
#define M_FCT_76                   76L
#define M_FCT_76_NAME              NO_FCTNAME
#define M_FCT_77                   77L
#define M_FCT_77_NAME              NO_FCTNAME
#define M_FCT_78                   78L
#define M_FCT_78_NAME              NO_FCTNAME
#define M_FCT_79                   79L
#define M_FCT_79_NAME              NO_FCTNAME
#define M_FCT_80                   80L
#define M_FCT_80_NAME              NO_FCTNAME
#define M_FCT_81                   81L
#define M_FCT_81_NAME              NO_FCTNAME
#define M_MGENENDOPCODE            81L

/* MBUF */

#define M_MBUFSTARTOPCODE          82L
#define M_MBUFALLOC1D              82L
#define M_FCT_82_NAME              "MbufAlloc1d"
#define M_MBUFALLOC2D              83L
#define M_FCT_83_NAME              "MbufAlloc2d"
#define M_MBUFATTRIBUTE            84L
#define M_FCT_84_NAME              "MbufAttribute"
#define M_MBUFCHILD1D              85L
#define M_FCT_85_NAME              "MbufChild1d"
#define M_MBUFCHILD2D              86L
#define M_FCT_86_NAME              "MbufChild2d"
#define M_MBUFCONTROLNEIGHBORHOOD  87L
#define M_FCT_87_NAME              "MbufControlNeighborhood"
#define M_MBUFCOPY                 88L
#define M_FCT_88_NAME              "MbufCopy"
#define M_MBUFDISKINQUIRE          89L
#define M_FCT_89_NAME              "MbufDiskInquire"
#define M_MBUFEXPORT               90L
#define M_FCT_90_NAME              "MbufExport"
#define M_MBUFFREE                 91L
#define M_FCT_91_NAME              "MbufFree"
#define M_MBUFGET1D                92L
#define M_FCT_92_NAME              "MbufGet1d"
#define M_MBUFGET2D                93L
#define M_FCT_93_NAME              "MbufGet2d"
#define M_MBUFIMPORT               94L
#define M_FCT_94_NAME              "MbufImport"
#define M_MBUFINQUIRE              95L
#define M_FCT_95_NAME              "MbufInquire"
#define M_MBUFLOAD                 96L
#define M_FCT_96_NAME              "MbufLoad"
#define M_MBUFRESTORE              97L
#define M_FCT_97_NAME              "MbufRestore"
#define M_MBUFSAVE                 98L
#define M_FCT_98_NAME              "MbufSave"
#define M_MBUFPUT1D                99L
#define M_FCT_99_NAME              "MbufPut1d"
#define M_MBUFPUT2D               100L
#define M_FCT_100_NAME            "MbufPut2d"
#define M_MBUFPUT                 101L
#define M_FCT_101_NAME            "MbufPut"
#define M_MBUFCLEAR               102L
#define M_FCT_102_NAME            "MbufClear"
#define M_MBUFCOPYCLIP            103L
#define M_FCT_103_NAME            "MbufCopyClip"
#define M_MBUFCOPYCOND            104L
#define M_FCT_104_NAME            "MbufCopyCond"
#define M_MBUFCOPYMASK            105L
#define M_FCT_105_NAME            "MbufCopyMask"
#define M_MBUFGET                 106L
#define M_FCT_106_NAME            "MbufGet"
#define M_MBUFCHILDCOLOR          107L
#define M_FCT_107_NAME            "MbufChildColor"
#define M_MBUFALLOCCOLOR          108L
#define M_FCT_108_NAME            "MbufAllocColor"
#define M_MBUFGETCOLOR            109L
#define M_FCT_109_NAME            "MbufGetColor"
#define M_MBUFPUTCOLOR            110L
#define M_FCT_110_NAME            "MbufPutColor"
#define M_MBUFCOPYCOLOR           111L
#define M_FCT_111_NAME            "MbufCopyColor"
#define M_MBUFCONTROL             112L
#define M_FCT_112_NAME            "MbufControl"
#define M_FCT_113                 113L
#define M_FCT_113_NAME            NO_FCTNAME
#define M_FCT_114                 114L
#define M_FCT_114_NAME            NO_FCTNAME
#define M_FCT_115                 115L
#define M_FCT_115_NAME            NO_FCTNAME
#define M_FCT_116                 116L
#define M_FCT_116_NAME            NO_FCTNAME
#define M_FCT_117                 117L
#define M_FCT_117_NAME            NO_FCTNAME
#define M_FCT_118                 118L
#define M_FCT_118_NAME            NO_FCTNAME
#define M_FCT_119                 119L
#define M_FCT_119_NAME            NO_FCTNAME
#define M_MBUFENDOPCODE           119L

/* MDIG */

#define M_MDIGSTARTOPCODE         120L
#define M_MDIGALLOC               120L
#define M_FCT_120_NAME            "MdigAlloc"
#define M_MDIGCHANNEL             121L
#define M_FCT_121_NAME            "MdigChannel"
#define M_MDIGFREE                122L
#define M_FCT_122_NAME            "MdigFree"
#define M_MDIGGRAB                123L
#define M_FCT_123_NAME            "MdigGrab"
#define M_MDIGINQUIRE             124L
#define M_FCT_124_NAME            "MdigInquire"
#define M_MDIGLUT                 125L
#define M_FCT_125_NAME            "MdigLut"
#define M_MDIGREFERENCE           126L
#define M_FCT_126_NAME            "MdigReference"
#define M_MDIGGRABCONTINUOUS      127L
#define M_FCT_127_NAME            "MdigGrabContinuous"
#define M_MDIGHALT                128L
#define M_FCT_128_NAME            "MdigHalt"
#define M_MDIGCONTROL             129L
#define M_FCT_129_NAME            "MdigControl"
#define M_MDIGGRABWAIT            130L
#define M_FCT_130_NAME            "MdigGrabWait"
#define M_MDIGAVERAGE             131L
#define M_FCT_131_NAME            "MdigAverage"
#define M_MDIGHOOKFUNCTION        132L
#define M_FCT_132_NAME            "MdigHookFunction"
#define M_FCT_133                 133L
#define M_FCT_133_NAME            NO_FCTNAME
#define M_FCT_134                 134L
#define M_FCT_134_NAME            NO_FCTNAME
#define M_FCT_135                 135L
#define M_FCT_135_NAME            NO_FCTNAME
#define M_MDIGENDOPCODE           135L

/* MDISP */

#define M_MDISPSTARTOPCODE        136L
#define M_MDISPDESELECT           136L
#define M_FCT_136_NAME            "MdispDeselect"
#define M_MDISPINQUIRE            137L
#define M_FCT_137_NAME            "MdispInquire"
#define M_MDISPLUT                138L
#define M_FCT_138_NAME            "MdispLut"
#define M_MDISPPAN                139L
#define M_FCT_139_NAME            "MdispPan"
#define M_MDISPSELECT             140L
#define M_FCT_140_NAME            "MdispSelect"
#define M_MDISPZOOM               141L
#define M_FCT_141_NAME            "MdispZoom"
#define M_MDISPALLOC              142L
#define M_FCT_142_NAME            "MdispAlloc"
#define M_MDISPFREE               143L
#define M_FCT_143_NAME            "MdispFree"
#define M_MDISPOVERLAYKEY         144L
#define M_FCT_144_NAME            "MdispOverlayKey"
#define M_FCT_145                 145L
#define M_FCT_145_NAME            NO_FCTNAME
#define M_FCT_146                 146L
#define M_FCT_146_NAME            NO_FCTNAME
#define M_FCT_147                 147L
#define M_FCT_147_NAME            NO_FCTNAME
#define M_FCT_148                 148L
#define M_FCT_148_NAME            NO_FCTNAME
#define M_FCT_149                 149L
#define M_FCT_149_NAME            NO_FCTNAME
#define M_FCT_150                 150L
#define M_FCT_150_NAME            NO_FCTNAME
#define M_MDISPENDOPCODE          150L

/* MSYS */

#define M_MSYSSTARTOPCODE         151L
#define M_MSYSALLOC               151L
#define M_FCT_151_NAME            "MsysAlloc"
#define M_MSYSFREE                152L
#define M_FCT_152_NAME            "MsysFree"
#define M_MSYSINQUIRE             153L
#define M_FCT_153_NAME            "MsysInquire"
#define M_MSYSCONTROL             154L
#define M_FCT_154_NAME            "MsysControl"
#define M_MDISPCONTROL            155L
#define M_FCT_155_NAME            "MdispControl"
#define M_FCT_156                 156L
#define M_FCT_156_NAME            NO_FCTNAME
#define M_FCT_157                 157L
#define M_FCT_157_NAME            NO_FCTNAME
#define M_FCT_158                 158L
#define M_FCT_158_NAME            NO_FCTNAME
#define M_FCT_159                 159L
#define M_FCT_159_NAME            NO_FCTNAME
#define M_FCT_160                 160L
#define M_FCT_160_NAME            NO_FCTNAME
#define M_FCT_161                 161L
#define M_FCT_161_NAME            NO_FCTNAME
#define M_MSYSENDOPCODE           161L

/* MAPP */

#define M_MAPPSTARTOPCODE         162L
#define M_MAPPALLOC               162L
#define M_FCT_162_NAME            "MappAlloc"
#define M_MAPPCONTROL             163L
#define M_FCT_163_NAME            "MappControl"
#define M_MAPPFREE                164L
#define M_FCT_164_NAME            "MappFree"
#define M_MAPPGETERROR            165L
#define M_FCT_165_NAME            "MappGetError"
#define M_MAPPHOOKFUNCTION        166L
#define M_FCT_166_NAME            "MappHookFunction"
#define M_MAPPGETHOOKINFO         167L
#define M_FCT_167_NAME            "MappGetHookInfo"
#define M_MAPPINQUIRE             168L
#define M_FCT_168_NAME            "MappInquire"
#define M_MAPPMODIFY              169L
#define M_FCT_169_NAME            "MappModify"
#define M_MAPPGETDEVICETYPE       170L
#define M_FCT_170_NAME            "MappGetDeviceType"
#define M_FCT_171                 171L
#define M_FCT_171_NAME            NO_FCTNAME
#define M_FCT_172                 172L
#define M_FCT_172_NAME            NO_FCTNAME
#define M_FCT_173                 173L
#define M_FCT_173_NAME            NO_FCTNAME
#define M_FCT_174                 174L
#define M_FCT_174_NAME            NO_FCTNAME
#define M_FCT_175                 175L
#define M_FCT_175_NAME            NO_FCTNAME
#define M_FCT_176                 176L
#define M_FCT_176_NAME            NO_FCTNAME
#define M_FCT_177                 177L
#define M_FCT_177_NAME            NO_FCTNAME
#define M_FCT_178                 178L
#define M_FCT_178_NAME            NO_FCTNAME
#define M_MFUNC                   179L
#define M_FCT_179_NAME            NO_FCTNAME
#define M_MAPPENDOPCODE           179L

#endif
