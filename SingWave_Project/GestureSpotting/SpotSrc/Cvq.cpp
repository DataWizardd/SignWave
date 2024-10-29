// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"
#include "utils.h"
#include "CFlist.h"
#include <math.h>
#include "Cvq.h"

const REAL SHIFT_CENT = (FLOATRESN / 2);

CVQ::CVQ()
{
	m_nLevel = m_nDim = 0;
}

CVQ::~CVQ()
{
}


////////////////////////////////////////////////////////////////////////////
// Private Member functions
////////////////////////////////////////////////////////////////////////////

// resize/create the codebook
BOOL CVQ::NewCodebook( const SHORT nLevel, const SHORT nDim )
{
	m_nLevel = nLevel;
	m_nDim	 = nDim;

	return( m_fCodebook.New( nLevel, nDim ) );
}

////////////////////////////////////////////////////////////////////////////

// Initialize the codebook

void CVQ::Initialize()
{
	int	i, j;
	REAL	sum;

	for( j = 0 ; j < m_nDim ; j ++ ) {
		for( i = 0, sum = 0.0 ; i < m_pfvec->m_nVector ; i ++ )
			sum += m_pfvec->GetFeature( i, j );
		m_fCodebook.SetFeature( 0, j, sum / m_pfvec->m_nVector );
	}
}

void CVQ::Initialize( CFilelist& filelist )
{
	int	i, j, k, tot;
	REAL*	psum;
	CFVec	fvec;

	psum = new REAL[m_nDim];
	if( !psum ) {
		Warning( "(CVQ::Initialize) new REAL[] failed" );
		return;
	}
	memset( psum, 0, sizeof( REAL )*m_nDim );
	
	for( tot = 0, i = 0 ; i < filelist.m_nFile ; i ++ ) {
		fvec.Read( filelist.GetFile( i ) );
		if( fvec.m_nVecDim != m_nDim )
			Warning( "(CVQ::Initialize) invalid dimension" );
		
		for( j = 0 ; j < m_nDim ; j ++ )
			for( k = 0 ; k < fvec.m_nVector ; k ++ )
				psum[j] += fvec.GetFeature( k, j );
		tot += fvec.m_nVector;
	}

	for( i = 0 ; i < m_nDim ; i ++ )
		m_fCodebook.SetFeature( 0, i, psum[i] / tot );

	delete[] psum;
}

void CVQ::Initialize( CFVec* pFVec, SHORT nFVec )
{
	int	i, j, k, tot;
	REAL*	psum;

	psum = new REAL[m_nDim];
	if( !psum )
		Warning( "(CVQ::Initialize) new REAL[] failed" );
	memset( psum, 0, sizeof( REAL )*m_nDim );
	
	for( tot = 0, i = 0 ; i < nFVec ; i ++ ) {
		for( j = 0 ; j < m_nDim ; j ++ )
			for( k = 0 ; k < pFVec[i].m_nVector ; k ++ )
				psum[j] += pFVec[i].GetFeature( k, j );
		tot += pFVec[i].m_nVector;
	}

	for( i = 0 ; i < m_nDim ; i ++ )
		m_fCodebook.SetFeature( 0, i, psum[i] / tot );

	delete[] psum;
}

////////////////////////////////////////////////////////////////////////////

// clean the memory space allocated by the remporary variables
void CVQ::CleanTempspace( SHORT* pnSum, REAL** pprSum,
				const SHORT nCode, const SHORT nDim )
{
	int i, nsize, rsize;
	nsize = nCode * sizeof(SHORT);
	rsize = nDim	* sizeof(REAL);
	memset( pnSum, 0, nsize );
	for( i = 0 ; i < nCode ; i ++ )
		memset( pprSum[i], 0, rsize );
}

// split L codebook to 2L
void CVQ::SplitCodebook( const SHORT nCode, const SHORT nNewCode )
{
	int	i, j, k;
	REAL	original, perturb;
	
	for( i = nCode ; i < nNewCode ; i ++ ) {
		for( k = i - nCode, j = 0 ; j < m_nDim ; j ++ ) {
			original = m_fCodebook.GetFeature( k, j );
			perturb	= FLOATRESN * original;

			// if the centroid shift is smaller than the given distance,
			// we must make centroid to move for the given distance.
			if( fabs( perturb ) < SHIFT_CENT )
				perturb = SHIFT_CENT;
			m_fCodebook.SetFeature( i, j, original + perturb );
			m_fCodebook.SetFeature( k, j, original - perturb );
		}
	}
}

////////////////////////////////////////////////////////////////////////////

// classify the set of training data into one of the clusters
REAL CVQ::Classify( const SHORT nCode, SHORT* pnSum, REAL** pprSum )
{
	REAL	dist, sumdist = 0.0;
	int	i, j, code;

	// find the nearest codevector and accumulate statistics for all vector
	for( i = 0 ; i < m_pfvec->m_nVector ; i ++ ) {
		code = Lookup( m_pfvec->m_pprFvec[i], m_nDim, nCode, &dist );

		// accumulate statistics
		sumdist += dist;
		pnSum[code] ++;
		for( j = 0 ; j < m_nDim ; j ++ )
			pprSum[code][j] += m_pfvec->GetFeature( i, j );
	}
	return( sumdist );
}

REAL CVQ::Classify( CFilelist& filelist, const SHORT nCode,
				SHORT* pnSum, REAL** pprSum )
{
	REAL	dist, sumdist = 0.0;
	int	i, j, k, code;
	CFVec	fvec;

	// find the nearest codevector and accumulate statistics for all vector
	for( i = 0 ; i < filelist.m_nFile ; i ++ ) {
		fvec.Read( filelist.GetFile( i ) );
		for( j = 0 ; j < fvec.m_nVector ; j ++ ) {
			code = Lookup( fvec.m_pprFvec[j], m_nDim, nCode, &dist );

			// accumulate statistics
			sumdist += dist;
			pnSum[code] ++;
			for( k = 0 ; k < m_nDim ; k ++ )
				pprSum[code][k] += fvec.GetFeature( j, k );
		}
	}
	return( sumdist );
}

REAL CVQ::Classify( CFVec* pFVec, const SHORT nFVec, const SHORT nCode,
				SHORT* pnSum, REAL** pprSum )
{
	REAL	dist, sumdist = 0.0;
	int	i, j, k, code;

	// find the nearest codevector and accumulate statistics for all vector
	for( i = 0 ; i < nFVec ; i ++ ) {
		for( j = 0 ; j < pFVec[i].m_nVector ; j ++ ) {
			code = Lookup( pFVec[i].m_pprFvec[j], m_nDim, nCode, &dist );

			// accumulate statistics
			sumdist += dist;
			pnSum[code] ++;
			for( k = 0 ; k < m_nDim ; k ++ )
				pprSum[code][k] += pFVec[i].GetFeature( j, k );
		}
	}
	return( sumdist );
}


// computing the centroid in each cluster
void CVQ::Reestimate( const SHORT nCode, SHORT* pnSum, REAL** pprSum )
{
	int i, j;
	
	// reestimate centroids
	for( i = 0 ; i < nCode ; i ++ ) {
		for( j = 0 ; j < m_nDim ; j ++ )
			m_fCodebook.SetFeature( i, j, pprSum[i][j] / pnSum[i] );
	}
}

////////////////////////////////////////////////////////////////////////////

// update the codeword of every cluster
REAL CVQ::Update( const SHORT nCode, const REAL rPrevDist,
			SHORT* pnSum, REAL** pprSum )
{
	REAL	sumdist, lsumdist;

	sumdist = rPrevDist;
	do {
		lsumdist = sumdist;
		CleanTempspace( pnSum, pprSum, nCode, m_nDim );
		sumdist = Classify( nCode, pnSum, pprSum );
		Reestimate( nCode, pnSum, pprSum );

#ifdef _DEBUG
		if ( !PrintProgressString( "%d   %f   %f", nCode, sumdist, 
								   lsumdist / sumdist ) )
			return -1.;
#endif

	} while( lsumdist > ( 1.0 + FLOATRESN ) * sumdist );

	return( sumdist );
}

REAL CVQ::Update( CFilelist& filelist, const SHORT	nCode,
			const REAL rPrevDist, SHORT* pnSum, REAL** pprSum )
{
	REAL	sumdist, lsumdist;

#ifdef _DEBUG
	if ( !PrintProgressString( "Start of CVQ::Update" ) )
		return -1.;
#endif
	sumdist = rPrevDist;
	do {
		lsumdist = sumdist;
		CleanTempspace( pnSum, pprSum, nCode, m_nDim );
		sumdist = Classify( filelist, nCode, pnSum, pprSum );
		Reestimate( nCode, pnSum, pprSum );

#ifdef _DEBUG
		if ( !PrintProgressString( "%d   %f   %f", nCode, sumdist, 
								   lsumdist / sumdist ) )
			return -1.;
#endif

	} while( lsumdist > ( 1.0 + FLOATRESN ) * sumdist );

#ifdef _DEBUG
	if ( !PrintProgressString( "End of CVQ::Update" ) )
		return -1.;
#endif

	return( sumdist );
}

REAL CVQ::Update( CFVec* pFVec, const SHORT nFVec, const SHORT nCode,
			const REAL rPrevDist, SHORT* pnSum, REAL** pprSum )
{
	REAL	sumdist, lsumdist;

#ifdef _DEBUG
	if ( !PrintProgressString( "Start of CVQ::Update" ) )
		return -1.;
#endif
	sumdist = rPrevDist;
	do {
		lsumdist = sumdist;
		CleanTempspace( pnSum, pprSum, nCode, m_nDim );
		sumdist = Classify( pFVec, nFVec, nCode, pnSum, pprSum );
		Reestimate( nCode, pnSum, pprSum );

#ifdef _DEBUG
		if ( !PrintProgressString( "%d   %f   %f", nCode, sumdist, 
								   lsumdist / sumdist ) )
			return -1.;
#endif

	} while( lsumdist > ( 1.0 + FLOATRESN ) * sumdist );

#ifdef _DEBUG
	if ( !PrintProgressString( "End of CVQ::Update" ) )
		return -1.;
#endif

	return( sumdist );
}


////////////////////////////////////////////////////////////////////////////
// Public Member functions
////////////////////////////////////////////////////////////////////////////


// codebook read/write using feature vector's function
BOOL CVQ::Read( const char* pszFileName )
{
	int res	= m_fCodebook.Read( pszFileName );
	m_nLevel = m_fCodebook.GetSize();
	m_nDim	 = m_fCodebook.GetDimension();
	return( res );
}

BOOL CVQ::ReadText( const char* pszFileName )
{
	int res	= m_fCodebook.ReadText( pszFileName );
	m_nLevel = m_fCodebook.GetSize();
	m_nDim	 = m_fCodebook.GetDimension();
	return( res );
}

BOOL CVQ::Write( const char* pszFileName )
{
	return( m_fCodebook.Write( pszFileName ) );
}

BOOL CVQ::WriteText( const char* pszFileName )
{
	return( m_fCodebook.WriteText( pszFileName ) );
}

////////////////////////////////////////////////////////////////////////////

// find the closest codebook entry in terms of Euclidean distance by
// performing a sequentioal search (with some prunning)
SHORT CVQ::Lookup( const REAL* pVector )
{
	return( Lookup( pVector, m_nDim, m_nLevel, NULL ) );
}

SHORT CVQ::Lookup( const REAL* pVector, const SHORT nDim,
		 const SHORT nCode, REAL* pBestDist )
{
	int	i, code, bestcode;
	REAL	sum, tmp, bestdist;

	if( !pVector || nDim <= 0 || nCode <= 0 || !m_fCodebook.m_pprFvec ) {
		Warning("(CVQ::Lookup) invalid input");
		return( -1 );
	}
	for( sum = 0.0, i = 0 ; i < nDim ; i ++ ) {
		tmp = pVector[i] - m_fCodebook.GetFeature( 0, i );
		sum += tmp * tmp;
	}
	bestdist = sum;
	bestcode = 0;

	// search all the other codebook entries to find any with lower distance
	for( code = 1 ; code < nCode ; code ++ ) {
		tmp = pVector[0] - m_fCodebook.GetFeature( code, 0 );
		sum = tmp * tmp;
		for( i = 1 ; sum < bestdist && i < nDim ; i ++ ) {
			tmp	= pVector[i] - m_fCodebook.GetFeature( code, i );
			sum += tmp * tmp;
		}

		if( sum < bestdist ) {
			bestdist = sum;
			bestcode = code;
		}
	}

	// optionally return the best distance
	if( pBestDist != NULL )
		*pBestDist = bestdist;

	return( bestcode );
}


// LBG algorithm
// generate the VQ codebook of desired level = nDLevel
// from nVector samples of dimensionality nDim
BOOL CVQ::GenCodebook( CFVec& fvector, const SHORT nDLevel )
{
	SHORT	nCode, nNewCode, *pnSum;
	REAL	rSumdist, **pprSum;
	
	m_pfvec = &fvector;
	if( nDLevel <= 0 || m_pfvec->m_nVecDim <= 0 ) {
		Warning( "(CVQ::GenCodebook) illegal codebook size or dimension" );
		return FALSE;
	}

	NewCodebook( nDLevel, m_pfvec->m_nVecDim );

	pnSum = MallocSHORT( (int)nDLevel );
	pprSum = MallocREAL( nDLevel, m_pfvec->m_nVecDim );
	if( !pnSum || !pprSum ) {
		if( pnSum ) Mfree( pnSum );
		Warning( "(CVQ::GenCodebook) MallocREAL failed" );
		return FALSE;
	}
	
	// initialize
	Initialize();
	nCode = 1;

	BOOL bRet = TRUE;

	rSumdist = 0.0;
	while( bRet && nCode < nDLevel ) {
		// split L into 2L partitions
		nNewCode = ( (nCode<<1) > nDLevel ? nDLevel : (nCode<<1) );
		SplitCodebook( nCode, nNewCode );
		nCode = nNewCode;

		// classify the sample vector and update the codebook
		rSumdist = Update( nCode, rSumdist, pnSum, pprSum );
		if (rSumdist == -1.)
			bRet = FALSE;
	}

	Mfree( pnSum );
	Mfree( (void**) pprSum, nDLevel );
	
	return bRet;
}

// if the file list are given, generate the VQ codebook from files
BOOL CVQ::GenCodebook( CFilelist& filelist,
			 const SHORT nDim, const SHORT nDLevel )
{
	SHORT	nCode, nNewCode, *pnSum;
	REAL	rSumdist, **pprSum;
	
	if( !filelist.m_nFile || nDLevel <= 0 || nDim <= 0 ) {
		Warning( "(CVQ::GenCodebook) ( %d, %d, %d )",
			 filelist.m_nFile, nDLevel, nDim );
		return FALSE;
	}

	NewCodebook( nDLevel, nDim );
	pnSum = MallocSHORT( (int)nDLevel );
	pprSum = MallocREAL( nDLevel, nDim );
	if( !pnSum || !pprSum ) {
		if( pnSum ) Mfree( pnSum );
		Warning( "(CVQ::GenCodebook) MallocREAL failed" );
		return FALSE;
	}

	// initialize
	Initialize( filelist );
	nCode = 1;

	BOOL bRet = TRUE;

	rSumdist = 0.0;
	while( bRet && nCode < nDLevel ) {
		// split L into 2L partitions
		nNewCode = ( (nCode<<1) > nDLevel ? nDLevel : (nCode<<1) );
		SplitCodebook( nCode, nNewCode );
		nCode = nNewCode;

		// classify the sample vector and update the codebook
		rSumdist = Update( filelist, nCode, rSumdist, pnSum, pprSum );
		if (rSumdist == -1.)
			bRet = FALSE;
	}

	Mfree( pnSum );
	Mfree( (void**) pprSum, nDLevel );
	
	return bRet;
}

BOOL CVQ::GenCodebook( CFVec* pFVec, const SHORT nFVec, const SHORT nDLevel )
{
	SHORT	nDim, nCode, nNewCode, *pnSum;
	REAL	rSumdist, **pprSum;
	
	if( nFVec==0 || nDLevel <= 0 )
		return FALSE;

	nDim = pFVec[0].m_nVecDim;
	NewCodebook( nDLevel, nDim );
	pnSum = MallocSHORT( (int)nDLevel );
	pprSum = MallocREAL( nDLevel, nDim );
	if( !pnSum || !pprSum ) {
		if( pnSum ) Mfree( pnSum );
		Warning( "(CVQ::GenCodebook) MallocREAL failed" );
		return FALSE;
	}

	// initialize
	Initialize( pFVec, nFVec );
	nCode = 1;

	BOOL bRet = TRUE;

	rSumdist = 0.0;
	while( bRet && nCode < nDLevel ) {
		// split L into 2L partitions
		nNewCode = ( (nCode<<1) > nDLevel ? nDLevel : (nCode<<1) );
		SplitCodebook( nCode, nNewCode );
		nCode = nNewCode;

		// classify the sample vector and update the codebook
		rSumdist = Update( pFVec, nFVec, nCode, rSumdist, pnSum, pprSum );
		if (rSumdist == -1.)
			bRet = FALSE;
	}

	Mfree( pnSum );
	Mfree( (void**) pprSum, nDLevel );
	
	return bRet;
}
