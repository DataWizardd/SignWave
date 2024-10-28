// PrefixDlg.cpp : implementation file
//

// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"
#include "PrefixDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefixDlg dialog


CPrefixDlg::CPrefixDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrefixDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrefixDlg)
	m_szPrefix = _T("");
	m_nNumber = 0;
	//}}AFX_DATA_INIT
}


void CPrefixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefixDlg)
	DDX_Text(pDX, IDC_PREFIX, m_szPrefix);
	DDX_Text(pDX, IDC_NUMBER, m_nNumber);
	DDV_MinMaxUInt(pDX, m_nNumber, 0, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefixDlg, CDialog)
	//{{AFX_MSG_MAP(CPrefixDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefixDlg message handlers

BOOL CPrefixDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
