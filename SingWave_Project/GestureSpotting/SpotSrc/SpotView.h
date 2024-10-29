// SpotView.h : interface of the CSpotView class
//
/////////////////////////////////////////////////////////////////////////////

class CSpotView : public CView
{
protected: // create from serialization only
	CSpotView();
	DECLARE_DYNCREATE(CSpotView)

// Attributes
public:
	CSpotDoc* GetDocument();
	MIL_ID		m_milDisplay;	// Display ID
	MIL_ID		m_milOverlayImage;

// Operations
public:
	void	RemoveFromDisplay();
	BOOL	GenerateFeature( SHORT nInputType, SHORT nFileID );

protected:
	BOOL	RecognizeTestData( REAL rThreshProb );
	BOOL	GenerateTestResult( char* pszFile, REAL rThreshProb ) ;
	BOOL	DisplayFrameImage( REAL rWait, BOOL bUseFrameID ) ;
	void	CompareRecogOut( FILE* fp, SHORT nDumpID, SHORT nLabel, MYLABEL* pLabel,
							 SHORT nRecogOut, RECOUT* pRecogOut );
	BOOL	SaveHandLocation( POINT* pPt, SHORT nPt );
	BOOL	LoadHandLocation( POINT* pPt, SHORT* pnPt );
	BOOL	SpotFrameData( POINT* pPt, SHORT nDumpID );
	void	CommandTextOut(int nX, int nY, char* pszStr, int nAlign);
	BOOL	GenResultForProb( SHORT nProb, SHORT nKind );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpotView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSpotView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSpotView)
	afx_msg void OnFinishGrab();
	afx_msg void OnUpdateFinishGrab(CCmdUI* pCmdUI);
	afx_msg void OnStartGrab();
	afx_msg void OnUpdateStartGrab(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnDisplayFrame();
	afx_msg void OnUpdateDisplayFrame(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnNextDumpFile();
	afx_msg void OnNext10DumpFile();
	afx_msg void OnPrevDumpFile();
	afx_msg void OnPrev10DumpFile();
	afx_msg void OnGenerateAllFeature();
	afx_msg void OnGenLastData();
	afx_msg void OnGenFirstData();
	afx_msg void OnGenNextData();
	afx_msg void OnGenPrevData();
	afx_msg void OnGenQuitData();
	afx_msg void OnGenThresholdData();
	afx_msg void OnGenTestData();
	afx_msg void OnSaveSnapFrame();
	afx_msg void OnCountLabel();
	afx_msg void OnRecogTestData();
	afx_msg void OnUpdateRecogTestData(CCmdUI* pCmdUI);
	afx_msg void OnGenTestResult();
	afx_msg void OnGenAlphaData();
	afx_msg void OnGenByeData();
	afx_msg void OnGenCircleData();
	afx_msg void OnGenSawData();
	afx_msg void OnGenTriangleData();
	afx_msg void OnGenCurFeature();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SpotView.cpp
inline CSpotDoc* CSpotView::GetDocument()
   { return (CSpotDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
