// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"
#include "CMyMIL.h"
#include "MyHand.h"
#include "SpotDoc.h"
#include "GestureDoc.h"
#include "CStroke.h"
#include "utils.h"

//#define GRAB_CONTINUOUSLY

#define MY_SCALE_FACTOR	(0.5)
//#define	WIDTH			(SHORT)(640 * MY_SCALE_FACTOR)
//#define HEIGHT			(SHORT)(480 * MY_SCALE_FACTOR)
#define	H_WID			(HEIGHT / 2)
#define H_HT			(WIDTH / 2)

BOOL CMyMIL::InitMILInstance()
{
	// Allocate application
//	MappAlloc(M_DEFAULT, &m_milAppl);
	// Allocate system
//	MsysAlloc(M_SYSTEM_SETUP, M_DEFAULT, M_COMPLETE, &m_milSystem);

	// Allocate digitizer(camera)
//	MdigAlloc(m_milSystem, M_DEFAULT, M_CAMERA_SETUP, M_DEFAULT, &m_milDigitizer);

	// Set scale factor of camera
//	MdigControl(m_milDigitizer, M_GRAB_SCALE, MY_SCALE_FACTOR);
//	MdigControl(m_milDigitizer, M_GRAB_FRAME_NUM, 1);

//	MsysControl(m_milSystem, M_STOP_LIVE_GRAB_WHEN_DISABLED, M_ENABLE);
	// Get digitizer size x, y, and number of bands
//	MdigInquire(m_milDigitizer, M_SIZE_X, &m_ldigSizeX);
//	MdigInquire(m_milDigitizer, M_SIZE_Y, &m_ldigSizeY);
//	MdigInquire(m_milDigitizer, M_SIZE_BAND, &m_lBand);

	// Set digitizer size according to scale factor
	m_ldigSizeX = (long) ( (float)m_ldigSizeX * MY_SCALE_FACTOR );
	m_ldigSizeY = (long) ( (float)m_ldigSizeY * MY_SCALE_FACTOR );

	if (m_ldigSizeX > M_DEF_IMAGE_SIZE_X_MAX)
		m_ldigSizeX = M_DEF_IMAGE_SIZE_X_MAX;
	if (m_ldigSizeY > M_DEF_IMAGE_SIZE_Y_MAX)
		m_ldigSizeY = M_DEF_IMAGE_SIZE_Y_MAX;

	// Get number of displays in the system
//	MsysInquire(m_milSystem, M_SYS_DISPLAY_NUM, &m_lMaxDisplay);

	// Clear flags for display selection
	m_pbSelDisplay = new BOOL[m_lMaxDisplay];
	memset(m_pbSelDisplay, 0, sizeof(long) * m_lMaxDisplay);

	// Clear grabbing falg
	m_bGrabStart = FALSE;

	return TRUE;
}

CMyMIL::CMyMIL()
{
	m_lSizeX		= 0;		// Buffer width
	m_lSizeY		= 0;		// Buffer height
	m_ldigSizeX		= 0;		// input width
	m_ldigSizeY		= 0;		// input height
	m_lBand			= 0;		// number of input color bands
	m_lMaxDisplay	= 0;		// maximum number of display
	m_bGrabStart	= FALSE;	// Is grabbing?
	m_theView		= NULL;		// the child view currently grabbing
	m_pbSelDisplay	= NULL;		// Is display selected?
	m_milAppl		= M_NULL;	// Application ID
	m_milSystem		= M_NULL;	// System ID
	m_milDigitizer	= M_NULL;	// Digitizer ID

	InitMILInstance();

	m_myHand = new CMyHand((SHORT)m_ldigSizeX, (SHORT)m_ldigSizeY);
}

CMyMIL::~CMyMIL()
{
	/*
	if (m_milDigitizer)	
		MdigFree(m_milDigitizer);
	if (m_milSystem) 
		MsysFree(m_milSystem);
	if (m_milAppl) 
		MappFree(m_milAppl);
	*/

	if (m_pbSelDisplay)
		delete [] m_pbSelDisplay;

	if (m_myHand)
		delete m_myHand;
	m_myHand = NULL;
}

// For SpotDoc class
BOOL CMyMIL::InitMILDocument(long* plDispIdx, MIL_ID* pmilImage,
							 MIL_ID* pmilDispImg)
{
	*pmilImage	 = M_NULL;
	*pmilDispImg = M_NULL;

	*plDispIdx = 0;
	while(*plDispIdx <= m_lMaxDisplay)
	{
		if (*plDispIdx < m_lMaxDisplay)
			if ( !(m_pbSelDisplay[*plDispIdx]) )
				break;
		(*plDispIdx)++;
	}

	m_lSizeX = m_ldigSizeX;
	m_lSizeY = m_ldigSizeY;
	
	/*
	if (*plDispIdx < m_lMaxDisplay) {
#ifdef GRAB_CONTINUOUSLY
		MbufAllocColor(m_milSystem, m_lBand,
			m_lSizeX, m_lSizeY, M_DEF_IMAGE_TYPE,
			M_IMAGE+M_GRAB+M_DISP, pmilDispImg);
		MbufClear(*pmilDispImg, 0);
#else
		MbufAllocColor(m_milSystem, m_lBand,
			m_lSizeX, m_lSizeY, M_DEF_IMAGE_TYPE,
			M_IMAGE+M_DISP, pmilDispImg);
		MbufClear(*pmilDispImg, 0);

		MbufAllocColor(m_milSystem, m_lBand,
			m_lSizeX, m_lSizeY, M_DEF_IMAGE_TYPE,
#	ifdef YIQ_COLOR
			M_IMAGE+M_GRAB+M_YUV16_PLANAR, pmilImage);
#	else
			M_IMAGE+M_GRAB, pmilImage);
#	endif
		MbufClear(*pmilImage, 0);
#endif
	}
	*/

	return TRUE;
}

void CMyMIL::CloseMILDocument(MIL_ID* pmilImage, MIL_ID* pmilDispImg)
{
	// if (*pmilImage) MbufFree(*pmilImage);
	*pmilImage = M_NULL;

	// if (*pmilDispImg) MbufFree(*pmilDispImg);
	*pmilDispImg = M_NULL;
}

// For SpotView class
void CMyMIL::InitMILUpdate(HWND hWnd, MIL_ID* pmilDisplay, long lDispIdx, MIL_ID milDispImg)
{
	// Allocate a display
	// MdispAlloc(	m_milSystem, lDispIdx, M_DISPLAY_SETUP, M_DEFAULT, pmilDisplay);
   
   // Disable scroll bars on display
	// MvgaDispControl(*pmilDisplay,M_DISP_WINDOW_SCROLLBAR,M_DISABLE);
	
	// Update the array DisplayIsSelected
	m_pbSelDisplay[lDispIdx] = TRUE;

	// Select the buffer from it's display object and given window
	// if (milDispImg)
	//	MvgaDispSelectClientArea(*pmilDisplay, milDispImg, hWnd);
}

void CMyMIL::RemoveMILDisplay(CView* pView, MIL_ID* pmilDisplay, MIL_ID milDispImg)
{
   	// Halt grab if in process in THIS view
	if ((m_theView == pView) && m_bGrabStart) {
#ifdef USE_HOOK_FUNC
    	MdigHalt(m_milDigitizer);
#endif
    	m_bGrabStart = FALSE;	
	}
 
	/*
   	// Deselect the buffer from it's display object and given window 
  	if (milDispImg && *pmilDisplay)
		MvgaDispDeselectClientArea(*pmilDisplay, milDispImg, pView->m_hWnd);
	
	// Free the display
	if(*pmilDisplay)
   		MdispFree(*pmilDisplay);
	*/

	*pmilDisplay= M_NULL;
}

BOOL CMyMIL::DestroyMILDisplay(CView* pView, long lDispIdx, MIL_ID milDispImg, 
						MIL_ID* pmilDisplay)
{
	if ((lDispIdx < m_lMaxDisplay) && milDispImg) {	
		m_pbSelDisplay[lDispIdx] = FALSE;
		RemoveMILDisplay(pView, pmilDisplay, milDispImg);
	} else if (lDispIdx >= m_lMaxDisplay)
		return FALSE;

	return TRUE;
}


void CMyMIL::DisplayFrame(MIL_ID milDispImg, SHORT nOnline)
{
#ifdef SHOW_COLOR_IMAGE
	if (nOnline != OP_REALTIME) {
#endif
		BYTE *pRbuf, *pGbuf, *pBbuf;

		pRbuf = &m_myHand->m_ImgBuf[0];
		pGbuf = &m_myHand->m_ImgBuf[m_ldigSizeY*m_ldigSizeX];
		pBbuf = &m_myHand->m_ImgBuf[m_ldigSizeY*2*m_ldigSizeX];
		for(int y=0; y<m_ldigSizeY; y++) {
			memcpy(pRbuf, m_myHand->m_curImg[y], m_ldigSizeX);
			pRbuf += m_ldigSizeX;
			memcpy(pGbuf, m_myHand->m_curImg[y], m_ldigSizeX);
			pGbuf += m_ldigSizeX;
			memcpy(pBbuf, m_myHand->m_curImg[y], m_ldigSizeX);
			pBbuf += m_ldigSizeX;
		}
#ifdef SHOW_COLOR_IMAGE
	}
#endif

//	MbufPutColor(milDispImg, M_PLANAR, M_ALL_BAND, m_myHand->m_ImgBuf);
}

POINT CMyMIL::ProcessFrame(MIL_ID milDispImg, SHORT nOnline, SHORT nCurFrame)
{
	POINT pt = {-1, -1};

	if (nOnline == OP_REALTIME)
		m_myHand->DumpFrame(m_myHand->m_curImg);

	if (!theApp.m_Flags.bGetGray) {
		if (theApp.m_Flags.bTrack || nOnline != OP_FRAMEDUMP) {
			pt = m_myHand->Recognize(nCurFrame);
		} else {
			for(int y=0; y<m_ldigSizeY; y++)
				for(int x=0; x<m_ldigSizeX; x++)
					m_myHand->m_curImg[y][x] = m_myHand->m_curImg[y][x] ? 255 : 0;
		}
	}

	DisplayFrame(milDispImg, nOnline);

//	MnatModified(milDispImg);

	return pt;
}

#ifdef USE_HOOK_FUNC
long WINAPI MPTYPE HookHandler(long lHookType, MIL_ID milEventID, void MPTYPE *pData)
{
	CSpotDoc*	 pDoc	= (CSpotDoc*)pData;
	CMyHand*	 pHand	= theMIL->m_myHand;

	if (m_bInProcessing)
		return (M_NULL);

	m_bInProcessing = TRUE;

//	MbufGet(pDoc->m_milImage, pHand->m_ImgBuf);

	if (theApp.m_Flags.bDumpMode) {
		pHand->DumpFrame(pHand->m_savImg[pHand->m_nCurFrame]);
		pHand->m_nCurFrame++;

		if (pHand->m_nCurFrame >= MAX_FRAME) {
			theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);
			SetStatusMessage("Dump finished");

			if (theApp.m_Flags.bAutoSave) {
				char szFrmFile[128];

				sprintf(szFrmFile, "Data\\Grab%04d.frm", theApp.m_nSaveCount++);
				pDoc->OnSaveDocument(szFrmFile);
			}
		}
	} else {
		theMIL->ProcessFrame(pDoc->m_milDispImg, OP_REALTIME, -1);
	}

	m_bInProcessing = FALSE;

	return(M_NULL);
}
#endif


#ifdef DEBUGGING_CODE
void CMyMIL::DebugProcessGrab(MIL_ID milImage, MIL_ID milDispImg)
{
	BOOL bTmp = TRUE;

	while(m_bGrabStart) {
		MdigGrab(m_milDigitizer, milImage);
		MbufGet(milImage, m_myHand->m_ImgBuf);

		m_myHand->DumpFrame(m_myHand->m_curImg);
		DisplayFrame(milDispImg, OP_FRAMEDUMP);

		bTmp = ProcessOtherMessage();
		m_bGrabStart &= bTmp; 
	}
}
#endif

BOOL CMyMIL::IsStayLong( POINT ptCur )
{
	if (ptCur.x < 0 || ptCur.y < 0)
		return TRUE;

	if (m_nRecent == 0) {
		m_ptAllDiff.x = 0;
		m_ptAllDiff.y = 0;
	} else {
		m_ptAllDiff.x += abs(m_ptRecent[m_nRecent-1].x - ptCur.x);
		m_ptAllDiff.y += abs(m_ptRecent[m_nRecent-1].y - ptCur.y);
	}
	m_ptRecent[m_nRecent++] = ptCur;

	if (m_nRecent >= MAX_RECENT) {
		if (m_ptAllDiff.x < MIN_MOVE && m_ptAllDiff.y < MIN_MOVE)
			return TRUE;

		m_ptAllDiff.x -= abs(m_ptRecent[0].x - m_ptRecent[1].x);
		m_ptAllDiff.y -= abs(m_ptRecent[0].y - m_ptRecent[1].y);

		for(int i=1; i<m_nRecent; i++)
			m_ptRecent[i-1] = m_ptRecent[i];
		m_nRecent--;
	}

	return FALSE;
}


BOOL CMyMIL::ConsiderSpotting( SHORT nOldLoc, POINT ptCur, REAL rWait )
{
	BOOL		 bStayLong;
	SHORT		 nNewLoc;
	CStroke*	 pStroke = m_myHand->m_pStroke;
	CGestureDoc* pGestDoc = (CGestureDoc*)theApp.m_pGestDoc;

	bStayLong = IsStayLong( ptCur );

	if ( m_myHand->m_nCurHand == -1 || bStayLong ) {
		pStroke->FlushHandPosition();
		m_ptAllDiff.x = m_ptAllDiff.y = 0;
		m_nRecent = 0;
	} else if (pStroke->m_Buf.nPt >= MAX_FRAME_INPUT) {
		pStroke->FlushHandPosition();
	}
	nNewLoc = pStroke->m_Norm.nPt;

	if (nNewLoc >= MAX_RESAMPLE_DATA || nOldLoc < nNewLoc) {
		POINT* pNewPt = &(pStroke->m_Norm.pPt[nOldLoc]);
		SHORT* pnFrameID = NULL;
		
		if (pStroke->m_Norm.pnFrameID)
			pnFrameID = &(pStroke->m_Norm.pnFrameID[nOldLoc]);

		pStroke->m_Norm.nPt = nOldLoc;
		for(int i=nOldLoc; i<nNewLoc; i++) {
			pStroke->m_Norm.pPt[pStroke->m_Norm.nPt] = pNewPt[i-nOldLoc];
			if (pnFrameID)
				pStroke->m_Norm.pnFrameID[pStroke->m_Norm.nPt] = pnFrameID[i-nOldLoc];
			pStroke->m_Norm.nPt++;

			if ( !pGestDoc->SpottingRecognition(pStroke, FALSE, rWait) ) {
				pStroke->m_Buf.nPt = 0;
				pStroke->m_Norm.nPt = 0;
				return FALSE;
			}
		}

		if ( nNewLoc >= MAX_RESAMPLE_DATA && nNewLoc == pStroke->m_Norm.nPt )
			pGestDoc->DisplaySpottedGesture( pStroke, FALSE, rWait );
	}

	if ( m_myHand->m_nCurHand == -1 || bStayLong ) {
		if (pStroke->m_Norm.nPt >= MIN_POINTS)
			pGestDoc->DisplaySpottedGesture( pStroke, TRUE, rWait );
		pStroke->m_Buf.nPt = 0;
		pStroke->m_Norm.nPt = 0;
	}

	return TRUE;
}

BOOL CMyMIL::StartFrameRecognize( BOOL bUseFrameID )
{
	CStroke*	 pStroke = m_myHand->m_pStroke;
	CGestureDoc* pGestDoc = (CGestureDoc*)theApp.m_pGestDoc;

	m_myHand->m_bStartRecognize = TRUE;
	pStroke->m_Norm.nPt = 0;
	pStroke->m_Buf.nPt = 0;
	m_ptAllDiff.x = m_ptAllDiff.y = 0;
	m_nRecent = 0;
	return pGestDoc->StartGestureRecognition( pStroke, bUseFrameID );
}

void CMyMIL::EndFrameRecognize(REAL rWait)
{
	CStroke*	 pStroke = m_myHand->m_pStroke;
	CGestureDoc* pGestDoc = (CGestureDoc*)theApp.m_pGestDoc;
	SHORT		 nOldLoc = pStroke->m_Norm.nPt;
	POINT		 ptCur = {0, 0};

	m_myHand->m_nCurHand = -1;
	ConsiderSpotting( nOldLoc, ptCur, rWait );
	m_myHand->m_bStartRecognize = FALSE;
	pGestDoc->EndSpottingRecognition( pStroke );

	m_ptAllDiff.x = m_ptAllDiff.y = 0;
	m_nRecent = 0;
}


void CMyMIL::ProcessGrab(MIL_ID milImage, MIL_ID milDispImg)
{
#ifdef DEBUGGING_CODE
	DebugProcessGrab( milImage, milDispImg );
	return;
#endif

	POINT		 ptCur;
	SHORT		 nOldLoc;
	CStroke*	 pStroke = m_myHand->m_pStroke;
	CGestureDoc* pGestDoc = (CGestureDoc*)theApp.m_pGestDoc;

	if (theApp.m_Flags.bDumpMode) {
		WaitMoment(2000.0, FALSE);
		MessageBeep(MB_OK);
	} else if (theApp.m_Flags.bRecognize) {
		WaitMoment(2000.0, FALSE);
		MessageBeep(MB_OK);

		StartFrameRecognize( FALSE );
	}

	SHORT nCheckFrame = 0;
	double dTime;

	if ( theApp.m_Flags.bCheckFrameRate )
		StartCheck(1);

	while(m_bGrabStart) {
#ifdef GRAB_CONTINUOUSLY
		// MdigGrab(m_milDigitizer, milDispImg);
#else
		// MdigGrab(m_milDigitizer, milImage);
		// MbufGet(milImage, m_myHand->m_ImgBuf);

		if ( theApp.m_Flags.bCheckFrameRate )
			nCheckFrame++;

		if (theApp.m_Flags.bDumpMode) {
			m_myHand->DumpFrame(m_myHand->m_savImg[m_myHand->m_nCurFrame]); 
			m_myHand->m_nCurFrame++;
		//	MbufPut(milDispImg, m_myHand->m_ImgBuf);

			if (m_myHand->m_nCurFrame >= theApp.m_nMaxFrame) {
				MessageBeep(MB_ICONHAND);
				if ( theApp.m_Flags.bCheckFrameRate ) {
					dTime = EndCheck(1);
					SetStatusMessage("Frame rate = %f", 
						(double)nCheckFrame*1000.0 / dTime );
					m_bGrabStart = FALSE;
				} else {
					m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);
					SetStatusMessage("Dump finished");

					if (theApp.m_Flags.bAutoSave) {
						CSpotDoc* pDoc = (CSpotDoc*)m_theView->GetDocument();
						char* pszFrmFile;

						pDoc->m_nInputType = theApp.m_nInputType;

						pDoc->m_nDumpID = GetDumpFileID(pDoc->m_nInputType);
						pszFrmFile = MakeMyDumpName(pDoc->m_nInputType, pDoc->m_nDumpID);
						pDoc->OnSaveDocument(pszFrmFile);
						pDoc->SetPathName(pszFrmFile);
						SetDumpFileID(pDoc->m_nInputType, pDoc->m_nDumpID+1);
					}
				}
			}
		} else {
			nOldLoc = pStroke->m_Norm.nPt;

			ptCur = ProcessFrame(milDispImg, OP_REALTIME, -1);
			if ( m_myHand->m_bStartRecognize ) {
				if ( !ConsiderSpotting(nOldLoc, ptCur, NO_WAIT) )
					m_bGrabStart = FALSE;
			}

			if (theApp.m_Flags.bCheckFrameRate && nCheckFrame >= MAX_FRAME)
				m_bGrabStart = FALSE;
		}
#endif

		if (m_bGrabStart) {
			if ( !ProcessOtherMessage() )
				m_bGrabStart = FALSE;
		}
	}

	if (m_myHand->m_bStartRecognize) {
		MessageBeep(MB_ICONHAND);
		EndFrameRecognize(NO_WAIT);

		if ( theApp.m_Flags.bCheckFrameRate ) {
			dTime = EndCheck(1);
			SetStatusMessage("Frame rate = %f", 
					(double)nCheckFrame*1000.0 / dTime );
		}
	}
}

void CMyMIL::StartGrab(MIL_ID milImage, MIL_ID milDispImg, CView* pView)
{
	// If there is a grab in a view, halt the grab before starting a new one
	if(m_bGrabStart)
		m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	if (theApp.m_Flags.bDumpMode)
		m_myHand->m_nCurFrame = 0;
	m_myHand->m_bFirst = TRUE;

	m_bGrabStart = TRUE;	
	m_theView = pView;

	/*

#ifdef USE_HOOK_FUNC
	m_bInProcessing = FALSE;
	MdigHookFunction(m_milDigitizer, M_GRAB_FRAME_END,
		(MDIGHOOKFCTPTR)HookHandler, 
		(void MPTYPE *)pView->GetDocument());
	MdigGrabContinuous(m_milDigitizer, milImage);
#else
#	ifdef GRAB_CONTINUOUSLY
	MdigGrabContinuous(m_milDigitizer, milDispImg);
#	else
	ProcessGrab(milImage, milDispImg);
#	endif
#endif
    */
}

void CMyMIL::FinishGrab()
{
	/*
#ifdef USE_HOOK_FUNC
	MdigHalt(m_milDigitizer);
#endif
	*/
	m_bGrabStart = FALSE;
}

void CMyMIL::GrabOneFrame(MIL_ID milImage, MIL_ID milDispImg)
{
	if(theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	WaitMoment(2000.0, FALSE);
	MessageBeep(MB_OK);
	
	/*
	MdigGrab(theMIL->m_milDigitizer, milImage);
	MbufGet(milImage, m_myHand->m_ImgBuf);
	MbufPut(milDispImg, m_myHand->m_ImgBuf);
	*/
}