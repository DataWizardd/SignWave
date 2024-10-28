// GestureView.cpp : implementation file
//

// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"

#include "utils.h"
#include "GestureDoc.h"
#include "GestureView.h"
#include "CFlist.h"
#include "Cmgvq.h"
#include "Cstroke.h"
#include "Cdhmm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGestureView

IMPLEMENT_DYNCREATE(CGestureView, CView)


BEGIN_MESSAGE_MAP(CGestureView, CView)
	//{{AFX_MSG_MAP(CGestureView)
	ON_COMMAND(IDM_START_CAPTURE, OnStartCapture)
	ON_UPDATE_COMMAND_UI(IDM_START_CAPTURE, OnUpdateStartCapture)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_CLEAR_DISPLAY, OnClearDisplay)
	ON_COMMAND(IDM_EDIT_STROKE, OnEditStroke)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_STROKE, OnUpdateEditStroke)
	ON_COMMAND(IDM_EDIT_NEXT_STROKE, OnEditNextStroke)
	ON_COMMAND(IDM_EDIT_SAVE_STROKE, OnEditSaveStroke)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDM_LEARN_VQ, OnLearnVq)
	ON_COMMAND(IDM_VECTOR_QUANTIZE, OnVectorQuantize)
	ON_COMMAND(IDM_EDIT_PREV_STROKE, OnEditPrevStroke)
	ON_COMMAND(IDM_MAKE_NORMAL_VQ, OnMakeNormalVq)
	ON_UPDATE_COMMAND_UI(IDM_VECTOR_QUANTIZE, OnUpdateVectorQuantize)
	ON_COMMAND(IDM_ONLINE_TEST, OnOnlineTest)
	ON_UPDATE_COMMAND_UI(IDM_ONLINE_TEST, OnUpdateOnlineTest)
	ON_COMMAND(IDM_RESAVE_ALL, OnResaveAll)
	ON_COMMAND(IDM_NEXT10_STROKE, OnNext10Stroke)
	ON_COMMAND(IDM_PREV10_STROKE, OnPrev10Stroke)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_NEXT_STROKE, OnUpdateEditNextStroke)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_PREV_STROKE, OnUpdateEditPrevStroke)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_SAVE_STROKE, OnUpdateEditSaveStroke)
	ON_UPDATE_COMMAND_UI(IDM_RESAVE_ALL, OnUpdateResaveAll)
	ON_UPDATE_COMMAND_UI(IDM_PREV10_STROKE, OnUpdatePrev10Stroke)
	ON_UPDATE_COMMAND_UI(IDM_NEXT10_STROKE, OnUpdateNext10Stroke)
	ON_UPDATE_COMMAND_UI(IDM_MAKE_NORMAL_VQ, OnUpdateMakeNormalVq)
	ON_UPDATE_COMMAND_UI(IDM_LEARN_VQ, OnUpdateLearnVq)
	ON_COMMAND(IDM_START_RECOGNIZE, OnStartRecognize)
	ON_UPDATE_COMMAND_UI(IDM_START_RECOGNIZE, OnUpdateStartRecognize)
	ON_COMMAND(IDM_EDIT_CHANGE_STROKE, OnEditChangeStroke)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_CHANGE_STROKE, OnUpdateEditChangeStroke)
	ON_COMMAND(IDM_IMMEDIATE_RECOG, OnImmediateRecog)
	ON_UPDATE_COMMAND_UI(IDM_IMMEDIATE_RECOG, OnUpdateImmediateRecog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGestureView construction/destruction

CGestureView::CGestureView()
{
	// TODO: add construction code here
	m_Flags.bStartCapture = FALSE;
	m_Flags.bLButtonDown = FALSE;
	m_Flags.bEditStroke = FALSE;
	m_Flags.bMovePoint = FALSE;
	m_Flags.bMGVQ = FALSE;
	m_Flags.bVectorQuantize = FALSE;
	m_Flags.bBlockInput = FALSE;
	m_Flags.bOnlineTest = FALSE;
	m_Flags.bStartRecognize = FALSE;
	m_Flags.bChangeDialog = FALSE;
	m_Flags.bImmediateRecog = FALSE;

	m_pStroke = new CStroke;
	m_nVQCount = 0;

	theApp.m_pGestView = this;
//	ClearDisplay( this );
}

CGestureView::~CGestureView()
{
	delete m_pStroke;
	m_pStroke = NULL;
}

REAL* CGestureView::CalcVQProbability()
{
	CGestureDoc* pDoc = GetDocument();

	if (pDoc->m_pHMM == NULL || !pDoc->m_Flags.bLoadThresholdModel)
		return NULL;

	return pDoc->m_pHMM[MODEL_THRESHOLD].CalcVQProbability();
}
/////////////////////////////////////////////////////////////////////////////
// CGestureView drawing

void CGestureView::OnDraw(CDC* pDC)
{
	CRect rc;
	CGestureDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	GetClientRect( &rc );

	// TODO: add draw code for native data here
	if (m_Flags.bEditStroke) {
		m_pStroke->UpdateNormalizedStroke();
		m_pStroke->DrawStroke( pDC, &rc, 
				m_Flags.bEditStroke, !pDoc->m_Flags.bShowRecognition );
		RecognizeInput( m_pStroke->m_nCurModel, TRUE );
	} else if (m_Flags.bVectorQuantize && pDoc->m_pMGVQ) {
		POINT ptCenter;

		ptCenter.x = rc.right / 2;
		ptCenter.y = rc.bottom / 2;
		
		REAL* pProb = CalcVQProbability();
		(pDoc->m_pMGVQ)->DrawVQResult( pDC,	ptCenter, NULL, 0, pProb );
		if (pProb)
			delete pProb;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGestureView diagnostics

#ifdef _DEBUG
void CGestureView::AssertValid() const
{
	CView::AssertValid();
}

void CGestureView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGestureDoc* CGestureView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGestureDoc)));
	return (CGestureDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGestureView message handlers

void CGestureView::RecognizeInput( SHORT nCurModel, BOOL bPaint )
{
	CFVec*	pFVec = NULL;
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();

	if (m_Flags.bStartRecognize && !m_Flags.bChangeDialog )
		pFVec = m_pStroke->StrokeToVector( TRUE );
	else if ( m_Flags.bOnlineTest ) {
		if ( m_Flags.bEditStroke ) {
			pFVec = m_pStroke->StrokeToVector( TRUE );
		} else {
			pFVec = m_pStroke->EndOnlineStroke( this, 
						!pDoc->m_Flags.bShowRecognition, bPaint );
		}
	} else if ( m_Flags.bImmediateRecog ) {
		if ( pDoc->m_pUnited ) {
			if ( !pDoc->ImmediateProcessing(m_pStroke) ) {
				PrintProgressString("Done!!!");
				return;
			}
		}

		pFVec = m_pStroke->EndOnlineStroke( this, 
						!pDoc->m_Flags.bShowRecognition, bPaint );
	}

	if (pFVec) {
		pDoc->OnlineTestGesture( pFVec, nCurModel, FALSE,
				m_pStroke->m_Norm.pPt, m_pStroke->m_Norm.nPt );
		delete pFVec;
	}
}

void CGestureView::OnStartCapture() 
{
	// TODO: Add your command handler code here
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();
	
	m_Flags.bOnlineTest = FALSE;
	m_Flags.bImmediateRecog = FALSE;
	m_Flags.bVectorQuantize = FALSE;

	m_Flags.bStartCapture = !m_Flags.bStartCapture;

	if ( m_Flags.bStartCapture ) {
		SHORT tmp;

		m_Flags.bEditStroke = FALSE;
		m_pStroke->ClearStroke();

		tmp = m_pStroke->SetPrefix( pDoc->m_pModel, pDoc->m_nModel );
		SetStatusMessage( "Stroke %d", tmp );
	}
	
	ClearDisplay( this );
}

void CGestureView::OnUpdateStartCapture(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();
	
	pCmdUI->Enable( pDoc->m_pModel != NULL );
	pCmdUI->SetCheck(m_Flags.bStartCapture);
}

void CGestureView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();

	if (nChar == VK_ESCAPE && m_Flags.bLButtonDown) {
		if (m_Flags.bStartCapture) {
			m_pStroke->EndStroke( this, !pDoc->m_Flags.bShowRecognition );
			RecognizeInput( m_pStroke->m_nCurModel, FALSE );
		} else if ( (!m_Flags.bEditStroke && m_Flags.bOnlineTest) || 
					 m_Flags.bImmediateRecog) {
			RecognizeInput( -1, FALSE );
		}
		if (m_Flags.bMovePoint)
			ClearDisplay( this );

		m_Flags.bStartCapture = FALSE;
		m_Flags.bMovePoint = FALSE;
	} else if ( !m_Flags.bBlockInput && nChar == VK_SPACE && m_Flags.bVectorQuantize ) {
		CFVec vector;
		SHORT nCode;
		CGestureDoc* pDoc = (CGestureDoc*)GetDocument();
			
		vector.New( 1, TEST_DIMENSION );
		m_pStroke->GetNewFeature( &vector );
		nCode = (pDoc->m_pMGVQ)->Lookup( vector, 0 );
		DrawVQResult( &vector, nCode );
		m_nVQCount++;
		if (m_nVQCount > 25) {
			ClearDisplay();
			m_Flags.bBlockInput = TRUE;
			DrawVQResult( NULL, 0 );
			m_Flags.bBlockInput = FALSE;
			m_nVQCount = 0;
		}
		SetStatusMessage( "Press <SPACE> key to continue" ) ;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGestureView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if ( m_Flags.bStartCapture || 
		 (!m_Flags.bEditStroke && m_Flags.bOnlineTest) ) {
		m_Flags.bLButtonDown = TRUE;
		SetCapture();	
		m_pStroke->StartStroke( point );
	} else if ( m_Flags.bImmediateRecog ) {
		CGestureDoc* pDoc = (CGestureDoc*)GetDocument();

		m_Flags.bLButtonDown = TRUE;
		SetCapture();	
		m_pStroke->StartImmediateRecog( point );

#ifdef OLD_IMMEDIATE
		if ( pDoc->m_pUnited ) {
			pDoc->m_pUnited->InitTraceViterbiScore( pDoc->m_nModel );
			pDoc->m_Flags.bFirstTraceViterbi = FALSE;
		}
#endif
	} else if ( m_Flags.bEditStroke && m_pStroke->CheckEditMark(point) ) {
		m_Flags.bMovePoint = TRUE;
		m_Flags.bLButtonDown = TRUE;
		SetCapture();

		if (GetKeyState(VK_CONTROL)	& 0x80)
			m_pStroke->AppendOnePoint( point );

		CDC* pDC = GetDC();
		m_pStroke->StartMovePoint( pDC );
		ReleaseDC( pDC );
	}

	CView::OnLButtonDown(nFlags, point);
}

void CGestureView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();

	if (m_Flags.bLButtonDown) {
		m_Flags.bLButtonDown = FALSE;
		if (m_Flags.bStartCapture) {
			m_pStroke->EndStroke( this, !pDoc->m_Flags.bShowRecognition );
			RecognizeInput( m_pStroke->m_nCurModel, FALSE );
		} else if ( (!m_Flags.bEditStroke && m_Flags.bOnlineTest) || 
					 m_Flags.bImmediateRecog) {
			RecognizeInput( -1, FALSE );
		} else if (m_Flags.bEditStroke && m_Flags.bMovePoint)
			ClearDisplay( this );
	}

	m_Flags.bMovePoint = FALSE;
	ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}

void CGestureView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_Flags.bLButtonDown) {
		if ( m_Flags.bStartCapture || 
			 (!m_Flags.bEditStroke && m_Flags.bOnlineTest) ) {
			CDC* pDC = GetDC();
			m_pStroke->AddStroke( point, pDC );
			ReleaseDC( pDC );
		} else if (m_Flags.bImmediateRecog) {
			CGestureDoc* pDoc = (CGestureDoc*)GetDocument();
			CFVec*	pFVec = m_pStroke->AddImmediateRecog( point, this );
			if (pFVec) {
				pDoc->OnlineTestGesture( pFVec, -1,	TRUE,
					m_pStroke->m_Norm.pPt, m_pStroke->m_Norm.nPt );
				delete pFVec;
			}
		} else if (m_Flags.bEditStroke && m_Flags.bMovePoint) {
			CDC* pDC = GetDC();
			m_pStroke->UpdateMovePoint( pDC, point );
			ReleaseDC( pDC );
		}
	}
	
	CView::OnMouseMove(nFlags, point);
}

void CGestureView::OnClearDisplay() 
{
	// TODO: Add your command handler code here
	ClearDisplay( this );	
}

void CGestureView::OnEditStroke() 
{
	// TODO: Add your command handler code here

	m_Flags.bVectorQuantize = FALSE;
	m_Flags.bOnlineTest = FALSE;
	m_Flags.bImmediateRecog = FALSE;

	m_Flags.bEditStroke = !m_Flags.bEditStroke;
	if (m_Flags.bEditStroke) {
		CGestureDoc* pDoc = (CGestureDoc*)GetDocument();

		m_Flags.bStartCapture = FALSE;
		if ( m_pStroke->StartEditStroke( this, pDoc->m_pModel, pDoc->m_nModel ) ) {
			ClearDisplay( this );
		} else
			m_Flags.bEditStroke = FALSE;
	}
}

void CGestureView::OnUpdateEditStroke(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here	
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();
	
	pCmdUI->Enable( pDoc->m_pModel != NULL );
	pCmdUI->SetCheck(m_Flags.bEditStroke);
}

void CGestureView::OnEditNextStroke() 
{
	// TODO: Add your command handler code here
	m_Flags.bVectorQuantize = FALSE;
	if (!m_Flags.bEditStroke && !m_Flags.bImmediateRecog)
		return;

	if (m_Flags.bImmediateRecog) {
		ClearDisplay( this );

		m_pStroke->NextOnlineStroke( 1 );
		m_pStroke->DrawOnlineStroke( this );

		if ( !WaitMoment( LONG_WAIT, TRUE ) )
			return;

		RecognizeInput( -1, FALSE );
	} else {
		CRect rc;
		CGestureDoc* pDoc = (CGestureDoc*)GetDocument();

		GetClientRect( &rc );
		m_pStroke->EditNextStroke( &rc, 1, pDoc->m_pModel, pDoc->m_nModel );

		ClearDisplay( this );	
	}
}

void CGestureView::OnEditSaveStroke() 
{
	// TODO: Add your command handler code here
	m_Flags.bVectorQuantize = FALSE;

	if ( (!m_Flags.bEditStroke && m_Flags.bOnlineTest) || 
		 m_Flags.bImmediateRecog) {
		m_pStroke->SaveOnlineStroke(m_Flags.bOnlineTest);
		return;
	}

	if (!m_Flags.bEditStroke)
		return;
	
	m_pStroke->SaveEditStroke();
}

void CGestureView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_Flags.bStartCapture) 
		ClearDisplay( this );
	else if ( m_Flags.bEditStroke && m_pStroke->CheckEditMark(point) ) {
		m_pStroke->DeleteEditPoint( );
		ClearDisplay( this );	
	}
	
	CView::OnRButtonDown(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// For vector quantization

void CGestureView::DrawVQResult( CFVec* pFVec, SHORT nCode )
{
	CRect rc;
	CDC*  pDC = GetDC();
	POINT ptCenter;
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();
	REAL* pProb = CalcVQProbability();

	if (pDoc->m_Flags.bMakeMetafile) {
		CMetaFileDC* pMetaDC;
		HENHMETAFILE hMF;

		rc.left = 0;
		rc.top  = 0;
		rc.right = WIDTH*2 + 10;
		rc.bottom = HEIGHT*2 + 10;

		ptCenter.x = rc.right / 2;
		ptCenter.y = rc.bottom / 2;

		pMetaDC = InitMetaFileDC( this, &rc );
		(pDoc->m_pMGVQ)->DrawVQResult( pMetaDC,	ptCenter, pFVec, nCode, pProb );

		hMF = pMetaDC->CloseEnhanced();
		delete	pMetaDC;

		if ( hMF ) {
			char*	pszFile = MakeMyMetaName( "Meta\\", "VQ_Out", pDoc->m_nMetafileCount );

			if ( ExportMetafile(pDC, hMF, pszFile, &rc) )
				pDoc->m_nMetafileCount++;
			DeleteEnhMetaFile( hMF );
		}
		PrintProgressString("MetaFile recording done!!" );
	}

	GetClientRect( &rc );
	ptCenter.x = rc.right / 2;
	ptCenter.y = rc.bottom / 2;

	(pDoc->m_pMGVQ)->DrawVQResult( pDC,	ptCenter, pFVec, nCode, pProb );
	ReleaseDC( pDC );

	if (pProb)
		delete pProb;
}

void CGestureView::ClearActionFlags()
{
	m_Flags.bStartCapture = FALSE;
	m_Flags.bLButtonDown = FALSE;
	m_Flags.bEditStroke = FALSE;
	m_Flags.bMovePoint = FALSE;
	m_Flags.bOnlineTest = FALSE;
	m_Flags.bImmediateRecog = FALSE;

	ClearDisplay( this );
}

void CGestureView::OnLearnVq() 
{
	// TODO: Add your command handler code here
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();

	m_Flags.bVectorQuantize = FALSE;
	ClearActionFlags();

	pDoc->MakeMGVQ(	this );
	m_Flags.bMGVQ = TRUE;
}

void CGestureView::OnVectorQuantize() 
{
	// TODO: Add your command handler code here
	ClearActionFlags();
	m_Flags.bVectorQuantize = !m_Flags.bVectorQuantize;

	if (m_Flags.bVectorQuantize)
	{
		CGestureDoc* pDoc = (CGestureDoc*)GetDocument();

		if (!m_Flags.bMGVQ) {
			if (pDoc->m_pMGVQ)
				delete pDoc->m_pMGVQ;
			pDoc->m_pMGVQ = new CMGVQ;

			if ( (pDoc->m_pMGVQ)->NewCodebook( TEST_LEVEL, TEST_DIMENSION ) )
			{
				(pDoc->m_pMGVQ)->Read( MakeMyFileName("VQ.out\\", "mgvq") );
				m_Flags.bMGVQ = TRUE;
				m_Flags.bBlockInput = TRUE;
				DrawVQResult( NULL, 0 );
				m_Flags.bBlockInput = FALSE;
			}
		}

		SetStatusMessage( "Press <SPACE> key to continue" ) ;
	}

	m_nVQCount = 0;
}

void CGestureView::OnUpdateVectorQuantize(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();
	
	pCmdUI->Enable( pDoc->m_pModel != NULL );
	pCmdUI->SetCheck(m_Flags.bVectorQuantize);
}

void CGestureView::OnEditPrevStroke() 
{
	// TODO: Add your command handler code here
	m_Flags.bVectorQuantize = FALSE;
	if (!m_Flags.bEditStroke && !m_Flags.bImmediateRecog)
		return;

	if (m_Flags.bImmediateRecog) {
		ClearDisplay( this );

		m_pStroke->PrevOnlineStroke( 1 );
		m_pStroke->DrawOnlineStroke( this );

		if ( !WaitMoment( LONG_WAIT, TRUE ) )
			return;

		RecognizeInput( -1, FALSE );
	} else {
		CRect rc;
		CGestureDoc* pDoc = (CGestureDoc*)GetDocument();

		GetClientRect( &rc );
		m_pStroke->EditPrevStroke( &rc, 1, pDoc->m_pModel, pDoc->m_nModel );

		ClearDisplay( this );	
	}
}

void CGestureView::OnMakeNormalVq() 
{
	// TODO: Add your command handler code here	
	CVQ vq;
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();

	m_Flags.bVectorQuantize = FALSE;
	ClearDisplay( this );

	if ( !pDoc->LoadAllRawData() )
		return;

	if ( !vq.GenCodebook(pDoc->m_pFVec, pDoc->m_nFVec, TEST_LEVEL) ) {
		pDoc->RemoveAllRawData();
		return;
	}

	pDoc->RemoveAllRawData();

	if (vq.Write(MakeMyFileName("VQ.out\\", "vq.bin")) )
		vq.WriteText( MakeMyFileName("VQ.out\\", "vq.txt") );
}

void CGestureView::OnOnlineTest() 
{
	// TODO: Add your command handler code here
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();

	m_Flags.bImmediateRecog = FALSE;
	m_Flags.bOnlineTest = !m_Flags.bOnlineTest;

	if (m_Flags.bOnlineTest)
		ClearDisplay(this);
}

void CGestureView::OnUpdateOnlineTest(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here	
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();
	
	pCmdUI->Enable( pDoc->m_pModel != NULL );
	pCmdUI->SetCheck(m_Flags.bOnlineTest);
}

void CGestureView::OnResaveAll() 
{
	// TODO: Add your command handler code here
	
	if ( !m_Flags.bEditStroke )
		return;

	ClearDisplay( this );	
	m_pStroke->ResaveAllStroke( this );
}

void CGestureView::OnNext10Stroke() 
{
	// TODO: Add your command handler code here
	m_Flags.bVectorQuantize = FALSE;
	if (!m_Flags.bEditStroke)
		return;

	CRect rc;
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();

	GetClientRect( &rc );
	m_pStroke->EditNextStroke( &rc, 10, pDoc->m_pModel, pDoc->m_nModel );

	ClearDisplay( this );	
}

void CGestureView::OnPrev10Stroke() 
{
	// TODO: Add your command handler code here
	m_Flags.bVectorQuantize = FALSE;
	if (!m_Flags.bEditStroke)
		return;

	CRect rc;
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();

	GetClientRect( &rc );
	m_pStroke->EditPrevStroke( &rc, 10, pDoc->m_pModel, pDoc->m_nModel );

	ClearDisplay( this );	
}

void CGestureView::OnUpdateEditNextStroke(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable(m_Flags.bEditStroke || m_Flags.bImmediateRecog);
}

void CGestureView::OnUpdateEditPrevStroke(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable(m_Flags.bEditStroke || m_Flags.bImmediateRecog);
}

void CGestureView::OnUpdateEditSaveStroke(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_Flags.bEditStroke || m_Flags.bOnlineTest ||
					m_Flags.bImmediateRecog );
}

void CGestureView::OnUpdateResaveAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();
	
	pCmdUI->Enable( pDoc->m_pModel != NULL );
	pCmdUI->Enable(m_Flags.bEditStroke);
}

void CGestureView::OnUpdatePrev10Stroke(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable(m_Flags.bEditStroke);
}

void CGestureView::OnUpdateNext10Stroke(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable(m_Flags.bEditStroke);
}

void CGestureView::OnUpdateMakeNormalVq(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();
	
	pCmdUI->Enable( pDoc->m_pModel != NULL );
}

void CGestureView::OnUpdateLearnVq(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();
	
	pCmdUI->Enable( pDoc->m_pModel != NULL );
}

void CGestureView::OnStartRecognize() 
{
	// TODO: Add your command handler code here
	
	m_Flags.bStartRecognize = !m_Flags.bStartRecognize;
	ClearDisplay( this );
}

void CGestureView::OnUpdateStartRecognize(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here	
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();
	
	pCmdUI->Enable( pDoc->m_pModel != NULL );
	pCmdUI->SetCheck( m_Flags.bStartRecognize );
}

void CGestureView::OnEditChangeStroke() 
{
	CRect rc;
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();

	GetClientRect( &rc );

	// TODO: Add your command handler code here
	if ( (!m_Flags.bEditStroke && m_Flags.bOnlineTest) || 
		 m_Flags.bImmediateRecog ) {
		m_Flags.bChangeDialog = TRUE;
		if ( m_pStroke->ChangeOnlineStroke( m_Flags.bOnlineTest ) ) {
			CGestureDoc* pDoc = (CGestureDoc*)GetDocument();
			m_Flags.bChangeDialog = FALSE;

			CDC* pDC = GetDC();
			m_pStroke->DrawStroke( pDC, &rc, FALSE, FALSE );
			ReleaseDC( pDC );

			if ( !WaitMoment( LONG_WAIT, TRUE ) )
				return;

			RecognizeInput( -1, FALSE );
		}
		m_Flags.bChangeDialog = FALSE;

		return;
	}

	if ( !m_Flags.bEditStroke )
		return;

	m_Flags.bChangeDialog = TRUE;
	if ( m_pStroke->ChangeEditStroke( &rc, pDoc->m_pModel, pDoc->m_nModel ) ) {
		m_Flags.bChangeDialog = FALSE;
		ClearDisplay( this );
	}
	m_Flags.bChangeDialog = FALSE;
}

void CGestureView::OnUpdateEditChangeStroke(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_Flags.bEditStroke || m_Flags.bOnlineTest ||
					m_Flags.bImmediateRecog );
}

void CGestureView::SetImmediateRecog()
{
	if ( !m_Flags.bImmediateRecog )
		return;

	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();

	m_pStroke->m_nOnlineStroke = -1;
	if ( !pDoc->m_Flags.bTestUnitedModel ) {
		pDoc->m_Flags.bTestUnitedModel = TRUE;		
		pDoc->SetTestUnited();
		pDoc->ReadTrainedModel();
	}
	pDoc->m_Flags.bShowRecognition = TRUE;
	ClearDisplay( this );
}

void CGestureView::OnImmediateRecog() 
{
	// TODO: Add your command handler code here
	m_Flags.bOnlineTest = FALSE;
	m_Flags.bEditStroke = FALSE;
	m_Flags.bImmediateRecog = !m_Flags.bImmediateRecog;
	SetImmediateRecog();
}

void CGestureView::OnUpdateImmediateRecog(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here	
	CGestureDoc* pDoc = (CGestureDoc*)GetDocument();
	
	pCmdUI->SetCheck( m_Flags.bImmediateRecog );
	pCmdUI->Enable( pDoc->m_pModel != NULL );
}
