// PrefixDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrefixDlg dialog

class CPrefixDlg : public CDialog
{
// Construction
public:
	CPrefixDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrefixDlg)
	enum { IDD = IDD_PREFIXDLG };
	CString	m_szPrefix;
	UINT	m_nNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrefixDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrefixDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
