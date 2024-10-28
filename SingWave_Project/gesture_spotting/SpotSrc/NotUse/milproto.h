/***************************************************************************/
/*

    Filename:  MILPROTO.H
    Owner   :  Matrox Imaging dept.
    Rev     :  $Revision:   1.0  $
    Content :  This file contains the prototypes for the Matrox
               Imaging Library (MIL) C user's functions.

    COPYRIGHT (c) 1993  Matrox Electronic Systems Ltd.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MILPROTO_H
#define __MILPROTO_H

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
{
#endif


/***************************************************************************/
/* BASIC IMAGE PROCESSING MODULE:                                          */
/***************************************************************************/

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* POINT TO POINT : */

      /* -------------------------------------------------------------- */

MFTYPE32 void MFTYPE    MimArith             (MIL_ID Src1ImageIdOrConstant,
                                              MIL_ID Src2ImageIdOrConstant,
                                              MIL_ID DestImageId,
                                              long Operation);

MFTYPE32 void MFTYPE    MimLutMap            (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              MIL_ID LutId);

MFTYPE32 void MFTYPE    MimShift             (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              long NbBitsToShift);

MFTYPE32 void MFTYPE    MimBinarize          (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              long Condition,
                                              long CondLow,
                                              long CondHigh);

MFTYPE32 void MFTYPE    MimClip              (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              long Condition,
                                              long CondLow,
                                              long CondHigh,
                                              long WriteLow,
                                              long WriteHigh);

MFTYPE32 void MFTYPE    MimConvert           (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              long ConversionType);

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* NEIGHBOURHOOD : */

      /* -------------------------------------------------------------- */

MFTYPE32 void MFTYPE    MimConvolve          (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              MIL_ID KernelId);

MFTYPE32 void MFTYPE    MimRank              (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              MIL_ID KernelId,
                                              long Rank,
                                              long Mode);

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* MORPHOLOGICAL: */

      /* -------------------------------------------------------------- */

MFTYPE32 void MFTYPE    MimLabel             (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              long Mode);

MFTYPE32 void MFTYPE    MimConnectMap        (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              MIL_ID LutBufId);

MFTYPE32 void MFTYPE    MimDilate            (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              long NbIteration,
                                              long Mode);

MFTYPE32 void MFTYPE    MimErode             (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              long NbIteration,
                                              long Mode);

MFTYPE32 void MFTYPE    MimClose             (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              long NbIteration,
                                              long Mode);

MFTYPE32 void MFTYPE    MimOpen              (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              long NbIteration,
                                              long Mode);

MFTYPE32 void MFTYPE    MimMorphic           (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              MIL_ID StructElementId,
                                              long Operation,
                                              long NbIteration,
                                              long Mode);

MFTYPE32 void MFTYPE    MimThin              (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              long NbIteration,
                                              long Mode);

MFTYPE32 void MFTYPE    MimThick             (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              long NbIteration,
                                              long Mode);

MFTYPE32 void MFTYPE    MimDistance          (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              long DistanceTranform);

MFTYPE32 void MFTYPE    MimZoneOfInfluence   (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              long OperationFlag);

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* GOEMETRICAL: */

      /* -------------------------------------------------------------- */

MFTYPE32 void MFTYPE    MimResize            (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              double FactorX,
                                              double FactorY,
                                              long InterpolationType);

MFTYPE32 void MFTYPE    MimRotate            (MIL_ID SrcImageId,
                                              MIL_ID DstImageId,
                                              double Angle,
                                              double SrcCenX,
                                              double SrcCenY,
                                              double DstCenX,
                                              double DstCenY,
                                              long   InterpolationMode);

MFTYPE32 void MFTYPE    MimTranslate         (MIL_ID SrcImageId,
                                              MIL_ID DestImageId,
                                              double xShift,
                                              double yShift,
                                              long InterpolationType);

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* STATISTICAL: */

      /* -------------------------------------------------------------- */

MFTYPE32 void MFTYPE    MimHistogram         (MIL_ID SrcImageId,
                                              MIL_ID HistogramListId);

MFTYPE32 void MFTYPE    MimHistogramEqualize (MIL_ID src_id,
                                              MIL_ID dst_id,
                                              long  EqualizationType,
                                              double Alpha,
                                              long Min,
                                              long Max);

MFTYPE32 void MFTYPE    MimProject           (MIL_ID SrcImageId,
                                              MIL_ID DestArrayId,
                                              double ProjectionAngle);

MFTYPE32 void MFTYPE    MimFindExtreme       (MIL_ID SrcImageId,
                                              MIL_ID ResultListId,
                                              long ExtremeType);

MFTYPE32 void MFTYPE    MimLocateEvent       (MIL_ID SrcImageId,
                                              MIL_ID EventResultId,
                                              long Condition,
                                              long CondLow,
                                              long CondHigh);

MFTYPE32 void MFTYPE    MimCountDifference   (MIL_ID Src1ImageId,
                                              MIL_ID Src2ImageId,
                                              MIL_ID ResId);

MFTYPE32 MIL_ID MFTYPE  MimAllocResult       (MIL_ID SystemId,
                                              long NumberOfResultElement,
                                              long ResultType,
                                              MIL_ID MPTYPE *IdVarPtr);

MFTYPE32 void MFTYPE    MimFree              (MIL_ID ImResultId);

MFTYPE32 long MFTYPE    MimInquire           (MIL_ID BufId,
                                              long InquireType,
                                              long MPTYPE *TargetVarPtr);

MFTYPE32 void MFTYPE    MimGetResult1d       (MIL_ID ImResultId,
                                              long Offresult,
                                              long Sizeresult,
                                              long ResultType,
                                              void MPTYPE *UserTargetArrayPtr);

MFTYPE32 void MFTYPE    MimGetResult         (MIL_ID ImResultId,
                                             long ResultType,
                                             void MPTYPE *UserTargetArrayPtr);

      /* -------------------------------------------------------------- */


/***************************************************************************/
/* GRAPHIC MODULE:                                                         */
/***************************************************************************/

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* CONTROL: */

      /* -------------------------------------------------------------- */

MFTYPE32 MIL_ID MFTYPE  MgraAlloc            (MIL_ID SystemId,
                                              MIL_ID MPTYPE *GraphContextIdVarPtr);

MFTYPE32 void MFTYPE    MgraFree             (MIL_ID GraphContextId);

MFTYPE32 void MFTYPE    MgraColor            (MIL_ID GraphContextId,
                                              long ForegroundColor);

MFTYPE32 void MFTYPE    MgraBackColor        (MIL_ID GraphContextId,
                                              long BackgroundColor);

MFTYPE32 void MFTYPE    MgraFont             (MIL_ID GraphContextId,
                                              void MPTYPE * Font);

MFTYPE32 void MPTYPE * MFTYPE MgraFontGetLarge(void);
MFTYPE32 void MPTYPE * MFTYPE MgraFontGetSmall(void);
MFTYPE32 void MPTYPE * MFTYPE MgraFontGetMedium(void);

MFTYPE32 void MFTYPE    MgraFontScale        (MIL_ID GraphContextId,
                                              double xFontScale,
                                              double yFontScale);

MFTYPE32 void MFTYPE    MgraInquire          (MIL_ID GraphContextId,
                                              long inquireType,
                                              void MPTYPE *result_ptr);
MFTYPE32 void MFTYPE    MgraControl          (MIL_ID GraphContextId,
                                              long ControlType,
                                              long ControlValue);


      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

  	   /* DRAWING : */

      /* -------------------------------------------------------------- */

MFTYPE32 void MFTYPE    MgraDot              (MIL_ID GraphContextId,
                                              MIL_ID ImageId,
                                              long XPos,
                                              long YPos);

MFTYPE32 void MFTYPE    MgraLine             (MIL_ID GraphContextId,
                                              MIL_ID ImageId,
                                              long XStart,
                                              long YStart,
                                              long XEnd,
                                              long YEnd);

MFTYPE32 void MFTYPE    MgraArc              (MIL_ID GraphContextId,
                                              MIL_ID ImageId,
                                              long XCenter,
                                              long YCenter,
                                              long XRad,
                                              long YRad,
                                              double StartAngle,
                                              double EndAngle);

MFTYPE32 void MFTYPE    MgraArcFill          (MIL_ID GraphContextId,
                                              MIL_ID ImageId,
                                              long XCenter,
                                              long YCenter,
                                              long XRad,
                                              long YRad,
                                              double StartAngle,
                                              double EndAngle);

MFTYPE32 void MFTYPE    MgraRect             (MIL_ID GraphContextId,
                                              MIL_ID ImageId,
                                              long XStart,
                                              long YStart,
                                              long XEnd,
                                              long YEnd);

MFTYPE32 void MFTYPE    MgraRectFill         (MIL_ID GraphContextId,
                                              MIL_ID ImageId,
                                              long XStart,
                                              long YStart,
                                              long XEnd,
                                              long YEnd);

MFTYPE32 void MFTYPE    MgraFill             (MIL_ID GraphContextId,
                                              MIL_ID ImageId,
                                              long XStart,
                                              long YStart);

MFTYPE32 void MFTYPE    MgraClear            (MIL_ID GraphContextId,
                                              MIL_ID ImageId);

MFTYPE32 void MFTYPE    MgraText             (MIL_ID GraphContextId,
                                              MIL_ID ImageId,
                                              long XStart,
                                              long YStart,
                                              char MPTYPE *String);

      /* -------------------------------------------------------------- */

/***************************************************************************/
/* DATA GENERATION MODULE:                                                 */
/***************************************************************************/

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* DATA BUFFERS: */

      /* -------------------------------------------------------------- */

MFTYPE32 void MFTYPE    MgenLutRamp          (MIL_ID LutBufId,
                                              long StartPoint,
                                              long StartValue,
         											    long EndPoint,
                                              long EndValue);

MFTYPE32 void MFTYPE    MgenLutFunction      (MIL_ID lut_id,
                                              long func,
                                              double a,
                                              double b,
                                              double c,
                                              long start_index,
                                              long StartXValue,
                                              long end_index);

      /* -------------------------------------------------------------- */

/***************************************************************************/
/* DATA BUFFERS MODULE:                                                    */
/***************************************************************************/

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* CREATION: */

      /* -------------------------------------------------------------- */

MFTYPE32 MIL_ID MFTYPE  MbufAlloc1d          (MIL_ID SystemId,
                                              long SizeX,
                                              long Type,
                                              long Attribute,
                                              MIL_ID MPTYPE *IdVarPtr);

MFTYPE32 MIL_ID MFTYPE  MbufAlloc2d          (MIL_ID SystemId,
                                              long SizeX,
                                              long SizeY,
                                              long Type,
                                              long Attribute,
                                              MIL_ID MPTYPE *IdVarPtr);

MFTYPE32 MIL_ID MFTYPE  MbufAllocColor       (MIL_ID SystemId,
                                              long SizeBand,
                                              long SizeX,
                                              long SizeY,
                                              long Type,
                                              long Attribute,
                                              MIL_ID MPTYPE *IdVarPtr);

MFTYPE32 MIL_ID MFTYPE  MbufChild1d          (MIL_ID ParentImageId,
                                              long OffX,
                                              long SizeX,
                                              MIL_ID MPTYPE *IdVarPtr);

MFTYPE32 MIL_ID MFTYPE  MbufChild2d          (MIL_ID ParentMilBufId,
                                              long OffX,
                                              long OffY,
                                              long SizeX,
                                              long SizeY,
                                              MIL_ID MPTYPE *IdVarPtr);

MFTYPE32 MIL_ID MFTYPE  MbufChildColor       (MIL_ID ParentMilBufId,
                                              long Band,
                                              MIL_ID MPTYPE *IdVarPtr);

MFTYPE32 void MFTYPE    MbufFree             (MIL_ID BufId);


      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* ACCESS: */

      /* -------------------------------------------------------------- */

MFTYPE32 void MFTYPE    MbufClear            (MIL_ID BufId,
                                              long Value);

MFTYPE32 void MFTYPE    MbufCopy             (MIL_ID SrcBufId,
                                              MIL_ID DestBufId);

MFTYPE32 void MFTYPE    MbufCopyColor        (MIL_ID SrcBufId,
                                              MIL_ID DestBufId,
                                              long Band);

MFTYPE32 void MFTYPE    MbufCopyClip         (MIL_ID SrcBufId,
                                              MIL_ID DestBufId,
                                              long DestOffsetX,
                                              long DestOffsetY);

MFTYPE32 void MFTYPE    MbufCopyMask         (MIL_ID SrcBufId,
                                              MIL_ID DestBufId,
                                              long MaskValue);

MFTYPE32 void MFTYPE    MbufCopyCond         (MIL_ID SrcBufId,
                                              MIL_ID DestBufId,
                                              MIL_ID CondBufId,
                                              long Cond,
                                              long CondVal);

MFTYPE32 void MFTYPE    MbufPut1d            (MIL_ID DestBufId,
                                              long Offx,
                                              long Sizex,
                                              void MPTYPE *BufferPtr);

MFTYPE32 void MFTYPE    MbufPut2d            (MIL_ID DestBufId,
                                              long Offx,
                                              long Offy,
                                              long Sizex,
                                              long Sizey,
                                              void MPTYPE *BufferPtr);

MFTYPE32 void MFTYPE    MbufPutColor         (MIL_ID DestBufId,
                                              long Format,
                                              long Band,
                                              void MPTYPE *BufferPtr);

MFTYPE32 void MFTYPE    MbufPut              (MIL_ID DestBufId,
                                              void MPTYPE *BufferPtr);

MFTYPE32 void MFTYPE    MbufGet1d            (MIL_ID SourceBufId,
                                              long Offx,
                                              long Sizex,
                                              void MPTYPE *BufferPtr);

MFTYPE32 void MFTYPE    MbufGet2d            (MIL_ID SourceBufId,
                                              long Offx,
                                              long Offy,
                                              long Sizex,
                                              long Sizey,
                                              void MPTYPE *BufferPtr);

MFTYPE32 void MFTYPE    MbufGetColor         (MIL_ID SourceBufId,
                                              long Format,
                                              long Band,
                                              void MPTYPE *BufferPtr);

MFTYPE32 void MFTYPE    MbufGet              (MIL_ID SourceBufId,
                                              void MPTYPE *BufferPtr);

MFTYPE32 long MFTYPE    MbufInquire          (MIL_ID BufId,
                                              long InquireType,
                                              void MPTYPE *ResultPtr);

MFTYPE32 long MFTYPE    MbufDiskInquire      (char MPTYPE *FileName,
                                              long InquireType,
                                              void MPTYPE *ResultPtr);

MFTYPE32 void MFTYPE    MbufSave             (char MPTYPE *FileName,
                                              MIL_ID BufId);

MFTYPE32 MIL_ID MFTYPE  MbufRestore          (char MPTYPE *FileName,
                                              MIL_ID SystemId,
                                              MIL_ID MPTYPE *IdVarPtr);

MFTYPE32 void MFTYPE    MbufLoad             (char MPTYPE *FileName,
                                              MIL_ID BufId);

MFTYPE32 MIL_ID MFTYPE  MbufImport           (char MPTYPE *FileName,
                                              MIL_ID FileFormatId,
                                              long Operation,
                                              MIL_ID SystemId,
                                              MIL_ID MPTYPE *IdVarPtr);

MFTYPE32 void MFTYPE    MbufExport           (char MPTYPE *FileName,
                                              MIL_ID FileFormatId,
                                              MIL_ID srcBufId);

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* CONTROL: */

      /* -------------------------------------------------------------- */

MFTYPE32 void MFTYPE    MbufControlNeighborhood (MIL_ID BufId,
                                                 long OperationFlags,
                                                 long OperationValue);

MFTYPE32 void MFTYPE    MbufControl             (MIL_ID BufId,
                                                 long OperationFlags,
                                                 double OperationValue);


      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

/***************************************************************************/
/* I/O DEVICES:                                                            */
/***************************************************************************/

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* CREATION: */

      /* -------------------------------------------------------------- */

typedef MFTYPE32 long (MFTYPE MPTYPE *MDIGHOOKFCTPTR)(long HookType,
                                                         MIL_ID EventId,
                                                         void MPTYPE *UserPtr);

MFTYPE32 MDIGHOOKFCTPTR MFTYPE MdigHookFunction(MIL_ID DigitizerId,
                                                long HookType,
                                                MDIGHOOKFCTPTR HandlerPtr,
                                                void MPTYPE *UserPtr);
                                                
MFTYPE32 MIL_ID MFTYPE  MdigAlloc            (MIL_ID SystemId,
                                              long DeviceNum,
                                              char MPTYPE *DataFormat,
                                              long InitFlag,
                                              MIL_ID MPTYPE *IdVarPtr);

MFTYPE32 void MFTYPE    MdigFree             (MIL_ID DevId);


      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* CONTROL: */

      /* -------------------------------------------------------------- */

MFTYPE32 void MFTYPE    MdigChannel          (MIL_ID DevId,
                                              long Channel);

MFTYPE32 void MFTYPE    MdigReference        (MIL_ID DevId,
                                              long ReferenceType,
                                              long ReferenceLevel);

MFTYPE32 void MFTYPE    MdigLut              (MIL_ID DevId,
                                              MIL_ID LutBufId);

MFTYPE32 void MFTYPE    MdigHalt             (MIL_ID DevId);

MFTYPE32 long MFTYPE    MdigInquire          (MIL_ID DevId,
                                              long InquireType,
                                              void MPTYPE *ResultPtr);

MFTYPE32 void MFTYPE    MdigControl          (MIL_ID DigitizerId,
                                              long ControlType,
                                              double Value);

MFTYPE32 void MFTYPE    MdigGrabWait         (MIL_ID DevId,
                                              long Flag);

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

	   /* ACCESS: */

      /* -------------------------------------------------------------- */

MFTYPE32 void MFTYPE    MdigGrab             (MIL_ID SrcDevId,
                                              MIL_ID DestImageId);

MFTYPE32 void MFTYPE    MdigGrabContinuous   (MIL_ID SrcDevId,
                                              MIL_ID DestImageId);

MFTYPE32 void MFTYPE    MdigAverage          (MIL_ID Digitizer,
                                              MIL_ID DestImageId,
                                              long WeightFactor,
                                              long AverageType,
                                              long NbIteration);

      /* -------------------------------------------------------------- */

/***************************************************************************/
/* DISPLAY MODULE:                                                         */
/***************************************************************************/

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* CONTROL: */

      /* -------------------------------------------------------------- */

MFTYPE32 MIL_ID MFTYPE  MdispAlloc           (MIL_ID SystemId,
                                              long DispNum,
                                              char MPTYPE *DispFormat,
                                              long InitFlag,
                                              MIL_ID MPTYPE *IdVarPtr);

MFTYPE32 void MFTYPE    MdispFree            (MIL_ID DisplayId);

MFTYPE32 void MFTYPE    MdispSelect          (MIL_ID DisplayId,
                                              MIL_ID ImageId);

MFTYPE32 void MFTYPE    MdispDeselect        (MIL_ID DisplayId,
                                              MIL_ID ImageId);

MFTYPE32 long MFTYPE    MdispInquire         (MIL_ID DisplayId,
                                              long inquire_type,
                                              void MPTYPE *result_ptr);

MFTYPE32 void MFTYPE    MdispPan             (MIL_ID DisplayId,
                                              long XOffset,
                                              long YOffset);

MFTYPE32 void MFTYPE    MdispZoom            (MIL_ID DisplayId,
                                              long XFactor,
                                              long YFactor);

MFTYPE32 void MFTYPE    MdispLut             (MIL_ID DisplayId,
                                              MIL_ID LutBufId);

MFTYPE32 void MFTYPE    MdispOverlayKey      (MIL_ID DisplayId,
                                              long Mode,
                                              long Cond,
                                              long Mask,
                                              long Color);

MFTYPE32 void MFTYPE    MdispControl         (MIL_ID DisplayId,
                                              long ControlType,
                                              long Value);


      /* -------------------------------------------------------------- */

/***************************************************************************/
/* SYSTEM MODULE:                                                          */
/***************************************************************************/

	  /* -------------------------------------------------------------- */
     /* -------------------------------------------------------------- */

     /* CONTROL: */

     /* -------------------------------------------------------------- */

MFTYPE32 MIL_ID MFTYPE MsysAlloc             (void MPTYPE *SystemType,
                                              long SystemNum,
                                              long InitFlag,
                                              MIL_ID MPTYPE *IdVarPtr);

MFTYPE32 void MFTYPE  MsysFree               (MIL_ID SystemId);

MFTYPE32 long MFTYPE  MsysInquire            (MIL_ID SystemId,
                                              long   InquireType,
                                              void MPTYPE *ResultPtr);

MFTYPE32 void MFTYPE  MsysControl            (MIL_ID SystemId,
                                              long ControlType,
                                              MIL_ID TargetSysId);

      /* -------------------------------------------------------------- */

/***************************************************************************/
/* APPLICATION MODULE:                                                     */
/***************************************************************************/

	  /* -------------------------------------------------------------- */
     /* -------------------------------------------------------------- */

     /* CONTROL: */

     /* -------------------------------------------------------------- */


typedef MFTYPE32 long (MFTYPE MPTYPE *MAPPHOOKFCTPTR)(long FHookType,
                                                      MIL_ID Id,
                                                      void MPTYPE *FExpansionFlagPtr);

MFTYPE32 MAPPHOOKFCTPTR MFTYPE MappHookFunction(long HookType,
                                                MAPPHOOKFCTPTR HookErrorCurrentPtr,
                                                void MPTYPE *ExpansionFlagPtr);

MFTYPE32 MIL_ID MFTYPE  MappAlloc         (long InitFlag,
                                           MIL_ID MPTYPE *IdVarPtr);

MFTYPE32 void MFTYPE    MappFree          (MIL_ID ApplicationId);

MFTYPE32 void MFTYPE    MappControl       (long ControlType,
                                           long ControlFlag);

MFTYPE32 long MFTYPE    MappGetError      (long ErrorType,
                                           void MPTYPE *ErrorVarPtr);

MFTYPE32 long MFTYPE    MappGetHookInfo   (MIL_ID Id,
                                           long InfoType,
                                           void MPTYPE *UserPtr);

MFTYPE32 long MFTYPE    MappInquire       (long InquireType,
                                           void MPTYPE *UserVarPtr);

MFTYPE32 void MFTYPE    MappModify        (MIL_ID FirstId,
                                           MIL_ID SecondId,
                                           long ModificationType,
                                           long ModificationFlag);

/* -------------------------------------------------------------- */



/* C++ directive if needed */
#ifdef __cplusplus
}
#endif
#endif


