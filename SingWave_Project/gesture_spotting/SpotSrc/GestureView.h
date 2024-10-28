// GestureView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGestureView view

class CGestureView : public CView
{
protected:
	CGestureView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGestureView)
	void	RecognizeInput( SHORT nCurModel, BOOL bPaint );
	void	DrawVQResult( class CFVec* pFVec, SHORT nCode );
	void	ClearActionFlags();
	void	SetImmediateRecog();
	REAL*	CalcVQProbability();
// Attributes
public:
	class	CMGVQ* m_pMGVQ;
	struct {
		BOOL	bStartCapture: 2;
		BOOL	bLButtonDown: 2;
		BOOL	bEditStroke: 2;
		BOOL	bMovePoint: 2;
		BOOL	bMGVQ: 2;
		BOOL	bVectorQuantize: 2;
		BOOL	bBlockInput: 2;
		BOOL	bOnlineTest: 2;
		BOOL	bStartRecognize: 2;
		BOOL	bChangeDialog: 2;
		BOOL	bImmediateRecog: 2;
	} m_Flags;

// Operations
public:
	CGestureDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGestureView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGestureView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	class	CStroke* m_pStroke; 
	SHORT	m_nVQCount;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGestureView)
	afx_msg void OnStartCapture();
	afx_msg void OnUpdateStartCapture(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClearDisplay();
	afx_msg void OnEditStroke();
	afx_msg void OnUpdateEditStroke(CCmdUI* pCmdUI);
	afx_msg void OnEditNextStroke();
	afx_msg void OnEditSaveStroke();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLearnVq();
	afx_msg void OnVectorQuantize();
	afx_msg void OnEditPrevStroke();
	afx_msg void OnMakeNormalVq();
	afx_msg void OnUpdateVectorQuantize(CCmdUI* pCmdUI);
	afx_msg void OnOnlineTest();
	afx_msg void OnUpdateOnlineTest(CCmdUI* pCmdUI);
	afx_msg void OnResaveAll();
	afx_msg void OnNext10Stroke();
	afx_msg void OnPrev10Stroke();
	afx_msg void OnUpdateEditNextStroke(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPrevStroke(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditSaveStroke(CCmdUI* pCmdUI);
	afx_msg void OnUpdateResaveAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePrev10Stroke(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNext10Stroke(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMakeNormalVq(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLearnVq(CCmdUI* pCmdUI);
	afx_msg void OnStartRecognize();
	afx_msg void OnUpdateStartRecognize(CCmdUI* pCmdUI);
	afx_msg void OnEditChangeStroke();
	afx_msg void OnUpdateEditChangeStroke(CCmdUI* pCmdUI);
	afx_msg void OnImmediateRecog();
	afx_msg void OnUpdateImmediateRecog(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SpotView.cpp
inline CGestureDoc* CGestureView::GetDocument()
   { return (CGestureDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
