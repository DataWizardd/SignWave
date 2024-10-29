
// SpotDoc.cpp : implementation of the CSpotDoc class
//

// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"
#include "MyHand.h"
#include "CMyMIL.h"
#include "SpotDoc.h"
#include "SpotView.h"
#include "utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpotDoc

IMPLEMENT_DYNCREATE(CSpotDoc, CDocument)

BEGIN_MESSAGE_MAP(CSpotDoc, CDocument)
	//{{AFX_MSG_MAP(CSpotDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpotDoc construction/destruction

CSpotDoc::CSpotDoc()
{
	// TODO: add one-time construction code here
	m_lDispIdx = 0;
	m_milImage = M_NULL;
	m_milDispImg = M_NULL;

	m_nDumpID = -1;
	m_nInputType = theApp.m_nInputType;

	theMIL->InitMILDocument(&m_lDispIdx, &m_milImage, &m_milDispImg);
}

CSpotDoc::~CSpotDoc()
{
}

BOOL CSpotDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSpotDoc serialization

void CSpotDoc::Serialize(CArchive& ar)
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
// CSpotDoc diagnostics

#ifdef _DEBUG
void CSpotDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSpotDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpotDoc commands

void CSpotDoc::OnCloseDocument()
{
	// TODO: Add your specialized code here and/or call the base class
	if ((m_lDispIdx < theMIL->m_lMaxDisplay) && m_milDispImg) {
		CSpotView* CurView;
		POSITION	CurPos;

		CurPos = GetFirstViewPosition();
		while (CurView = (CSpotView*)GetNextView(CurPos)) {
			theMIL->RemoveMILDisplay(CurView, &(CurView->m_milDisplay),
				m_milDispImg);
		}

		theMIL->CloseMILDocument(&m_milImage, &m_milDispImg);
	}

	CDocument::OnCloseDocument();
}


void SaveBinaryImage(FILE* fp, BYTE** img, SHORT nHeight, SHORT nWidth);
void LoadBinaryImage(FILE* fp, BYTE** img, SHORT nHeight, SHORT nWidth);

BOOL CSpotDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO: Add your specialized creation code here
	FILE* fp;
	BOOL	bGray;

	BeginWaitCursor();

	if (!(fp = fopen(lpszPathName, "rb"))) {
		EndWaitCursor();
		return FALSE;
	}

	GetDumpFileInform(lpszPathName, &m_nInputType, &m_nDumpID);

	SetStatusMessage("Reading frame files %s ...", lpszPathName);

	fread(&bGray, sizeof(BOOL), 1, fp);
	theApp.m_Flags.bGetGray = bGray;
	fread(&(theMIL->m_myHand->m_nCurFrame), sizeof(SHORT), 1, fp);
	if (theMIL->m_myHand->m_nCurFrame > MAX_FRAME)
		theMIL->m_myHand->m_nCurFrame = MAX_FRAME;

	if (theMIL->m_myHand->m_nCurFrame > 0) {
		for (int i = 0; i < theMIL->m_myHand->m_nCurFrame; i++) {
			if (theApp.m_Flags.bGetGray) {
				for (int j = 0; j < theMIL->m_myHand->m_nHeight; j++) {
					fread(theMIL->m_myHand->m_savImg[i][j], 1,
						theMIL->m_myHand->m_nWidth, fp);
#ifdef MAKE_BINARY_IMAGE
					for (int k = 0; k < theMIL->m_myHand->m_nWidth; k++) {
						if (theMIL->m_myHand->m_savImg[i][j][k] & 0x80)
							theMIL->m_myHand->m_savImg[i][j][k] = 1;
						else
							theMIL->m_myHand->m_savImg[i][j][k] = 0;
					}
#endif
				}
			}
			else {
				LoadBinaryImage(fp, theMIL->m_myHand->m_savImg[i],
					theMIL->m_myHand->m_nHeight,
					theMIL->m_myHand->m_nWidth);
			}
		}

		fclose(fp);

		EndWaitCursor();
	}

	return TRUE;
	}

BOOL CSpotDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	const char* pszNewFile;

	if (lpszPathName)
		pszNewFile = lpszPathName;
	else {
		if (m_nDumpID < 0) {
			MessageBeep(MB_ICONHAND);
			return FALSE;
		}
		pszNewFile = MakeMyDumpName(m_nInputType, m_nDumpID);
	}

	if (!CDocument::OnSaveDocument(pszNewFile))
		return FALSE;

	// TODO: Add your specialized code here and/or call the base class
	if (theMIL->m_myHand->m_nCurFrame > 0) {
		FILE* fp;
		int		nWrite;
		BOOL	bGray;

		BeginWaitCursor();

		if (!(fp = fopen(pszNewFile, "wb"))) {
			EndWaitCursor();
			return FALSE;
		}

		SetStatusMessage("Writing frame files %s ...", pszNewFile);

		bGray = theApp.m_Flags.bGetGray;
		nWrite = fwrite(&bGray, sizeof(BOOL), 1, fp);
		nWrite = fwrite(&(theMIL->m_myHand->m_nCurFrame), sizeof(SHORT), 1, fp);
		for (int i = 0; i < theMIL->m_myHand->m_nCurFrame; i++) {
			if (theApp.m_Flags.bGetGray) {
				for (int j = 0; j < theMIL->m_myHand->m_nHeight; j++)
					fwrite(theMIL->m_myHand->m_savImg[i][j], 1,
						theMIL->m_myHand->m_nWidth, fp);
			}
			else {
				SaveBinaryImage(fp, theMIL->m_myHand->m_savImg[i],
					theMIL->m_myHand->m_nHeight,
					theMIL->m_myHand->m_nWidth);
			}
		}
		fclose(fp);

		EndWaitCursor();
	}

	return TRUE;
}

BOOL CSpotDoc::GetNextDumpFile(SHORT nStep)
{
	char* pPathName;
	SHORT nID;

	if (m_nDumpID < 0)
		m_nDumpID = 0;
	m_nDumpID += nStep;

	for (int i = 0; i < MAX_INPUTTYPE; i++) {
		nID = GetDumpFileID(m_nInputType);
		if (nID > m_nDumpID) {
			pPathName = MakeMyDumpName(m_nInputType, m_nDumpID);
			if (OnOpenDocument(pPathName)) {
				SetPathName(pPathName);
				return TRUE;
			}
			break;
		}
		else {
			m_nDumpID -= nID;
			m_nInputType = (m_nInputType + 1) % MAX_INPUTTYPE;
		}
	}

	m_nDumpID = -1;
	return FALSE;
}

BOOL CSpotDoc::GetPrevDumpFile(SHORT nStep)
{
	char* pPathName;
	SHORT nID;

	if (m_nDumpID < 0)
		m_nDumpID = 0;
	m_nDumpID -= nStep;

	if (m_nDumpID >= 0) {
		pPathName = MakeMyDumpName(m_nInputType, m_nDumpID);
		if (OnOpenDocument(pPathName)) {
			SetPathName(pPathName);
			return TRUE;
		}

		m_nDumpID = -1;
		return FALSE;
	}

	for (int i = 0; i < MAX_INPUTTYPE; i++) {
		if (m_nInputType == 0)
			m_nInputType = MAX_INPUTTYPE;
		m_nInputType = (m_nInputType - 1) % MAX_INPUTTYPE;
		nID = GetDumpFileID(m_nInputType);
		m_nDumpID += nID;
		if (m_nDumpID >= 0) {
			pPathName = MakeMyDumpName(m_nInputType, m_nDumpID);
			if (OnOpenDocument(pPathName)) {
				SetPathName(pPathName);
				return TRUE;
			}
			break;
		}
	}

	m_nDumpID = -1;

	return FALSE;
}

BOOL CSpotDoc::SaveLabellingData(SHORT nLabel, MYLABEL* pLabel)
{
	const char* pszNewFile;
	FILE* fp;

	if (nLabel < 1 || m_nDumpID < 0) {
		MessageBeep(MB_ICONHAND);
		return FALSE;
	}

	pszNewFile = MakeMyResultName(NAME_LABEL);

	if (!(fp = fopen(pszNewFile, "w"))) {
		return FALSE;
	}

	SetStatusMessage("Writing label file %s ...", pszNewFile);

	fprintf(fp, "%d\n", nLabel);
	for (int i = 0; i < nLabel; i++) {
		fprintf(fp, "%d %d %s\n", pLabel[i].nStart, pLabel[i].nLast,
			GetModelName(pLabel[i].nModel));
	}
	fclose(fp);

	return TRUE;
}

BOOL CSpotDoc::LoadLabellingData(SHORT* nLabel, MYLABEL* pLabel)
{
	const char* pszNewFile;
	char	szTmp[20];
	int		t1, t2;
	FILE* fp;

	*nLabel = 0;

	if (m_nDumpID < 0) {
		MessageBeep(MB_ICONHAND);
		return FALSE;
	}

	pszNewFile = MakeMyResultName(NAME_LABEL);

	if (!(fp = fopen(pszNewFile, "r"))) {
		return FALSE;
	}

	SetStatusMessage("Reading label file %s ...", pszNewFile);

	fscanf(fp, "%d", &t1);
	if (t1 < 1 || t1 >= MAX_MYLABEL) {
		fclose(fp);
		return FALSE;
	}

	*nLabel = t1;
	for (int i = 0; i < *nLabel; i++) {
		fscanf(fp, "%d %d %s", &t1, &t2, szTmp);
		pLabel[i].nStart = t1;
		pLabel[i].nLast = t2;
		pLabel[i].nModel = -1;
		for (int j = 0; j < MODEL_THRESHOLD; j++) {
			if (!strcmpi(szTmp, GetModelName(j))) {
				pLabel[i].nModel = j;
				break;
			}
		}

		if (pLabel[i].nModel < 0) {
			MessageBeep(MB_ICONHAND);
			*nLabel = 0;
			SetStatusMessage("Illegal label file!!!");
			fclose(fp);
			return FALSE;
		}
	}
	fclose(fp);

	return TRUE;
}
