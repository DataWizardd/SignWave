
// SpotView.cpp : implementation of the CSpotView class
//

// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"
#include "MyHand.h"
#include "SpotDoc.h"
#include "SpotView.h"
#include "GestureDoc.h"
#include "CStroke.h"
#include "CMyMIL.h"
#include "utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpotView

IMPLEMENT_DYNCREATE(CSpotView, CView)

BEGIN_MESSAGE_MAP(CSpotView, CView)
	//{{AFX_MSG_MAP(CSpotView)
	ON_COMMAND(IDM_FINISH_GRAB, OnFinishGrab)
	ON_UPDATE_COMMAND_UI(IDM_FINISH_GRAB, OnUpdateFinishGrab)
	ON_COMMAND(IDM_START_GRAB, OnStartGrab)
	ON_UPDATE_COMMAND_UI(IDM_START_GRAB, OnUpdateStartGrab)
	ON_WM_DESTROY()
	ON_COMMAND(IDM_DISPLAY_FRAME, OnDisplayFrame)
	ON_UPDATE_COMMAND_UI(IDM_DISPLAY_FRAME, OnUpdateDisplayFrame)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(IDM_NEXT_DUMP_FILE, OnNextDumpFile)
	ON_COMMAND(IDM_NEXT10_DUMP_FILE, OnNext10DumpFile)
	ON_COMMAND(IDM_PREV_DUMP_FILE, OnPrevDumpFile)
	ON_COMMAND(IDM_PREV10_DUMP_FILE, OnPrev10DumpFile)
	ON_COMMAND(IDM_GENERATE_ALL_FEATURE, OnGenerateAllFeature)
	ON_COMMAND(IDM_GEN_LASTDATA, OnGenLastData)
	ON_COMMAND(IDM_GEN_FIRSTDATA, OnGenFirstData)
	ON_COMMAND(IDM_GEN_NEXTDATA, OnGenNextData)
	ON_COMMAND(IDM_GEN_PREVDATA, OnGenPrevData)
	ON_COMMAND(IDM_GEN_QUITDATA, OnGenQuitData)
	ON_COMMAND(IDM_GEN_THRESHOLDDATA, OnGenThresholdData)
	ON_COMMAND(IDM_GEN_TESTDATA, OnGenTestData)
	ON_COMMAND(IDM_SAVE_SNAP_FRAME, OnSaveSnapFrame)
	ON_COMMAND(IDM_COUNT_LABEL, OnCountLabel)
	ON_COMMAND(IDM_RECOG_TEST_DATA, OnRecogTestData)
	ON_UPDATE_COMMAND_UI(IDM_RECOG_TEST_DATA, OnUpdateRecogTestData)
	ON_COMMAND(IDM_GEN_TEST_RESULT, OnGenTestResult)
	ON_COMMAND(IDM_GEN_ALPHADATA, OnGenAlphaData)
	ON_COMMAND(IDM_GEN_BYEDATA, OnGenByeData)
	ON_COMMAND(IDM_GEN_CIRCLEDATA, OnGenCircleData)
	ON_COMMAND(IDM_GEN_SAWDATA, OnGenSawData)
	ON_COMMAND(IDM_GEN_TRIANGLEDATA, OnGenTriangleData)
	ON_COMMAND(IDM_GEN_CUR_FEATURE, OnGenCurFeature)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpotView construction/destruction

CSpotView::CSpotView()
{
	// TODO: add construction code here

}

CSpotView::~CSpotView()
{
}

BOOL CSpotView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSpotView drawing

void CSpotView::OnDraw(CDC* pDC)
{
	CSpotDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSpotView diagnostics

#ifdef _DEBUG
void CSpotView::AssertValid() const
{
	CView::AssertValid();
}

void CSpotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSpotDoc* CSpotView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpotDoc)));
	return (CSpotDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpotView message handlers

void CSpotView::OnInitialUpdate()
{
	CSpotDoc* pDoc = GetDocument();

	theMIL->InitMILUpdate(m_hWnd, &m_milDisplay,
		pDoc->m_lDispIdx, pDoc->m_milDispImg);

	if (theMIL->m_lSizeX > 0 && theMIL->m_lSizeY > 0)
	{
		// Get active multimedia window rectangle    
		CRect MMRect(0, 0, theMIL->m_lSizeX, theMIL->m_lSizeY);

		// Resize frame to the dimensions of the multimedia window
		GetParent()->CalcWindowRect(&MMRect);
		MMRect.OffsetRect(-MMRect.left, -MMRect.top);

		GetParent()->SetWindowPos(NULL,
			0, 0,
			MMRect.right,
			MMRect.bottom,
			SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE);

		GetParent()->InvalidateRect(NULL, FALSE);
	}

	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class	
}

void CSpotView::OnDestroy()
{
	CSpotDoc* pDoc = (CSpotDoc*)GetDocument();

	// Update the array DisplayIsSelected if the maximum number of display is not reached
	if (!theMIL->DestroyMILDisplay(this, pDoc->m_lDispIdx, pDoc->m_milDispImg,
		&m_milDisplay)) {
		AfxMessageBox("The maximum number of display allowed on this device\nis reached. A new document can not be created.",
			MB_OK, 0);
	}

	CView::OnDestroy();

	// TODO: Add your message handler code here

}

// Function used to halt the grab, deselect the buffer and free the display
void CSpotView::RemoveFromDisplay()
{
	CSpotDoc* pDoc = (CSpotDoc*)GetDocument();

	theMIL->RemoveMILDisplay(this, &m_milDisplay, pDoc->m_milDispImg);
}

void CSpotView::OnFinishGrab()
{
	// TODO: Add your command handler code here

	SetStatusMessage("Grab finished");
	theMIL->FinishGrab();
}

void CSpotView::OnUpdateFinishGrab(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here

//	pCmdUI->Enable( (theMIL->m_theView == this) &&
//					(theMIL->m_bGrabStart == TRUE) );
}

void CSpotView::OnStartGrab()
{
	// TODO: Add your command handler code here
	CSpotDoc* pDoc = (CSpotDoc*)GetDocument();

	SetStatusMessage("Grab started");

	if (theApp.m_Flags.bRecognize) {
		CGestureDoc* pGestDoc = (CGestureDoc*)theApp.m_pGestDoc;

		pGestDoc->GenerateThresholdModel(THRESHOLD_PROB);
		pGestDoc->GenerateUnitedModel(THRESHOLD_PROB);
	}

	theMIL->StartGrab(pDoc->m_milImage, pDoc->m_milDispImg, this);

	// Document has been modified
//	if (theApp.m_Flags.bDumpMode)
//		pDoc->SetModifiedFlag(TRUE);
}

void CSpotView::OnUpdateStartGrab(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here

	pCmdUI->Enable((theMIL->m_theView != this) ||
		(theMIL->m_bGrabStart == FALSE));
}


void CSpotView::CommandTextOut(int nX, int nY, char* pszStr, int nAlign)
{
	if (!pszStr || strlen(pszStr) == 0)
		return;

	CDC* pDC = GetDC();
	int  nOldBk, nOldAlign;

	nOldBk = pDC->SetBkMode(TRANSPARENT);
	nOldAlign = pDC->SetTextAlign(nAlign);
	pDC->TextOut(nX, nY, pszStr, strlen(pszStr));
	pDC->SetTextAlign(nOldAlign);
	pDC->SetBkMode(nOldBk);
	ReleaseDC(pDC);
}


#define MIRROR_IMAGE

// Display dumped frams
// Commands
//		Common commands
//			N: Next
//			P: Previous
//			S: Save
//			Q: Quit displaying and cancel all operations(editing, labelling)
//		Frame editing commands
//			D: Delete current frame
//			Shift+D: Delete remaining frames
//		Labelling commands
//			L: Start labelling
//			0: Label 'Last'
//			1: Label 'First'
//			2: Label 'Next'
//			3: Label 'Prev'
//			4: Label 'Quit'
//			-: Cancel previous labelling
//			   Clear nLast setting
BOOL CSpotView::DisplayFrameImage(REAL rWait, BOOL bUseFrameID)
{
	// TODO: Add your command handler code here

	SHORT		 nFrame, nChange = +1;
	BOOL		 bLoop = TRUE;
	BOOL		 bSave = FALSE;
	SHORT		 nOldLoc;
	CSpotDoc* pDoc = (CSpotDoc*)GetDocument();
	CMyHand* pHand = theMIL->m_myHand;
	CStroke* pStroke = pHand->m_pStroke;
	CGestureDoc* pGestDoc = (CGestureDoc*)theApp.m_pGestDoc;
	BYTE* pbRemoved = NULL;
	char		 szStr[50];
	POINT		 ptCur, ptPre = { 0, 0 };
	SHORT		 nLabel = 0;
	MYLABEL* pLabel = NULL;

	pHand->m_bFirst = TRUE;
#ifdef USE_HOOK_FUNC
	theMIL->m_bInProcessing = FALSE;
#endif
	theMIL->m_theView = this;

	if (theApp.m_Flags.bRecognize) {
		theMIL->StartFrameRecognize(bUseFrameID);
		if (theApp.m_Flags.bContinuous && theApp.m_Flags.bCheckFrameRate) {
			StartCheck(2);
			rWait = NO_WAIT;
		}
	}
	else if (theApp.m_Flags.bLabelling) {
		nLabel = 0;
		pLabel = new MYLABEL[MAX_MYLABEL];
		pLabel[0].nStart = -1;
	}
	else {
		pbRemoved = new BYTE[pHand->m_nCurFrame];
		memset(pbRemoved, 0, pHand->m_nCurFrame);
	}

	nFrame = 0;
	while (bLoop && !bSave) {
		if (!pbRemoved || !pbRemoved[nFrame]) {
			if (nChange == 0) {
				nChange = +1;
			}
			else {
				for (int j = 0; j < pHand->m_nHeight; j++) {
#ifdef MIRROR_IMAGE
					memcpy(pHand->m_curImg[j], pHand->m_savImg[nFrame][j], pHand->m_nWidth);
#else
					for (int k = 0; k < pHand->m_nWidth; k++)
						pHand->m_curImg[j][k] = pHand->m_savImg[nFrame][j][pHand->m_nWidth - k - 1];
#endif
				}

				nOldLoc = pStroke->m_Norm.nPt;

				ptCur = theMIL->ProcessFrame(pDoc->m_milDispImg, OP_FRAMEDUMP, nFrame);

				if (pHand->m_nCurFrame > 1) {
					sprintf(szStr, "%d", nFrame);
					CommandTextOut(5, 5, szStr, TA_TOP | TA_LEFT);
				}

				if (pHand->m_bStartRecognize) {
					if (!theMIL->ConsiderSpotting(nOldLoc, ptCur, rWait))
						bLoop = FALSE;
				}

				if (pHand->m_nCurFrame > 1) {
					if (pHand->m_nCurHand > 0)
						sprintf(szStr, "(%d, %d)", ptCur.x - ptPre.x, ptCur.y - ptPre.y);
					else
						sprintf(szStr, "Hand not found");
					CommandTextOut(5, 235, szStr, TA_BOTTOM | TA_LEFT);
				}
				if (pHand->m_nCurHand > 0)
					ptPre = ptCur;
			}

			if (!theApp.m_Flags.bContinuous) {
				MSG  msg;
				BOOL bSelfLoop = TRUE;

				while (bSelfLoop) {
					while (PeekMessage((LPMSG)&msg, NULL, 0, 0, PM_REMOVE)) {
						TranslateMessage(&msg);
						DispatchMessage(&msg);

						if (!theApp.m_Flags.bRecognize &&
							msg.message == WM_KEYUP && msg.wParam == VK_DELETE) {
							msg.message = WM_CHAR;
							msg.wParam = 'd';
						}

						if (msg.message == WM_CHAR) {
							bSelfLoop = FALSE;
							switch (msg.wParam) {
							case 'c': case 'C':	// Change display mode: 
								// Frame by frame -> Continuous
								theApp.m_Flags.bContinuous = TRUE;
								break;
							case 'd': case 'D':	// Delete frame
								if (theApp.m_Flags.bRecognize || theApp.m_Flags.bLabelling) {
									MessageBeep(MB_ICONHAND);
									SetStatusMessage("Can not delete frame!!!");
								}
								else {
									CommandTextOut(160, 235, "Deleted!!", TA_BOTTOM | TA_CENTER);

									pbRemoved[nFrame] = TRUE;
									if (GetKeyState(VK_SHIFT) & 0x80) {
										for (int i = nFrame; i < pHand->m_nCurFrame; i++)
											pbRemoved[i] = TRUE;
									}
								}
								break;
							case '-':
								if (pLabel && theApp.m_Flags.bLabelling) {
									if (nLabel > 0) {
										nChange = 0;
										nLabel--;
										sprintf(szStr, "Clear %s(%d)",
											GetModelName(pLabel[nLabel].nModel), nLabel);
										CommandTextOut(315, 235, szStr, TA_BOTTOM | TA_RIGHT);
									}
								}
								break;
							case 'l': case 'L':
								if (pLabel && theApp.m_Flags.bLabelling) {
									CommandTextOut(160, 235, "Start Labelling", TA_BOTTOM | TA_CENTER);
									pLabel[nLabel].nStart = nFrame;
									nChange = +1;
								}
								break;
							case '0': case '1': case '2': case '3': case '4':
							case '5': case '6': case '7': case '8': case '9':
								if (pLabel && theApp.m_Flags.bLabelling) {
									if (pLabel[nLabel].nStart < 0 ||
										pLabel[nLabel].nStart >= nFrame) {
										MessageBeep(MB_ICONHAND);
										SetStatusMessage("Starting point is not set!!!");
									}
									else {
										sprintf(szStr, "%s(%d)", GetModelName(msg.wParam - '0'), nLabel);
										CommandTextOut(160, 235, szStr, TA_BOTTOM | TA_CENTER);

										pLabel[nLabel].nLast = nFrame;
										pLabel[nLabel].nModel = msg.wParam - '0';
										nLabel++;
										pLabel[nLabel].nStart = -1;
										nChange = 0;
									}
								}
								break;
							case 'n': case 'N':	// Display frame in order
								if (!theApp.m_Flags.bRecognize)
									nChange = +1;
								break;
							case 'p': case 'P':	// Display frame in reverse order
								if (!theApp.m_Flags.bRecognize)
									nChange = -1;
								break;
							case 'q': case 'Q':	// Quit displaying frames
								bLoop = FALSE;
								break;
							case 's': case 'S':	// Save changed frame or labelling data
								if (!theApp.m_Flags.bRecognize || theApp.m_Flags.bLabelling) {
									bSave = TRUE;
									CommandTextOut(315, 235, "Saving...", TA_BOTTOM | TA_RIGHT);
								}
								break;
							default:
								break;
							}
						}
					}
				}
			}
			else {
				if (bLoop)
					bLoop = ProcessOtherMessage();
			}
		}
		if (bLoop && !bSave) {
			nFrame += nChange;
			if (nFrame == pHand->m_nCurFrame && theApp.m_Flags.bRecognize)
				break;
			if (nFrame < 0)
				nFrame = pHand->m_nCurFrame - 1;
			else
				nFrame = nFrame % pHand->m_nCurFrame;
			if (nFrame == 0 || nFrame == pHand->m_nCurFrame - 1)
				MessageBeep(MB_OK);
		}
	}

	if (pbRemoved) {
		nFrame = 0;
		for (int i = 0; i < pHand->m_nCurFrame; i++) {
			if (!pbRemoved[i]) {
				if (i > nFrame) {
					for (int j = 0; j < pHand->m_nHeight; j++) {
						memcpy(pHand->m_savImg[nFrame][j],
							pHand->m_savImg[i][j], pHand->m_nWidth);
					}
				}
				nFrame++;
			}
		}
		pHand->m_nCurFrame = nFrame;

		delete[] pbRemoved;
	}

	if (bLoop && bSave) {
		if (pLabel && theApp.m_Flags.bLabelling)
			pDoc->SaveLabellingData(nLabel, pLabel);
		else
			pDoc->OnSaveDocument(NULL);
	}

	if (pLabel)
		delete[] pLabel;

	if (pHand->m_bStartRecognize) {
		theMIL->EndFrameRecognize(rWait);
		if (theApp.m_Flags.bContinuous && theApp.m_Flags.bCheckFrameRate) {
			double dTime = EndCheck(2);
			SetStatusMessage("Frame rate = %f",
				(double)(pHand->m_nCurFrame) * 1000.0 / dTime);
		}
	}

	return bLoop;
}

void CSpotView::OnDisplayFrame()
{
	// TODO: Add your command handler code here
	REAL		rWait = NO_WAIT;
	CSpotDoc* pDoc = (CSpotDoc*)GetDocument();

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	if (pDoc->m_nInputType == MODEL_TEST)
		rWait = LONG_WAIT;

	if (theApp.m_Flags.bRecognize) {
		CGestureDoc* pGestDoc = (CGestureDoc*)theApp.m_pGestDoc;

		pGestDoc->GenerateThresholdModel(THRESHOLD_PROB);
		pGestDoc->GenerateUnitedModel(THRESHOLD_PROB);
	}

	DisplayFrameImage(rWait, FALSE);
}

void CSpotView::OnUpdateDisplayFrame(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here

	pCmdUI->Enable(theMIL->m_myHand->m_nCurFrame > 0);
}

void CSpotView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: Add your specialized code here and/or call the base class
	if (theMIL->m_theView != pActivateView && theMIL->m_bGrabStart) {
#ifdef USE_HOOK_FUNC
		MdigHalt(theMIL->m_milDigitizer);
#endif
		theMIL->m_bGrabStart = FALSE;
	}
	theMIL->m_theView = pActivateView;

	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CSpotView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (theMIL->m_theView == this && !theMIL->m_bGrabStart) {
		OnStartGrab();
	}
	CView::OnLButtonDblClk(nFlags, point);
}

void CSpotView::OnNextDumpFile()
{
	// TODO: Add your command handler code here

	if (((CSpotDoc*)GetDocument())->GetNextDumpFile(1))
		OnDisplayFrame();
}

void CSpotView::OnNext10DumpFile()
{
	// TODO: Add your command handler code here

	if (((CSpotDoc*)GetDocument())->GetNextDumpFile(10))
		OnDisplayFrame();
}

void CSpotView::OnPrevDumpFile()
{
	// TODO: Add your command handler code here

	if (((CSpotDoc*)GetDocument())->GetPrevDumpFile(1))
		OnDisplayFrame();
}

void CSpotView::OnPrev10DumpFile()
{
	// TODO: Add your command handler code here

	if (((CSpotDoc*)GetDocument())->GetPrevDumpFile(10))
		OnDisplayFrame();
}

BOOL CSpotView::SaveHandLocation(POINT* pPt, SHORT nPt)
{
	FILE* fp;
	char* pszFileName;

	pszFileName = MakeMyResultName(NAME_LOCATION);

	if (!(fp = fopen(pszFileName, "wb"))) {
		Warning("(CSpotView::SavePointsWithFrameID) file <%s> not found", pszFileName);
		return(FALSE);
	}

	SetStatusMessage("Writing location file %s ......", pszFileName);

	MyWrite(&nPt, sizeof(SHORT), 1, fp);
	// For writing POINT structure {LONG, LONG}
	MyWrite(pPt, sizeof(LONG), nPt * 2, fp);

	fclose(fp);

	return TRUE;
}

BOOL CSpotView::LoadHandLocation(POINT* pPt, SHORT* pnPt)
{
	FILE* fp;
	char* pszFileName;

	*pnPt = 0;
	pszFileName = MakeMyResultName(NAME_LOCATION);

	if (!(fp = fopen(pszFileName, "rb"))) {
		Warning("(CSpotView::LoadPointsWithFrameID) file <%s> not found", pszFileName);
		return(FALSE);
	}

	SetStatusMessage("Reading location file %s ......", pszFileName);

	MyRead(pnPt, sizeof(SHORT), 1, fp);
	// For writing POINT structure {LONG, LONG}
	MyRead(pPt, sizeof(LONG), *pnPt * 2, fp);

	fclose(fp);

	return TRUE;
}

BOOL CSpotView::GenerateFeature(SHORT nInputType, SHORT nFileID)
{
	SHORT		 nFiles, n1stFile = 0;
	BOOL		 bLoop = TRUE;
	CMyHand* pHand = theMIL->m_myHand;
	CSpotDoc* pDoc = (CSpotDoc*)GetDocument();
	CStroke* pStroke = pHand->m_pStroke;
	CGestureDoc* pGestDoc = (CGestureDoc*)theApp.m_pGestDoc;
	char* pPathName;
	POINT		 ptCur, ptPre = { 0, 0 };

	theMIL->m_theView = this;

	nFiles = GetDumpFileID(nInputType);
	if (nFileID >= 0 && nFileID < nFiles) {
		n1stFile = nFileID;
		nFiles = nFileID + 1;
	}

	pDoc->m_nInputType = nInputType;

	//	for(int i=50; bLoop && i<80; i++) {
	for (int i = n1stFile; bLoop && i < nFiles; i++) {
		pDoc->m_nDumpID = i;
		pPathName = MakeMyDumpName(nInputType, i);
		if (!pDoc->OnOpenDocument(pPathName))
			continue;
		pDoc->SetPathName(pPathName);

		pHand->m_bFirst = TRUE;
		pStroke->m_Norm.nPt = 0;
		pStroke->m_Buf.nPt = 0;
		pStroke->m_bNormalized = FALSE;

		for (int nFrame = 0; bLoop && nFrame < pHand->m_nCurFrame; nFrame++) {
			for (int j = 0; j < pHand->m_nHeight; j++)
				memcpy(pHand->m_curImg[j], pHand->m_savImg[nFrame][j], pHand->m_nWidth);

			ptCur = theMIL->ProcessFrame(pDoc->m_milDispImg, OP_GETFEATURE, -1);

			if (nInputType == MODEL_TEST) {
				if (pHand->m_nCurHand > 0) {
					pStroke->m_Buf.pPt[pStroke->m_Buf.nPt] = ptCur;
				}
				else {
					pStroke->m_Buf.pPt[pStroke->m_Buf.nPt].x = -1;
					pStroke->m_Buf.pPt[pStroke->m_Buf.nPt].y = -1;
				}
				pStroke->m_Buf.nPt++;
			}
			else if (pHand->m_nCurHand > 0) {
				if (pStroke->m_Buf.nPt == 0 ||
					ptCur.x != ptPre.x || ptCur.y != ptPre.y) {
					pStroke->m_Buf.pPt[pStroke->m_Buf.nPt++] = ptCur;
				}
				ptPre = ptCur;
			}

			bLoop = ProcessOtherMessage();
		}
		if (bLoop) {
			if (nInputType == MODEL_TEST) {
				SaveHandLocation(pStroke->m_Buf.pPt, pStroke->m_Buf.nPt);
			}
			else {
				pStroke->SaveFrameStroke(nInputType, i);
			}

			bLoop = ProcessOtherMessage();
		}
	}
	MessageBeep(MB_OK);

	return bLoop;
}

void CSpotView::OnGenerateAllFeature()
{
	// TODO: Add your command handler code here

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	for (int i = 0; i <= MODEL_TEST; i++)
		if (!GenerateFeature(i, -1)) break;

	SetStatusMessage("Feature generation done!!!");
}

void CSpotView::OnGenLastData()
{
	// TODO: Add your command handler code here

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	GenerateFeature(MODEL_LAST, -1);
	SetStatusMessage("Last: Feature generation done!!!");
}

void CSpotView::OnGenFirstData()
{
	// TODO: Add your command handler code here

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	GenerateFeature(MODEL_FIRST, -1);
	SetStatusMessage("First: Feature generation done!!!");
}

void CSpotView::OnGenNextData()
{
	// TODO: Add your command handler code here

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	GenerateFeature(MODEL_NEXT, -1);
	SetStatusMessage("Next: Feature generation done!!!");
}

void CSpotView::OnGenPrevData()
{
	// TODO: Add your command handler code here

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	GenerateFeature(MODEL_PREV, -1);
	SetStatusMessage("Previous: Feature generation done!!!");
}

void CSpotView::OnGenQuitData()
{
	// TODO: Add your command handler code here

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	GenerateFeature(MODEL_QUIT, -1);
	SetStatusMessage("Quit: Feature generation done!!!");
}

void CSpotView::OnGenAlphaData()
{
	// TODO: Add your command handler code here

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	GenerateFeature(MODEL_ALPHA, -1);
	SetStatusMessage("Alpha: Feature generation done!!!");
}

void CSpotView::OnGenByeData()
{
	// TODO: Add your command handler code here

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	GenerateFeature(MODEL_BYE, -1);
	SetStatusMessage("Bye: Feature generation done!!!");
}

void CSpotView::OnGenCircleData()
{
	// TODO: Add your command handler code here

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	GenerateFeature(MODEL_CIRCLE, -1);
	SetStatusMessage("Circle: Feature generation done!!!");
}

void CSpotView::OnGenSawData()
{
	// TODO: Add your command handler code here

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	GenerateFeature(MODEL_SAW, -1);
	SetStatusMessage("Saw: Feature generation done!!!");
}

void CSpotView::OnGenTriangleData()
{
	// TODO: Add your command handler code here

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	GenerateFeature(MODEL_TRIANGLE, -1);
	SetStatusMessage("Triangle: Feature generation done!!!");
}

void CSpotView::OnGenThresholdData()
{
	// TODO: Add your command handler code here

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	GenerateFeature(MODEL_THRESHOLD, -1);
	SetStatusMessage("Threshold: Feature generation done!!!");
}

void CSpotView::OnGenTestData()
{
	// TODO: Add your command handler code here

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	GenerateFeature(MODEL_TEST, -1);
	SetStatusMessage("Test: Feature generation done!!!");
}


SHORT GetSnapFileID()
{
	int		nID;
	FILE* fp;

	fp = fopen(MakeMyFileName("Snap\\", "Snap", "id"), "r");

	if (!fp)
		return 0;

	fscanf(fp, "%d", &nID);
	fclose(fp);

	return ((SHORT)nID);
}

void SetSnapFileID(SHORT nID)
{
	FILE* fp;

	fp = fopen(MakeMyFileName("Snap\\", "Snap", "id"), "w");

	fprintf(fp, "%d\n", nID);
	fclose(fp);
}

void CSpotView::OnSaveSnapFrame()
{
	// TODO: Add your command handler code here

	CSpotDoc* pDoc = (CSpotDoc*)GetDocument();
	CMyHand* pHand = theMIL->m_myHand;
	BYTE* pRbuf, * pGbuf, * pBbuf;
	BOOL		bOldGetGray = theApp.m_Flags.bGetGray;
	BOOL		bOldGetY = theApp.m_Flags.bGetY;
	SHORT		nSnapID;
	char		szStr[10];
	char* pszFName;

	theMIL->GrabOneFrame(pDoc->m_milImage, pDoc->m_milDispImg);

	pRbuf = &pHand->m_ImgBuf[0];
	pGbuf = &pHand->m_ImgBuf[pHand->m_nHeight * pHand->m_nWidth];
	pBbuf = &pHand->m_ImgBuf[pHand->m_nHeight * 2 * pHand->m_nWidth];

	nSnapID = GetSnapFileID();

	pHand->m_nCurFrame = 3;
	theApp.m_Flags.bGetGray = TRUE;
	for (int y = 0; y < pHand->m_nHeight; y++) {
		memcpy(pHand->m_savImg[0][y], pRbuf, pHand->m_nWidth);
		pRbuf += pHand->m_nWidth;
		memcpy(pHand->m_savImg[1][y], pGbuf, pHand->m_nWidth);
		pGbuf += pHand->m_nWidth;
		memcpy(pHand->m_savImg[2][y], pBbuf, pHand->m_nWidth);
		pBbuf += pHand->m_nWidth;
	}
	sprintf(szStr, "RGB%03d", nSnapID);
	pszFName = MakeMyFileName("Snap\\", szStr, "frm");
	pDoc->OnSaveDocument(pszFName);

	pHand->m_nCurFrame = 1;
	theApp.m_Flags.bGetY = TRUE;
	pHand->DumpFrame(pHand->m_savImg[0]);
	sprintf(szStr, "Gray%03d", nSnapID);
	pszFName = MakeMyFileName("Snap\\", szStr, "frm");
	pDoc->OnSaveDocument(pszFName);

	theApp.m_Flags.bGetY = FALSE;
	pHand->DumpFrame(pHand->m_savImg[0]);
	sprintf(szStr, "YIQ%03d", nSnapID);
	pszFName = MakeMyFileName("Snap\\", szStr, "frm");
	pDoc->OnSaveDocument(pszFName);

	theApp.m_Flags.bGetGray = FALSE;
	pHand->DumpFrame(pHand->m_savImg[0]);
	sprintf(szStr, "Bin%03d", nSnapID);
	pszFName = MakeMyFileName("Snap\\", szStr, "frm");
	pDoc->OnSaveDocument(pszFName);

	SetSnapFileID(nSnapID + 1);

	pHand->m_nCurFrame = 0;
	theApp.m_Flags.bGetGray = bOldGetGray;
	theApp.m_Flags.bGetY = bOldGetY;
}

void CSpotView::OnCountLabel()
{
	// TODO: Add your command handler code here

	SHORT		nData = 0;
	SHORT		nLabel = 0;
	CSpotDoc* pDoc = (CSpotDoc*)GetDocument();
	SHORT		nOldInputType = pDoc->m_nInputType;
	SHORT		nOldDumpID = pDoc->m_nDumpID;
	int			i, j;

	pDoc->m_nInputType = MODEL_TEST;
	SHORT nFiles = GetDumpFileID(MODEL_TEST);

	if (nFiles < 1)
		return;

	SHORT* pnData = new SHORT[MODEL_THRESHOLD];
	MYLABEL* pLabel = new MYLABEL[MAX_MYLABEL];

	memset(pnData, 0, sizeof(SHORT) * MODEL_THRESHOLD);
	memset(pLabel, 0, sizeof(MYLABEL) * MAX_MYLABEL);

	for (i = 0; i < nFiles; i++) {
		pDoc->m_nDumpID = i;
		if (!pDoc->LoadLabellingData(&nLabel, pLabel))
			break;
		if (nLabel > 0) {
			nData += nLabel;
			for (j = 0; j < nLabel; j++)
				pnData[pLabel[j].nModel]++;
		}
	}

	ClearDisplay(theApp.m_pGestView);
	for (i = 0; i < MODEL_THRESHOLD; i++)
		PrintProgressString("%s: %d", GetModelName(i), pnData[i]);
	PrintProgressString("Total: %d", nData);

	delete[] pLabel;
	delete[] pnData;

	pDoc->m_nInputType = nOldInputType;
	pDoc->m_nDumpID = nOldDumpID;
}

BOOL CSpotView::SpotFrameData(POINT* pPt, SHORT nDumpID)
{
	BOOL		bLoop = TRUE;
	SHORT		nOldLoc, nPt;
	CMyHand* pHand = theMIL->m_myHand;
	CStroke* pStroke = pHand->m_pStroke;

	if (!LoadHandLocation(pPt, &nPt))
		return FALSE;

	pHand->m_bFirst = TRUE;
	theMIL->m_theView = this;
	theMIL->StartFrameRecognize(TRUE);

	for (int i = 0; bLoop && i < nPt; i++) {
		nOldLoc = pStroke->m_Norm.nPt;

		if (pPt[i].x < 0 || pPt[i].y < 0)
			pHand->m_nCurHand = -1;
		else
			pHand->m_nCurHand = 1;

		if (pHand->m_nCurHand > 0)
			pStroke->AddHandPosition(pPt[i], i);
		if (!theMIL->ConsiderSpotting(nOldLoc, pPt[i], NO_WAIT))
			bLoop = FALSE;

		if (bLoop)
			bLoop = ProcessOtherMessage();
	}

	theMIL->EndFrameRecognize(NO_WAIT);

	return bLoop;
}


#define RECOG_CORRECT		1
#define ERR_INSERTION		2
#define ERR_DELETION		3
#define ERR_SUBSTITUTION	4

static SHORT nCorrect[MODEL_THRESHOLD], nInsert[MODEL_THRESHOLD],
nDelete[MODEL_THRESHOLD], nSubstitute[MODEL_THRESHOLD],
nNewModel[MODEL_THRESHOLD];

void CSpotView::CompareRecogOut(FILE* fp, SHORT nDumpID,
	SHORT nLabel, MYLABEL* pLabel,
	SHORT nRecogOut, RECOUT* pRecogOut)
{
	int		i, j;
	SHORT	nCor[MODEL_THRESHOLD], nDel[MODEL_THRESHOLD];
	SHORT	nIns[MODEL_THRESHOLD], nSub[MODEL_THRESHOLD], nNew[MODEL_THRESHOLD];
	BYTE* pLFlag = MallocBYTE(nLabel);
	BYTE* pRFlag = MallocBYTE(nRecogOut);

	// Find correct recognition
	memset(nCor, 0, sizeof(SHORT) * MODEL_THRESHOLD);
	for (i = 0; i < nLabel; i++) {
		for (j = 0; j < nRecogOut; j++) {
			if (pLabel[i].nModel == pRecogOut[j].nModel &&
				pLabel[i].nStart < pRecogOut[j].nFirstEndT &&
				pLabel[i].nLast >= pRecogOut[j].nFirstEndT) {
				pLFlag[i] = RECOG_CORRECT;
				pRFlag[j] = RECOG_CORRECT;
				nCor[pLabel[i].nModel]++;
				break;
			}
		}
	}

	// Find deletion error
	memset(nDel, 0, sizeof(SHORT) * MODEL_THRESHOLD);
	for (i = 0; i < nLabel; i++) {
		if (!pLFlag[i]) {
			if (theApp.m_Flags.bCheckSubstitution) {
				for (j = 0; j < nRecogOut; j++) {
					if (pLabel[i].nStart < pRecogOut[j].nFirstEndT &&
						pLabel[i].nLast >= pRecogOut[j].nFirstEndT)
						break;
				}
				if (j >= nRecogOut) {
					pLFlag[i] = ERR_DELETION;
					nDel[pLabel[i].nModel]++;
				}
			}
			else {
				pLFlag[i] = ERR_DELETION;
				nDel[pLabel[i].nModel]++;
			}
		}
	}

	// Find insertion/SUBSTITUTION error
	memset(nIns, 0, sizeof(SHORT) * MODEL_THRESHOLD);
	memset(nSub, 0, sizeof(SHORT) * MODEL_THRESHOLD);
	memset(nNew, 0, sizeof(SHORT) * MODEL_THRESHOLD);
	for (i = 0; i < nRecogOut; i++) {
		if (!pRFlag[i]) {
			if (theApp.m_Flags.bCheckSubstitution) {
				for (j = 0; j < nLabel; j++) {
					if (pLabel[j].nStart < pRecogOut[i].nFirstEndT &&
						pLabel[j].nLast >= pRecogOut[i].nFirstEndT)
						break;
				}
				if (j >= nLabel || pLFlag[j]) {
					pRFlag[i] = ERR_INSERTION;
					nIns[pRecogOut[i].nModel]++;
				}
				else {
					pRFlag[i] = ERR_SUBSTITUTION + j;
					pLFlag[j] = ERR_SUBSTITUTION + i;
					nSub[pLabel[j].nModel]++;
					nNew[pRecogOut[i].nModel]++;
				}
			}
			else {
				pRFlag[i] = ERR_INSERTION;
				nIns[pRecogOut[i].nModel]++;
			}
		}
	}

	if (theApp.m_Flags.bCheckSubstitution) {
		for (i = 0; i < nRecogOut; i++) {
			if (pRFlag[i] == ERR_INSERTION) {
				for (j = 0; j < nLabel; j++) {
					if (pLFlag[j] == ERR_DELETION) {
						if (pLabel[j].nLast > pRecogOut[i].nStartT + 3 &&
							pLabel[j].nLast <= pRecogOut[i].nFirstEndT) {
							pRFlag[i] = ERR_SUBSTITUTION + j;
							pLFlag[j] = ERR_SUBSTITUTION + i;
							nDel[pLabel[j].nModel]--;
							nIns[pRecogOut[i].nModel]--;
							nSub[pLabel[j].nModel]++;
							nNew[pRecogOut[i].nModel]++;
							break;
						}
					}
				}
			}
		}
	}

	for (i = 0; i < MODEL_THRESHOLD; i++) {
		nCorrect[i] += nCor[i];
		nInsert[i] += nIns[i];
		nDelete[i] += nDel[i];
		nSubstitute[i] += nSub[i];
		nNewModel[i] += nNew[i];
	}

	fprintf(fp, "%3d|", nDumpID);
	for (i = 0; i < MODEL_THRESHOLD; i++) {
		fprintf(fp, "%3d%3d%3d%3d%3d |",
			nCor[i], nIns[i], nDel[i], nSub[i], nNew[i]);
	}
	fprintf(fp, "\n");

	for (i = 0; i < nRecogOut; i++) {
		if (pRFlag[i] == ERR_INSERTION) {
			fprintf(fp, "***** %s: %d %d %d (Insert)\n",
				GetModelName(pRecogOut[i].nModel), pRecogOut[i].nStartT,
				pRecogOut[i].nFirstEndT, pRecogOut[i].nEndT);
		}
	}
	for (i = 0; i < nLabel; i++) {
		if (pLFlag[i] == ERR_DELETION) {
			fprintf(fp, "***** %s: %d %d (Delete)\n",
				GetModelName(pLabel[i].nModel),
				pLabel[i].nStart, pLabel[i].nLast);
		}
	}
	for (i = 0; i < nRecogOut; i++) {
		if (pRFlag[i] >= ERR_SUBSTITUTION) {
			j = pRFlag[i] - ERR_SUBSTITUTION;
			fprintf(fp, "***** %s: %d %d  ==> %s: %d %d %d\n",
				GetModelName(pLabel[j].nModel),
				pLabel[j].nStart, pLabel[j].nLast,
				GetModelName(pRecogOut[i].nModel), pRecogOut[i].nStartT,
				pRecogOut[i].nFirstEndT, pRecogOut[i].nEndT);
		}
	}

	Mfree(pLFlag);
	Mfree(pRFlag);
}

void SaveTotalRecogResult(FILE* fp, REAL rThreshProb, BOOL bUseTab)
{
	SHORT nTotal;
	SHORT nTotCor = 0, nTotIns = 0, nTotDel = 0, nTotSub = 0, nTotNew = 0;

	if (!bUseTab) {
		fprintf(fp, "\n\n                         Summary                         \n");
		fprintf(fp, "=======+=====================+=====+========+==========+\n");
		fprintf(fp, " Model | COR INS DEL SUB NEW | TOT | Detect | Accuracy |\n");
		fprintf(fp, "=======+=====================+=====+========+==========+\n");
	}

	for (int i = 0; i < MODEL_THRESHOLD; i++) {
		nTotal = nCorrect[i] + nDelete[i] + nSubstitute[i];
		if (bUseTab) {
			fprintf(fp, "%e\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%f\t%f\n",
				rThreshProb, GetModelName(i),
				nCorrect[i], nInsert[i], nDelete[i], nSubstitute[i],
				nNewModel[i], nTotal,
				(double)nCorrect[i] / (double)nTotal * 100.0,
				(double)nCorrect[i] / (double)(nTotal + nInsert[i]) * 100.0);
		}
		else {
			fprintf(fp, " %5s | %3d %3d %3d %3d %3d | %3d | %6.2f | %8.2f |\n", GetModelName(i),
				nCorrect[i], nInsert[i], nDelete[i], nSubstitute[i],
				nNewModel[i], nTotal,
				(double)nCorrect[i] / (double)nTotal * 100.0,
				(double)nCorrect[i] / (double)(nTotal + nInsert[i]) * 100.0);
		}
		nTotCor += nCorrect[i];
		nTotIns += nInsert[i];
		nTotDel += nDelete[i];
		nTotSub += nSubstitute[i];
		nTotNew += nNewModel[i];
	}

	if (!bUseTab)
		fprintf(fp, "=======+=====================+=====+========+==========+\n");

	nTotal = nTotCor + nTotDel + nTotSub;
	if (bUseTab) {
		fprintf(fp, "%e\tTotal\t%d\t%d\t%d\t%d\t%d\t%d\t%f\t%f\n\n",
			rThreshProb, nTotCor, nTotIns, nTotDel, nTotSub, nTotNew, nTotal,
			(double)nTotCor / (double)nTotal * 100.0,
			(double)nTotCor / (double)(nTotal + nTotIns) * 100.0);
	}
	else {
		fprintf(fp, " Total | %3d %3d %3d %3d %3d | %3d | %6.2f | %8.2f |\n",
			nTotCor, nTotIns, nTotDel, nTotSub, nTotNew, nTotal,
			(double)nTotCor / (double)nTotal * 100.0,
			(double)nTotCor / (double)(nTotal + nTotIns) * 100.0);
	}
	if (!bUseTab)
		fprintf(fp, "=======+=====================+=====+========+==========+\n");
}

BOOL CSpotView::GenerateTestResult(char* pszFile, REAL rThreshProb)
{
	int			i;
	FILE* fp;
	MYLABEL* pLabel;
	RECOUT* pRecogOut;
	SHORT		nLabel, nRecogOut;
	CSpotDoc* pDoc = (CSpotDoc*)GetDocument();
	CGestureDoc* pGestDoc = (CGestureDoc*)theApp.m_pGestDoc;

	memset(nCorrect, 0, sizeof(SHORT) * MODEL_THRESHOLD);
	memset(nInsert, 0, sizeof(SHORT) * MODEL_THRESHOLD);
	memset(nDelete, 0, sizeof(SHORT) * MODEL_THRESHOLD);
	memset(nSubstitute, 0, sizeof(SHORT) * MODEL_THRESHOLD);
	memset(nNewModel, 0, sizeof(SHORT) * MODEL_THRESHOLD);

	pDoc->m_nInputType = MODEL_TEST;

	pDoc->m_nDumpID = 0;

	fp = fopen(pszFile, "w");
	if (!fp) {
		MessageBeep(MB_ICONHAND);
		SetStatusMessage("Invalid result file: %s", pszFile);
		return FALSE;
	}

	fprintf(fp, "===+");
	for (i = 0; i < MODEL_THRESHOLD; i++)
		fprintf(fp, "================+");
	fprintf(fp, "\n");

	fprintf(fp, "   |");
	for (i = 0; i < MODEL_THRESHOLD; i++)
		fprintf(fp, "      %5s     |", GetModelName(i));
	fprintf(fp, "\n");

	fprintf(fp, "   |");
	for (i = 0; i < MODEL_THRESHOLD; i++)
		fprintf(fp, " CO IN DE SU NE |");
	fprintf(fp, "\n");

	fprintf(fp, "===+");
	for (i = 0; i < MODEL_THRESHOLD; i++)
		fprintf(fp, "================+");
	fprintf(fp, "\n");

	nLabel = 0;
	pLabel = new MYLABEL[MAX_MYLABEL];
	nRecogOut = 0;
	pRecogOut = new RECOUT[MAX_GESTURE];

	// GetDumpFileID must executed after file open of result file
	SHORT		nFiles = GetDumpFileID(MODEL_TEST);
	for (i = 0; i < nFiles; i++) {
		pDoc->m_nDumpID = i;
		if (!pDoc->LoadLabellingData(&nLabel, pLabel) ||
			!pGestDoc->LoadRecogOutData(&nRecogOut, pRecogOut)) {
			break;
		}
		CompareRecogOut(fp, i, nLabel, pLabel, nRecogOut, pRecogOut);
	}

	delete[] pLabel;
	delete[] pRecogOut;

	fprintf(fp, "===+");
	for (i = 0; i < MODEL_THRESHOLD; i++)
		fprintf(fp, "================+");
	fprintf(fp, "\n");

	fprintf(fp, "   |");
	for (i = 0; i < MODEL_THRESHOLD; i++) {
		fprintf(fp, "%3d%3d%3d%3d%3d |",
			nCorrect[i], nInsert[i], nDelete[i], nSubstitute[i], nNewModel[i]);
	}
	fprintf(fp, "\n");

	fprintf(fp, "===+");
	for (i = 0; i < MODEL_THRESHOLD; i++)
		fprintf(fp, "================+");
	fprintf(fp, "\n");

	SaveTotalRecogResult(fp, rThreshProb, FALSE);

	fclose(fp);

	return TRUE;
}

BOOL CSpotView::RecognizeTestData(REAL rThreshProb)
{
	// TODO: Add your command handler code here

	CSpotDoc* pDoc = (CSpotDoc*)GetDocument();
	POINT* pPt;
	char* pPathName;
	char		szTmp[30];
	BOOL		bLoop = TRUE;
	CGestureDoc* pGestDoc = (CGestureDoc*)theApp.m_pGestDoc;

	pGestDoc->GenerateThresholdModel(rThreshProb);
	pGestDoc->GenerateUnitedModel(rThreshProb);

	theApp.m_Flags.bLabelling = FALSE;
	pDoc->m_nInputType = MODEL_TEST;

	pPt = new POINT[MAX_POINTS];

	SHORT		nFiles = GetDumpFileID(MODEL_TEST);
	for (int i = 0; bLoop && i < nFiles; i++) {
		//	for(int i=47; bLoop && i<48; i++) {
		CDC* pDC = GetDC();

		sprintf(szTmp, "Prob: %e", rThreshProb);
		pDC->TextOut(10, 10, szTmp, strlen(szTmp));
		ReleaseDC(pDC);

		pDoc->m_nDumpID = i;
		pPathName = MakeMyDumpName(MODEL_TEST, i);
		pDoc->SetPathName(pPathName);

		pPathName = MakeMyResultName(NAME_RECOGOUT);
		remove(pPathName);

		if (!SpotFrameData(pPt, i))
			bLoop = FALSE;
	}

	delete[] pPt;

	SetStatusMessage("Recognizing test data done!!! (e=%e)", rThreshProb);

	return bLoop;
}


#define MAX_TEST_PROB		13

SHORT pnThreshProb[MAX_TEST_PROB] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 30 };

#define PROB_POSITIVE	0
#define PROB_NEGATIVE	1
#define PROB_NORMAL		2

BOOL CSpotView::GenResultForProb(SHORT nProb, SHORT nKind)
{
	char	szTmp[30];
	REAL	rProb = 1.0;
	char* pszFile;
	FILE* fp;

	if (nKind == PROB_NORMAL) {
		rProb = nProb / 10.0;
	}
	else {
		for (int j = 0; j < pnThreshProb[nProb]; j++)
			rProb /= 10.0;
		if (nKind == PROB_POSITIVE)
			rProb = 1.0 - rProb;
	}

	CDC* pDC = GetDC();

	sprintf(szTmp, "Prob: %e", rProb);
	pDC->TextOut(10, 10, szTmp, strlen(szTmp));
	ReleaseDC(pDC);

	if (!RecognizeTestData(rProb))
		return FALSE;

	switch (nKind) {
	case PROB_POSITIVE:
		sprintf(szTmp, "Prob+%d", pnThreshProb[nProb]);
		break;
	case PROB_NEGATIVE:
		sprintf(szTmp, "Prob-%d", pnThreshProb[nProb]);
		break;
	default:
		sprintf(szTmp, "Prob0%d", nProb);
		break;
	}

	pszFile = MakeMyFileName("Cont\\Out\\", szTmp, "out");
	if (GenerateTestResult(pszFile, rProb)) {
		pszFile = MakeMyResultName(NAME_RESULT);
		fp = fopen(pszFile, "a");
		SaveTotalRecogResult(fp, rProb, TRUE);
		fclose(fp);
	}

	return TRUE;
}

void CSpotView::OnGenTestResult()
{
	// TODO: Add your command handler code here
	int		i;
	char* pszFile;
	FILE* fp;
	CSpotDoc* pDoc = (CSpotDoc*)GetDocument();

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	if (!theApp.m_Flags.bRecognize)
		theApp.SetRecogMode();

	pDoc->m_nInputType = MODEL_TEST;
	pDoc->m_nDumpID = 0;

	pszFile = MakeMyResultName(NAME_RESULT);
	fp = fopen(pszFile, "w");
	if (!fp) {
		MessageBeep(MB_ICONHAND);
		SetStatusMessage("Can not open result file: %s", pszFile);
		return;
	}
	fclose(fp);

	// 0.9999999 ~ 0.9
	for (i = 6; i >= 0; i--) {
		if (!GenResultForProb(i, PROB_POSITIVE))
			break;
	}

	// 0.8 ~ 0.2
	for (i = 8; i > 1; i--) {
		if (!GenResultForProb(i, PROB_NORMAL))
			break;
	}

	// 1.0e-1 ~ 1.0e-30
	for (i = 0; i < MAX_TEST_PROB; i++) {
		if (!GenResultForProb(i, PROB_NEGATIVE))
			break;
	}
}

void CSpotView::OnRecogTestData()
{
	// TODO: Add your command handler code here

	if (theMIL->m_bGrabStart)
		theMIL->m_theView->SendMessage(WM_COMMAND, IDM_FINISH_GRAB, 0);

	if (!theApp.m_Flags.bRecognize)
		theApp.SetRecogMode();

	if (!RecognizeTestData(THRESHOLD_PROB))
		return;

	char* pszFile = MakeMyResultName(NAME_RESULT);
	GenerateTestResult(pszFile, THRESHOLD_PROB);
}

void CSpotView::OnUpdateRecogTestData(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here

}

void CSpotView::OnGenCurFeature()
{
	// TODO: Add your command handler code here
	CSpotDoc* pDoc = (CSpotDoc*)GetDocument();

	GenerateFeature(pDoc->m_nInputType, pDoc->m_nDumpID);
	SetStatusMessage("Feature generation of current motion is done!!!");
}
