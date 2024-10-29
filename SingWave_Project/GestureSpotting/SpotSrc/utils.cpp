// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
//#define _WIN32_WINNT	_WIN32_WINNT_MAXVER    // by hklee
#include "Spot.h"

#include <memory.h>
#include <stdarg.h>
#include <math.h>

// #include "utils.h"
// #include "GestureDoc.h"
// #include "GestureView.h"
// #include "SpotDoc.h"
// #include "SpotView.h"
// #include "CMyMIL.h"

#include "CMyMIL.h"
#include "SpotDoc.h"
#include "SpotView.h"
#include "GestureDoc.h"
#include "GestureView.h"
#include "utils.h"

#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>

char   szUtilBuf[256];

double lStartTm[10];
double lElapsedTm[10];

void StartCheck(int n)
{
	struct _timeb tm;
	
	_ftime(&tm);
	lStartTm[n] = (double)tm.time * 1000. + (double)tm.millitm;
}


double EndCheck(int n)
{
	struct _timeb tm;
	
	_ftime(&tm);
	lElapsedTm[n] = (double)tm.time * 1000. + (double)tm.millitm - lStartTm[n];
	return lElapsedTm[n];
}

void Mfree(void *ptr)
{
	if (ptr)
		delete[] ptr;
}

void Mfree(void **pptr, int nY)
{
	if (!pptr)
		return;

	for(int i=0; i<nY; i++)
		Mfree((void*)pptr[i]);

	Mfree((void*)pptr);
}

void Mfree(void*** ppptr, int nZ, int nY)
{
	if (!ppptr)
		return;

	for(int i=0; i<nZ; i++)
		Mfree((void**)ppptr[i], nY);

	Mfree((void*)ppptr);
}

REAL*	MallocREAL( int nX, REAL* pReal)
{
	if (nX < 1)
		return NULL;

	pReal = new REAL[nX];
	memset( pReal, 0, sizeof(REAL) * nX );

	return pReal;
}

REAL**	MallocREAL( int nY, int nX)
{
	int i;
	REAL **pptr;

	if (nY < 1 || nX < 1)
		return NULL;
	
	pptr = new REAL*[nY];
	for (i=0; i<nY; i++)
		pptr[i] = MallocREAL(nX, pptr[i]);

	return (pptr);
}

SHORT*	MallocSHORT( int nX, SHORT* pSHORT )
{
	if (nX < 1)
		return NULL;

	pSHORT = new SHORT[nX];
	memset( pSHORT, 0, sizeof(SHORT) * nX );

	return pSHORT;
}

SHORT**	MallocSHORT( int nY, int nX )
{
	int i;
	SHORT **pptr;

	if (nY < 1 || nX < 1)
		return NULL;
	
	pptr = new SHORT*[nY];
	for (i=0; i<nY; i++)
		pptr[i] = MallocSHORT(nX, pptr[i]);

	return (pptr);
}

BYTE* MallocBYTE(int nX)
{
	BYTE* ptr;

	if (nX < 1)
		return NULL;

	ptr = new BYTE[nX];
	memset(ptr, 0, nX);

	return ptr;
}

BYTE** MallocBYTE(int nY, int nX)
{
	BYTE** pptr;

	if (nY < 1 || nX < 1)
		return NULL;

	pptr = new BYTE*[nY];
	for(int i=0; i<nY; i++)
		pptr[i] = MallocBYTE(nX);

	return pptr;
}

BYTE*** MallocBYTE(int nZ, int nY, int nX)
{
	BYTE*** ppptr;

	if (nY < 1 || nX < 1 || nZ < 1)
		return NULL;

	ppptr = new BYTE**[nZ];
	for(int i=0; i<nZ; i++)
		ppptr[i] = MallocBYTE(nY, nX);

	return ppptr;
}

// File I/O related functions
FILE* OpenListFile( const char *pszListFile, SHORT *pnModel, 
					 SHORT *pnData )
{
	int		Mdl, Dat;
	FILE*	fp;

	*pnModel = -1;
	*pnData = 0;
	if( !(fp = fopen( pszListFile, "r" )) ) 
	{
		Warning( "(OpenFileList) file <%s> not found", pszListFile );
		return( NULL );
	}

	if( !fscanf( fp, "# Label : %d\n", &Mdl ) ||
		!fscanf( fp, "# NumData : %d\n", &Dat ) )
	{
		Warning( "(OpenFileList) invalid list files" );
		fclose( fp );
		return( NULL );
	}
	*pnModel = (SHORT)Mdl;
	*pnData  = (SHORT)Dat;

	if ( *pnModel < 0 || *pnData <= 0 )
	{
		Warning( "(OpenFileList) invalid label" );
		fclose( fp );
		*pnModel = -1;
		*pnData = 0;
		return( NULL );
	}

	return ( fp );
}

BOOL GetData( SHORT **ppnData, SHORT *pnData, SHORT *pnTime, 
				SHORT nCodeSize, FILE* fp )
{
	int		i, j;
	int		count, Dat;

	for ( i=0; i<*pnData; i++ )
	{
		if( !fscanf( fp, "%d", &count ) )
		{
			*pnData = i;
			return( FALSE );
		}
		if ( count <= 0 )
		{
			*pnData = i;
			return( FALSE );
		}
		
		ppnData[i] = MallocSHORT((int)count);
		for( j=0; j<count; j++ )
		{
			if( !fscanf( fp, "%d", &Dat ) )
			{
				*pnData = i;
				pnTime[i] = j;
				return( FALSE );
			}

			ppnData[i][j] = Dat;
			if ( ppnData[i][j] < 0 || ppnData[i][j] >= nCodeSize )
			{
				*pnData = i;
				pnTime[i] = j;
				return( FALSE );
			}
		}
		pnTime[i] = (SHORT)count;
	}
	
	return( TRUE );
}

size_t MyRead( void* pData, SHORT nSize, SHORT nData, FILE* fp )
{
	if (!pData)
		return 0;

	if ( (SHORT)fread(pData, nSize, nData, fp) != nData )
		return 0;

	return nData;
}

size_t MyWrite( const void* pData, SHORT nSize, SHORT nData, FILE* fp )
{
	if (!pData)
		return 0;

	if ( (SHORT)fwrite(pData, nSize, nData, fp) != nData )
		return 0;

	return nData;
}

void Warning( const char *pszFmt, ... )
{
	va_list	argptr;

	va_start( argptr, pszFmt );
	vsprintf( szUtilBuf, pszFmt, argptr );

	MessageBox( NULL, szUtilBuf, "Warning", MB_OK );
}

CGestureView* GetMyView(CDocument* pDoc)
{
	CGestureView* 	pView = NULL;
	POSITION		pos = pDoc->GetFirstViewPosition();

	if ( pos != NULL )
		pView = (CGestureView *)pDoc->GetNextView( pos );
	return( pView );
}

BOOL IsValidRange( const SHORT nMax, const SHORT nStart, const SHORT nEnd )
{
  if( nStart < 0 || nEnd > nMax || ( nEnd >= 0 && nStart > nEnd ) )
    return( FALSE );
  return( TRUE );
}

void SetStatusMessage( const char *pszFmt, ... ) 
{
	va_list	argptr;

	if (!IsWindow(theStatus->m_hWnd))
		return;

	va_start( argptr, pszFmt );
	vsprintf( szUtilBuf, pszFmt, argptr );
	
	theStatus->SetWindowText( szUtilBuf );
}


////////////////////////////////////////////////////////////////////////////
// Routines for display information

static CView* theView		= NULL;
static SHORT  nCurLine		= 0;
static SHORT  nCurCol		= 0;

#define START_MARGIN		20
#define END_MARGIN			10
#define TEXT_HT				15
#define LINE_HT				(TEXT_HT)

#define MIN_ELIPSED_TIME	3000.0

#define SAVE_MESSAGE		1
#define MAX_LINE_WIDTH		(TEXT_HT * 80)
static  BOOL bFirstSave = TRUE;

BOOL ProcessOtherMessage()
{
	MSG msg;

	while (PeekMessage((LPMSG)&msg, NULL, 0, 0, PM_REMOVE)) {
		switch (msg.message) {
			case WM_CHAR:
				if (msg.wParam == 'q' || msg.wParam == 'Q')
					return FALSE;
				break;
			case WM_RBUTTONDOWN:
			case WM_DESTROY:
			case WM_CLOSE:
			case WM_QUERYENDSESSION:
				return FALSE;
			default:
				break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return TRUE;
}

BOOL WaitMoment( double dTimeLimit, BOOL bClear )
{
	BOOL bLoop = TRUE;
	MSG msg;

	if ( dTimeLimit <= NO_WAIT )
		return TRUE;

	SetStatusMessage( "Press any key to continue" ) ;

	if ( dTimeLimit > 0)
		StartCheck(0);

	while (bLoop) {
		while (PeekMessage((LPMSG)&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			switch (msg.message) {
				case WM_CHAR:
					bLoop = FALSE;
					if (msg.wParam == 'q' || msg.wParam == 'Q')
						return FALSE;
					break;
				case WM_COMMAND:
					if (msg.wParam != IDM_FINISH_GRAB)
						break;
				case WM_RBUTTONDOWN:
				case WM_DESTROY:
				case WM_CLOSE:
				case WM_QUERYENDSESSION:
					return FALSE;
				default:
					break;
			}
		}
		if (dTimeLimit > 0 && EndCheck(0) >= dTimeLimit)
			bLoop = FALSE;
	}
	SetStatusMessage( "" ) ;
	if (bClear && theView)
		ClearDisplay( theView );

	return TRUE;
}

SHORT GetTotalLines()
{
	SHORT	nTotLines;
	RECT	rc;

	if (!theView)
		return (0);

	theView->GetClientRect((LPRECT)&rc);
	nTotLines = (rc.bottom - rc.top - START_MARGIN - END_MARGIN) / LINE_HT;
	nTotLines = max( 1, nTotLines );

	return( nTotLines );
}

void ClearDisplay( CView* pView )
{
	theView = pView;
	if (!pView || !IsWindow(pView->m_hWnd))
		return;

	pView->InvalidateRect(NULL, TRUE);
	pView->UpdateWindow();
	nCurLine = 0;
	nCurCol = 0;
}

void ClearDisplay()
{
	if (!theView || !IsWindow(theView->m_hWnd))
		return;

	theView->InvalidateRect(NULL, TRUE);
	theView->UpdateWindow();
	nCurLine = 0;
	nCurCol = 0;
}

BOOL PrepareSpace( SHORT nLines )
{
	SHORT	nTotLines;
	
	if (!theView)
		return TRUE;

	nTotLines = GetTotalLines();
	if (nCurLine + nLines > nTotLines) {
		if ( !WaitMoment( 1000.0, TRUE ) ) {
			ClearDisplay( theView );
			return FALSE;
		}
		ClearDisplay( theView );
	}
	nCurCol = 0;

	return (TRUE);
}

LOGFONT lfText = { 0, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
			ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS,
			"Arial"
	};

CFont* CreateMyFont( SHORT nSize, BOOL bSymbol )
{
	CFont*	newFont;
	
	if (bSymbol) {
		lfText.lfCharSet = SYMBOL_CHARSET;
		lfText.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
		strcpy( lfText.lfFaceName, "Symbol" );
	} else {
		lfText.lfCharSet = ANSI_CHARSET;
		lfText.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
		strcpy( lfText.lfFaceName, "Arial" );
	}

	newFont = new CFont;

	lfText.lfHeight = nSize;
	newFont->CreateFontIndirect( &lfText );

	return newFont;
}

CSize GetMyStringExtent( CView* pView, char* pszStr, BOOL bSymbol )
{
	CSize	sizeStr;
	CFont	*newFont, *oldFont;

	newFont = CreateMyFont( 15, bSymbol );
	CDC* pScrDC = pView->GetDC();
	oldFont = pScrDC->SelectObject( newFont );
	sizeStr  = pScrDC->GetTextExtent( pszStr, strlen(pszStr) );
	pScrDC->SelectObject( oldFont );
	pView->ReleaseDC( pScrDC );
	delete newFont;

	return sizeStr;
}

void DrawMyText( CDC* pDC, CView* pView, POINT pt, int nBkMode, int nAlign, 
				BOOL bEraseBk, BOOL bSymbol, SHORT nFSize, char* pszStr )
{
	int		 X, Y;
	COLORREF rgbOldColor;
	CFont	 *newFont, *oldFont;
	CSize	 sizeStr, sizeZero;

	newFont = CreateMyFont( nFSize, bSymbol );

	CDC* pScrDC = pView->GetDC();
	oldFont = pScrDC->SelectObject( newFont );
	sizeStr  = pScrDC->GetTextExtent( pszStr, strlen(pszStr) );
	if ( nBkMode == OPAQUE && bEraseBk )
		sizeZero = pScrDC->GetTextExtent( "0000.00", 7 );			
	pScrDC->SelectObject( oldFont );
	pView->ReleaseDC( pScrDC );

	X = pt.x;
	if ( nAlign & ALIGN_RIGHT )
		X = pt.x - sizeStr.cx;
	else if ( nAlign & ALIGN_LRCENTER )
		X = pt.x - sizeStr.cx / 2;
	
	Y = pt.y;
	if ( nAlign & ALIGN_BOTTOM )
		Y = pt.y - sizeStr.cy;
	else if ( nAlign & ALIGN_TBCENTER )
		Y = pt.y - sizeStr.cy / 2;

	oldFont = pDC->SelectObject( newFont );
	int	nOldBk = pDC->SetBkMode(nBkMode);

	if ( nBkMode == OPAQUE ) {
		rgbOldColor = pDC->SetBkColor( MY_WHITE );
		if ( bEraseBk ) {
			CRect rc(pt.x, Y, pt.x + sizeZero.cx, Y + sizeZero.cy);

			rc.left = pt.x;
			if ( nAlign & ALIGN_RIGHT )
				rc.left = pt.x - sizeZero.cx;
			else if ( nAlign & ALIGN_LRCENTER )
				rc.left = pt.x - sizeZero.cx / 2;
			rc.right = rc.left + sizeZero.cx;

			pDC->ExtTextOut( rc.left, rc.top, ETO_OPAQUE, 
							&rc, " ", 1, NULL );
		}
	}

	pDC->TextOut( X, Y, pszStr, strlen(pszStr) );
	pDC->SetBkMode( nOldBk );

	if ( nBkMode == OPAQUE )
		pDC->SetBkColor( rgbOldColor );

	pDC->SelectObject( oldFont );
	delete newFont;
}

BOOL PutString( const char *pszStr, BOOL bNewLine ) 
{
	if (!theView)
		return TRUE;

	int		nOldBk;
	CSize	sz;
	CFont	*newFont, *oldFont;
	CDC*	pDC = theView->GetDC();

	newFont = new CFont;
	lfText.lfHeight = TEXT_HT;
	newFont->CreateFontIndirect( &lfText );
	oldFont = pDC->SelectObject( newFont );

	sz = pDC->GetTextExtent( pszStr, strlen(pszStr));
	if (bNewLine) {
		if ( !PrepareSpace(1) ) return FALSE;
	} else if ( (nCurCol + sz.cx) > MAX_LINE_WIDTH ) {
		nCurLine++;
		if ( !PrepareSpace(1) ) return FALSE;
		nCurCol = START_MARGIN * 2;
	}

	nOldBk = pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut( nCurCol + START_MARGIN, nCurLine*LINE_HT + START_MARGIN,
			pszStr, strlen(pszStr) );
	pDC->SelectObject( oldFont );
	pDC->SetBkMode(nOldBk);

	theView->ReleaseDC( pDC );

	delete newFont;

#ifdef SAVE_MESSAGE
	FILE* fp;

	if (bFirstSave)
		fp = fopen( MakeMyFileName( "Model\\", "Message.txt" ), "w" );
	else
		fp = fopen( MakeMyFileName( "Model\\", "Message.txt" ), "a" );

	bFirstSave = FALSE;
	if (fp) {
		if ((nCurCol + sz.cx) > MAX_LINE_WIDTH)
			fprintf(fp, "\n");
		fprintf(fp, "%s", pszStr);
		if (bNewLine)
			fprintf(fp, "\n");
		fclose(fp);
	}
#endif

	if (bNewLine) {
		nCurLine++;
		nCurCol = 0;
	} else
		nCurCol += (SHORT)sz.cx;
	
	return ProcessOtherMessage();
}

BOOL PrintProgressString( const char *pszFmt, ... ) 
{
	va_list	argptr;

	va_start( argptr, pszFmt );
	vsprintf( szUtilBuf, pszFmt, argptr );

	return PutString( szUtilBuf, TRUE );
}

BOOL PutProgressString( const char *pszFmt, ... ) 
{
	va_list	argptr;

	va_start( argptr, pszFmt );
	vsprintf( szUtilBuf, pszFmt, argptr );

	return PutString( szUtilBuf, FALSE );
}

BOOL PutProgressNumber( const REAL dNum ) 
{
	char cBuf[50];

	sprintf(cBuf, "(%g), ", dNum);
	return PutString( cBuf, FALSE );
}

static char szFilePath[MAX_BUFFER];
static char szBaseDir[MAX_BUFFER];

void SetBaseDir( char* pszBaseDirName )
{
	strcpy( szBaseDir, pszBaseDirName );
	CorrectDirDelimeter( szBaseDir );
}

char* GetBaseDir()
{
	return szBaseDir;
}

char* MakeMyFileName( const char* pszMidName, const char* pszFileName, 
					  const char* pszExtName )
{
	if ( pszExtName ) {
		sprintf( szFilePath, "%s%s%s.%s", szBaseDir, pszMidName, 
				 pszFileName, pszExtName );
	} else {
		sprintf( szFilePath, "%s%s%s", szBaseDir, pszMidName, pszFileName );
	}
	CorrectDirDelimeter( szFilePath );
	
	return szFilePath;
}

char* MakeMyDataName( const char* pszMidName, const char* pszPrefix, SHORT nFileID )
{
	sprintf( szFilePath, "%s%s%s.%03d", szBaseDir, pszMidName, 
					pszPrefix, nFileID );
	CorrectDirDelimeter( szFilePath );
	
	return szFilePath;
}

char* MakeMyMetaName( const char* pszMidName, const char* pszPrefix, SHORT nMetaID )
{
	sprintf( szFilePath, "%s%s%s%03d.wmf", szBaseDir, pszMidName, 
					pszPrefix, nMetaID );
	CorrectDirDelimeter( szFilePath );
	
	return szFilePath;
}


#ifdef MORE_MODEL
	char *szDumpType[MAX_INPUTTYPE] = { "Last", "First", "Next", "Prev", "Quit", 
					"Bye", "Cir", "Tri", "Saw", "Alpha", 
					"Etc", "Cont" };
//	char *szModelFullName[MODEL_THRESHOLD+1] = { "Last", "First", "Next", "Previous", 
//					"Quit", "Bye", "Circle", "Triangle", "Saw", "Alpha", "Threshold" };
	char *szModelFullName[MODEL_THRESHOLD+1] = { "last", "first", "next", "previous", 
					"start", "bye", "white", "black", "hidden", "stop", "threshold" };
#else
	char *szDumpType[MAX_INPUTTYPE] = { "Last", "First", "Next", "Prev", "Quit", 
					"Etc", "Cont" };
	char *szModelFullName[MODEL_THRESHOLD+1] = { "Last", "First", "Next", "Previous", "Quit", 
					"Threshold" };
#endif

char* GetModelName( SHORT nModel )
{
	if (nModel < 0 || nModel > MODEL_TEST)
		return NULL;

	return (szDumpType[nModel]);
}

char* GetModelFullName( SHORT nModel )
{
	if (nModel < 0 || nModel > MODEL_THRESHOLD)
		return NULL;

	return (szModelFullName[nModel]);
}

char* MakeMyResultName( SHORT nKind )
{
	CSpotView*	pView = (CSpotView *)theMIL->m_theView;
	CSpotDoc*	pDoc = (CSpotDoc *)pView->GetDocument();
	SHORT		nDumpType = pDoc->m_nInputType;
	SHORT		nDumpID = pDoc->m_nDumpID;

	if (nDumpType < 0 || nDumpType > MODEL_TEST || nDumpID < 0 )
		return NULL;

	switch( nKind ) {
	case NAME_LABEL:
		sprintf( szFilePath, "%s%s\\%s%03d.lab", szBaseDir, szDumpType[nDumpType], 
				szDumpType[nDumpType], nDumpID );
		break;
	case NAME_RECOGOUT:
		sprintf( szFilePath, "%s%s\\%s%03d.rec", szBaseDir, szDumpType[nDumpType], 
				szDumpType[nDumpType], nDumpID );
		break;
	case NAME_RESULT:
		sprintf( szFilePath, "%s%s\\%s.out", szBaseDir, szDumpType[nDumpType], 
				szDumpType[nDumpType] );
		break;
	case NAME_LOCATION:
		sprintf( szFilePath, "%s%s\\%s%03d.loc", szBaseDir, szDumpType[nDumpType], 
				szDumpType[nDumpType], nDumpID );
		break;
	}
	CorrectDirDelimeter( szFilePath );
	
	return szFilePath;
}

char* MakeMyDumpName( SHORT nDumpType, SHORT nDumpID )
{
	sprintf( szFilePath, "%s%s\\%s%03d.frm", szBaseDir, szDumpType[nDumpType], 
				szDumpType[nDumpType], nDumpID );
	CorrectDirDelimeter( szFilePath );
	
	return szFilePath;
}

char* MakeMyDumpFeatureName( const char* pszMidName, SHORT nDumpType, SHORT nDumpID )
{
	sprintf( szFilePath, "%s%s%s.%03d", szBaseDir, pszMidName, 
				szDumpType[nDumpType], nDumpID );
	CorrectDirDelimeter( szFilePath );
	
	return szFilePath;
}

char* MakeMyDumpIDName( SHORT nDumpType )
{
	sprintf( szFilePath, "%s%s\\%s.ID", szBaseDir, szDumpType[nDumpType], 
				szDumpType[nDumpType] );
	CorrectDirDelimeter( szFilePath );
	
	return szFilePath;
}

void GetDumpFileInform( const char* pszFullName, SHORT* nType, SHORT* nID )
{
	char* pszBase = GetBaseName( pszFullName );
	char szTmp[8];
	int	 i, j;

	for (i = 0; i < 3; i++) 
		szTmp[i] = pszBase[i];
	if (pszBase[i] < '0' || pszBase[i] > '9') {
		szTmp[i] = pszBase[i];
		i++;
		if (pszBase[i] < '0' || pszBase[i] > '9') {
			szTmp[i] = pszBase[i];
			i++;
		}
	}
	
	szTmp[i] = 0;

	for(j=0; j<MAX_INPUTTYPE; j++) {
		if ( !strcmpi(szTmp, szDumpType[j]) ) {
			*nType = j;
			break;
		}
	}

	if (*nType >= MAX_INPUTTYPE)
		*nType = MAX_INPUTTYPE-1;

	if ( pszBase[i+0] >= '0' && pszBase[i+0] <= '9' ||
		 pszBase[i+1] >= '0' && pszBase[i+1] <= '9' ||
		 pszBase[i+2] >= '0' && pszBase[i+2] <= '9') {

		*nID = pszBase[i++] - '0';
		*nID = *nID * 10 + pszBase[i++] - '0';
		*nID = *nID * 10 + pszBase[i++] - '0';
	} else
		*nID = -1;
}

SHORT GetDumpFileID(SHORT nInputType)
{
	int		nID;
	FILE*	fp;
	
	fp = fopen(MakeMyDumpIDName(nInputType), "r");

	if ( !fp )
		return 0;

	fscanf(fp, "%d", &nID);
	fclose( fp );

	return ( (SHORT)nID );
}

void SetDumpFileID( SHORT nInputType, SHORT nID )
{
	FILE*	fp;
	
	fp = fopen(MakeMyDumpIDName(nInputType), "w");

	fprintf(fp, "%d\n", nID);
	fclose( fp );
}

char* GetBaseName( const char* pszFullName )
{
	int		loc = 0, len = strlen( pszFullName );

	for( int i=len-1; i>=0; i-- ) {
		if (pszFullName[i] == '\\' || pszFullName[i] == '/') {
			loc = i + 1;
			break;
		}
	}

	return &((char*)pszFullName)[loc];
}

void CorrectDirDelimeter( char* pszPath )
{
	int	len = strlen( pszPath );

	for( int i=0; i<len; i++ ) {
		if (pszPath[i] == '/')
			pszPath[i] = '\\';
	}
}

int Dir_fprintf( FILE* fp, const char* fmt, ... )
{
	char	szStr[MAX_BUFFER];
	va_list	argptr;

	va_start( argptr, fmt );
	vsprintf( szStr, fmt, argptr );
	CorrectDirDelimeter( szStr );

	return fprintf( fp, "%s", szStr );
}

int Dir_sprintf( char* pszBuf, const char* fmt, ... )
{
	char	szStr[MAX_BUFFER];
	va_list	argptr;

	va_start( argptr, fmt );
	vsprintf( szStr, fmt, argptr );
	CorrectDirDelimeter( szStr );

	return sprintf( pszBuf, "%s", szStr );
}
