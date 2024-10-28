// CStroke.h : Mouse input processing
//
/////////////////////////////////////////////////////////////////////////////
#ifndef	_CSTROKE_HPP
#define	_CSTROKE_HPP

#define MAX_POINTS		500

typedef struct tagSTROKE {
	struct	tagSTROKE* pPrev;
	struct	tagSTROKE* pNext;
	SHORT	nPt;
	POINT*	pPt;
	SHORT*	pnFrameID;	// for restoring the frame number
	CRect	rcBound;
} MYSTROKE;

class CStroke {
protected:
	SHORT		m_nCurFile;
	MYSTROKE*	m_pStartStroke;
	MYSTROKE*	m_pCurStroke;
	char		m_szPrefix[8];

	SHORT		m_nEditStroke;
	class		CFilelist*	m_pFilelist;

	SHORT		m_nCurPt;
	REAL		m_rDist;

public:
	BOOL		m_bNormalized;
	SHORT		m_nOnlineStroke;
	SHORT		m_nCurModel;
	SHORT		m_nStartFrame;	// for restoring the frame number
	SHORT*		m_pnFrameID;		// for restoring the frame number
	MYSTROKE	m_Norm;
	MYSTROKE	m_Buf;

protected:
	void	DrawEditMark( CDC* pDC, POINT pt, SHORT nLoc, BOOL bNorm );
	void	DrawLineSegment( CDC* pDC, POINT* pPt, SHORT nPt );
	void	CenterStroke( CRect* prc );
	SHORT	GetOnlineFileID( BOOL bOnline );
	void	SetOnlineFileID( BOOL bOnline, SHORT nID );
	BOOL	FitCurrentStroke( MYSTROKE* pBuf, BOOL bFitBound );
	BOOL	NormalizeStroke( MYSTROKE* pBuf, BOOL bFitBound );
	BOOL	WriteFeatureVector( const char* pszFileName, BOOL bText );
	void	SetCurModelID( char* pszFile, MODEL* pModel, SHORT nModel );
	void	RecalcBoundingBox( CRect* prc, POINT* pPt, SHORT nPt );
	void	AddPointToNormalize( MYSTROKE* pBuf, REAL NFactor, 
						SHORT nCurPt, SHORT* pPrev, BOOL bForced );

public:
	void	ClearStroke();
	CStroke();
	~CStroke();
	void	AllocFrameID();
	void	FreeFrameID();
	BOOL	Read( const char* pszFileName );
	BOOL	ReadText( const char* pszFileName );
	BOOL	Write( const char* pszFileName, const BOOL bUseNorm );
	BOOL	WriteText( const char* pszFileName, const BOOL bUseNorm );

	class	CFVec* MakeImmediateVector( SHORT nPoints );
	void	PointToVector( class CFVec* pFVec, SHORT nLoc, BOOL bUseNorm );
	class	CFVec* StrokeToVector( BOOL bUseNorm );
	void	UpdateNormalizedStroke();
	BOOL	SaveEditStroke();
	BOOL	SaveFrameStroke(SHORT nInputType, SHORT nDumpID);
	void	FitToRect( MYSTROKE* pBuf, CRect rcFit, BOOL bFitBound );
	void	AddHandPosition( POINT pt, SHORT nCurFrame );
	void	FlushHandPosition();

	SHORT	SetPrefix( MODEL* pModel, SHORT nModel );
	BOOL	ChangeEditStroke( CRect* prc, MODEL* pModel, SHORT nModel );
	BOOL	ChangeOnlineStroke( BOOL bOnline );
	BOOL	NextOnlineStroke( SHORT nSkip );
	BOOL	PrevOnlineStroke( SHORT nSkip );
	void	DrawOnlineStroke( CView* pView );
	void	StartStroke(POINT pt);
	BOOL	AddStroke(POINT pt, CDC* pDC);
	void	StartImmediateRecog(POINT pt);
	CFVec*	AddImmediateRecog(POINT pt, CView* pView);
	class	CFVec* EndOnlineStroke( CView* pView, BOOL bDrawNormal, BOOL bPaint );
	BOOL	SaveOnlineStroke( BOOL bOnline );
	void	EndStroke( CView* pView, BOOL bDrawNormal );

	void	DrawStroke( CDC* pDC, CRect* prc, BOOL bEdit, BOOL bShowNormal );
	void	DrawNormalizedStroke( CDC* pDC );
	BOOL	StartEditStroke( CView* pView, MODEL* pModel, SHORT nModel );
	BOOL	EditNextStroke( CRect* prc, SHORT nSkip, MODEL* pModel, SHORT nModel );
	BOOL	EditPrevStroke( CRect* prc, SHORT nSkip, MODEL* pModel, SHORT nModel );

	void	DrawInverseSelection( CDC* pDC );
	BOOL	CheckEditMark( POINT pt );
	BOOL	AppendOnePoint( POINT pt );
	void	StartMovePoint( CDC* pDC );
	void	UpdateMovePoint( CDC* pDC, POINT pt );
	void	DeleteEditPoint();
	void	GetNewFeature( class CFVec* pFVec );

	void	ResaveAllStroke( CView* pView );

	void	RepositionTrace( POINT ptLoc );
	void	ClearTraceDraw( CView* pView, CMetaFileDC* pMetaDC );
	void	PrepareTrace( char* pszStrokeFile, 
						const POINT* pPt=NULL, const SHORT nPt=0 );
	void	DrawTraceLine( CView* pView, CMetaFileDC* pMetaDC, SHORT nLine );
	void	CalcSpotBoundingRect( CView* pView, CRect* prc );
	void	DrawSpottingResult( CMetaFileDC* pDC, CView* pView, 
								struct tagRECOUT* pRecogOut, 
								SHORT nRecogOut, SHORT nDrawT,
								MODEL* pModel, SHORT nThresholdModel );
	BOOL	PointToStroke( POINT* pPt, SHORT nPt );
};

#endif

/////////////////////////////////////////////////////////////////////////////
