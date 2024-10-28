////////////////////////////////////////////////////////////////////////////
//
//         Programmed by Yun, YoungSun (ysyun@bulsai.kaist.ac.kr)
//
//                  Spoken Language Lab. CS, KAIST
//
//                        Date : 1995/Fall
//
///////////////////////////////////////////////////////////////////////////

#ifndef	_CFVEC_HPP
#define	_CFVEC_HPP

class CFVec
{
public:
	CFVec();
	~CFVec();

  // Attributes
private:
	BOOL	m_bAliased;	// TRUE if the wave data is aliased
  
public:
	SHORT	m_nVector;	// the number of wave sample
	SHORT	m_nVecDim;	// Vector Dimension
	REAL**	m_pprFvec;	// real

	// Operations
public:
	// get size & dimension
	SHORT	GetSize()	{ return( m_nVector ); }
	SHORT	GetDimension()	{ return( m_nVecDim ); }

	// resize the feature vector space
	BOOL	New( const SHORT nFrame, const SHORT nVecDim );

	// Read
	BOOL	Read( const char* pszFileName ) {
				  return Read( pszFileName, 0, -1 );
				}
	BOOL	Read( const char* pszFileName,
				  const SHORT nStart, const SHORT nEnd );
	BOOL	ReadText( const char* pszFileName );

	// Write
	BOOL	Write( const char* pszFileName ) {
				  return Write(pszFileName, 0, m_nVector-1);
				}

	BOOL	Write( const char* pszFileName,
				   const SHORT nStart, const SHORT nEnd );
	BOOL	WriteText( const char* pszFileName );

	// Get/Set
	REAL	GetFeature( const SHORT nRow, const SHORT nCol );
	BOOL	SetFeature( const SHORT nRow, const SHORT nCol, const REAL rVal );

	// Normalize and Some Operations
	REAL*	GetMeanVec( void );		// get mean vector
	void	MeanNormalize( void );		// make zero mean
	void	MeanNormalize( REAL* rMean );	// make zero mean
	void	RastaHPF();			// make RASTA-HPF

	void	GetUnitVector(void);

	// Share the feature vector
	BOOL	Alias( const CFVec& wave,
				   const SHORT nStart, const SHORT nLen );
	// Operator
	CFVec&	operator=(const CFVec& wave);

	// Difference
	void	DeltaFeature(SHORT shift);
	CFVec&	DeltaFeature(const CFVec& fvec, SHORT shift);
};

#endif	// _CFVEC_HPP
