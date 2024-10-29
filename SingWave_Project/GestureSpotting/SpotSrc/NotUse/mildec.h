/***************************************************************************/
/*

    Filename:  MILDEC.H
    Owner   :  Matrox Imaging dept.
    Rev     :  $Revision:   1.0  $
    Content :  This file contains the defines that are used by the
               mil functions to specify which type of command decoder
               will be used by the allocated system (MsysAlloc()).

    COPYRIGHT (c) 1993  Matrox Electronic Systems Ltd.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MILDEC_H
#define __MILDEC_H

    #ifdef __cplusplus
    extern "C"
    {
    #endif

    MFTYPE32 void MFTYPE MDMagicCommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MDVgaCommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MDImageCommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MDIp8CommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MDCometCommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MDMeteorCommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MDPulsarCommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MDGenesisCommandDecoder(void MPTYPE *Param);
    // ...

    #ifdef __cplusplus
    }
    #endif

    #define M_SYSTEM_HOST        ((void MPTYPE *)(((void (MFTYPE *)(void MPTYPE *Param))NULL)))
    #define M_SYSTEM_MAGIC       ((void MPTYPE *)(MDMagicCommandDecoder))
    #define M_SYSTEM_VGA         ((void MPTYPE *)(MDVgaCommandDecoder))
    #define M_SYSTEM_IMAGE       ((void MPTYPE *)(MDImageCommandDecoder))
    #define M_SYSTEM_IP8         ((void MPTYPE *)(MDIp8CommandDecoder))
    #define M_SYSTEM_COMET       ((void MPTYPE *)(MDCometCommandDecoder))
    #define M_SYSTEM_METEOR      ((void MPTYPE *)(MDMeteorCommandDecoder))
    #define M_SYSTEM_PULSAR      ((void MPTYPE *)(MDPulsarCommandDecoder))
    #define M_SYSTEM_GENESIS     ((void MPTYPE *)(MDGenesisCommandDecoder))
    // ...

#endif




