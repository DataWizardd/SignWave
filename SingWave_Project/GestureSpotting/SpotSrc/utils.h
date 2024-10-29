#ifndef	_UTILS_H
#define	_UTILS_H

#include "values.h"

#define FSIZE_SMALL		12
#define FSIZE_NORMAL	15
#define FSIZE_LARGE		20

#define NO_WAIT			0.0
#define SHORT_WAIT		1000.0
#define NORMAL_WAIT		10000.0
#define LONG_WAIT		60000.0

const	REAL FLOATRESN  = 0.000001;
const	REAL cMinREAL   = ( sizeof(REAL) == sizeof(float) ?
									MINFLOAT : MINDOUBLE );
const	REAL cMaxREAL   = ( sizeof(REAL) == sizeof(float) ?
									MAXFLOAT : MAXDOUBLE );
#define	LOG_RESOLUTION		1000

#define ALIGN_LEFT		0x01
#define ALIGN_RIGHT		0x02
#define ALIGN_LRCENTER	0x04
#define ALIGN_TOP		0x10
#define ALIGN_BOTTOM	0x20
#define ALIGN_TBCENTER	0x40

#define NAME_LABEL		0
#define NAME_RECOGOUT	1
#define NAME_RESULT		2
#define NAME_LOCATION	3

#define MY_BLACK		RGB(  0,   0,   0)
#define MY_WHITE		RGB(255, 255, 255)
#define MY_GRAY			RGB(128, 128, 128)
#define MY_PASSED		MY_WHITE

#define MY_RED			RGB(255,   0,   0)
#define MY_GREEN		RGB(  0, 255,   0)
#define MY_BLUE			RGB(  0,   0, 255)
#define MY_SKYBLUE		RGB(  0, 255, 255)
#define MY_YELLOW		RGB(255, 255,   0)
#define MY_PINK			RGB(255,   0, 255)
#define MY_GRAYRED		RGB(255, 128, 128)
#define MY_LIGHTPINK	RGB(255, 128, 128)
#define MY_PURPLE		RGB(128,   0, 128)
#define MY_DARKGREEN	RGB(  0, 128, 128)
#define MY_LIGHTPURPLE	RGB(128, 128, 255)
#define MY_ORANGE		RGB(255, 128,   0)


/* utils.cpp */
// Time elapsed checking routine
void	StartCheck(int n);
double	EndCheck(int n);

REAL*	MallocREAL( int nX, REAL* pReal=NULL );
REAL**	MallocREAL( int nY, int nX );
SHORT*	MallocSHORT( int nX, SHORT* pInt=NULL );
SHORT**	MallocSHORT( int nY, int nX );
BYTE*	MallocBYTE(int nX);
BYTE**	MallocBYTE(int nY, int nX);
BYTE*** MallocBYTE(int nZ, int nY, int nX);
void	Mfree( void *ptr );
void	Mfree( void **pptr, int nY );
void	Mfree( void ***pptr, int nZ, int nY );

void	Warning( const char *pszFmt, ... );
BOOL	IsValidRange( const SHORT nMax, const SHORT nStart, const SHORT nEnd );
void	SetStatusMessage( const char *pszFmt, ... ); 
BOOL	WaitMoment( double dTimeLimit, BOOL bClear );

/* io */
		// Get observation sequences for training or testing */
		//	  *ppnData	: Array of observation sequence, 2-D
		//	  *pnData	: Number of observation sequences
		//	  *pnTime	: Array for length of observation sequence
BOOL	GetData( SHORT **ppnData, SHORT *pnData, SHORT *pnTime, 
					SHORT nCodeSize, FILE* fp );
FILE*	OpenListFile( const char *pszListFile, SHORT *pnModel, 
					SHORT *pnData );
size_t	MyRead( void* pData, SHORT nSize, SHORT nData, FILE* fp );
size_t	MyWrite( const void* pData, SHORT nSize, SHORT nData, FILE* fp );

void	SetBaseDir( char* pszBaseDirName );
char*	GetBaseDir();
char*	MakeMyFileName( const char* pszMidName, const char* pszFileName,
					    const char* pszExtName=NULL );
char*	MakeMyDataName( const char* pszMidName, const char* pszPrefix, 
					   SHORT nFileID );
char*	MakeMyMetaName( const char* pszMidName, const char* pszPrefix, 
					   SHORT nMetaID );

// For files for dumped frames
char*	GetModelName( SHORT nModel );
char*	GetModelFullName( SHORT nModel );
char*	MakeMyResultName( SHORT nKind );
char*	MakeMyDumpName( SHORT nDumpType, SHORT nDumpID );
char*	MakeMyDumpFeatureName( const char* pszMidName, 
							  SHORT nDumpType, SHORT nDumpID );
char*	MakeMyDumpIDName( SHORT nDumpType );
void	GetDumpFileInform( const char* pszFullName, SHORT* nType, SHORT* nID );
SHORT	GetDumpFileID(SHORT nInputType);
void	SetDumpFileID( SHORT nInputType, SHORT nID );
char*	MakeMyLabelName( SHORT nDumpType, SHORT nDumpID );

char*	GetBaseName( const char* pszFullName );
void	CorrectDirDelimeter( char* pszPath );
int		Dir_fprintf( FILE* fp, const char* fmt, ... );
int		Dir_sprintf( char* pszBuf, const char* fmt, ... );

// Display message on display
class	CGestureView*	GetMyView(CDocument* pDoc);

void	ClearDisplay( CView* pView );
void	ClearDisplay();
BOOL	PrepareSpace( SHORT nLines );
BOOL	ProcessOtherMessage();
CFont*	CreateMyFont( SHORT nSize, BOOL bSymbol );
CSize	GetMyStringExtent( CView* pView, char* pszStr, BOOL bSymbol );
void	DrawMyText( CDC* pDC, CView* pView, POINT pt, int nBkMode, int nAlign, 
				   BOOL bEraseBk, BOOL bSymbol, SHORT nFSize, char* pszStr );

CDC*	GetMyDC( CView* pView );
CMetaFileDC* InitMetaFileDC( CView* pView, CRect* pRect );
REAL	GetLogOnePixel( CView* pView );
BOOL	ExportMetafile( CDC* pDC, HENHMETAFILE hMetaBit, 
					   char* pszFile, CRect* prc );

BOOL	PrintProgressString( const char *pszFmt, ... ) ;
BOOL	PutProgressString( const char *pszStr, ... ) ;
BOOL	PutProgressNumber( const REAL dNum ); 

#endif



