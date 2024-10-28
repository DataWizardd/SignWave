// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"
#include "utils.h"
#include "Cfvec.h"

const char cszMagicStr[MAGIC_SIZE] = "KAIST AI Lab FVector 1.0\n\004";


////////////////////////////////////////////////////////////////////////////
// CFVec
////////////////////////////////////////////////////////////////////////////


CFVec::CFVec()
{
	m_nVector = m_nVecDim = 0;
	m_pprFvec = NULL;
	m_bAliased = FALSE;
}


CFVec::~CFVec()
{
	if( !m_bAliased )
		Mfree( (void**) m_pprFvec, m_nVector );
}


////////////////////////////////////////////////////////////////////////////

BOOL CFVec::New( const SHORT nVector, const SHORT nVecDim )
{
	// Memory allocation
	if( !m_bAliased ) {
		// if the desired memory space is identical to the current space,
		// we clear the memory rather than allocating.
		if( m_pprFvec && m_nVector == nVector && 
			m_nVecDim == nVecDim ) {
			for( int i = 0 ; i < m_nVector ; i++ )
				memset( m_pprFvec[i], 0, sizeof(REAL)*m_nVecDim );
			return( TRUE );
		} else
			Mfree( (void**) m_pprFvec, m_nVector );
	} else
		m_bAliased = FALSE;

	// new allocate
	if( m_pprFvec  = MallocREAL( nVector, nVecDim ) ) {
		m_nVector = nVector;
		m_nVecDim = nVecDim;
		return( TRUE );
	} else
		return( FALSE );
}


////////////////////////////////////////////////////////////////////////////


BOOL CFVec::Read( const char* pszFileName, const SHORT nStart, const SHORT nEnd )
{
	FILE* fpin;
	SHORT   nVector, nVecDim;
	char  szMagic[MAGIC_SIZE];

	// file open and check the status of the fopen(...)
	if( !( fpin = fopen( pszFileName, "rb" ) ) ) {
		Warning( "(CFVec::Read) file <%s> not found", pszFileName );
		return( FALSE );
	}

	SetStatusMessage( "Reading feature file %s ......", pszFileName );

	// Read Header and check the header is correct.
	int r = MyRead( szMagic, 1, MAGIC_SIZE, fpin );
	if( r <= 0 || strcmp( szMagic, cszMagicStr ) ) {
		Warning( "(CFVec::Read) feature file is corrupted" );
		fclose( fpin );
		return( FALSE );
	}

	// read the number of frame and dimension
	if( MyRead( &nVector, sizeof( SHORT ), 1, fpin ) &&
		MyRead( &nVecDim, sizeof( SHORT ), 1, fpin ) ) {
		int nLen;

		if( !IsValidRange( nVector, nStart, nEnd ) ) {
			Warning( "(CFvevc::Read) out of range" );
			fclose( fpin );
			return( FALSE );
		}

		if( nEnd > 0 )
			nLen = nEnd - nStart + 1;
		else
			nLen = nVector - nStart;

		New( nLen, nVecDim );

		// jump to the reading position.
		fseek( fpin, nStart*m_nVecDim*sizeof( REAL ), 1 );

		// Read the vectors
		for( int i = 0 ; i < nLen ; i ++ ) {
			if( !MyRead( m_pprFvec[i], sizeof( REAL ), m_nVecDim, fpin ) ) {
				Warning( "(CFVec::Read) feature file is corrupted" );
				Mfree( (void**) m_pprFvec, nLen );
				fclose( fpin );
				return( FALSE );
			}
		}
		m_nVector = nLen;
	} else {
		Warning( "(CFVec::Read) feature file is corrupted" );
		fclose( fpin );
		return( FALSE );
	}

	fclose( fpin );
	return( TRUE );
}


BOOL CFVec::ReadText( const char* pszFileName )
{
	FILE    *fp;
	int     nVector, nVecDim;
    
	if( !(fp = fopen( pszFileName, "r" )) ) {
		Warning( "(CFVec::ReadText) file <%s> not found", pszFileName );
		return( FALSE );
	}

	SetStatusMessage( "Reading feature file %s ......", pszFileName );

	// read header
	if( !fscanf_s( fp, "# NumVector : %d\n", &nVector ) ||
		!fscanf_s( fp, "# NumVectorDimension : %d\n", &nVecDim ) ) {
		Warning( "(CFVec::ReadText) feature file is corrupted" );
		fclose( fp );
		return( FALSE );
	}

	New( nVector, nVecDim );

	int i, j;
	REAL rTmp;
	while( fscanf_s( fp, "%d%d%g", &i, &j, &rTmp ) > 0 ) {
		if( i < 0 || i >= m_nVector || j < 0 || j >= m_nVecDim ) {
			Warning( "(CFVec::ReadText) feature file is corrupted" );
			Mfree( (void**) m_pprFvec, m_nVector );
			fclose( fp );
			return( FALSE );
		} else
			m_pprFvec[i][j] = rTmp;
	}

	fclose( fp );
	return( TRUE );
}


////////////////////////////////////////////////////////////////////////////


BOOL CFVec::Write( const char* pszFileName, const SHORT nStart, const SHORT nEnd )
{
	FILE* fpout;

	// file open and check the status of the fopen(...)
	if( !( fpout = fopen( pszFileName, "wb" ) ) ) {
		Warning( "(CFVec::Write) file <%s> not found", pszFileName );
		return( FALSE );
	}

	SetStatusMessage( "Writing feature file %s ......", pszFileName );

	if( !IsValidRange( m_nVector, nStart, nEnd ) ) {
		Warning( "(CFVec::Write) out of range" );
		return( FALSE );
	}

	// header write
	if( MyWrite( cszMagicStr, 1, MAGIC_SIZE, fpout ) <= 0 ) {
		Warning( "(CFVec::Write) write error" );
		return( FALSE );
	}

	int nLen = nEnd - nStart + 1;
	// read the number of frame and dimension
	MyWrite( &nLen, sizeof( SHORT ), 1, fpout );
	MyWrite( &m_nVecDim, sizeof( SHORT ), 1, fpout );

	for( int i = nStart ; i <= nEnd ; i ++ )
		MyWrite( m_pprFvec[i], m_nVecDim, sizeof( REAL ), fpout );

	fclose( fpout );
	return( TRUE );
}


BOOL CFVec::WriteText( const char* pszFileName )
{
	FILE    *fp;
    
	if( !(fp = fopen( pszFileName, "w" )) ) {
		Warning( "(CFVec::WriteText) file <%s> not found", pszFileName );
		return( FALSE );
	}

	SetStatusMessage( "Writing feature file %s ......", pszFileName );

	// write header
	fprintf( fp, "# NumVector : %d\n", m_nVector );
	fprintf( fp, "# NumVectorDimension : %d\n", m_nVecDim );

	for( int i = 0; i < m_nVector ; i++ ) {
		for( int j = 0 ; j < m_nVecDim ; j++ )
			fprintf( fp, "%d\t%d\t%g\n", i, j, *(m_pprFvec[i]+j) );
		fputc( '\n', fp );
	}

	fclose( fp );
	return( TRUE );
}


////////////////////////////////////////////////////////////////////////////


BOOL CFVec::Alias( const CFVec& wave, const SHORT nStart, const SHORT nLen )
{
	if( nLen <= 0 || ( nStart+nLen ) > wave.m_nVector ) {
		Warning( "(CFVec::Alias) out of range" );
		return( FALSE );
	}

	if( !m_bAliased )
		Mfree( (void**) m_pprFvec, m_nVector );

	m_nVector  = nLen;
	m_nVecDim  = wave.m_nVecDim;
	m_pprFvec  = wave.m_pprFvec + nStart;
	m_bAliased = TRUE;

	return( TRUE );
}


////////////////////////////////////////////////////////////////////////////

CFVec&	CFVec::operator=(const CFVec& fvec)
{
	if( !m_bAliased ) {
		Mfree( (void**) m_pprFvec, m_nVector );
		m_pprFvec = NULL;
	}

	if( fvec.m_pprFvec ) {
		New( fvec.m_nVector, fvec.m_nVecDim );
  
		for( int i = 0 ; i < m_nVector ; i ++ )
			memcpy( m_pprFvec[i], fvec.m_pprFvec[i], m_nVecDim * sizeof( REAL ) );
	}
  
	return( *this );
}

void CFVec::DeltaFeature(SHORT shift)
{
	SHORT	nmax = m_nVecDim - shift;
	REAL* preal;

	if( !(preal=new REAL[m_nVecDim]) )
		Warning( "(CFVec::DeltaFeature) preal allocation error" );

	if( m_pprFvec ) {
		int	  i, j;

		for( i = 0 ; i < m_nVector ; i ++ ) {
			for( j = 0 ; j < shift ; j ++ )
				preal[j] = m_pprFvec[i][j];

			for( j = shift ; j < nmax ; j ++ )
				preal[j] = m_pprFvec[i][j + shift] - m_pprFvec[i][j - shift];  

			for( ; j < m_nVecDim ; j ++ )
				preal[j] = m_pprFvec[i][j];
		}
	}

	delete[] preal;
}

CFVec&	CFVec::DeltaFeature(const CFVec& fvec, SHORT shift)
{
	SHORT	nmax = m_nVecDim - shift;

	if( !m_bAliased ) {
		Mfree( (void**) m_pprFvec, m_nVector );
		m_pprFvec = NULL;
	}

	if( fvec.m_pprFvec ) {
		int	i, j;
		New( fvec.m_nVector, fvec.m_nVecDim );
  
		for( i = 0 ; i < m_nVector ; i ++ ) {
			for( j = 0 ; j < shift ; j ++ )
				m_pprFvec[i][j] = fvec.m_pprFvec[i][j];

			for( j = shift ; j < nmax ; j ++ )
				m_pprFvec[i][j] = fvec.m_pprFvec[i][j + shift] -
					fvec.m_pprFvec[i][j - shift];  

			for( ; j < m_nVecDim ; j ++ )
				m_pprFvec[i][j] = fvec.m_pprFvec[i][j];
		}
	}
  
	return( *this );
}


////////////////////////////////////////////////////////////////////////////

REAL CFVec::GetFeature( const SHORT nRow, const SHORT nCol )
{
	if( m_pprFvec )
		return( m_pprFvec[nRow][nCol] );
	else
		return( 0.0 );
}

BOOL CFVec::SetFeature( const SHORT nRow, const SHORT nCol, const REAL rVal )
{
	if( m_pprFvec )
		m_pprFvec[nRow][nCol] = rVal;
	else
		return( FALSE );
	return( TRUE );
}

////////////////////////////////////////////////////////////////////////////

REAL* CFVec::GetMeanVec()
{
	int   i, j;
	REAL* prMean;

	prMean = MallocREAL( m_nVecDim );
	for( i = 0 ; i < m_nVecDim ; i ++ ) {
		prMean[i] = 0.0;
		for( j = 0 ; j < m_nVector ; j ++ )
			prMean[i] += m_pprFvec[j][i];
		prMean[i] /= m_nVector;
	}

	return( prMean );
}

// Mean Normalize is well used in Cepstral feature comparison
// In this case, we call the following method to Cepstral Mean
// Normalization (CMN) or Cepstral Mean Substraction (CMS).
// 
void CFVec::MeanNormalize()
{
	int i, j;
	REAL mean;

	for( i = 0 ; i < m_nVecDim ; i ++ ) {
		for( mean = 0.0, j = 0 ; j < m_nVector ; j ++ )
			mean += m_pprFvec[j][i];
  
		mean /= m_nVector;

		for( j = 0 ; j < m_nVector ; j ++ )
			m_pprFvec[j][i] -= mean;
	}
}

void CFVec::MeanNormalize( REAL* prMean )
{
	int i, j;
  
	// already we get the means 
	for( i = 0 ; i < m_nVecDim ; i ++ )
		for( j = 0 ; j < m_nVector ; j ++ )
			m_pprFvec[j][i] -= prMean[i];
}


// RASTA High Pass Filter
// Hermansky, H., Morgran, N., Bayya, A., Kohn, P.
//	"RASTA-PLP Speech Analysis Technique",
//	ICASSP-92, pages 121-124, March, 1992.

void CFVec::RastaHPF()
{
	int	i, j;
	REAL*	preal;

	preal = new REAL [m_nVector];
	for( i = 0 ; i < m_nVecDim ; i ++ ) {
		preal[0] = m_pprFvec[0][i];

		for( j = 1 ; j < m_nVector ; j ++ )
			preal[j] = m_pprFvec[j][i] - m_pprFvec[j-1][i] + 0.97 * preal[j-1];

		for( j = 1 ; j < m_nVector ; j ++ )
			m_pprFvec[j][i] = preal[j];
	}
	delete[] preal;
}

void CFVec::GetUnitVector()
{
	int i, j;
	REAL sum;
    
	for( i = 0 ; i < m_nVector ; i ++ ) {
		for( sum = 0.0, j = 0 ; j < m_nVecDim ; j ++ )
			sum += m_pprFvec[i][j];
    
		for( j = 0 ; j < m_nVecDim ; j ++ )
			m_pprFvec[i][j] /= sum;
	}
}
