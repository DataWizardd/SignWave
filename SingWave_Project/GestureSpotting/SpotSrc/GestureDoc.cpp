// GestureDoc.cpp : implementation file
//

// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"

#include "Cdhmm.h"
#include "utils.h"
#include "CFlist.h"
#include "Cmgvq.h"
#include "CVScore.h"
#include "GestureDoc.h"
#include "GestureView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGestureDoc

IMPLEMENT_DYNCREATE(CGestureDoc, CDocument)

BEGIN_MESSAGE_MAP(CGestureDoc, CDocument)
	//{{AFX_MSG_MAP(CGestureDoc)
	ON_COMMAND(ID_HMM_ASCII, OnHmmAscii)
	ON_UPDATE_COMMAND_UI(ID_HMM_ASCII, OnUpdateHmmAscii)
	ON_COMMAND(ID_HMM_TEST, OnHmmTest)
	ON_COMMAND(ID_HMM_TRAIN, OnHmmTrain)
	ON_COMMAND(IDM_DO_ALL, OnDoAll)
	ON_COMMAND(IDM_MAKE_LIST_FILE, OnMakeListFile)
	ON_UPDATE_COMMAND_UI(IDM_MAKE_LIST_FILE, OnUpdateMakeListFile)
	ON_UPDATE_COMMAND_UI(IDM_DO_ALL, OnUpdateDoAll)
	ON_UPDATE_COMMAND_UI(ID_HMM_TEST, OnUpdateHmmTest)
	ON_UPDATE_COMMAND_UI(ID_HMM_TRAIN, OnUpdateHmmTrain)
	ON_COMMAND(IDM_LOAD_THRESHOLD_HMM, OnLoadThresholdHmm)
	ON_UPDATE_COMMAND_UI(IDM_LOAD_THRESHOLD_HMM, OnUpdateLoadThresholdHmm)
	ON_COMMAND(IDM_MAKE_THRESHOLD_MODEL, OnGenerateThresholdModel)
	ON_UPDATE_COMMAND_UI(IDM_MAKE_THRESHOLD_MODEL, OnUpdateGenerateThresholdModel)
	ON_COMMAND(IDM_TRAIN_THRESHOLD, OnTrainThreshold)
	ON_UPDATE_COMMAND_UI(IDM_TRAIN_THRESHOLD, OnUpdateTrainThreshold)
	ON_COMMAND(IDM_MODEL_FIRST, OnModelFirst)
	ON_UPDATE_COMMAND_UI(IDM_MODEL_FIRST, OnUpdateModelFirst)
	ON_COMMAND(IDM_MODEL_LAST, OnModelLast)
	ON_UPDATE_COMMAND_UI(IDM_MODEL_LAST, OnUpdateModelLast)
	ON_COMMAND(IDM_MODEL_NEXT, OnModelNext)
	ON_UPDATE_COMMAND_UI(IDM_MODEL_NEXT, OnUpdateModelNext)
	ON_COMMAND(IDM_MODEL_PREV, OnModelPrev)
	ON_UPDATE_COMMAND_UI(IDM_MODEL_PREV, OnUpdateModelPrev)
	ON_COMMAND(IDM_MODEL_QUIT, OnModelQuit)
	ON_UPDATE_COMMAND_UI(IDM_MODEL_QUIT, OnUpdateModelQuit)
	ON_COMMAND(IDM_INIT_MODEL, OnInitModel)
	ON_UPDATE_COMMAND_UI(IDM_INIT_MODEL, OnUpdateInitModel)
	ON_COMMAND(IDM_MODEL_THRESHOLD, OnModelThreshold)
	ON_UPDATE_COMMAND_UI(IDM_MODEL_THRESHOLD, OnUpdateModelThreshold)
	ON_COMMAND(IDM_TEST_FIRST, OnTestFirst)
	ON_UPDATE_COMMAND_UI(IDM_TEST_FIRST, OnUpdateTestFirst)
	ON_COMMAND(IDM_TEST_THRESHOLD, OnTestThreshold)
	ON_UPDATE_COMMAND_UI(IDM_TEST_THRESHOLD, OnUpdateTestThreshold)
	ON_COMMAND(IDM_TEST_LAST, OnTestLast)
	ON_UPDATE_COMMAND_UI(IDM_TEST_LAST, OnUpdateTestLast)
	ON_COMMAND(IDM_TEST_NEXT, OnTestNext)
	ON_UPDATE_COMMAND_UI(IDM_TEST_NEXT, OnUpdateTestNext)
	ON_COMMAND(IDM_TEST_PREV, OnTestPrev)
	ON_UPDATE_COMMAND_UI(IDM_TEST_PREV, OnUpdateTestPrev)
	ON_COMMAND(IDM_TEST_QUIT, OnTestQuit)
	ON_UPDATE_COMMAND_UI(IDM_TEST_QUIT, OnUpdateTestQuit)
	ON_COMMAND(IDM_SHOW_RECOGNITION, OnShowRecognition)
	ON_UPDATE_COMMAND_UI(IDM_SHOW_RECOGNITION, OnUpdateShowRecognition)
	ON_COMMAND(IDM_SINGLE_TRANS, OnSingleTrans)
	ON_UPDATE_COMMAND_UI(IDM_SINGLE_TRANS, OnUpdateSingleTrans)
	ON_COMMAND(IDM_TEST_TRAIN_DATA, OnTestTrainData)
	ON_UPDATE_COMMAND_UI(IDM_TEST_TRAIN_DATA, OnUpdateTestTrainData)
	ON_COMMAND(IDM_SHOW_MATCH, OnShowMatch)
	ON_UPDATE_COMMAND_UI(IDM_SHOW_MATCH, OnUpdateShowMatch)
	ON_COMMAND(IDM_UNITE_MODEL, OnUniteModel)
	ON_UPDATE_COMMAND_UI(IDM_UNITE_MODEL, OnUpdateUniteModel)
	ON_COMMAND(IDM_TEST_UNITED, OnTestUnited)
	ON_UPDATE_COMMAND_UI(IDM_TEST_UNITED, OnUpdateTestUnited)
	ON_COMMAND(IDM_MAKE_METAFILE, OnMakeMetafile)
	ON_UPDATE_COMMAND_UI(IDM_MAKE_METAFILE, OnUpdateMakeMetafile)
	ON_COMMAND(IDM_MODEL_ALPHA, OnModelAlpha)
	ON_UPDATE_COMMAND_UI(IDM_MODEL_ALPHA, OnUpdateModelAlpha)
	ON_COMMAND(IDM_MODEL_BYE, OnModelBye)
	ON_UPDATE_COMMAND_UI(IDM_MODEL_BYE, OnUpdateModelBye)
	ON_COMMAND(IDM_MODEL_CIRCLE, OnModelCircle)
	ON_UPDATE_COMMAND_UI(IDM_MODEL_CIRCLE, OnUpdateModelCircle)
	ON_COMMAND(IDM_MODEL_SAW, OnModelSaw)
	ON_UPDATE_COMMAND_UI(IDM_MODEL_SAW, OnUpdateModelSaw)
	ON_COMMAND(IDM_MODEL_TRIANGLE, OnModelTriangle)
	ON_UPDATE_COMMAND_UI(IDM_MODEL_TRIANGLE, OnUpdateModelTriangle)
	ON_COMMAND(IDM_TEST_ALPHA, OnTestAlpha)
	ON_UPDATE_COMMAND_UI(IDM_TEST_ALPHA, OnUpdateTestAlpha)
	ON_COMMAND(IDM_TEST_BYE, OnTestBye)
	ON_UPDATE_COMMAND_UI(IDM_TEST_BYE, OnUpdateTestBye)
	ON_COMMAND(IDM_TEST_CIRCLE, OnTestCircle)
	ON_UPDATE_COMMAND_UI(IDM_TEST_CIRCLE, OnUpdateTestCircle)
	ON_COMMAND(IDM_TEST_SAW, OnTestSaw)
	ON_UPDATE_COMMAND_UI(IDM_TEST_SAW, OnUpdateTestSaw)
	ON_COMMAND(IDM_TEST_TRIANGLE, OnTestTriangle)
	ON_UPDATE_COMMAND_UI(IDM_TEST_TRIANGLE, OnUpdateTestTriangle)
	ON_COMMAND(IDM_REDUCEDTHRESHOLD, OnReducedthreshold)
	ON_UPDATE_COMMAND_UI(IDM_REDUCEDTHRESHOLD, OnUpdateReducedthreshold)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGestureDoc construction/destruction
void CGestureDoc::InitVariables()
{
	m_nSymbol = 8;
	m_nClass = 6;
	m_nModel = 5;
	if (m_pModel)
		delete[] m_pModel;
	m_pModel = NULL;
	m_szTrainFile[0] = 0;
	m_szTestFile[0] = 0;
	m_szModelDir[0] = 0;
	m_szBaseDir[0] = 0;

	if (m_pMGVQ)
		delete m_pMGVQ;
	m_pMGVQ = NULL;
}

CGestureDoc::CGestureDoc()
{
	// TODO: add one-time construction code here
	
	m_pModel = NULL;
	m_pMGVQ = NULL;
	m_pnOutput = NULL;
	m_nFVec = 0;
	m_pFVec = NULL;
	m_nOutput = 0;
	m_nProcessedTime = 0;
	m_Flags.bAscii = FALSE;
	m_Flags.bLoadThresholdModel = TRUE;
	m_Flags.bShowRecognition = FALSE;
	m_Flags.bSingleTransition = FALSE;
	m_Flags.bTestTrainData = FALSE;
	m_Flags.bShowMatchProcess = FALSE;
	m_Flags.bTestUnitedModel = FALSE;
	m_Flags.bMakeMetafile = FALSE;
	m_Flags.bFirstTraceViterbi = TRUE;
	m_Flags.bReducedThreshold = TRUE;
	m_nMetafileCount = 0;
	m_pHMM = NULL;
	m_pUnited = NULL;
	m_pVScore = NULL;
	m_nThresholdModel = 0;

	m_nRecogOut = 0;
	m_pRecogOut = NULL;

	InitVariables();
}

CGestureDoc::~CGestureDoc()
{
	if (m_pModel)
		delete[] m_pModel;

	if (m_pMGVQ)
		delete m_pMGVQ;

	if (m_pHMM)
		delete[] m_pHMM;

	if (m_pUnited)
		delete m_pUnited;
	
	if (m_pFVec)
		delete[] m_pFVec;

	if (m_pRecogOut)
		delete[] m_pRecogOut;

	if (m_pVScore)
		delete m_pVScore;

	if (m_pnOutput)
		delete[] m_pnOutput;
}

BOOL CGestureDoc::OnNewDocument()
{
	// OnNew is not permitted
	return FALSE;

	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGestureDoc serialization

void CGestureDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGestureDoc diagnostics

#ifdef _DEBUG
void CGestureDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGestureDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGestureDoc commands

BOOL CGestureDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	FILE*	fp;

	if (theApp.m_pGestDoc)
		return FALSE;

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	if( !(fp = fopen( lpszPathName, "r" )) ) 
	{
		Warning( "(CGestureDoc::OnOpenDocument) file <%s> not found", lpszPathName );
		return( FALSE );
	}

	if ( !ReadDocument(fp) ) {
		fclose( fp );
		InitVariables();
		return( FALSE );
	}
	fclose( fp );

	theApp.m_pGestDoc = this;

	ClearDisplay( theApp.m_pGestView );
	
	return TRUE;
}

void CGestureDoc::OnHmmAscii() 
{
	// TODO: Add your command handler code here
	m_Flags.bAscii = !m_Flags.bAscii;

	CGestureView* pView = (CGestureView*)theApp.m_pGestView;
	if (pView)
	{
		ClearDisplay( pView );
		pView->UpdateWindow();
		PrepareSpace( 5 );

		PrintProgressString( "Number of states = %d", m_nModel );
		PrintProgressString( "Number of symbols = %d", m_nSymbol );
		PrintProgressString( "Training data file = %s", m_szTrainFile );
		PrintProgressString( "Testing data file = %s", m_szTestFile );
		PrintProgressString( "Model directory = %s", m_szModelDir );
	}
}

void CGestureDoc::OnUpdateHmmAscii(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	pCmdUI->SetCheck(m_Flags.bAscii);
}

void CGestureDoc::OnHmmTest() 
{
	// TODO: Add your command handler code here	
	CGestureView* pView = (CGestureView*)theApp.m_pGestView;

	ClearDisplay( pView );
	TestGesture();
}

void CGestureDoc::OnHmmTrain() 
{
	// TODO: Add your command handler code here
	CGestureView* pView = (CGestureView*)theApp.m_pGestView;

	ClearDisplay( pView );
	TrainGesture( NULL );
}

void CGestureDoc::MakeMGVQ( CGestureView* pView )
{
	if ( !GenerateMGVQ() )
		return;

	CRect rc;
	POINT ptCenter;
	CDC* pDC = pView->GetDC();

	pView->GetClientRect( &rc );
	ptCenter.x = rc.right / 2;
	ptCenter.y = rc.bottom / 2;
	m_pMGVQ->DrawVQResult( pDC,	ptCenter, NULL, 0, NULL );
	pView->ReleaseDC( pDC );
	
	WaitMoment(20000.0, TRUE);
}

void CGestureDoc::OnDoAll() 
{
	// TODO: Add your command handler code here
	CGestureView* pView = (CGestureView*)theApp.m_pGestView;

	ClearDisplay( pView );

	MakeMGVQ( pView );
	if ( !m_pMGVQ )
		return;

	TrainGesture( NULL );
	TestGesture();
}

void CGestureDoc::OnMakeListFile() 
{
	// TODO: Add your command handler code here
	ClearDisplay( theApp.m_pGestView );

	MakeListFile();
}

void CGestureDoc::OnUpdateMakeListFile(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnUpdateDoAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnUpdateHmmTest(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnUpdateHmmTrain(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnLoadThresholdHmm() 
{
	// TODO: Add your command handler code here

	ClearDisplay( theApp.m_pGestView );

	m_Flags.bLoadThresholdModel = !m_Flags.bLoadThresholdModel;

	if ( m_pModel ) {
		if ( m_Flags.bLoadThresholdModel )
			m_nModel++;
		else
			m_nModel--;

		if (m_pHMM)
			delete[] m_pHMM;
		m_pHMM = NULL;
	}
}

void CGestureDoc::OnUpdateLoadThresholdHmm(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck( m_Flags.bLoadThresholdModel );
}

void CGestureDoc::OnTrainThreshold() 
{
	// TODO: Add your command handler code here
	ClearDisplay( theApp.m_pGestView );

	TrainThresholdModel();
}

void CGestureDoc::OnUpdateTrainThreshold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_Flags.bLoadThresholdModel && m_pModel != NULL );
}

void CGestureDoc::OnModelFirst() 
{
	// TODO: Add your command handler code here
	
	TrainGesture( "first" );
}

void CGestureDoc::OnUpdateModelFirst(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnModelLast() 
{
	// TODO: Add your command handler code here
	
	TrainGesture( "last" );
}

void CGestureDoc::OnUpdateModelLast(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnModelNext() 
{
	// TODO: Add your command handler code here
	
	TrainGesture( "next" );
}

void CGestureDoc::OnUpdateModelNext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnModelPrev() 
{
	// TODO: Add your command handler code here
	
	TrainGesture( "prev" );
}

void CGestureDoc::OnUpdateModelPrev(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnModelQuit() 
{
	// TODO: Add your command handler code here
	
	TrainGesture( "quit" );
}

void CGestureDoc::OnUpdateModelQuit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnModelAlpha() 
{
	// TODO: Add your command handler code here
	
	TrainGesture( "alpha" );
}

void CGestureDoc::OnUpdateModelAlpha(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnModelBye() 
{
	// TODO: Add your command handler code here
	
	TrainGesture( "bye" );
}

void CGestureDoc::OnUpdateModelBye(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnModelCircle() 
{
	// TODO: Add your command handler code here
	
	TrainGesture( "cir" );
}

void CGestureDoc::OnUpdateModelCircle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnModelSaw() 
{
	// TODO: Add your command handler code here
	
	TrainGesture( "saw" );
}

void CGestureDoc::OnUpdateModelSaw(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnModelTriangle() 
{
	// TODO: Add your command handler code here
	
	TrainGesture( "tri" );
}

void CGestureDoc::OnUpdateModelTriangle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnModelThreshold() 
{
	// TODO: Add your command handler code here
	
	ClearDisplay( theApp.m_pGestView );
	TrainThresholdModel();
}

void CGestureDoc::OnUpdateModelThreshold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnInitModel() 
{
	// TODO: Add your command handler code here

	ClearDisplay( theApp.m_pGestView );
	InitializeAllModel();
}

void CGestureDoc::OnUpdateInitModel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnTestFirst() 
{
	// TODO: Add your command handler code here
	
	TestGesture( "first" );
}

void CGestureDoc::OnUpdateTestFirst(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnTestThreshold() 
{
	// TODO: Add your command handler code here
	
	if ( !m_Flags.bLoadThresholdModel ) 
		OnLoadThresholdHmm() ;
	TestGesture( "etc" );
}

void CGestureDoc::OnUpdateTestThreshold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnTestLast() 
{
	// TODO: Add your command handler code here
	
	TestGesture( "last" );
}

void CGestureDoc::OnUpdateTestLast(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnTestNext() 
{
	// TODO: Add your command handler code here
	
	TestGesture( "next" );
}

void CGestureDoc::OnUpdateTestNext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnTestPrev() 
{
	// TODO: Add your command handler code here
	
	TestGesture( "prev" );
}

void CGestureDoc::OnUpdateTestPrev(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnTestQuit() 
{
	// TODO: Add your command handler code here
	
	TestGesture( "quit" );
}

void CGestureDoc::OnUpdateTestQuit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnTestAlpha() 
{
	// TODO: Add your command handler code here
	
	TestGesture( "alpha" );
}

void CGestureDoc::OnUpdateTestAlpha(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnTestBye() 
{
	// TODO: Add your command handler code here
	
	TestGesture( "bye" );
}

void CGestureDoc::OnUpdateTestBye(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnTestCircle() 
{
	// TODO: Add your command handler code here
	
	TestGesture( "cir" );
}

void CGestureDoc::OnUpdateTestCircle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnTestSaw() 
{
	// TODO: Add your command handler code here
	
	TestGesture( "saw" );
}

void CGestureDoc::OnUpdateTestSaw(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnTestTriangle() 
{
	// TODO: Add your command handler code here
	
	TestGesture( "tri" );
}

void CGestureDoc::OnUpdateTestTriangle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnShowRecognition() 
{
	// TODO: Add your command handler code here

	m_Flags.bShowRecognition = !m_Flags.bShowRecognition;
	ClearDisplay( theApp.m_pGestView );
}

void CGestureDoc::OnUpdateShowRecognition(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck( m_Flags.bShowRecognition );
}

void CGestureDoc::OnSingleTrans() 
{
	// TODO: Add your command handler code here

	m_Flags.bSingleTransition = !m_Flags.bSingleTransition;
}

void CGestureDoc::OnUpdateSingleTrans(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck( m_Flags.bSingleTransition );
}

void CGestureDoc::OnTestTrainData() 
{
	// TODO: Add your command handler code here

	m_Flags.bTestTrainData = !m_Flags.bTestTrainData;
}

void CGestureDoc::OnUpdateTestTrainData(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	pCmdUI->SetCheck( m_Flags.bTestTrainData );
}

void CGestureDoc::OnShowMatch() 
{
	// TODO: Add your command handler code here

	m_Flags.bShowMatchProcess = !m_Flags.bShowMatchProcess;
}

void CGestureDoc::OnUpdateShowMatch(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck( m_Flags.bShowMatchProcess );
	pCmdUI->Enable( m_Flags.bShowRecognition );
}

void CGestureDoc::OnGenerateThresholdModel() 
{
	// TODO: Add your command handler code here
	
	ClearDisplay( theApp.m_pGestView );

	GenerateThresholdModel();
}

void CGestureDoc::OnUpdateGenerateThresholdModel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnUniteModel() 
{
	// TODO: Add your command handler code here
	
	ClearDisplay( theApp.m_pGestView );

	GenerateUnitedModel();
}

void CGestureDoc::OnUpdateUniteModel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::SetTestUnited()
{
	if ( !m_Flags.bTestUnitedModel && m_pUnited ) {
		delete m_pUnited;
		m_pUnited = NULL;
	}

	if ( m_Flags.bTestUnitedModel && !m_Flags.bLoadThresholdModel ) {
		m_Flags.bLoadThresholdModel = TRUE;
		m_nModel++;

		if (m_pHMM)
			delete[] m_pHMM;
		m_pHMM = NULL;
	}
}

void CGestureDoc::OnTestUnited() 
{
	// TODO: Add your command handler code here	
	m_Flags.bTestUnitedModel = !m_Flags.bTestUnitedModel;

	SetTestUnited();
}

void CGestureDoc::OnUpdateTestUnited(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck( m_Flags.bTestUnitedModel );
	pCmdUI->Enable( m_pModel != NULL );
}

void CGestureDoc::OnMakeMetafile() 
{
	// TODO: Add your command handler code here

	m_Flags.bMakeMetafile = !m_Flags.bMakeMetafile;
}

void CGestureDoc::OnUpdateMakeMetafile(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck( m_Flags.bMakeMetafile );
	pCmdUI->Enable( m_pModel != NULL && !m_Flags.bShowMatchProcess );
}

void CGestureDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	theApp.m_pGestDoc = NULL;
	CDocument::OnCloseDocument();
}

void CGestureDoc::OnReducedthreshold() 
{
	// TODO: Add your command handler code here
	
	m_Flags.bReducedThreshold = !m_Flags.bReducedThreshold;
}

void CGestureDoc::OnUpdateReducedthreshold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck( m_Flags.bReducedThreshold );
}
