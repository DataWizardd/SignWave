////////////////////////////////////////////////////////////////////////////
//
//         Programmed by Yun, YoungSun (ysyun@bulsai.kaist.ac.kr)
//
//                  Spoken Language Lab. CS, KAIST
//
//                        Date : 1995/Fall
//
///////////////////////////////////////////////////////////////////////////

#ifndef	_CVQ_H
#define	_CVQ_H

#include "Cfvec.h"

class CVQ {
public:
	// constructor && deconstructor
	CVQ();
	~CVQ();

	// attributes
private:
	CFVec*	m_pfvec;

public:
	SHORT	m_nLevel;	// the number of level (codebook size)
	SHORT	m_nDim;		// dimensionality
	CFVec	m_fCodebook;
  
	// operations
public:

	// size & dimension
	SHORT   GetSize() 	{ return( m_nLevel ); }
	SHORT   GetDimension()  { return( m_nDim ); }

	// codebook read/write using feature vector's function
	BOOL	Read( const char* pszFileName );
	BOOL	ReadText( const char* pszFileName );
	BOOL	Write( const char* pszFileName );
	BOOL	WriteText( const char* pszFileName );

	// find the closest codebook entry in terms of Euclidean distance by
	// performing a sequentioal search (with some prunning)
	SHORT	Lookup( const REAL* pVector );
	SHORT	Lookup( const REAL* pVector, const SHORT nDim, const SHORT nCode,
					REAL* pBestDist );

	// generate the VQ codebook from nVector samples of dimensionality nDim
	BOOL	GenCodebook( CFVec& fvector, const SHORT nDLevel );

	// if the wave file list are given, generate the VQ codebook from files
	BOOL	GenCodebook( CFilelist& filelist,
					const SHORT nDim, const SHORT nDLevel );
	BOOL	GenCodebook( class CFVec* pFVec, const SHORT nFVec, 
					const SHORT nDLevel );

private:
	// resize/create the codebook
	BOOL	NewCodebook( const SHORT nLevel, const SHORT nDim );
	void	Initialize();
	void	Initialize( CFilelist& filelist );
	void	Initialize( class CFVec* pFVec, SHORT nFVec );
	void	CleanTempspace( SHORT* pnSum, REAL** pprSum,
					const SHORT nCode, const SHORT nDim );
	void	SplitCodebook( const SHORT nCode, const SHORT nNewCode );
	REAL	Classify( const SHORT nCode, SHORT* pnSum, REAL** pprSum );
	REAL	Classify( CFilelist& filelist, const SHORT nCode,
					SHORT* pnSum, REAL** pprSum );
	REAL	Classify( class CFVec* pFVec, const SHORT nFVec, const SHORT nCode,
					SHORT* pnSum, REAL** pprSum );
	void	Reestimate( const SHORT nCode, SHORT* pnSum, REAL** pprSum );
	REAL	Update( const SHORT  nCode, const REAL rPrevDist,
					SHORT* pnSum, REAL** pptSum );
	REAL	Update( CFilelist& filelist, const SHORT nCode,
					const REAL rPrevDist, SHORT* pnSum, REAL** pptSum );
	REAL	Update( class CFVec* pFVec, const SHORT nFVec, const SHORT nCode,
					const REAL rPrevDist, SHORT* pnSum, REAL** pprSum );
};

#endif
