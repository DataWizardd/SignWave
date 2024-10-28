////////////////////////////////////////////////////////////////////////////
//
//         Programmed by Yun, YoungSun (ysyun@bulsai.kaist.ac.kr)
//
//                  Spoken Language Lab. CS, KAIST
//
//                        Date : 1996/Spring
//
///////////////////////////////////////////////////////////////////////////

#ifndef	_CMGVQ_H
#define	_CMGVQ_H

#include "Cvq.h"

class CMGVQ {	// Mixture Gaussian VQ
public:
	// constructor && deconstructor
	CMGVQ();
	~CMGVQ();

	// attributes
public:
	CFVec	m_fMean;	// mean     [level][dim]
	CFVec	m_fVar;		// variance [level][dim*dim]

private:
	SHORT	m_nLevel;	// the number of level (codebook size)
	SHORT	m_nDim;		// dimensionality
	SHORT	m_nSample;	//

	REAL*	m_prDet;	// space for temporary determinants
	REAL*	m_prPrior;	// priori probability		[level]
	REAL**	m_pprPost;	// posteriori probability	[sample][lebel]

	SHORT*	m_pnSubtot;	// Temporary variables		[level]
	REAL	m_rDenom;	// Temporary denominator
	REAL*	m_prTSum;	// Temporary variables		[dim]
	REAL**	m_pprTSum;	//							[dim][dim]
	REAL***	m_ppprTVar;	// variance summation		[level][dim][dim]

	// operations
public:
	BOOL	NewCodebook( const SHORT nLevel, const SHORT nDim );
	// caclulate the Mixture Gaussian pdf
	REAL	CalcMGpdf( const REAL* preal, SHORT level );

	// size & dimension
	SHORT	GetSize() 			{ return( m_nLevel ); }
	SHORT	GetDimension()  	{ return( m_nDim ); }
	REAL*	GetPriorProb()		{ return( m_prPrior ); }
	CFVec&	GetMean()			{ return( m_fMean ); }
	CFVec&	GetVariance()		{ return( m_fVar ); }

	// codebook read/write using feature vector's function
	BOOL	Read( const char* pszFileName );
	BOOL	ReadText( const char* pszFileName );
	BOOL	Write( const char* pszFileName );
	BOOL	WriteText( const char* pszFileName );

	// calculate the posteriori prob.
	void	CalcCodebookProb( const REAL* pVector, REAL* pPost );
	void	DrawVQResult( CDC* pDC, POINT ptCenter, CFVec* pFVec, SHORT nCode, REAL* pProb=NULL );

	// generate the VQ codebook from nVector samples of dimensionality nDim
	BOOL	GenCodebook( CFVec& fvector, const SHORT nDLevel );

	// if the wave file list are given, generate the VQ codebook from files
	BOOL	GenCodebook( char* pcdbk, CFilelist& filelist,
					const SHORT nDim, const SHORT nDLevel );
	BOOL	GenCodebook( CFVec* pFVec, const SHORT nFVec,
					const SHORT nDim, const SHORT nDLevel );
	BOOL	GenCodebook( CFilelist& filelist,
					const SHORT nDim, const SHORT nDLevel );
	void	CalcDeterminants();
	void	FreeDeterminants();
	SHORT	Lookup( CFVec& fvector, const SHORT nIdx );
	SHORT	Lookup( CFVec& fvector, const SHORT nIdx, const SHORT nDim,
					const SHORT nDLevel, REAL* pBestDist );


private:
	void	InitInitialize( SHORT level, SHORT dim );
	void	SumVar( SHORT level, SHORT dim, REAL* pvec, REAL* pmean );
	void	CalcInitVar();
	void	EndInitialize( SHORT level, SHORT dim );
	void	AllocPostProb();
	void	FreePostProb();

	// Main routine of step 1 
	void	Initialize( CFVec& fvec, class CVQ& vq );
	void	Initialize( CFilelist& filelist, class CVQ& vq );
	void	Initialize( CFVec* pFVec, const SHORT nFVec, class CVQ& vq );

	REAL	ComputeContrib( CFVec& fvec, SHORT base );

	// Main routine of step 2
	void	Contribution( CFVec& fvec );
	void	Contribution( CFilelist& filelist );
	void	Contribution( CFVec* pFVec, const SHORT nFVec );

	void	InitCodebookUpdate( SHORT level, SHORT dim );
	void	UpdatePriori();
	void	CalcExpectedMean( CFVec& fvec, SHORT level, SHORT base );
	void	UpdateMean( CFVec& fvec );
	void	UpdateMean( CFilelist& filelist );
	void	UpdateMean( CFVec* pFVec, const SHORT nFVec );
	void	CalcExpectedVariance( CFVec& fvec, SHORT level, SHORT base );
	void	UpdateVariance( CFVec& fvec );
	void	UpdateVariance( CFilelist& filelist );
	void	UpdateVariance( CFVec* pFVec, const SHORT nFVec );

	// Main routine of step 3
	void	CodebookUpdate( CFVec& fvec );
	void	CodebookUpdate( CFilelist& filelist );
	void	CodebookUpdate( CFVec* pFVec, const SHORT nFVec );

	void	EndCodebookUpdate( SHORT level, SHORT dimm );
	REAL	CalcQEstimate( CFVec& fvec, SHORT level, SHORT base );
	REAL	CalcQFunction( CFVec& fvec );
	REAL	CalcQFunction( CFilelist& filelist );
	REAL	CalcQFunction( CFVec* pFVec, const SHORT nFVec );
	BOOL	GetCodebookByVQ( class CVQ& vq, CFilelist& filelist,
					const SHORT nDim, const SHORT nDLevel );
	BOOL	GetCodebookByVQ( class CVQ& vq, CFVec* pFVec, const SHORT nFVec, 
					const SHORT nDim, const SHORT nDLevel );
	void	DrawVQvector( CDC* pDC, POINT ptCenter, CFVec* pFVec, SHORT level, REAL* pProb=NULL );
};

#endif
