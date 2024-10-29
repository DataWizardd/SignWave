// SpotDoc.h : interface of the CSpotDoc class
//
/////////////////////////////////////////////////////////////////////////////


class CSpotDoc : public CDocument
{
protected: // create from serialization only
	CSpotDoc();
	DECLARE_DYNCREATE(CSpotDoc)

// Attributes
public:
	MIL_ID	m_milImage;		// Image buffer ID
	MIL_ID	m_milDispImg;	// Image for display
	long	m_lDispIdx;		// display number
	SHORT	m_nInputType;
	SHORT	m_nDumpID;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpotDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSpotDoc();
	BOOL	GetNextDumpFile(SHORT nStep);
	BOOL	GetPrevDumpFile(SHORT nStep);
	BOOL	SaveLabellingData(SHORT nLabel, MYLABEL* pLabel);
	BOOL	LoadLabellingData(SHORT* nLabel, MYLABEL* pLabel);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSpotDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
