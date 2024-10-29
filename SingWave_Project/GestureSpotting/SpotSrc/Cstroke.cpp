// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"
#include <math.h>
#include "utils.h"
#include "CFlist.h"
#include "Cfvec.h"
#include "Cstroke.h"
#include "PrefixDlg.h"
#include "GestureDoc.h"

//==========================================================================
//
// User interface for stroke operation
//
//	1. ESC_Key_Down:	cancel all editing operation
//
//	2. Stroke creation
//		RButton_Down:	clear screen
//
//	3. Stroke editing
//		LButton_Down:	move stroke point
//		^LButton_Down:	add a stroke point and move it
//		RButton_Down:	remove stroke point
//
//==========================================================================

#define MARK_SIZE	3
#define PICK_SIZE	5
#define NORMAL_GAP	5

#define MAKE_CENTER	1

#define	PI			(REAL)3.141592654


const char cszStrokeMagic[MAGIC_SIZE] = "KAIST AI Lab  Stroke Version 1.0\n\004";

COLORREF PenColor[3] = { MY_RED, MY_GREEN, MY_BLUE };


void SetBoundingBox( CRect* prcBound, POINT pt )
{
	prcBound->left	= min( prcBound->left  , pt.x );
	prcBound->top	= min( prcBound->top   , pt.y );
	prcBound->right	= max( prcBound->right , pt.x );
	prcBound->bottom= max( prcBound->bottom, pt.y );
}

void CStroke::RecalcBoundingBox( CRect* prc, POINT* pPt, SHORT nPt )
{
	int i;

	prc->left = prc->right = pPt[0].x;
	prc->top = prc->bottom = pPt[0].y;
	for(i=1; i<nPt; i++) 
		SetBoundingBox( prc, pPt[i] );
}

void CStroke::ClearStroke()
{
	MYSTROKE *pCur, *pNext;

	pCur = m_pStartStroke;
	while (pCur) {
		if (pCur->pPt)
			delete[] pCur->pPt;
		if (pCur->pnFrameID)
			delete[] pCur->pnFrameID;
		pNext = pCur->pNext;
		delete pCur;
		pCur = pNext;
	}

	m_pStartStroke = NULL;
	m_pCurStroke = NULL;
	m_Buf.nPt  = 0;
	m_Norm.nPt  = 0;
	m_bNormalized = TRUE;
}

CStroke::CStroke()
{
	m_szPrefix[0] = 0;
	m_pStartStroke = NULL;
	m_pCurStroke = NULL;
	m_nCurFile = 0;
	m_nCurModel = -1;
	m_Buf.pPt = new POINT[MAX_POINTS];
	m_Buf.pnFrameID = NULL;
	m_Buf.pPrev = m_Buf.pNext = NULL;
	m_Norm.nPt  = 0;
	m_Norm.pPt = new POINT[MAX_POINTS];
	m_Norm.pnFrameID = NULL;
	m_Norm.pPrev = m_Norm.pNext = NULL;
	m_pFilelist = NULL;
	m_bNormalized = TRUE;
}

CStroke::~CStroke()
{
	ClearStroke();

	delete[] m_Buf.pPt;
	if (m_Buf.pnFrameID)
		delete[] m_Buf.pnFrameID;
	delete[] m_Norm.pPt;
	if (m_Norm.pnFrameID)
		delete[] m_Norm.pnFrameID;

	if (m_pFilelist)
		delete m_pFilelist;
}

void CStroke::AllocFrameID()
{
	if (m_Buf.pnFrameID)
		delete[] m_Buf.pnFrameID;
	m_Buf.pnFrameID = new SHORT[MAX_POINTS];
	memset(m_Buf.pnFrameID, 0, sizeof(SHORT)*MAX_POINTS);

	if (m_Norm.pnFrameID)
		delete[] m_Norm.pnFrameID;
	m_Norm.pnFrameID = new SHORT[MAX_POINTS];
	memset(m_Norm.pnFrameID, 0, sizeof(SHORT)*MAX_POINTS);
}

void CStroke::FreeFrameID()
{
	if (m_Buf.pnFrameID)
		delete[] m_Buf.pnFrameID;
	m_Buf.pnFrameID = NULL;

	if (m_Norm.pnFrameID)
		delete[] m_Norm.pnFrameID;
	m_Norm.pnFrameID = NULL;
}

SHORT CStroke::SetPrefix( MODEL* pModel, SHORT nModel )
{
	CPrefixDlg	PrefixDlg;
	int i;

	m_nCurModel = (m_nCurModel + 1) % nModel;
	PrefixDlg.m_szPrefix = pModel[m_nCurModel].szName;

	PrefixDlg.m_nNumber = pModel[m_nCurModel].nNumFile;
	if ( PrefixDlg.DoModal() != IDOK )
		return FALSE;
	if ( PrefixDlg.m_szPrefix.GetLength() == 0)
		return FALSE;

	for(i=0; i<nModel; i++) {
		if (!strcmpi(PrefixDlg.m_szPrefix, pModel[i].szName)) {
			m_nCurModel = i;
			break;
		}
	}

	m_nCurFile = PrefixDlg.m_nNumber;
	strcpy( m_szPrefix, PrefixDlg.m_szPrefix );

	return m_nCurFile;
}

void CStroke::SetCurModelID( char* pszFile, MODEL* pModel, SHORT nModel )
{
	SHORT len;
	char szTName[10];
	int i;

	m_nCurModel = -1;
	char* pszBase = GetBaseName( pszFile );

	len = strlen( pszBase );
	for(i=0; i<len; i++) {
		if (pszFile[i] == '.') {
			szTName[i] = 0;
			break;
		} else
			szTName[i] = pszBase[i];
	}

	for(i=0; i<nModel; i++) {
		if ( !strcmpi(szTName, pModel[i].szName) ) {
			m_nCurModel = i;
			break;
		}
	}
}

BOOL CStroke::ChangeEditStroke( CRect* prc, MODEL* pModel, SHORT nModel )
{
	char		szTmp[20];
	CPrefixDlg	PrefixDlg;

	if ( !m_pFilelist->SplitFileName(m_nEditStroke, szTmp, &PrefixDlg.m_nNumber) )
		return FALSE;

	if (szTmp[0] == 'o' || szTmp[0] == 'O')
		PrefixDlg.m_szPrefix = &szTmp[1];
	else
		PrefixDlg.m_szPrefix = szTmp;

	if ( PrefixDlg.DoModal() != IDOK )
		return TRUE;
	if ( PrefixDlg.m_szPrefix.GetLength() == 0)
		return TRUE;

	SHORT nOldStroke = m_nEditStroke;
	char* pszFile = MakeMyDataName("Stroke\\o", PrefixDlg.m_szPrefix, PrefixDlg.m_nNumber);

	m_nCurPt = -1;
	if ( (m_nEditStroke = m_pFilelist->FindFileName(pszFile)) < 0 ) {
		m_nEditStroke = nOldStroke;
		return FALSE;
	}

	pszFile = m_pFilelist->GetFile(m_nEditStroke);

	if ( !Read( pszFile ) ) {
		m_nEditStroke = nOldStroke;
		SetStatusMessage( m_pFilelist->GetFile(m_nEditStroke) );
		MessageBeep(MB_OK);

		return FALSE;
	}

	SetCurModelID( pszFile, pModel, nModel );
	NormalizeStroke( &m_Buf, TRUE );
#	ifdef MAKE_CENTER
	CenterStroke( prc );
#	endif

	return TRUE;
}

BOOL CStroke::ChangeOnlineStroke( BOOL bOnline )
{
	char		szTmp[20];
	CPrefixDlg	PrefixDlg;

	if ( bOnline )
		sprintf( szTmp, "oonline" );
	else
		sprintf( szTmp, "oimm" );

	PrefixDlg.m_szPrefix = &szTmp[1];
	if ( m_nOnlineStroke < 0)
		PrefixDlg.m_nNumber = 0;
	else
		PrefixDlg.m_nNumber = m_nOnlineStroke;

	if ( PrefixDlg.DoModal() != IDOK )
		return TRUE;

	SHORT nOldStroke = m_nOnlineStroke;
	char* pszFile;
	
	m_nOnlineStroke = PrefixDlg.m_nNumber;
	if (bOnline)
		pszFile = MakeMyDataName("Online\\", "oonline", PrefixDlg.m_nNumber);
	else
		pszFile = MakeMyDataName("Online\\", "oimm", PrefixDlg.m_nNumber);

	if ( !Read( pszFile ) ) {
		m_nOnlineStroke = nOldStroke;
		SetStatusMessage( pszFile );
		MessageBeep(MB_OK);

		return FALSE;
	}

	return TRUE;
}

BOOL CStroke::NextOnlineStroke( SHORT nSkip )
{
	if (nSkip < 1)
		return FALSE;

	SHORT nMaxOnline = GetOnlineFileID( FALSE );
	SHORT nOldStroke = m_nOnlineStroke;
	char* pszFile;

	m_nOnlineStroke = (m_nOnlineStroke+nSkip) % nMaxOnline;
	pszFile = MakeMyDataName("Online\\", "oimm", m_nOnlineStroke);

	if ( !Read( pszFile ) ) {
		m_nOnlineStroke = nOldStroke;
		SetStatusMessage( pszFile );
		MessageBeep(MB_OK);

		return FALSE;
	}

	return TRUE;
}

BOOL CStroke::PrevOnlineStroke( SHORT nSkip )
{
	if (nSkip < 1)
		return FALSE;

	SHORT nMaxOnline = GetOnlineFileID( FALSE );
	SHORT nOldStroke = m_nOnlineStroke;
	char* pszFile;

	if (m_nOnlineStroke <= 0)
		m_nOnlineStroke = nMaxOnline;

	m_nOnlineStroke = (m_nOnlineStroke-nSkip) % nMaxOnline;
	pszFile = MakeMyDataName("Online\\", "oimm", m_nOnlineStroke);

	if ( !Read( pszFile ) ) {
		m_nOnlineStroke = nOldStroke;
		SetStatusMessage( pszFile );
		MessageBeep(MB_OK);

		return FALSE;
	}

	return TRUE;
}

void CStroke::DrawOnlineStroke( CView* pView )
{
	CRect	rc;
	CDC*	pDC;

	pView->GetClientRect( &rc );
	pDC = pView->GetDC();

	DrawStroke( pDC, &rc, FALSE, FALSE );
	char* pszFile = MakeMyDataName("Online\\", "oimm", m_nOnlineStroke);
	int nOldBk = pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut( 10, rc.bottom - 50, pszFile, strlen(pszFile) );
	pDC->SetBkMode(nOldBk);
	pView->ReleaseDC( pDC );
}

BOOL CStroke::Read( const char* pszFileName )
{
	FILE    *fp;
    
	if (!pszFileName)
		return FALSE;

	if( !(fp = fopen( pszFileName, "rb" )) ) {
		Warning( "(CStroke::Read) file <%s> not found", pszFileName );
		return( FALSE );
	}

	SetStatusMessage( "Reading stroke file %s ......", pszFileName );

	// write header (dx, dy, sin, cos)
	char* pszTmp = new char[MAX_BUFFER];

	MyRead( pszTmp, 1, MAGIC_SIZE, fp );
	if ( strcmp( pszTmp, cszStrokeMagic ) ) {
		delete[] pszTmp;
		Warning( "(CStroke::Read) invalid magic" );	
		fclose(fp);
		return FALSE;
	}
	delete[] pszTmp;

	MyRead( &m_Buf.nPt, sizeof(SHORT), 1, fp );
	if ( m_Buf.nPt <= 1) {
		Warning( "(CStroke::Read) invalid number of stroke points." );	
		fclose(fp);
		return FALSE;
	}

	m_Buf.rcBound.left = m_Buf.rcBound.top = 0;
	MyRead( &m_Buf.rcBound.right, sizeof(int), 1, fp );
	MyRead( &m_Buf.rcBound.bottom, sizeof(int), 1, fp );

	// For reading POINT structure {LONG, LONG}
	if ( !MyRead( m_Buf.pPt, sizeof(LONG), m_Buf.nPt*2, fp ) ) {
		Warning( "(CStroke::Read) invalid stroke points." );	
		fclose(fp);
		return FALSE;
	}

	fclose( fp );
	m_bNormalized = FALSE;

	return( TRUE );
}

BOOL CStroke::ReadText( const char* pszFileName )
{
	FILE    *fp;
    
	if (!pszFileName)
		return FALSE;

	if( !(fp = fopen( pszFileName, "r" )) ) {
		Warning( "(CStroke::ReadText) file <%s> not found", pszFileName );
		return( FALSE );
	}

	SetStatusMessage( "Reading stroke file %s ......", pszFileName );

	// write header (dx, dy, sin, cos)
	fscanf( fp, "# NumVector : %d\n", &m_Buf.nPt );
	if ( m_Buf.nPt <= 1) {
		Warning( "(CStroke::Read) invalid number of stroke points." );	
		fclose(fp);
		return FALSE;
	}

	fscanf( fp, "# Stroke : %d\n", &m_Buf.nPt );
	m_Buf.rcBound.left = m_Buf.rcBound.top = 0;
	fscanf( fp, "# (Width Height) : (%d %d)\n", 
			&m_Buf.rcBound.right, &m_Buf.rcBound.bottom );
	for( int i = 0; i < m_Buf.nPt ; i++ )
		fscanf( fp, "%4d %4d ", &m_Buf.pPt[i].x, &m_Buf.pPt[i].y );

	fclose( fp );
	m_bNormalized = FALSE;

	return( TRUE );
}

BOOL CStroke::Write( const char* pszFileName, const BOOL bUseNorm )
{
	SHORT	nPt;
	int		right, bottom;
	POINT*	pPt;
	FILE    *fp;

	if (!pszFileName)
		return FALSE;

	if( !(fp = fopen( pszFileName, "wb" )) ) {
		Warning( "(CStroke::Write) file <%s> not found", pszFileName );
		return( FALSE );
	}

	SetStatusMessage( "Writing stroke file %s ......", pszFileName );

	if (bUseNorm) {
		nPt = m_Norm.nPt;
		pPt = m_Norm.pPt;
		right  = m_Norm.rcBound.right;
		bottom = m_Norm.rcBound.bottom;
	} else {
		nPt = m_Buf.nPt;
		pPt = m_Buf.pPt;
		right  = m_Buf.rcBound.right;
		bottom = m_Buf.rcBound.bottom;
	}

	MyWrite( cszStrokeMagic, 1, MAGIC_SIZE, fp );
	MyWrite( &nPt, sizeof(SHORT), 1, fp );
	MyWrite( &right, sizeof(int), 1, fp );
	MyWrite( &bottom, sizeof(int), 1, fp );

	// For writing POINT structure {LONG, LONG}
	MyWrite( pPt, sizeof(LONG), nPt*2, fp );

	fclose( fp );

	return( TRUE );
}

BOOL CStroke::WriteText( const char* pszFileName, const BOOL bUseNorm )
{
	SHORT	nPt;
	int		right, bottom;
	POINT*	pPt;
	FILE    *fp;
	
	if (!pszFileName)
		return FALSE;

	if( !(fp = fopen( pszFileName, "w" )) ) {
		Warning( "(CStroke::WriteText) file <%s> not found", pszFileName );
		return( FALSE );
	}

	SetStatusMessage( "Writing stroke file %s ......", pszFileName );

	if (bUseNorm) {
		nPt = m_Norm.nPt;
		pPt = m_Norm.pPt;
		right  = m_Norm.rcBound.right;
		bottom = m_Norm.rcBound.bottom;
	} else {
		nPt = m_Buf.nPt;
		pPt = m_Buf.pPt;
		right  = m_Buf.rcBound.right;
		bottom = m_Buf.rcBound.bottom;
	}

	fprintf( fp, "# Stroke : %d\n", nPt );
	fprintf( fp, "# (Width Height) : (%d %d)\n", right, bottom );

	for( int i = 0; i < nPt ; i++ ) {
		fprintf( fp, "%4d %4d ", pPt[i].x, pPt[i].y );
		if ( i % 8 == 7)
			fputc( '\n', fp );
	}
	fputc( '\n', fp );
	fclose( fp );

	return( TRUE );
}

void CStroke::DrawLineSegment( CDC* pDC, POINT* pPt, SHORT nPt )
{
	CPen	newPen(PS_SOLID, 1, PenColor[nPt % 3]);
	CPen*	oldPen;

	oldPen = (CPen *)pDC->SelectObject((CPen*)&newPen);
	pDC->MoveTo( pPt[nPt-1].x, pPt[nPt-1].y );
	pDC->LineTo( pPt[nPt].x, pPt[nPt].y );
	pDC->SelectObject(oldPen);
}

void CStroke::StartStroke(POINT pt)
{
	m_Buf.nPt = 0;
	m_Buf.pPt[m_Buf.nPt++] = pt;
	m_Buf.rcBound.SetRect( pt.x, pt.y, pt.x, pt.y );
	m_bNormalized = FALSE;
}

BOOL CStroke::AddStroke(POINT pt, CDC* pDC)
{
	if (m_Buf.nPt >= MAX_POINTS || m_Buf.nPt <= 0)
		return FALSE;

	if ( m_Buf.pPt[m_Buf.nPt-1].x == pt.x &&
		 m_Buf.pPt[m_Buf.nPt-1].y == pt.y )
		 return TRUE;

	SetBoundingBox( &m_Buf.rcBound, pt );
	m_Buf.pPt[m_Buf.nPt] = pt;

	DrawLineSegment( pDC, m_Buf.pPt, m_Buf.nPt );

	m_Buf.nPt++;
	m_bNormalized = FALSE;

	return TRUE;
}

void CStroke::StartImmediateRecog(POINT pt)
{
	m_Buf.nPt = 0;
	m_Buf.pPt[m_Buf.nPt++] = pt;
	m_Buf.rcBound.SetRect( pt.x, pt.y, pt.x, pt.y );
	m_bNormalized = FALSE;
	m_rDist = 0.0;
}

CFVec* CStroke::MakeImmediateVector( SHORT nPoints )
{
	if ( nPoints < 3 )
		return NULL;

	MYSTROKE* pBuf = new MYSTROKE;

	pBuf->pPt = new POINT[MAX_POINTS];
	pBuf->nPt = nPoints;
	pBuf->pnFrameID = NULL;

	memcpy(pBuf->pPt, m_Buf.pPt, sizeof(POINT)*nPoints);
	RecalcBoundingBox( &(pBuf->rcBound), pBuf->pPt, nPoints );
	pBuf->pPrev = pBuf->pNext = NULL;

	if ( !FitCurrentStroke(pBuf, FALSE) ) {
		delete[] pBuf->pPt;
		delete pBuf;
		return NULL;
	}

	m_bNormalized = FALSE;
	m_rDist = 0.0;

	delete[] pBuf->pPt;
	delete pBuf;

	if (m_Norm.nPt < MIN_POINTS )
		return NULL;

	return StrokeToVector( TRUE );
}

CFVec* CStroke::AddImmediateRecog(POINT pt, CView* pView)
{
	if (m_Buf.nPt >= MAX_POINTS || m_Buf.nPt <= 0)
		return NULL;

	if ( m_Buf.pPt[m_Buf.nPt-1].x == pt.x &&
		 m_Buf.pPt[m_Buf.nPt-1].y == pt.y )
		 return NULL;

	SetBoundingBox( &m_Buf.rcBound, pt );

	REAL dx = pt.x - m_Buf.pPt[m_Buf.nPt-1].x;
	REAL dy = pt.y - m_Buf.pPt[m_Buf.nPt-1].y;
	m_rDist += sqrt(dx*dx + dy*dy);

	m_Buf.pPt[m_Buf.nPt] = pt;

	CDC* pDC = pView->GetDC();
	DrawLineSegment( pDC, m_Buf.pPt, m_Buf.nPt );
	pView->ReleaseDC( pDC );

	m_Buf.nPt++;
#ifdef OLD_IMMEDIATE
	if (m_rDist < (REAL)HEIGHT / NORMAL_GAP / 2.0)
		return NULL;

#	ifdef CLEAR_SCREEN
	ClearDisplay( pView );

	pDC = pView->GetDC();
	for ( int i=1; i<m_Buf.nPt; i++ )
		DrawLineSegment( pDC, m_Buf.pPt, i );
	pView->ReleaseDC( pDC );
#	endif

	return MakeImmediateVector( m_Buf.nPt );
#else
	return NULL;
#endif
}

void CStroke::PointToVector( CFVec* pFVec, SHORT nLoc, BOOL bUseNorm )
{
	SHORT	nPt;
	POINT*	pPt;
	REAL	dist, dx, dy;

	if (bUseNorm) {
		nPt = m_Norm.nPt;
		pPt = m_Norm.pPt;
	} else {
		nPt = m_Buf.nPt;
		pPt = m_Buf.pPt;
	}

	dx = pPt[nLoc+1].x - pPt[nLoc].x;
	dy = pPt[nLoc+1].y - pPt[nLoc].y;
	dist = sqrt( dx*dx + dy*dy );

#ifdef OLD_FEATURE
	pFVec->SetFeature( nLoc, 0, fabs(dx)/WIDTH );
	pFVec->SetFeature( nLoc, 1, fabs(dy)/HEIGHT );
	if (dist == 0.0)	{
		pFVec->SetFeature( nLoc, 2, 0.5 );	// sin
		pFVec->SetFeature( nLoc, 3, 0.5 );	// cos
	} else {
		pFVec->SetFeature( nLoc, 2, (1.0+dy/dist)/2.0 );	// sin
		pFVec->SetFeature( nLoc, 3, (1.0+dx/dist)/2.0 );	// cos
	}
#else
	if (dist == 0.0)	{
		pFVec->SetFeature( nLoc, 0, 0.5 );	// sin
		pFVec->SetFeature( nLoc, 1, 0.5 );	// cos
	} else {
		pFVec->SetFeature( nLoc, 0, (1.0+dy/dist)/2.0 );	// sin
		pFVec->SetFeature( nLoc, 1, (1.0+dx/dist)/2.0 );	// cos
	}
#endif
}

CFVec* CStroke::StrokeToVector( BOOL bUseNorm )
{
	SHORT	nPt;
	CFVec*	pFVec = new CFVec;	

	if (bUseNorm)
		nPt = m_Norm.nPt;
	else
		nPt = m_Buf.nPt;

	pFVec->New( nPt - 1, TEST_DIMENSION );
	// features (dx, dy, sin, cos)
	for( int i = 0; i < nPt-1 ; i++ )
		PointToVector( pFVec, i, bUseNorm );

	return pFVec;
}

BOOL CStroke::WriteFeatureVector( const char* pszFileName, BOOL bText )
{
	BOOL	bRet;
	CFVec*	pFVec = StrokeToVector( TRUE );

	if (bText)
		bRet = pFVec->WriteText( pszFileName );
	else
		bRet = pFVec->Write( pszFileName );

	delete pFVec;

	return bRet;
}
		
void CStroke::AddPointToNormalize( MYSTROKE* pBuf, REAL NFactor, 
								  SHORT nCurPt, SHORT* pPrev, BOOL bForced )
{
	SHORT	savecnt;
	SHORT	prev = *pPrev;
	REAL	dx, dy, dist, dist1, dist2;
	REAL	cosA;
	REAL	thresh = -0.8660254;	// cos 150
//	REAL	thresh = -0.7071068;	// cos 135
//	REAL	thresh = -0.5;			// cos 120

	dx = (REAL)(pBuf->pPt[nCurPt-1].x - pBuf->pPt[nCurPt].x);
	dy = (REAL)(pBuf->pPt[nCurPt-1].y - pBuf->pPt[nCurPt].y);
	dist1 = sqrt( dx*dx + dy*dy );

	if (!bForced) {
		dx = (REAL)(pBuf->pPt[nCurPt].x - pBuf->pPt[nCurPt+1].x);
		dy = (REAL)(pBuf->pPt[nCurPt].y - pBuf->pPt[nCurPt+1].y);
		dist2 = sqrt (dx*dx + dy*dy);

		dx = (REAL)(pBuf->pPt[nCurPt-1].x - pBuf->pPt[nCurPt+1].x);
		dy = (REAL)(pBuf->pPt[nCurPt-1].y - pBuf->pPt[nCurPt+1].y);
		dist = dx*dx + dy*dy;

		cosA = (dist1*dist1 + dist2*dist2 - dist) / (2.0*dist1*dist2);
	}

	if (cosA > thresh || bForced) {
		savecnt = m_Norm.nPt;
		for(int j=prev+1; j<=nCurPt; ) {
			REAL x1, y1, x2, y2;

			dx = (REAL)(m_Norm.pPt[m_Norm.nPt-1].x - pBuf->pPt[j].x);
			dy = (REAL)(m_Norm.pPt[m_Norm.nPt-1].y - pBuf->pPt[j].y);
			dist = sqrt (dx*dx + dy*dy);

			if (dist < NFactor) {
				j++;
			} else if (j == prev+1) {
				x1 = m_Norm.pPt[m_Norm.nPt-1].x;	
				y1 = m_Norm.pPt[m_Norm.nPt-1].y;
				x2 = pBuf->pPt[j].x;	
				y2 = pBuf->pPt[j].y;

				m_Norm.pPt[m_Norm.nPt].x = (int)(NFactor * (x2 - x1) / dist + x1);
				m_Norm.pPt[m_Norm.nPt].y = (int)(NFactor * (y2 - y1) / dist + y1);

				if (pBuf->pnFrameID && m_Norm.pnFrameID)
					m_Norm.pnFrameID[m_Norm.nPt] = pBuf->pnFrameID[j];
				SetBoundingBox( &m_Norm.rcBound, m_Norm.pPt[m_Norm.nPt] );

				m_Norm.nPt++;
			} else {
				REAL k, a, b, c, D;
				REAL x, y, tmp;

				// Equation passing (x1, y1) and (x2, y2)
				//		y =  k*(x - x1) + y1
				//		where k = (y2-y1)/(x2-x1)
				// Qudratic function: a*x*x + b*x + c = 0
				//		root: (-b +- sqrt(b*b - 4*a*c)) / (2*a)
				x  = m_Norm.pPt[m_Norm.nPt-1].x;	
				y  = m_Norm.pPt[m_Norm.nPt-1].y;
				x1 = pBuf->pPt[j-1].x;	y1 = pBuf->pPt[j-1].y;
				x2 = pBuf->pPt[j].x;	y2 = pBuf->pPt[j].y;

				if (x2 == x1) {
					a = 1;
					b = -2*y;
					c = y*y + x1*x1 - 2*x*x1 + x*x - NFactor*NFactor;

					D = sqrt( b*b - 4*a*c );

					tmp = (-b + D) / (2 * a);
					if ( ((y2 < y1) && (tmp < y2 || tmp > y1)) ||
						 ((y2 > y1) && (tmp > y2 || tmp < y1)) )
						tmp = (-b - D) / (2 * a);

					m_Norm.pPt[m_Norm.nPt].x = (int)x1;
					m_Norm.pPt[m_Norm.nPt].y = (int)tmp;
				} else {
					k =	  (y2 - y1)	/ (x2 - x1);
					a =	k*k + 1;
					b = -2 * ( x + k*k*x1 - k*y1 + k*y );
					c = x*x + k*k*x1*x1 + y1*y1 - 2*k*x1*y1 + 2*k*x1*y - 2*y*y1
						+ y*y - NFactor*NFactor;

					D = sqrt( b*b - 4*a*c );

					tmp = (-b + D) / (2 * a);
					if ( ((x2 < x1) && (tmp < x2 || tmp > x1)) ||
						 ((x2 > x1) && (tmp > x2 || tmp < x1)) )
						tmp = (-b - D) / (2 * a);

					m_Norm.pPt[m_Norm.nPt].x = (int)tmp;
					m_Norm.pPt[m_Norm.nPt].y = (int)(k*(tmp - x1) + y1);
				}

				if (pBuf->pnFrameID && m_Norm.pnFrameID)
					m_Norm.pnFrameID[m_Norm.nPt] = pBuf->pnFrameID[j];
				SetBoundingBox( &m_Norm.rcBound, m_Norm.pPt[m_Norm.nPt] );

				m_Norm.nPt++;
				prev = j - 1;
			}				
		}

		if ( /*savecnt != m_Norm.nPt &&*/ dist < (NFactor / 3.0) ) {
			m_Norm.pPt[m_Norm.nPt-1] = pBuf->pPt[nCurPt];
			if (pBuf->pnFrameID && m_Norm.pnFrameID)
				m_Norm.pnFrameID[m_Norm.nPt-1] = pBuf->pnFrameID[nCurPt];
		} else {
			m_Norm.pPt[m_Norm.nPt] = pBuf->pPt[nCurPt];
			if (pBuf->pnFrameID && m_Norm.pnFrameID)
				m_Norm.pnFrameID[m_Norm.nPt] = pBuf->pnFrameID[nCurPt];
			m_Norm.nPt++;
		}

		SetBoundingBox( &m_Norm.rcBound, pBuf->pPt[nCurPt] );

		prev = nCurPt;
	}
	*pPrev = prev;
}

BOOL CStroke::NormalizeStroke( MYSTROKE* pBuf, BOOL bFitBound )
{

	if ( m_bNormalized || pBuf->nPt < 3)
		return 0;

	REAL	NFactor;
	SHORT	prev = 0;

	if ( bFitBound ) {
		if (pBuf->rcBound.right > pBuf->rcBound.bottom)
			NFactor = (REAL)pBuf->rcBound.right / (REAL)NORMAL_GAP;
		else
			NFactor = (REAL)pBuf->rcBound.bottom / (REAL)NORMAL_GAP;
	} else {
//		NFactor = (REAL)pBuf->rcBound.bottom / (REAL)NORMAL_GAP;
//		NFactor = max( NFactor, (REAL)HEIGHT/NORMAL_GAP/2.0 );
		NFactor = (REAL)HEIGHT/NORMAL_GAP/1.5;
	}

	m_Norm.nPt = 0;
	m_Norm.pPt[m_Norm.nPt++] = pBuf->pPt[0];

	m_Norm.rcBound.left	  = pBuf->pPt[0].x;
	m_Norm.rcBound.top	  = pBuf->pPt[0].y;
	m_Norm.rcBound.right  = pBuf->pPt[0].x;
	m_Norm.rcBound.bottom = pBuf->pPt[0].y;

	for(SHORT i=1; i<pBuf->nPt-1; i++)
		AddPointToNormalize( pBuf, NFactor, i, &prev, FALSE );
	AddPointToNormalize( pBuf, NFactor, pBuf->nPt-1, &prev, TRUE );

	m_bNormalized = TRUE;

	return pBuf->nPt;
}

void CStroke::FitToRect( MYSTROKE* pBuf, CRect rcFit, BOOL bFitBound )
{
	int		i, left, top, xx, yy;
	SHORT	count = 0;
	REAL	ratio;

	// Recalculate bounding box
	pBuf->rcBound.left = pBuf->rcBound.right = pBuf->pPt[0].x;
	pBuf->rcBound.top = pBuf->rcBound.bottom = pBuf->pPt[0].y;
	for(i=1; i<pBuf->nPt; i++)
		SetBoundingBox( &(pBuf->rcBound), pBuf->pPt[i] );

	left = pBuf->rcBound.left;
	top  = pBuf->rcBound.top ;
	pBuf->rcBound.OffsetRect( rcFit.left - pBuf->rcBound.left, 
							  rcFit.top  - pBuf->rcBound.top );

	if (bFitBound) {
		REAL rx, ry;

		rx = (REAL)(rcFit.right - rcFit.left) 
			/ (pBuf->rcBound.right - pBuf->rcBound.left);
		ry = (REAL)(rcFit.bottom - rcFit.top) 
			/ (pBuf->rcBound.bottom - pBuf->rcBound.top);

		if (rx < ry) ratio = rx;
		else ratio = ry;
	} else {
		ratio = 1.0;
	}

	pBuf->rcBound.left	 = rcFit.left;
	pBuf->rcBound.top    = rcFit.top;
	pBuf->rcBound.right	 = rcFit.left;
	pBuf->rcBound.bottom = rcFit.top;

	for (i=0; i<pBuf->nPt; i++) {
		xx = (int)((pBuf->pPt[i].x - left) * ratio) + rcFit.left;
		yy = (int)((pBuf->pPt[i].y - top) * ratio)  + rcFit.top;
		if ( count == 0 || (count > 0 && ((abs(xx - pBuf->pPt[count-1].x) > 2)
									   || (abs(yy - pBuf->pPt[count-1].y) > 2))))
		{
			pBuf->pPt[count].x = xx;
			pBuf->pPt[count].y = yy;
			SetBoundingBox( &(pBuf->rcBound), pBuf->pPt[count] );
			count++;
		}
	}
	pBuf->nPt = count;
}

BOOL CStroke::FitCurrentStroke( MYSTROKE* pBuf, BOOL bFitBound )
{
	CRect rcFit( 0, 0, WIDTH, HEIGHT );
	FitToRect( pBuf, rcFit, bFitBound );

	return NormalizeStroke( pBuf, bFitBound );
}

void CStroke::UpdateNormalizedStroke()
{
	if (m_bNormalized)
		return;

	MYSTROKE* pBuf = new MYSTROKE;
	pBuf->pPrev = m_Buf.pPrev;
	pBuf->pNext = m_Buf.pNext;
	pBuf->nPt = m_Buf.nPt;
	pBuf->pPt = new POINT[MAX_POINTS];
	memcpy( pBuf->pPt, m_Buf.pPt, sizeof(POINT)*MAX_POINTS );
	pBuf->rcBound.CopyRect( &m_Buf.rcBound );
	pBuf->pnFrameID = NULL;

	FitCurrentStroke( pBuf, TRUE );

	delete[] pBuf->pPt;
	delete pBuf;
}

void CStroke::AddHandPosition( POINT pt, SHORT nCurFrame )
{
	SHORT	prev = 0;
	REAL	NFactor = (REAL)HEIGHT/NORMAL_GAP/1.5;

	if ( m_Buf.nPt == 0 || m_Buf.pPt[m_Buf.nPt-1].x != pt.x || 
		 m_Buf.pPt[m_Buf.nPt-1].y != pt.y ) {
		m_Buf.pPt[m_Buf.nPt] = pt;
		if (m_Buf.pnFrameID && nCurFrame >= 0)
			m_Buf.pnFrameID[m_Buf.nPt] = nCurFrame;
		m_Buf.nPt++;
	}

	if (m_Norm.nPt == 0) {
		m_Norm.rcBound.left	  = pt.x;
		m_Norm.rcBound.top	  = pt.y;
		m_Norm.rcBound.right  = pt.x;
		m_Norm.rcBound.bottom = pt.y;
		m_Norm.pPt[m_Norm.nPt] = pt;
		if (m_Norm.pnFrameID && nCurFrame >= 0)
			m_Norm.pnFrameID[m_Norm.nPt] = nCurFrame;
		m_Norm.nPt++;
		return;
	}

	if (m_Buf.nPt < 3)
		return;

	AddPointToNormalize( &m_Buf, NFactor, m_Buf.nPt-2, &prev, FALSE );

	if (prev > 0) {
		for(int i=prev; i<m_Buf.nPt; i++) {
			m_Buf.pPt[i-prev] = m_Buf.pPt[i];
			if (m_Buf.pnFrameID)
				m_Buf.pnFrameID[i-prev] = m_Buf.pnFrameID[i];
		}
		m_Buf.nPt -= prev;
	}
}

// Add remaining input points to normalized buffer
void CStroke::FlushHandPosition()
{
	SHORT	prev = 0;
	REAL	NFactor = (REAL)HEIGHT/NORMAL_GAP/1.5;

	if (m_Norm.nPt == 0 || m_Buf.nPt < 2)
		return;

	AddPointToNormalize( &m_Buf, NFactor, m_Buf.nPt-1, &prev, TRUE );
	m_Buf.nPt = 0;
}

CFVec* CStroke::EndOnlineStroke( CView* pView, BOOL bDrawNormal, BOOL bPaint )
{
	if (m_Buf.nPt <= 1)
		return NULL;

	if ( !bPaint )
		ClearDisplay( pView );

	CDC* pDC = pView->GetDC();
	for ( int i=1; i<m_Buf.nPt; i++ )
		DrawLineSegment( pDC, m_Buf.pPt, i );
	pView->ReleaseDC( pDC );

	FitCurrentStroke( &m_Buf, FALSE );

	if ( bDrawNormal ) {
		pDC = pView->GetDC();
		DrawNormalizedStroke( pDC );
		pView->ReleaseDC( pDC);
	}
	
	return StrokeToVector( TRUE );
}

SHORT CStroke::GetOnlineFileID( BOOL bOnline )
{
	int		nID;
	FILE*	fp;
	
	if ( bOnline )
		fp = fopen(MakeMyFileName("Online\\", "ID.on"), "r");
	else
		fp = fopen(MakeMyFileName("Online\\", "ID.imm"), "r");

	if ( !fp )
		return 0;

	fscanf(fp, "%d", &nID);
	fclose( fp );

	return ( (SHORT)nID );
}

void CStroke::SetOnlineFileID( BOOL bOnline, SHORT nID )
{
	FILE*	fp;
	
	if ( bOnline )
		fp = fopen(MakeMyFileName("Online\\", "ID.on"), "w");
	else
		fp = fopen(MakeMyFileName("Online\\", "ID.imm"), "w");

	fprintf(fp, "%d\n", nID);
	fclose( fp );
}

BOOL CStroke::SaveOnlineStroke( BOOL bOnline )
{
	SHORT nOnlineID;

	FitCurrentStroke( &m_Buf, FALSE );

	nOnlineID = GetOnlineFileID( bOnline );
	if ( bOnline )
		Write( MakeMyDataName("Online\\", "oonline", nOnlineID), FALSE );
	else
		Write( MakeMyDataName("Online\\", "oimm", nOnlineID), FALSE );

	nOnlineID++;
	SetOnlineFileID( bOnline, nOnlineID );

	return TRUE;
}

void CStroke::EndStroke( CView* pView, BOOL bDrawNormal )
{
	if (m_Buf.nPt <= 1)
		return;

	FitCurrentStroke( &m_Buf, TRUE );

	if ( bDrawNormal ) {
		CDC* pDC = pView->GetDC();
		DrawNormalizedStroke( pDC );
		pView->ReleaseDC( pDC);
	}

	MYSTROKE* newStroke = new MYSTROKE;

	newStroke->nPt = m_Buf.nPt;
	newStroke->pPt = new POINT[m_Buf.nPt];
	newStroke->pnFrameID = NULL;

	newStroke->rcBound = m_Buf.rcBound;
	memcpy( newStroke->pPt, m_Buf.pPt, m_Buf.nPt * sizeof(POINT) );

	newStroke->pPrev = m_pCurStroke;
	newStroke->pNext = NULL;
	if (!m_pCurStroke)
		m_pStartStroke = newStroke;
	else
		m_pCurStroke->pNext = newStroke;

	Write( MakeMyDataName("Stroke\\", m_szPrefix, m_nCurFile), TRUE );
	Write( MakeMyDataName("Stroke\\o", m_szPrefix, m_nCurFile), FALSE );
//	WriteText( MakeMyDataName("Stroke\\t", m_szPrefix, m_nCurFile) );
	WriteFeatureVector( MakeMyDataName("RawData\\", m_szPrefix, m_nCurFile), FALSE );
//	WriteFeatureVector( MakeMyDataName("RawData\\t", m_szPrefix, m_nCurFile), TRUE );
	
	m_nCurFile++;

	m_Buf.nPt = 0;
	m_pCurStroke = newStroke;
}

void CStroke::DrawEditMark( CDC* pDC, POINT pt, SHORT nLoc, BOOL bNorm )
{
	CBrush	newBrush( RGB((nLoc == 0) ? 255 : 0, 0, 0) );
	CBrush	normBrush( MY_BLUE );
	CBrush* oldBrush;

	oldBrush = (CBrush *)pDC->SelectObject( (CBrush *)&newBrush );
	if (bNorm && nLoc != 0)
		pDC->SelectObject( (CBrush *)&normBrush );

	if (nLoc == 0)	// Stroke starting point
		pDC->Ellipse( pt.x - PICK_SIZE, pt.y - PICK_SIZE,
					  pt.x + PICK_SIZE, pt.y + PICK_SIZE );
	else
		pDC->Rectangle( pt.x - MARK_SIZE, pt.y - MARK_SIZE,
						pt.x + MARK_SIZE, pt.y + MARK_SIZE );

	pDC->SelectObject( oldBrush );
}

void CStroke::DrawStroke( CDC* pDC, CRect* prc, BOOL bEdit, BOOL bShowNormal )
{
	int   i;

	for ( i=1; i<m_Buf.nPt; i++ )
		DrawLineSegment( pDC, m_Buf.pPt, i );
//	pDC->Polyline( m_Buf.pPt, m_Buf.nPt );
	
	for ( i=0; i<m_Buf.nPt; i++ )
		DrawEditMark( pDC, m_Buf.pPt[i], i, FALSE );

	if ( bShowNormal )
		DrawNormalizedStroke( pDC );

	if (bEdit && m_pFilelist) {
		char* pszFile = m_pFilelist->GetFile(m_nEditStroke);
		if (pszFile) {
			int nOldBk = pDC->SetBkMode(TRANSPARENT);
			pDC->TextOut( 10, prc->bottom - 50, pszFile, strlen(pszFile) );
			pDC->SetBkMode(nOldBk);
		}
	}
}

void CStroke::DrawNormalizedStroke( CDC* pDC )
{
	int i;

	for ( i=1; i<m_Norm.nPt; i++ )
		DrawLineSegment( pDC, m_Norm.pPt, i );

	for ( i=0; i<m_Norm.nPt; i++ )
		DrawEditMark( pDC, m_Norm.pPt[i], i, TRUE );
}

void CStroke::CenterStroke( CRect* prc )
{
	int left = max( 0, (prc->right  - m_Buf.rcBound.right ) / 2 );
	int top  = max( 0, (prc->bottom - m_Buf.rcBound.bottom) / 2 );
	int i;

	if (left == 0 && top == 0)
		return;

	m_Buf.rcBound.OffsetRect( left, top );
	for (i=0; i<m_Buf.nPt; i++ ) {
		m_Buf.pPt[i].x += left;
		m_Buf.pPt[i].y += top ;
	}
}

BOOL CStroke::StartEditStroke( CView* pView, MODEL* pModel, SHORT nModel )
{
	if (m_pFilelist)
		delete m_pFilelist;

	m_pFilelist = new CFilelist( MakeMyFileName("Stroke\\", "Stroke.dat") );

	if (!m_pFilelist)
		return FALSE;

	m_nCurPt = -1;
	m_nEditStroke = m_nCurFile = 0;
	char* pszFile = m_pFilelist->GetFile(m_nEditStroke);

	if ( !Read( pszFile ) ) {
		Warning( "(CStroke::StartEditStroke) read error" );
		return FALSE;
	}

	SetCurModelID( pszFile, pModel, nModel );
	NormalizeStroke( &m_Buf, TRUE );

#	ifdef MAKE_CENTER
	CRect rc;
	pView->GetClientRect( &rc );
	CenterStroke( &rc );
#	endif

	return TRUE;
}

BOOL CStroke::SaveEditStroke()
{
	char*	pszFile;
	int		loc=0, len, i;

	FitCurrentStroke( &m_Buf, TRUE );

	pszFile = m_pFilelist->GetFile(m_nEditStroke);

	len = strlen( pszFile );
	for( i=len-1; i>=0; i-- ) {
		if (pszFile[i] == '\\' || pszFile[i] == '/') {
			loc = i + 1;
			break;
		}
	}

	if (pszFile[loc] == 'O' || pszFile[loc] == 'o')
		loc++;

	WriteFeatureVector( MakeMyFileName("RawData\\", &pszFile[loc]), FALSE );
	Write( MakeMyFileName("Stroke\\", &pszFile[loc]), TRUE );
	Write( MakeMyFileName("Stroke\\o", &pszFile[loc]), FALSE );

	return TRUE;
}

BOOL CStroke::SaveFrameStroke(SHORT nInputType, SHORT nDumpID)
{
	FitCurrentStroke( &m_Buf, FALSE );

	Write( MakeMyDumpFeatureName("Stroke\\", nInputType, nDumpID), TRUE );
	Write( MakeMyDumpFeatureName("Stroke\\o", nInputType, nDumpID), FALSE );
	WriteFeatureVector( MakeMyDumpFeatureName("RawData\\", nInputType, nDumpID), FALSE );

	return TRUE;
}

BOOL CStroke::EditNextStroke( CRect* prc, SHORT nSkip, MODEL* pModel, SHORT nModel )
{
	if (nSkip < 1)
		return FALSE;

	m_nCurPt = -1;
	m_nEditStroke = (m_nEditStroke+nSkip) % m_pFilelist->m_nFile;
	char* pszFile = m_pFilelist->GetFile(m_nEditStroke);

	if ( !Read( pszFile ) ) {
		if (m_nEditStroke < nSkip)
			m_nEditStroke = m_pFilelist->m_nFile + m_nEditStroke - 1;
		m_nEditStroke = (m_nEditStroke-nSkip) % m_pFilelist->m_nFile;
		SetStatusMessage( m_pFilelist->GetFile(m_nEditStroke) );
		MessageBeep(MB_OK);

		return FALSE;
	}

	SetCurModelID( pszFile, pModel, nModel );
	NormalizeStroke( &m_Buf, TRUE );
#	ifdef MAKE_CENTER
	CenterStroke( prc );
#	endif

	return TRUE;
}

BOOL CStroke::EditPrevStroke( CRect* prc, SHORT nSkip, MODEL* pModel, SHORT nModel )
{
	m_nCurPt = -1;
	if (m_nEditStroke < nSkip)
		m_nEditStroke = m_pFilelist->m_nFile + m_nEditStroke - 1;
	m_nEditStroke = (m_nEditStroke-nSkip) % m_pFilelist->m_nFile;
	char* pszFile = m_pFilelist->GetFile(m_nEditStroke);

	if ( !Read( pszFile ) ) {
		m_nEditStroke = (m_nEditStroke+nSkip) % m_pFilelist->m_nFile;
		SetStatusMessage( m_pFilelist->GetFile(m_nEditStroke) );
		MessageBeep(MB_OK);

		return FALSE;
	}

	SetCurModelID( pszFile, pModel, nModel );
	NormalizeStroke( &m_Buf, TRUE );
#	ifdef MAKE_CENTER
	CenterStroke( prc );
#	endif

	return TRUE;
}

BOOL CStroke::CheckEditMark( POINT pt )
{
	int i;

	m_nCurPt = -1;

	for (  i=0; i<m_Buf.nPt; i++ ) {
		CRect rc( m_Buf.pPt[i].x - PICK_SIZE, m_Buf.pPt[i].y - PICK_SIZE,
				  m_Buf.pPt[i].x + PICK_SIZE, m_Buf.pPt[i].y + PICK_SIZE );

		if ( rc.PtInRect( pt ) ) {
			m_nCurPt = i;
			break;
		}
	}

	return (m_nCurPt >= 0);
}

void CStroke::DrawInverseSelection( CDC* pDC )
{
	int	oldR2 = pDC->SetROP2( R2_NOTXORPEN );

	if (m_nCurPt > 0)
		DrawLineSegment( pDC, m_Buf.pPt, m_nCurPt );
	if (m_nCurPt < m_Buf.nPt-1)
		DrawLineSegment( pDC, m_Buf.pPt, m_nCurPt+1 );
	DrawEditMark( pDC, m_Buf.pPt[m_nCurPt], m_nCurPt, FALSE );

	pDC->SetROP2( oldR2 );
}

BOOL CStroke::AppendOnePoint( POINT pt )
{
	int i;

	if (m_Buf.nPt >= MAX_POINTS || m_Buf.nPt <= 0)
		return FALSE;

	for( i=m_Buf.nPt; i>m_nCurPt; i-- )
		m_Buf.pPt[i] = m_Buf.pPt[i-1];
	
	m_Buf.nPt++;
	m_nCurPt++;
	m_bNormalized = FALSE;

	return TRUE;
}

void CStroke::StartMovePoint( CDC* pDC )
{
	DrawInverseSelection( pDC );
}

void CStroke::UpdateMovePoint( CDC* pDC, POINT pt )
{
	DrawInverseSelection( pDC );
	m_Buf.pPt[m_nCurPt] = pt;
	DrawInverseSelection( pDC );
	m_bNormalized = FALSE;
}

void CStroke::DeleteEditPoint()
{
	int i;

	if ( m_Buf.nPt <= 2 ) {
		MessageBeep(MB_OK);
		return;
	}

	for( i=m_nCurPt; i<m_Buf.nPt-1; i++)
		m_Buf.pPt[i] = m_Buf.pPt[i+1];

	m_Buf.nPt--;
	m_bNormalized = FALSE;
}

void CStroke::GetNewFeature( CFVec* pFVec )
{
	POINT Pt[2];
	REAL dx, dy, dist;

	Pt[0].x = (int) ((float)rand() / (float)RAND_MAX * WIDTH);
	Pt[0].y = (int) ((float)rand() / (float)RAND_MAX * HEIGHT);
	Pt[1].x = (int) ((float)rand() / (float)RAND_MAX * WIDTH);
	Pt[1].y = (int) ((float)rand() / (float)RAND_MAX * HEIGHT);

	dx = Pt[1].x - Pt[0].x;
	dy = Pt[1].y - Pt[0].y;
	dist = sqrt( dx*dx + dy*dy );

	if (dist == 0.0)	{
		pFVec->SetFeature( 0, 0, 0.5 );	// sin
		pFVec->SetFeature( 0, 1, 0.5 );	// cos
	} else {
		pFVec->SetFeature( 0, 0, (1.0+dy/dist)/2.0 );	// sin
		pFVec->SetFeature( 0, 1, (1.0+dx/dist)/2.0 );	// cos
	}
}

void CStroke::ResaveAllStroke( CView* pView )
{
	CRect rc;
	int i;

	pView->GetClientRect( &rc );

	for (i=m_nEditStroke; i < m_pFilelist->m_nFile; i++) {
		m_nEditStroke = i;
		if ( !Read(m_pFilelist->GetFile(i)) ) {
			SetStatusMessage( m_pFilelist->GetFile(i) );
			MessageBeep(MB_OK);
		}

		NormalizeStroke( &m_Buf, TRUE );
#	ifdef MAKE_CENTER
		CenterStroke( &rc );
#	endif

		ClearDisplay();
//		if ( !WaitMoment( 10000, FALSE ) )
//			break;

		SaveEditStroke();
	}
}

void CStroke::RepositionTrace( POINT ptLoc )
{
	int nOffX, nOffY;

	nOffX = ptLoc.x - m_Buf.rcBound.left;
	nOffY = ptLoc.y - m_Buf.rcBound.top;

	CRect rcFit( ptLoc.x, ptLoc.y, 
				 m_Buf.rcBound.right + nOffX, m_Buf.rcBound.bottom + nOffY );
	FitToRect( &m_Buf, rcFit, FALSE );
}

void CStroke::ClearTraceDraw( CView* pView, CMetaFileDC* pMetaDC )
{
	CDC* pDC = pView->GetDC();
	CDC* pTmpDC = pMetaDC ? (CDC*)pMetaDC : pDC;
	int i;

	for ( i=1; i<m_Buf.nPt; i++ ) {
		pTmpDC->MoveTo( m_Buf.pPt[i-1].x, m_Buf.pPt[i-1].y );
		pTmpDC->LineTo( m_Buf.pPt[i].x, m_Buf.pPt[i].y );
	}
	
	for ( i=0; i<m_Buf.nPt; i++ ) {
		CBrush	newBrush( RGB((i == 0) ? 255 : 0, 0, 0) );
		CBrush* oldBrush;

		oldBrush = (CBrush *)pDC->SelectObject( (CBrush *)&newBrush );
		if ( pMetaDC )
			pMetaDC->SelectObject( (CBrush *)&newBrush );

		if (i == 0)	{// Stroke starting point
			pTmpDC->Ellipse( m_Buf.pPt[i].x - PICK_SIZE, 
							 m_Buf.pPt[i].y - PICK_SIZE,
							 m_Buf.pPt[i].x + PICK_SIZE, 
							 m_Buf.pPt[i].y + PICK_SIZE );
		} else {
			pTmpDC->Rectangle( m_Buf.pPt[i].x - MARK_SIZE, 
							   m_Buf.pPt[i].y - MARK_SIZE,
							   m_Buf.pPt[i].x + MARK_SIZE, 
							   m_Buf.pPt[i].y + MARK_SIZE );
		}

		pDC->SelectObject( oldBrush );
		if ( pMetaDC )
			pMetaDC->SelectObject( oldBrush );
	}
	
	pView->ReleaseDC( pDC );
}

void CStroke::PrepareTrace( char* pszStrokeFile, 
						    const POINT* pPt, const SHORT nPt )
{
	m_Buf.nPt = 0;
	if ( pszStrokeFile ) {
		if ( !Read(MakeMyFileName("Stroke\\", pszStrokeFile)) )
			return;
	} else {
		if ( !pPt )
			return;
		memcpy( m_Buf.pPt, pPt, sizeof(POINT)*nPt );
		m_Buf.nPt = nPt;
	}
}

void CStroke::DrawTraceLine( CView* pView, CMetaFileDC* pMetaDC,
							 SHORT nLine )
{
	if ( m_Buf.nPt < 1)
		return;

	CDC* pDC = pView->GetDC();

	CPen*	oldPen;
	CPen	newPen(PS_SOLID, 1, PenColor[(nLine+1) % 3]);
	CDC*	pTmpDC = pMetaDC ? (CDC*)pMetaDC : pDC;

	oldPen = (CPen *)pDC->SelectObject((CPen*)&newPen);
	if ( pMetaDC )
		pMetaDC->SelectObject((CPen*)&newPen);

	pTmpDC->MoveTo( m_Buf.pPt[nLine].x, m_Buf.pPt[nLine].y );
	pTmpDC->LineTo( m_Buf.pPt[nLine+1].x, m_Buf.pPt[nLine+1].y );

	pDC->SelectObject(oldPen);
	if ( pMetaDC )
		pMetaDC->SelectObject(oldPen);

	pView->ReleaseDC( pDC );
}

void DrawPointLabel( CView* pView, CDC* pDC, POINT ptLoc, SHORT nLabel )
{
	char	 szTmp[10];

	pDC->Ellipse( ptLoc.x-3, ptLoc.y-3, ptLoc.x+3, ptLoc.y+3 );
	pDC->MoveTo( ptLoc.x, ptLoc.y );

	ptLoc.y += 3;
	sprintf( szTmp, "%d", nLabel );
	DrawMyText( pDC, pView, ptLoc, TRANSPARENT, 
				ALIGN_LRCENTER | ALIGN_TOP, FALSE, FALSE, FSIZE_NORMAL, szTmp );
	
}

void CStroke::CalcSpotBoundingRect( CView* pView, CRect* prc )
{
	CRect	 rcFit;

	pView->GetClientRect( &rcFit );
	rcFit.left    = 150;
//	rcFit.top     = 600;
	rcFit.right   = rcFit.left + m_Norm.rcBound.right;
	rcFit.bottom  -= 10;
	rcFit.top	  = rcFit.bottom - 100;

	CStroke* pTmp = new CStroke;
	memcpy( pTmp->m_Buf.pPt, m_Norm.pPt, sizeof(POINT)*m_Norm.nPt );
	pTmp->m_Buf.nPt = m_Norm.nPt;
	pTmp->m_Buf.rcBound = m_Norm.rcBound;
	pTmp->FitToRect( &(pTmp->m_Buf), rcFit, TRUE );
	
	prc->left   = pTmp->m_Buf.rcBound.left  - 15;
	prc->top    = pTmp->m_Buf.rcBound.top   - 15;
	prc->right  = pTmp->m_Buf.rcBound.right + 15;
	prc->bottom = pTmp->m_Buf.rcBound.bottom+ 15;

	delete pTmp;
}

void CStroke::DrawSpottingResult( CMetaFileDC* pMetaDC, CView* pView, 
					RECOUT* pRecogOut, SHORT nRecogOut, SHORT nDrawT,
					MODEL* pModel, SHORT nThresholdModel )
{
	CStroke* pTmp;
	CRect	 rcFit;
	extern	 COLORREF rgbGraph[6];
	CPen	 *newPen, *oldPen;
	CDC*	 pDC;
	int      i, j;

	pView->GetClientRect( &rcFit );
	rcFit.left    = 150;
	rcFit.right   = rcFit.left + m_Norm.rcBound.right;
	rcFit.bottom -= 10;
	rcFit.top     = rcFit.bottom - 100;

	pTmp = new CStroke;
	memcpy( pTmp->m_Buf.pPt, m_Norm.pPt, sizeof(POINT)*m_Norm.nPt );
	pTmp->m_Buf.nPt = m_Norm.nPt;
	pTmp->m_Buf.rcBound = m_Norm.rcBound;
	pTmp->FitToRect( &(pTmp->m_Buf), rcFit, TRUE );

	if (pMetaDC)
		pDC = pMetaDC;
	else
		pDC = pView->GetDC();

	DrawPointLabel( pView, pDC, pTmp->m_Buf.pPt[0], 0 );

	newPen = new CPen( PS_SOLID, 1, MY_BLACK );
	oldPen = (CPen *)pDC->SelectObject( newPen );
	for(i=1; i<pTmp->m_Buf.nPt; i++) {
		pDC->LineTo(pTmp->m_Buf.pPt[i].x, pTmp->m_Buf.pPt[i].y);
		pDC->Ellipse( pTmp->m_Buf.pPt[i].x-3, pTmp->m_Buf.pPt[i].y-3,
					  pTmp->m_Buf.pPt[i].x+3, pTmp->m_Buf.pPt[i].y+3 );
		if ( (i % 5) == 0 )
			DrawPointLabel( pView, pDC, pTmp->m_Buf.pPt[i], i );

		if (nDrawT > 0 && i >= nDrawT)
			break;
	}
	pDC->SelectObject( oldPen );
	delete newPen;

	for(i=0; i<nRecogOut; i++) {
		if ( pRecogOut[i].nModel < 0 || pRecogOut[i].nModel >= nThresholdModel )
			continue;

		COLORREF	rgbOld;
		CBrush		*newBrush, *oldBrush;

		pRecogOut[i].nStartT = min(pRecogOut[i].nStartT, pTmp->m_Buf.nPt-1);
		pRecogOut[i].nEndT = min(pRecogOut[i].nEndT, pTmp->m_Buf.nPt-1);

		if (m_Norm.pnFrameID) {
			PrintProgressString("%s: %d(%d) %d(%d) %d(%d)", 
					pModel[pRecogOut[i].nModel].szName,
					pRecogOut[i].nStartT, m_Norm.pnFrameID[pRecogOut[i].nStartT],
					pRecogOut[i].nFirstEndT, m_Norm.pnFrameID[pRecogOut[i].nFirstEndT],
					pRecogOut[i].nEndT, m_Norm.pnFrameID[pRecogOut[i].nEndT] );
		} else {
			PrintProgressString("%s: %d %d %d", 
					pModel[pRecogOut[i].nModel].szName,
					pRecogOut[i].nStartT, 
					pRecogOut[i].nFirstEndT, 
					pRecogOut[i].nEndT );
		}

		newPen = new CPen( PS_SOLID, 1, rgbGraph[pRecogOut[i].nModel] );
		oldPen = (CPen *)pDC->SelectObject( newPen );

		newBrush = new CBrush( rgbGraph[pRecogOut[i].nModel] );
		oldBrush = (CBrush *)pDC->SelectObject( newBrush );
		rgbOld = pDC->SetTextColor( rgbGraph[pRecogOut[i].nModel] );
		DrawPointLabel( pView, pDC, pTmp->m_Buf.pPt[pRecogOut[i].nStartT], 
						pRecogOut[i].nStartT );
		pDC->SelectObject( oldBrush );
		delete newBrush;

		pDC->MoveTo( pTmp->m_Buf.pPt[pRecogOut[i].nStartT].x, 
					 pTmp->m_Buf.pPt[pRecogOut[i].nStartT].y );
		for(j=pRecogOut[i].nStartT+1; j<=pRecogOut[i].nEndT; j++) {
			pDC->LineTo( pTmp->m_Buf.pPt[j].x, pTmp->m_Buf.pPt[j].y );
			if ( j != pRecogOut[i].nEndT && pRecogOut[i].nFirstEndT == j )
				DrawPointLabel( pView, pDC, pTmp->m_Buf.pPt[j], j ); 
		}
		DrawPointLabel( pView, pDC, pTmp->m_Buf.pPt[pRecogOut[i].nEndT], 
						pRecogOut[i].nEndT );
		pDC->SetTextColor( rgbOld );

		pDC->SelectObject( oldPen );
		delete newPen;
	}
	
	if ( !pMetaDC )
		pView->ReleaseDC( pDC );

	delete pTmp;
}

BOOL CStroke::PointToStroke( POINT* pPt, SHORT nPt )
{
	if (nPt < MIN_POINTS) {
		return FALSE;
	}

	memcpy(m_Buf.pPt, pPt, sizeof(POINT)*nPt);
	m_Buf.nPt = nPt;
	m_bNormalized = FALSE;
	RecalcBoundingBox( &m_Buf.rcBound, m_Buf.pPt, nPt );

	return TRUE;
}

