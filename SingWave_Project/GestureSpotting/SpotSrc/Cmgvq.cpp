// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"
#include "utils.h"
#include <math.h>
#include "CFlist.h"
#include "Cmgvq.h"

const REAL NEAR_ZERO	= 1.0e-45;
const REAL SHIFT_CENT	= (FLOATRESN / 2);
const REAL pi = 3.141592654;

// Reference : EDITS, Hidden Markov Models for Speech Recognition
// X. D. HUANG, Y. ARIKI, M. A. JACK

CMGVQ::CMGVQ()
{
	m_nLevel = m_nDim = 0;
	m_pprPost = NULL;
	m_prPrior = NULL;
}

CMGVQ::~CMGVQ()
{
	if( m_prPrior )
		delete[] m_prPrior;

	if( m_pprPost )
		FreePostProb();
}

////////////////////////////////////////////////////////////////////////////
// Private Member functions
////////////////////////////////////////////////////////////////////////////

// resize/create the codebook
BOOL CMGVQ::NewCodebook( const SHORT nLevel, const SHORT nDim )
{
	m_nLevel = nLevel;
	m_nDim	 = nDim;
	m_prPrior = new REAL [nLevel];
	if( !m_prPrior )
		Warning( "(CMGVQ::NewCodebook) new REAL allocation failure!" );

	if( m_fMean.New( nLevel, nDim ) &&
			m_fVar.New( nLevel, nDim * nDim ) )
		return( TRUE );
	else
		return( FALSE );
}

////////////////////////////////////////////////////////////////////////////
//
// STEP 1:
//
////////////////////////////////////////////////////////////////////////////

void CMGVQ::InitInitialize( SHORT level, SHORT dim )
{
	int i, j, s = dim * sizeof(REAL);

	if( !( m_ppprTVar = new REAL**[level] ))
		Warning("(CMGVQ::InitInitialize) fail(1)" );

	for( i = 0 ; i < level ; i ++ ) {
		m_ppprTVar[i] = new REAL*[dim];

		if( !m_ppprTVar[i] )
			Warning("(CMGVQ::InitInitialize) fail(2)" );

		for( j = 0 ; j < dim ; j ++ ) {
			if( !(m_ppprTVar[i][j] = new REAL[dim]) )
				Warning("(CMGVQ::InitInitialize) fail(3)" );

			// clear the allocated memory
			memset( m_ppprTVar[i][j], 0, s );
		}
	}

	if( !( m_pnSubtot = new SHORT [level] ))
		Warning("(CMGVQ::InitInitialize) m_pnSubtot allocation failed" );

	memset( m_pnSubtot, 0, sizeof(SHORT)*level );
}

void CMGVQ::SumVar( SHORT level, SHORT dim, REAL* pvec, REAL* pmean )
{
	int i, j;
	REAL** ppTVar = m_ppprTVar[level];
	REAL*	x;

	if( !( x = new REAL[dim] ))
		Warning("(CMGVQ::SumVar) alloc failed" );

	for( i = 0 ; i < dim ; i ++ )
		x[i] = pvec[i] - pmean[i];

	for( i = 0 ; i < dim ; i ++ ) {
		for( j = 0 ; j < dim ; j ++ )
			ppTVar[i][j] += x[i] * x[j];
	}

	delete[] x;
}

void CMGVQ::CalcInitVar()
{
	int i, j, k;
	REAL** ppTVar;

	for( i = 0 ; i < m_nLevel ; i ++ ) {
		ppTVar = m_ppprTVar[i];

		if( !m_pnSubtot[i] )
			Warning("(CMGVQ::CalcInitVar) denominator is zero");

		for( j = 0 ;	j < m_nDim ; j ++ )
			for( k = 0 ; k < m_nDim ; k ++ )
				m_fVar.SetFeature( i, j*m_nDim + k, 
					ppTVar[j][k] / m_pnSubtot[i] );
	}
}

void CMGVQ::EndInitialize( SHORT level, SHORT dim )
{
	int i, j;

	if( !m_ppprTVar || !m_pnSubtot )
		Warning( "(CMGVQ::EndInitialize) m_ppprTVar or m_pnSubtot are NULL" );

	for( i = 0 ; i < level ; i ++ ) {
		for( j = 0 ; j < dim ; j ++ )
			delete[] m_ppprTVar[i][j];
		delete[] m_ppprTVar[i];
	}

	delete[] m_ppprTVar; m_ppprTVar = NULL;
	delete[] m_pnSubtot; m_pnSubtot = NULL;
}


////////////////////////////////////////////////////////////////////////////
// Initialize the codebook with filelist
//
//	Pr_i (Priori probability) : 1/L (L := number of VQ codebook size)
//	u_i	(mean) : the mean value of K-means algorithm
//	s_i	(variance) : the variance
//

void CMGVQ::AllocPostProb()
{
	if( m_pprPost ) {
		Warning( "(CMGVQ::AllocPostProb) m_pprPost isn't NULL" );
		FreePostProb();
	}

	if( !(m_pprPost = new REAL*[m_nSample] ))
		Warning( "(CMGVQ::AllocPostProb) m_prPost allocation fail!" );
	
		int i, s = m_nLevel*sizeof(REAL);
		for( i = 0 ; i < m_nSample ; i ++ ) {
			m_pprPost[i] = new REAL[m_nLevel];
			if( !m_pprPost[i] )
				Warning( "(CMGVQ::AllocPostProb) m_pprPost[i] allocation failed" );
			memset( m_pprPost[i], 0, s );
		}
}

void CMGVQ::FreePostProb()
{
	if( m_pprPost ) {
		for( int i = 0 ; i < m_nSample ; i ++ )
			delete[] m_pprPost[i];
		delete[] m_pprPost;
		m_pprPost = NULL;
	}
}

void CMGVQ::Initialize( CFVec& fvec, CVQ& vq )
{
	int	i, j, cdbk;

	if( vq.m_nLevel != m_nLevel && vq.m_nDim != m_nDim ) {
		Warning( "(CMGVQ::Initialize) VQ: (%d,%d) - MGVQ: (%d,%d)",
			 vq.m_nLevel, vq.m_nDim, m_nLevel, m_nDim );
		Warning( "(CMGVQ::Initialize) incorrect dimension and level" );
	}

	for( i = 0 ; i < m_nLevel ; i ++ ) {
		// initialize the prior probability
		m_prPrior[i] = 1.0 / m_nLevel;

		// assign means
		for( j = 0 ; j < vq.m_nDim ; j ++ ) 
			m_fMean.SetFeature( i, j, vq.m_fCodebook.GetFeature( i, j ) );
	}

	// allocate the temporary variance
	InitInitialize( m_nLevel, m_nDim );

	// calculate the variance
	if( fvec.m_nVecDim != m_nDim )
		Warning( "(CMGVQ::Initialize) invalid dimension" );

	for( j = 0 ; j < fvec.m_nVector ; j ++ ) {
		cdbk = vq.Lookup( fvec.m_pprFvec[j] );
		SumVar( cdbk, m_nDim, fvec.m_pprFvec[j], m_fMean.m_pprFvec[cdbk] );
		m_pnSubtot[cdbk] ++;
	}

	m_nSample = fvec.m_nVector;
	printf( "Total number of samples: %d\n", m_nSample );

	CalcInitVar();
	EndInitialize( m_nLevel, m_nDim );

	AllocPostProb();
}

void CMGVQ::Initialize( CFilelist& filelist, CVQ& vq )
{
	int	i, j, tot, cdbk;
	CFVec	fvec;

	if( vq.m_nLevel != m_nLevel && vq.m_nDim != m_nDim ) {
		Warning( "(CMGVQ::Initialize) VQ: (%d,%d) - MGVQ: (%d,%d)",
			 vq.m_nLevel, vq.m_nDim, m_nLevel, m_nDim );
		Warning( "(CMGVQ::Initialize) incorrect dimension and level" );
	}

	for( i = 0 ; i < m_nLevel ; i ++ ) {
		// initialize the prior probability
		m_prPrior[i] = 1.0 / m_nLevel;

		// assign means
		for( j = 0 ; j < vq.m_nDim ; j ++ ) 
			m_fMean.SetFeature( i, j, vq.m_fCodebook.GetFeature( i, j ) );
	}

	// allocate the temporary variance
	InitInitialize( m_nLevel, m_nDim );

	// calculate the variance
	for( tot = 0, i = 0 ; i < filelist.m_nFile ; i ++ ) {
		fvec.Read( filelist.GetFile( i ) );

		if( fvec.m_nVecDim != m_nDim )
			Warning( "(CMGVQ::Initialize) invalid dimension" );

		for( j = 0 ; j < fvec.m_nVector ; j ++ ) {
			cdbk = vq.Lookup( fvec.m_pprFvec[j] );
			SumVar( cdbk, m_nDim, fvec.m_pprFvec[j], m_fMean.m_pprFvec[cdbk] );
			m_pnSubtot[cdbk] ++;
		}
		tot += fvec.m_nVector;
	}
	m_nSample = tot;
	printf( "Total number of samples: %d\n", m_nSample );

	CalcInitVar();
	EndInitialize( m_nLevel, m_nDim );

	AllocPostProb();
}

void CMGVQ::Initialize( CFVec* pFVec, const SHORT nFVec, CVQ& vq )
{
	int	i, j, tot, cdbk;

	if( vq.m_nLevel != m_nLevel && vq.m_nDim != m_nDim ) {
		Warning( "(CMGVQ::Initialize) VQ: (%d,%d) - MGVQ: (%d,%d)",
			 vq.m_nLevel, vq.m_nDim, m_nLevel, m_nDim );
		Warning( "(CMGVQ::Initialize) incorrect dimension and level" );
	}

	for( i = 0 ; i < m_nLevel ; i ++ ) {
		// initialize the prior probability
		m_prPrior[i] = 1.0 / m_nLevel;

		// assign means
		for( j = 0 ; j < vq.m_nDim ; j ++ ) 
			m_fMean.SetFeature( i, j, vq.m_fCodebook.GetFeature( i, j ) );
	}

	// allocate the temporary variance
	InitInitialize( m_nLevel, m_nDim );

	// calculate the variance
	for( tot = 0, i = 0 ; i < nFVec ; i ++ ) {
		for( j = 0 ; j < pFVec[i].m_nVector ; j ++ ) {
			cdbk = vq.Lookup( pFVec[i].m_pprFvec[j] );
			SumVar( cdbk, m_nDim, pFVec[i].m_pprFvec[j], m_fMean.m_pprFvec[cdbk] );
			m_pnSubtot[cdbk] ++;
		}
		tot += pFVec[i].m_nVector;
	}
	m_nSample = tot;
	printf( "Total number of samples: %d\n", m_nSample );

	CalcInitVar();
	EndInitialize( m_nLevel, m_nDim );

	AllocPostProb();
}

////////////////////////////////////////////////////////////////////////////
//
// STEP 2:
//
////////////////////////////////////////////////////////////////////////////

// Calculate the multivariate Gaussian pdf, pp. 22
//

REAL CMGVQ::CalcMGpdf( const REAL* pREAL, SHORT level )
{
	int i;
	REAL	denom, sum;
	
	denom = pow( (double) (2.0 * pi), (double)(m_nDim / 2) );
	denom *= (double) sqrt( (double) m_prDet[level] );
	if( denom < NEAR_ZERO )		// lower bound of denominator
		denom = NEAR_ZERO;

	REAL xi;

	sum = 0;
	// [ (x_k - u_i) * (x_k - u_i)_T / Sigma ], Sigma means the vairance
	for( i = 0 ; i < m_nDim ; i ++ ) {
		xi = pREAL[i] - m_fMean.m_pprFvec[level][i];
		sum += xi * xi / m_fVar.m_pprFvec[level][i*m_nDim+i];
	}

	return( exp( -sum / 2 ) / denom );
}

// Compute the Pr_i f_i(x_k|q) / f(x_k|Q), pp. 125
// Hidden Markov Models in Speech Recognition
//
REAL CMGVQ::ComputeContrib( CFVec& fvec, SHORT base )
{
	int	i, j, k;
	REAL sum;

	for( i = 0 ; i < fvec.m_nVector ; i ++ ) {
		sum = 0.0;
		k = base + i;
		for( j = 0 ; j < m_nLevel ; j ++ ) {
			m_pprPost[k][j] = CalcMGpdf( fvec.m_pprFvec[i], j ) * m_prPrior[j];
			sum += m_pprPost[k][j];
		}
		for( j = 0 ; j < m_nLevel ; j ++ )
			m_pprPost[k][j] /= sum;
	}
	return 0.0;
}

void CMGVQ::CalcDeterminants()
{
	int i, j;

	if( !( m_prDet = new REAL[m_nLevel] ))
		Warning( "(CMGVQ::ComputerContrib) new REAL failure!" );

	for( i = 0 ; i < m_nLevel ; i ++ ) {
		m_prDet[i] = 1.0;
		for( j = 0 ; j < m_nDim ; j ++ )
			m_prDet[i] *= m_fVar.m_pprFvec[i][j * m_nDim + j];
		if( m_prDet[i] == 0.0 )
			Warning( "(CMGVQ::CalcDeterminants) determinant is zero" );
	}
}

void CMGVQ::Contribution( CFVec& fvec )
{
	ComputeContrib( fvec, 0 );
}

void CMGVQ::Contribution( CFilelist& filelist )
{
	CFVec fvec;
	int	i, k;

	for( k = 0, i = 0 ; i < filelist.m_nFile ; i ++ ) {
		fvec.Read( filelist.GetFile( i ) );
		if( fvec.m_nVecDim != m_nDim )
			Warning( "(CMGVQ::Initialize) invalid dimension" );

		if( k + fvec.m_nVector > m_nSample )
			Warning("(CMGVQ::Contribution) memory size error" );

		ComputeContrib( fvec, k );
		k += fvec.m_nVector;
	}
}

void CMGVQ::Contribution( CFVec* pFVec, const SHORT nFVec )
{
	int	i, k;

	for( k = 0, i = 0 ; i < nFVec ; i ++ ) {
		ComputeContrib( pFVec[i], k );
		k += pFVec[i].m_nVector;
	}
}

void CMGVQ::FreeDeterminants()
{
	delete[] m_prDet;
}

////////////////////////////////////////////////////////////////////////////
//
// STEP 3:
//
////////////////////////////////////////////////////////////////////////////

void CMGVQ::InitCodebookUpdate( SHORT level, SHORT dim )
{
	int i;

	m_prTSum = new REAL[dim];
	m_pprTSum = new REAL*[dim];

	if( !m_prTSum || !m_pprTSum )
		Warning("(CMGVQ::InitCodebookUpdate) fail(1)" );

	for( i = 0 ; i < dim ; i ++ ) {
		m_pprTSum[i] = new REAL[dim];

		if( !m_pprTSum[i] )
			Warning("(CMGVQ::InitCodebookUpdate) fail(2)" );
	}
}

void CMGVQ::UpdatePriori()
{
	int i, j;
	REAL sum;
	for( i = 0 ; i < m_nLevel ; i ++ ) {
		sum = 0.0;
		for( j = 0 ; j < m_nSample ; j ++ )
			sum += m_pprPost[j][i];
		m_prPrior[i] = sum / m_nSample;
		if( m_prPrior[i] < NEAR_ZERO )
			m_prPrior[i] = NEAR_ZERO;
	}
}

void CMGVQ::CalcExpectedMean( CFVec& fvec, SHORT level, SHORT base )
{
	int i, j, k;

	for( i = 0 ; i < fvec.m_nVector ; i ++ ) {
		k = base + i;
		m_rDenom += m_pprPost[k][level];
		for( j = 0 ; j < m_nDim ; j ++ )
			m_prTSum[j] += fvec.GetFeature( i, j ) * m_pprPost[k][level];
	}
}

void CMGVQ::UpdateMean( CFVec& fvec )
{
	int i, j;

	for( i = 0 ; i < m_nLevel ; i ++ ) {
		m_rDenom = 0.0;
		for( j = 0 ; j < m_nDim ; j ++ )
			m_prTSum[j] = 0.0;

		CalcExpectedMean( fvec, i, 0 );

		for( j = 0 ; j < m_nDim ; j ++ )
			m_fMean.SetFeature( i, j, m_prTSum[j] / m_rDenom );
	}
}

void CMGVQ::UpdateMean( CFilelist& filelist )
{
	int i, j, k, t;
	CFVec fvec;

	for( i = 0 ; i < m_nLevel ; i ++ ) {
		m_rDenom = 0.0;
		for( j = 0 ; j < m_nDim ; j ++ )
			m_prTSum[j] = 0.0;

		for( t = 0, k = 0 ; k < filelist.m_nFile ; k ++ ) {
			fvec.Read( filelist.GetFile( k ) );
			if( fvec.m_nVecDim != m_nDim )
				Warning( "(CMGVQ::UpdateMean) invalid dimension" );
		 
			if( t + fvec.m_nVector > m_nSample )
				Warning("(CMGVQ::UpdateMean) memory size error" );

			CalcExpectedMean( fvec, i, t );
			t += fvec.m_nVector;
		}

		for( j = 0 ; j < m_nDim ; j ++ )
			m_fMean.SetFeature( i, j, m_prTSum[j] / m_rDenom );
	}
}

void CMGVQ::UpdateMean( CFVec* pFVec, const SHORT nFVec )
{
	int i, j, k, t;

	for( i = 0 ; i < m_nLevel ; i ++ ) {
		m_rDenom = 0.0;
		for( j = 0 ; j < m_nDim ; j ++ )
			m_prTSum[j] = 0.0;

		for( t = 0, k = 0 ; k < nFVec ; k ++ ) {
			CalcExpectedMean( pFVec[k], i, t );
			t += pFVec[k].m_nVector;
		}

		for( j = 0 ; j < m_nDim ; j ++ )
			m_fMean.SetFeature( i, j, m_prTSum[j] / m_rDenom );
	}
}

void CMGVQ::CalcExpectedVariance( CFVec& fvec, SHORT level, SHORT base )
{
	int i, j, k, l;
	REAL* x;

	if( !( x = new REAL[m_nDim] ))
		Warning( "(CMGVQ::CalcExpectedVariance) mem allocation error" );
	
	for( i = 0 ; i < fvec.m_nVector ; i ++ ) {
		l = base + i;
		m_rDenom += m_pprPost[l][level];

		// x = ( x_k - u_i )
		for( j = 0 ; j < m_nDim ; j ++ )
			x[j] = fvec.GetFeature( i, j ) - m_fMean.GetFeature( level, j );
		
		for( j = 0 ; j < m_nDim ; j ++ )
			for( k = 0 ; k < m_nDim ; k ++ )
				m_pprTSum[j][k]+= x[j] * x[k] * m_pprPost[l][level];
		
	}

	delete[] x;
}

void CMGVQ::UpdateVariance( CFVec& fvec )
{
	int i, j, k;

	for( i = 0 ; i < m_nLevel ; i ++ ) {
		m_rDenom = 0.0;

		for( j = 0 ; j < m_nDim ; j ++ )
			memset( m_pprTSum[j], 0, sizeof(REAL)*m_nDim );

		CalcExpectedVariance( fvec, i, 0 );

		for( j = 0 ; j < m_nDim ; j ++ )
			for( k = 0 ; k < m_nDim ; k ++ )
				m_fVar.SetFeature( i, j*m_nDim + k, m_pprTSum[j][k] / m_rDenom );
	}
}

void CMGVQ::UpdateVariance( CFilelist& filelist )
{
	int i, j, k, t;
	CFVec fvec;

	for( i = 0 ; i < m_nLevel ; i ++ ) {
		m_rDenom = 0.0;

		for( j = 0 ; j < m_nDim ; j ++ )
			memset( m_pprTSum[j], 0, sizeof(REAL)*m_nDim );

		for( t = 0, k = 0 ; k < filelist.m_nFile ; k ++ ) {
			fvec.Read( filelist.GetFile( k ) );
			if( fvec.m_nVecDim != m_nDim )
				Warning( "(CMGVQ::UpdateVariance) invalid dimension" );
		 
			if( t + fvec.m_nVector > m_nSample )
				Warning("(CMGVQ::UpdateVairance) memory size error" );

			CalcExpectedVariance( fvec, i, t );
			t += fvec.m_nVector;
		}

		for( j = 0 ; j < m_nDim ; j ++ )
			for( k = 0 ; k < m_nDim ; k ++ )
				m_fVar.SetFeature( i, j*m_nDim + k, m_pprTSum[j][k] / m_rDenom );
	}
}

void CMGVQ::UpdateVariance( CFVec* pFVec, const SHORT nFVec )
{
	int i, j, k, t;

	for( i = 0 ; i < m_nLevel ; i ++ ) {
		m_rDenom = 0.0;

		for( j = 0 ; j < m_nDim ; j ++ )
			memset( m_pprTSum[j], 0, sizeof(REAL)*m_nDim );

		for( t = 0, k = 0 ; k < nFVec ; k ++ ) {
			CalcExpectedVariance( pFVec[k], i, t );
			t += pFVec[k].m_nVector;
		}

		for( j = 0 ; j < m_nDim ; j ++ )
			for( k = 0 ; k < m_nDim ; k ++ )
				m_fVar.SetFeature( i, j*m_nDim + k, m_pprTSum[j][k] / m_rDenom );
	}
}

void CMGVQ::CodebookUpdate( CFVec& fvec )
{
	InitCodebookUpdate( m_nLevel, m_nDim );

	UpdatePriori();
	UpdateMean( fvec );
	UpdateVariance( fvec );

	EndCodebookUpdate( m_nLevel, m_nDim );
}

void CMGVQ::CodebookUpdate( CFilelist& filelist )
{
	InitCodebookUpdate( m_nLevel, m_nDim );

	UpdatePriori();
	UpdateMean( filelist );
	UpdateVariance( filelist );

	EndCodebookUpdate( m_nLevel, m_nDim );
}

void CMGVQ::CodebookUpdate( CFVec* pFVec, const SHORT nFVec )
{
	InitCodebookUpdate( m_nLevel, m_nDim );

	UpdatePriori();
	UpdateMean( pFVec, nFVec );
	UpdateVariance( pFVec, nFVec );

	EndCodebookUpdate( m_nLevel, m_nDim );
}

void CMGVQ::EndCodebookUpdate( SHORT level, SHORT dim )
{
	int i;

	if( !m_prTSum || !m_pprTSum )
		Warning( "(CMGVQ::EndInitialize) m_ppprTVar or m_pnSubtot are NULL" );

	for( i = 0 ; i < dim ; i ++ )
		delete[] m_pprTSum[i];

	delete[] m_prTSum;	m_prTSum	= NULL;
	delete[] m_pprTSum; m_pprTSum = NULL;
}

////////////////////////////////////////////////////////////////////////////
//
// STEP 4:
//
////////////////////////////////////////////////////////////////////////////

REAL CMGVQ::CalcQEstimate( CFVec& fvec, SHORT level, SHORT base )
{
	int	i, j;
	REAL qi = 0.0, pdf;

	for( i = 0 ; i < fvec.m_nVector ; i ++ ) {
		j = base + i;
		pdf = CalcMGpdf( fvec.m_pprFvec[i], level );
		if( pdf < NEAR_ZERO )
			pdf = NEAR_ZERO;
		qi += m_pprPost[j][level] * log( (double) pdf );
	}
	return( qi );
}

// pp. 122
REAL CMGVQ::CalcQFunction( CFVec& fvec )
{
	int i, j;
	REAL a, q = 0.0;

	for( i = 0 ; i < m_nLevel ; i ++ ) {

		a = 0.0;
		for( j = 0 ; j < m_nSample ; j ++ )
			a += m_pprPost[j][i];

		q += a * log( (double) m_prPrior[i] );
		q += CalcQEstimate( fvec, i, 0 );
	}
	return( q );
}

REAL CMGVQ::CalcQFunction( CFilelist& filelist )
{
	int i, j, k, t ;
	REAL a, q = 0.0;
	CFVec fvec;

	for( i = 0 ; i < m_nLevel ; i ++ ) {

		a = 0.0;
		for( j = 0 ; j < m_nSample ; j ++ )
			a += m_pprPost[j][i];

		q += a * log( (double) m_prPrior[i] );
		for( t = 0, k = 0 ; k < filelist.m_nFile ; k ++ ) {
			fvec.Read( filelist.GetFile( k ) );
			q += CalcQEstimate( fvec, i, k );
		}
	}
	return( q );
}

REAL CMGVQ::CalcQFunction( CFVec* pFVec, const SHORT nFVec )
{
	int i, j, k, t ;
	REAL a, q = 0.0;

	for( i = 0 ; i < m_nLevel ; i ++ ) {

		a = 0.0;
		for( j = 0 ; j < m_nSample ; j ++ )
			a += m_pprPost[j][i];

		q += a * log( (double) m_prPrior[i] );
		for( t = 0, k = 0 ; k < nFVec; k ++ )
			q += CalcQEstimate( pFVec[k], i, k );
	}
	return( q );
}

////////////////////////////////////////////////////////////////////////////
// Public Member functions
////////////////////////////////////////////////////////////////////////////

// codebook read/write using feature vector's function
BOOL CMGVQ::Read( const char* pszFileName )
{
	char szFileName[256];

	sprintf_s( szFileName, "%s.bm", pszFileName );
	int res	= m_fMean.Read( szFileName );
	m_nLevel = m_fMean.GetSize();
	m_nDim	 = m_fMean.GetDimension();

	sprintf_s( szFileName, "%s.bv", pszFileName );
	res &= m_fVar.Read( szFileName );
	if( m_nLevel != m_fVar.GetSize() ) 
		Warning( "(CMGVQ::Read) Invalid Levels" );
	if( (m_nDim*m_nDim) != m_fVar.GetDimension() )
		Warning( "(CMGVQ::Read) Invalid Dimensions" );

	FILE* fp;
	sprintf_s( szFileName, "%s.bp", pszFileName );
	if( ( fp = fopen( szFileName, "rb" ) ) == NULL )
		Warning( "(CMGVQ::Read) Priori prob. not opend" );

	if (!m_prPrior)
		m_prPrior = new REAL [m_nLevel];
	if( !m_prPrior )
		Warning( "(CMGVQ::Read) m_prPrior allocation failure!" );
	if( (SHORT)MyRead( m_prPrior, sizeof(REAL), m_nLevel, fp ) != m_nLevel )
		Warning( "(CMGVQ::Read) m_prPrior read error" );
	fclose( fp );

	return( res );
}

BOOL CMGVQ::ReadText( const char* pszFileName )
{
	char	szFileName[256];

	sprintf_s( szFileName, "%s.tm", pszFileName );
	int res	= m_fMean.ReadText( szFileName );
	m_nLevel = m_fMean.GetSize();
	m_nDim	 = m_fMean.GetDimension();

	sprintf_s( szFileName, "%s.tv", pszFileName );
	res &= m_fVar.ReadText( szFileName );
	if( m_nLevel != m_fVar.GetSize() ) 
		Warning( "(CMGVQ::Read) Invalid Levels" );
	if( ( m_nDim*m_nDim ) != m_fVar.GetDimension() )
		Warning( "(CMGVQ::Read) Invalid Dimensions" );

	FILE* fp;
	sprintf_s( szFileName, "%s.tp", pszFileName );
	if( ( fp = fopen( szFileName, "r" ) ) == NULL )
		Warning( "(CMGVQ::Read) Priori prob. not opend" );

	if (!m_prPrior)
		m_prPrior = new REAL [m_nLevel];
	if( !m_prPrior )
		Warning( "(CMGVQ::Read) m_prPrior allocation failure!" );
	for( int i = 0 ; i < m_nLevel ; i ++ )
		fscanf_s( fp, "%g\n", &m_prPrior[i] );
	fclose( fp );

	return( res );
}

BOOL CMGVQ::Write( const char* pszFileName )
{
	char szFileName[256];

	sprintf_s( szFileName, "%s.bm", pszFileName );
	int res = m_fMean.Write( szFileName );

	sprintf_s( szFileName, "%s.bv", pszFileName );
	res &= m_fVar.Write( szFileName );

	FILE* fp;
	sprintf_s( szFileName, "%s.bp", pszFileName );
	if( ( fp = fopen( szFileName, "wb" ) ) == NULL )
		Warning( "(CMGVQ::Read) Priori prob. not opend" );
	if( (SHORT)MyWrite( m_prPrior, sizeof(REAL), m_nLevel, fp ) != m_nLevel )
		Warning( "(CMGVQ::Write) m_prPrior write error" );
	fclose( fp );

	return( res );
}

BOOL CMGVQ::WriteText( const char* pszFileName )
{
	char szFileName[256];

	sprintf_s( szFileName, "%s.tm", pszFileName );
	int res = m_fMean.WriteText( szFileName );

	sprintf_s( szFileName, "%s.tv", pszFileName );
	res &= m_fVar.WriteText( szFileName );

	FILE* fp;
	sprintf_s( szFileName, "%s.tp", pszFileName );
	if( ( fp = fopen( szFileName, "wb" ) ) == NULL )
		Warning( "(CMGVQ::Read) Priori prob. not opend" );
	for( int i = 0 ; i < m_nLevel ; i ++ )
		fprintf( fp, "%g\n", m_prPrior[i] );
	fclose( fp );

	return( res );
}

////////////////////////////////////////////////////////////////////////////

void CMGVQ::CalcCodebookProb( const REAL* pVector, REAL* pPost )
{
	int	i;
	REAL sum;

	sum = 0.0;
	for( i = 0 ; i < m_nLevel ; i ++ ) {
		pPost[i] = CalcMGpdf( pVector, i ) * m_prPrior[i];
		sum += pPost[i];
	}

	for( i = 0 ; i < m_nLevel ; i ++ )
		pPost[i] /= sum;
}

BOOL CMGVQ::GenCodebook( CFVec& fvector, const SHORT nDLevel )
{
	CVQ vq;
	BOOL	bRet = TRUE;
	REAL	q = 0.0, oq, r;

	if ( !vq.GenCodebook( fvector, nDLevel ) )
		return FALSE;

	NewCodebook( nDLevel, fvector.GetDimension() );
	Initialize( fvector, vq );

	do {
		oq = q;
		CalcDeterminants();

		Contribution( fvector );
		CodebookUpdate( fvector );
		q = CalcQFunction( fvector );

		r = oq / ((1.0 + FLOATRESN) * q);

		bRet = PrintProgressString( "q: %f   oq: %f   diff: %f", q, oq, r );

		FreeDeterminants();
	} while( bRet && (!r || r > 1.0) );

	FreePostProb();

	return bRet;
}

BOOL CMGVQ::GetCodebookByVQ( CVQ& vq, CFilelist& filelist,
					 const SHORT nDim, const SHORT nDLevel )
{
	BOOL	bRet = TRUE;
	REAL	q = 0.0, oq, r;

	NewCodebook( nDLevel, nDim );
	Initialize( filelist, vq );

	do {
		oq = q;
		CalcDeterminants();

		Contribution( filelist );
		CodebookUpdate( filelist );
		q = CalcQFunction( filelist );

		r = oq / ((1.0 + FLOATRESN) * q);

		bRet = PrintProgressString( "q: %f   oq: %f   diff: %f", q, oq, r );

		FreeDeterminants();
	} while( bRet && (!r || r > 1.0) );

	FreePostProb();

	return bRet;
}

BOOL CMGVQ::GetCodebookByVQ( CVQ& vq, CFVec* pFVec, const SHORT nFVec, 
							const SHORT nDim, const SHORT nDLevel )
{
	REAL	q = 0.0, oq, r;
	BOOL	bRet = TRUE;
	SHORT	nLoop = 0;

	NewCodebook( nDLevel, nDim );
	Initialize( pFVec, nFVec, vq );

	do {
		PrintProgressString( "******** ( %d ) ********", nLoop );

		oq = q;
		CalcDeterminants();

		Contribution( pFVec, nFVec );
		CodebookUpdate( pFVec, nFVec );
		q = CalcQFunction( pFVec, nFVec );

		r = oq / ((1.0 + FLOATRESN) * q);
		bRet = PrintProgressString( "q: %f   oq: %f   diff: %f", q, oq, r );

		FreeDeterminants();

		nLoop++;
	} while( bRet && (!r || r > 1.0) );

	FreePostProb();

	if (!bRet)
		return FALSE;

	return PrintProgressString( "End of CMGVQ::GetCodebookByVQ" );
}

// if the file list are given, generate the VQ codebook from files
BOOL CMGVQ::GenCodebook( char* pcdbk, CFilelist& filelist,
			 const SHORT nDim, const SHORT nDLevel )
{
	CVQ	vq;
	if ( !vq.Read( pcdbk ) )
		return FALSE;

	return GetCodebookByVQ( vq, filelist, nDim, nDLevel );
}

BOOL CMGVQ::GenCodebook( CFVec* pFVec, const SHORT nFVec,
			 const SHORT nDim, const SHORT nDLevel )
{
	CVQ	vq;
	
	if (!pFVec || nFVec <= 0 || nDim <= 0 || nDLevel <= 0)
		return TRUE;

	if ( !vq.GenCodebook( pFVec, nFVec, nDLevel ) )
		return FALSE;

	if ( !vq.Write(MakeMyFileName("VQ.out\\", "vq.bin")) )
		return FALSE;

	if ( !vq.WriteText(MakeMyFileName("VQ.out\\", "vq.txt")) )
		return FALSE;

	return GetCodebookByVQ( vq, pFVec, nFVec, nDim, nDLevel );
}

BOOL CMGVQ::GenCodebook( CFilelist& filelist,
			 const SHORT nDim, const SHORT nDLevel )
{
	CVQ	vq;

	if ( !vq.GenCodebook( filelist, nDim, nDLevel ) )
		return FALSE;
	return GetCodebookByVQ( vq, filelist, nDim, nDLevel );
}

SHORT CMGVQ::Lookup( CFVec& fvector, const SHORT nIdx )
{
	return Lookup( fvector, nIdx, m_nDim, m_nLevel, NULL );
}

SHORT CMGVQ::Lookup( CFVec& fvector, const SHORT nIdx, const SHORT nDim,
			 const SHORT nDLevel, REAL* pBestDist )
{
	SHORT	i, level, bestlevel;
	REAL	xi, sum, bestdist;

	if( nDim <= 0 || nDLevel <= 0 ) {
		Warning( "(CMGVQ::Lookup) (%d, %d, - )", nDim, nDLevel );
		return( -1 );
	}

	sum = 0.0;
	// Get Mahalanobis distance : [ (x_k - u_i) * (x_k - u_i)_T / Sigma ]
	for( i = 0 ; i < nDim ; i ++ ) {
		xi = fvector.m_pprFvec[nIdx][i] - m_fMean.m_pprFvec[0][i];
		sum += xi * xi / m_fVar.m_pprFvec[0][i*m_nDim+i];
	}
	bestdist = sum;
	bestlevel = 0;

	// search all the other codebook entries to find any with lower distance
	for( level = 1 ; level < nDLevel ; level ++ ) {
		sum = 0.0;
		for( i = 0 ; sum < bestdist && i < nDim ; i ++ ) {
			xi	= fvector.m_pprFvec[nIdx][i] - m_fMean.m_pprFvec[level][i];
			sum += xi * xi / m_fVar.m_pprFvec[level][i*m_nDim+i];
		}

		if( sum < bestdist ) {
			bestdist = sum;
			bestlevel = level;
		}
	}

	// optionally return the best distance
	if( pBestDist != NULL )
		*pBestDist = bestdist;

		return( bestlevel );
}

void CMGVQ::DrawVQvector( CDC* pDC, POINT ptCenter, CFVec* pFVec, SHORT level, REAL* pProb )
{
	char	szTmp[MAX_BUFFER];
	extern	COLORREF PenColor[];
	SHORT	DX, DY;
	REAL	dx, dy, tsin, tcos;

#ifdef OLD_FEATURE
	if (pFVec) {
		dx = pFVec->GetFeature(0, 0) * 320;
		dy = pFVec->GetFeature(0, 1) * 240;
		tsin = pFVec->GetFeature(0, 2) * 2 - 1.0;
		tcos = pFVec->GetFeature(0, 3) * 2 - 1.0;
	} else {
		dx = m_fMean.GetFeature(level, 0) * 320;
		dy = m_fMean.GetFeature(level, 1) * 240;
		tsin = m_fMean.GetFeature(level, 2) * 2 - 1.0;
		tcos = m_fMean.GetFeature(level, 3) * 2 - 1.0;
	}

	if (tsin >= 0 && tcos >= 0) // 1st quater
		dy = -dy;
	else if (tsin >= 0 && tcos < 0) // 2nd quater
		{ dx = -dx; dy = -dy; }
	else if (tsin < 0 && tcos < 0) // 3rd quater
		dx = -dx;
	
	DX = (SHORT)dx; 
	DY = (SHORT)dy;

	if (pFVec)
		sprintf(szTmp, "%d(%d,%d)", level, DX, DY);
	else
		sprintf(szTmp, "%d", level);

	CPen	newPen(PS_SOLID, 1, PenColor[level % 3]);
	CPen*	oldPen;
	
	DX = (SHORT)(DX * 2.5);
	DY = (SHORT)(DY * -2.5);

	if (abs(DX) > WIDTH)
		DX = DX / abs(DX) * WIDTH;
	if (abs(DY) > HEIGHT)
		DY = DY / abs(DY) * HEIGHT;
#else
	dx = dy = 40;
	if (pFVec) {
		tsin = pFVec->GetFeature(0, 0) * 2 - 1.0;
		tcos = pFVec->GetFeature(0, 1) * 2 - 1.0;
	} else {
		tsin = m_fMean.GetFeature(level, 0) * 2 - 1.0;
		tcos = m_fMean.GetFeature(level, 1) * 2 - 1.0;
	}

	if ( pProb )
		sprintf_s(szTmp, "%d (%g)", level, pProb[level]);
	else
		sprintf_s(szTmp, "%d", level);
#endif

	DX = (SHORT)(200 * tcos); 
	DY = (SHORT)(200 * tsin);

	CPen	newPen(PS_SOLID, 1, PenColor[level % 3]);
	CPen*	oldPen = NULL;
	
	if (!pFVec)
		oldPen = (CPen *)pDC->SelectObject((CPen*)&newPen);

	pDC->MoveTo( ptCenter.x, ptCenter.y );
	pDC->LineTo( ptCenter.x + DX, ptCenter.y + DY );

	if (!pFVec)
		pDC->SelectObject(oldPen);
		
	int		nOldBk = pDC->SetBkMode(TRANSPARENT);
	CFont*	newFont = CreateMyFont( 12, FALSE );
	CFont*	oldFont = pDC->SelectObject( newFont );

	//pDC->TextOut( ptCenter.x+DX, ptCenter.y+DY, szTmp, strlen(szTmp) );   // by hklee
	pDC->TextOut(/*pDC->m_hDC,*/ ptCenter.x + DX, ptCenter.y + DY, szTmp, strlen(szTmp));
	pDC->SelectObject( oldFont );
	pDC->SetBkMode(nOldBk);

	delete newFont;
}

void CMGVQ::DrawVQResult( CDC* pDC, POINT ptCenter, CFVec* pFVec, SHORT nCode, REAL* pProb )
{
	if (pFVec)
		DrawVQvector( pDC, ptCenter, pFVec, nCode );
	else {
		// Rectangle
		pDC->Rectangle(ptCenter.x-WIDTH, ptCenter.y-HEIGHT, ptCenter.x+WIDTH, ptCenter.y+HEIGHT );

		// X-axis
		pDC->MoveTo(ptCenter.x-WIDTH, ptCenter.y);
		pDC->LineTo(ptCenter.x+WIDTH, ptCenter.y);
		// Y-axis
		pDC->MoveTo(ptCenter.x, ptCenter.y-HEIGHT);
		pDC->LineTo(ptCenter.x, ptCenter.y+HEIGHT);

		for( int i=0; i<m_nLevel; i++ )	{
			DrawVQvector( pDC, ptCenter, NULL, i, pProb );
//			if ( !WaitMoment( 10000.0, FALSE ) )
//				break;
		}
	}
}
