// GestureDoc.h : header file
//

// The kinds of metafile output
#define MO_STROKE		1
#define MO_GRAPH		2
#define MO_MODEL		3
#define MO_NETWORK		4

#define THRESHOLD_PROB		0.090909 // 0.1
#define MAX_GESTURE_LENGTH	50
#define MAX_GESTURE_INPUT	(MAX_GESTURE_LENGTH + 20)


/////////////////////////////////////////////////////////////////////////////
// CGestureDoc document

class CGestureDoc : public CDocument
{
protected:
	CGestureDoc();           // protected constructor used by dynamic creation
	void InitVariables();
	DECLARE_DYNCREATE(CGestureDoc)

// Attributes
public:
	struct {
		BOOL	bAscii: 2;
		BOOL	bProcessThreshold: 2;
		BOOL	bLoadThresholdModel: 2;
		BOOL	bShowRecognition: 2;
		BOOL	bSingleTransition: 2;
		BOOL	bTestTrainData: 2;
		BOOL	bShowMatchProcess: 2;
		BOOL	bTestUnitedModel: 2;
		BOOL	bMakeMetafile: 2;
		BOOL	bFirstTraceViterbi: 2;
		BOOL	bReducedThreshold: 2;
	} m_Flags;
	SHORT	m_nMetafileCount;
	SHORT	m_nSymbol;
	SHORT	m_nClass;
	SHORT	m_nFVec;
	SHORT	m_nProcessedTime;
	SHORT	m_nThresholdModel;
	SHORT	m_nOutput;
	SHORT	m_nModel;
	SHORT*	m_pnOutput;
	MODEL*	m_pModel;
	char	m_szBaseDir[MAX_BUFFER];
	char	m_szTrainFile[MAX_BUFFER];
	char	m_szTestFile[MAX_BUFFER];
	char	m_szModelDir[MAX_BUFFER];
	class	CMGVQ* m_pMGVQ;
	class	CDHmm*  m_pHMM;
	class	CDHmm*	m_pUnited;
	class	CVScore* m_pVScore;
	class	CFVec*	m_pFVec;

	// Temporaries for gesture spotting recognition
	SHORT	m_nRecogOut;
	RECOUT*	m_pRecogOut;
	class	CStroke* m_pTmpStroke;

// Operations
public:
	// DoHmm.cpp
	BOOL	TrainGesture( const char* pszModelName=NULL );
	BOOL	TestGesture( const char* pszModelName=NULL );
	SHORT	OnlineTestGesture( class CFVec* pFVec, SHORT nCurModel,
				BOOL bImmediate, const POINT* pPt=NULL, const SHORT nPt=0 );
	BOOL	ImmediateProcessing( class CStroke* pStroke );
	BOOL	StartGestureRecognition( CStroke* pStroke, BOOL bUseFrameID );
	BOOL	SpottingRecognition( CStroke* pStroke, BOOL bLast, REAL rWait );
	void	ResetSpottingRecognition( CStroke* pStroke, BOOL bResetAll );
	BOOL	DisplaySpottedGesture( CStroke* pStroke, BOOL bResetAll, REAL rWait );
	void	EndSpottingRecognition( CStroke* pStroke );
	BOOL	SaveRecogOutData( SHORT nRecOut, RECOUT* pRecOut, CStroke* pStroke );
	BOOL	LoadRecogOutData( SHORT* pnRecOut, RECOUT* pRecOut );

	// DocMisc.cpp
	void	ReadTrainedModel();
	void	MakeMGVQ( class CGestureView* pView );
	void	RemoveAllRawData();
	BOOL	LoadAllRawData();
	BOOL	TrainThresholdModel();
	void	InitializeAllModel();
	BOOL	ReadDocument( FILE* fp );
	BOOL	GenerateMGVQ();
	BOOL	MakeListFile();
	void	GenerateThresholdModel( REAL rThreshProb=THRESHOLD_PROB );
	BOOL	GenerateUnitedModel( REAL rThreshProb=THRESHOLD_PROB );
	void	SetTestUnited();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGestureDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGestureDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// DoHmm.cpp
	SHORT*	GetCode( char* pszFileName, SHORT* pnData );
	SHORT*	GetCode( class CFVec* pFVec, SHORT* pnData );
	SHORT	GetModelFromList( FILE* fp, char* pszListFile, const char* pszModelName=NULL );
	BOOL	TrainHMM( class CFilelist& filelist, SHORT nState, SHORT nModel );
	BOOL	PrintRecogResult( char* pszBaseName, REAL* prLL, REAL rBest, 
					SHORT nBest, SHORT nInModel );
	class	CVScore* MatchNormalModel( char* pszBaseName, SHORT* pnOutput, 
					SHORT nOutput, SHORT nCurModel, SHORT* pnBestModel, 
					BOOL bImmediate );
	class	CVScore* MatchUnitedModel( char* pszBaseName, SHORT* pnOutput, 
					SHORT nOutput, SHORT nCurModel, SHORT* pnBestModel, 
					BOOL bImmediate );
	class	CVScore* MatchModel( char* pszFileName, class CFVec* pFVec,
					SHORT nCurModel, SHORT* pnBestModel, BOOL bImmediate );
	BOOL	DisplayMatchingOutput( class CVScore* pVScore, SHORT nCurModel,
					SHORT nBestModel, BOOL bImmediate, REAL rWait,
					class CStroke* pStroke );
	BOOL	DisplayUnitedMatching( CMetaFileDC* pMetaDC, BOOL bImmediate,
							REAL rWait, CVScore* pVScore, CStroke* pStroke );
	void	CalcMetaBoundingRect( CVScore* pVScore, SHORT nBestModel, 
								  CStroke* pStroke, CRect* prc );
	BOOL	FinishMetaRecording( CMetaFileDC* pMetaDC, SHORT nCurModel, 
						BOOL bImmediate, REAL rWait, CRect* prc, 
						BOOL bOK, SHORT nKind );
	BOOL	TestHMM( class CFilelist& filelist, SHORT nCurModel );
	void	AdjustSpotting();
	void	SpottingOneModel( CVScore* pVScore, SHORT nBestModel );
	void	FlushSpotting();
	void	PeekDetection( class CVScore* pVScore, SHORT bestModel );
	void	SendPowerPointMessage( SHORT nCurModel );
	SHORT	TestHMM( class CFVec* pFVec, SHORT nCurModel, BOOL bImmediate, 
					REAL rWait, BOOL bLast, class CStroke* pStroke );
	SHORT	TestUnitedHMM( REAL rWait, BOOL bLast, class CStroke* pStroke );
	void	DisplayCurrentProcess(CStroke* pStroke, SHORT nDrawT);
	void	RemoveUselessInput( CStroke* pStroke, SHORT nLength );

	// DocMisc.cpp
	BOOL	MakeRawList( const char* pStrokeFile, const char* pRawFile,
							SHORT nFromModel, SHORT nToModel );
	BOOL	MakeThresholdRawList( const char* pStrokeFile, const char* pRawFile,
							SHORT* pnTotFile, BYTE** pcFlag );

	// Generated message map functions
protected:
	//{{AFX_MSG(CGestureDoc)
	afx_msg void OnHmmAscii();
	afx_msg void OnUpdateHmmAscii(CCmdUI* pCmdUI);
	afx_msg void OnHmmTest();
	afx_msg void OnHmmTrain();
	afx_msg void OnDoAll();
	afx_msg void OnMakeListFile();
	afx_msg void OnUpdateMakeListFile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDoAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHmmTest(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHmmTrain(CCmdUI* pCmdUI);
	afx_msg void OnLoadThresholdHmm();
	afx_msg void OnUpdateLoadThresholdHmm(CCmdUI* pCmdUI);
	afx_msg void OnGenerateThresholdModel();
	afx_msg void OnUpdateGenerateThresholdModel(CCmdUI* pCmdUI);
	afx_msg void OnTrainThreshold();
	afx_msg void OnUpdateTrainThreshold(CCmdUI* pCmdUI);
	afx_msg void OnModelFirst();
	afx_msg void OnUpdateModelFirst(CCmdUI* pCmdUI);
	afx_msg void OnModelLast();
	afx_msg void OnUpdateModelLast(CCmdUI* pCmdUI);
	afx_msg void OnModelNext();
	afx_msg void OnUpdateModelNext(CCmdUI* pCmdUI);
	afx_msg void OnModelPrev();
	afx_msg void OnUpdateModelPrev(CCmdUI* pCmdUI);
	afx_msg void OnModelQuit();
	afx_msg void OnUpdateModelQuit(CCmdUI* pCmdUI);
	afx_msg void OnInitModel();
	afx_msg void OnUpdateInitModel(CCmdUI* pCmdUI);
	afx_msg void OnModelThreshold();
	afx_msg void OnUpdateModelThreshold(CCmdUI* pCmdUI);
	afx_msg void OnTestFirst();
	afx_msg void OnUpdateTestFirst(CCmdUI* pCmdUI);
	afx_msg void OnTestThreshold();
	afx_msg void OnUpdateTestThreshold(CCmdUI* pCmdUI);
	afx_msg void OnTestLast();
	afx_msg void OnUpdateTestLast(CCmdUI* pCmdUI);
	afx_msg void OnTestNext();
	afx_msg void OnUpdateTestNext(CCmdUI* pCmdUI);
	afx_msg void OnTestPrev();
	afx_msg void OnUpdateTestPrev(CCmdUI* pCmdUI);
	afx_msg void OnTestQuit();
	afx_msg void OnUpdateTestQuit(CCmdUI* pCmdUI);
	afx_msg void OnShowRecognition();
	afx_msg void OnUpdateShowRecognition(CCmdUI* pCmdUI);
	afx_msg void OnSingleTrans();
	afx_msg void OnUpdateSingleTrans(CCmdUI* pCmdUI);
	afx_msg void OnTestTrainData();
	afx_msg void OnUpdateTestTrainData(CCmdUI* pCmdUI);
	afx_msg void OnShowMatch();
	afx_msg void OnUpdateShowMatch(CCmdUI* pCmdUI);
	afx_msg void OnUniteModel();
	afx_msg void OnUpdateUniteModel(CCmdUI* pCmdUI);
	afx_msg void OnTestUnited();
	afx_msg void OnUpdateTestUnited(CCmdUI* pCmdUI);
	afx_msg void OnMakeMetafile();
	afx_msg void OnUpdateMakeMetafile(CCmdUI* pCmdUI);
	afx_msg void OnModelAlpha();
	afx_msg void OnUpdateModelAlpha(CCmdUI* pCmdUI);
	afx_msg void OnModelBye();
	afx_msg void OnUpdateModelBye(CCmdUI* pCmdUI);
	afx_msg void OnModelCircle();
	afx_msg void OnUpdateModelCircle(CCmdUI* pCmdUI);
	afx_msg void OnModelSaw();
	afx_msg void OnUpdateModelSaw(CCmdUI* pCmdUI);
	afx_msg void OnModelTriangle();
	afx_msg void OnUpdateModelTriangle(CCmdUI* pCmdUI);
	afx_msg void OnTestAlpha();
	afx_msg void OnUpdateTestAlpha(CCmdUI* pCmdUI);
	afx_msg void OnTestBye();
	afx_msg void OnUpdateTestBye(CCmdUI* pCmdUI);
	afx_msg void OnTestCircle();
	afx_msg void OnUpdateTestCircle(CCmdUI* pCmdUI);
	afx_msg void OnTestSaw();
	afx_msg void OnUpdateTestSaw(CCmdUI* pCmdUI);
	afx_msg void OnTestTriangle();
	afx_msg void OnUpdateTestTriangle(CCmdUI* pCmdUI);
	afx_msg void OnReducedthreshold();
	afx_msg void OnUpdateReducedthreshold(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
