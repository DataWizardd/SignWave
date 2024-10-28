// #include "pch.h"
#include <SDKDDKVer.h>       // by hklee

#include "stdafx.h"
#include "Spot.h"
#include "utils.h"
#include <math.h>
#include "Cmatrix.h"

#define	TINY	1.0e-20

// Reference :Numerical Recipes in C -- The Art of Scientific Computing -- 2nd
// CAMBRIDGE UNIVERSITY PRESS pp. 43-49
//
CMatrix::CMatrix()
{
}

CMatrix::~CMatrix()
{
}

//
// Given a matrix a[1..n][1..n], this routine replaces it by the LU
// decomposition of a rowwise permutation of itself.
// Source Book: Numerical Recipes in C pp 46.
//
BOOL CMatrix::LUdecomp()
{
	int i, imax, j, k, n;
	REAL big, dum, sum, temp;
	REAL *vv;

	if( m_nRow != m_nCol )
		Warning( "(CMatrix::LUdecomp) row and col are mismatch!" );
	n = m_nRow;
	
	vv = new REAL[n];
	m_rParity = 1.0;
	
	for( i = 0 ; i < n ; i ++ ) {
		big = 0.0;
		for( j = 0 ; j < n ; j ++ )
			if( (temp=fabs(m_pprElt[i][j])) > big ) big=temp;
		if( big == 0.0 ) {
			Warning( "(CMatrix::LUdecomp) Singular matrix in routine LUdecomp" );
			delete[] vv;
			return 0;
		}
		// No nonzero largest element.
		vv[i] = 1.0 / big;	// Save the scaling
	}

	for( j = 0 ; j < n ; j ++ ) {
		// this is the loop over columns of Crout's method.
		for( i = 0 ; i < j ; i ++ ) {
			// this is equation (2.3.12) except for i = j
			sum = m_pprElt[i][j];
			for( k = 0 ; k < i ; k ++ )
				sum -= m_pprElt[i][k] * m_pprElt[k][j];
			m_pprElt[i][j] = sum;
		}
		// initialize for the search for largest pivot element.
		big = 0.0;
		for( i = j ; i < n ; i ++ ) {
			// this is i = j of equation (2.3.12) and i = j+1,..N
			sum = m_pprElt[i][j];
			for( k = 0 ; k < j ; k ++ )
				sum -= m_pprElt[i][k] * m_pprElt[k][j];
			m_pprElt[i][j] = sum;
			if( (dum=vv[i]*fabs(sum)) >= big ) {
				// is the figure of merit for the pivot better than the best so far
				big = dum;
				imax = i;
			}
		}
		if( j != imax ) {	// do we need to interchange rows?
			for( k = 0 ; k < n ; k ++ ) {	// yes, do so..
				dum = m_pprElt[imax][k];
				m_pprElt[imax][k] = m_pprElt[j][k];
				m_pprElt[j][k] = dum;
			}
			m_rParity = -m_rParity;		// and change the parity of d
			vv[imax] = vv[j];		// also interchange the scale factor
		}
		m_pnIndex[j] = imax;
		if( m_pprElt[j][j] == 0.0 )
			m_pprElt[j][j] = TINY;
		// if the pivot element is zero the matrix is singluar (at least to
		// the precision of the algorithm). For some applications on singular
		// matrics, it is desirable to substitue TINY for zero.
		if( j != n ) {
			dum = 1.0 / m_pprElt[j][j];
			for( i = j + 1 ; i < n ; i ++ )
				m_pprElt[i][j] *= dum;	// now finally, divide by the pivot element
		}
	}

	delete[] vv;
	return 1;
}

void CMatrix::LUBacksub(REAL* pb)
{
	int i, ip, j, n=m_nRow;
	REAL sum;

	// when ii is set to a positive value, it will become the index of the
	// first nonvanishing element of pb. We now do the forward substitution,
	// equation (2.3.6). The only new wrinkle is to unscramble the permutation
	// as we go.
	for( i = 0 ; i < n ; i ++ ) {
		ip = m_pnIndex[i];
		sum = pb[ip];
		pb[ip] = pb[i];
		for( j = 0 ; j <= i - 1 ; j ++ )
			sum -= m_pprElt[i][j] * pb[j];
		pb[i] = sum;
	}

	// now we do the backsubstitution, equation (2.3.7)
	for( i = n - 1 ; i >= 0 ; i -- ) {
		sum = pb[i];
		for( j = i + 1 ; j < n ;j ++ )
			sum -= m_pprElt[i][j] * pb[j];

		// store a component of the solution vector X.
		pb[i] = sum / m_pprElt[i][i];
	}
}

REAL CMatrix::InverseMatrix(REAL* pm, SHORT row, SHORT col)
{
	int		i, j, r;
	double dbDet = 0.0;

	if( row != col ) {
		Warning( "(CMatrix::InverseMatrix" );
		return 0.0;
	}
	m_nRow = row, m_nCol = col;
	
	// copy
	if( !( m_pnIndex = new SHORT[row] ))
		Warning( "(CMatrix::inverseMatrix) m_pnIndex new fail" );

	if( !( m_pprElt = new REAL*[row] ))
		Warning( "(CMatrix::InverseMatrix) m_pprElt new fail" );
	
	for( i = 0 ; i < row ; i ++ ) {
		if( !( m_pprElt[i] = new REAL[col] ))
			Warning( "(CMatrix::InverseMatrix) m_pprElt[i] new fail" );

		r = i*col;
		for( j = 0 ; j < col ; j ++ )
			m_pprElt[i][j] = pm[r + j];
	}

	if( LUdecomp() ) {
		REAL* pcol, de;
		if( !(pcol = new REAL[row]) )
			Warning( "(CMatrix::InverseMatrix) pcol new fail" );

		for( j = 0 ; j < col ; j ++ ) {
			if( m_pprElt[j][j] == 0.0 )
				Warning( "(CMatrix::InverseMatrix) diag elt[%d][%d] is zero.", j, j );

			if( ( de = m_pprElt[j][j] ) < 0 ) {
				de = -de;
				m_rParity = -m_rParity;
			}
			dbDet += log( (double) de );	// determinant

			for( i = 0 ; i < row ; i ++ )
				pcol[i] = 0;
			pcol[j] = 1.0;

			LUBacksub( pcol );
			for( i = 0 ; i < row ; i ++ )
				pm[i*col + j] = pcol[i];
		}

		delete[] pcol;
	}

	// free the temporary memory
	for( i = 0 ; i < row ; i ++ )
		delete[] m_pprElt[i];
	delete[] m_pprElt;
	delete[] m_pnIndex;

	return (exp(dbDet) * m_rParity);
}

REAL CMatrix::InverseMatrix(REAL** ppm, SHORT row, SHORT col)
{
	int	 i, j;
	double dbDet = 0.0;

	if( row != col ) {
		Warning( "(CMatrix::InverseMatrix" );
		return 0.0;
	}
	m_nRow = row, m_nCol = col;
	
	// copy
	if( !( m_pnIndex = new SHORT[row] ))
		Warning( "(CMatrix::inverseMatrix) m_pnIndex new fail" );
	
	if( !( m_pprElt = new REAL*[row] ))
		Warning( "(CMatrix::InverseMatrix) m_pprElt new fail" );

	for( i = 0 ; i < row ; i ++ ) {
		if( !( m_pprElt[i] = new REAL[col] ))
			Warning( "(CMatrix::InverseMatrix) m_pprElt[i] new fail" );

		for( j = 0 ; j < col ; j ++ )
			m_pprElt[i][j] = ppm[i][j];
	}

	if( LUdecomp() ) {
		REAL* pcol, de;
		if( !(pcol = new REAL[row]) )
			Warning( "(CMatrix::InverseMatrix) pcol new fail" );

		for( j = 0 ; j < col ; j ++ ) {
			if( m_pprElt[j][j] == 0.0 )
				Warning( "(CMatrix::InverseMatrix) diag elt[%d][%d] is zero.", j, j );

			if( ( de = m_pprElt[j][j] ) < 0 ) {
				de = -de;
				m_rParity = -m_rParity;
			}
			dbDet += log( (double) de );	// determinant

			for( i = 0 ; i < row ; i ++ )
				pcol[i] = 0;
			pcol[j] = 1.0;

			LUBacksub( pcol );
			for( i = 0 ; i < row ; i ++ )
				ppm[i][j] = pcol[i];
		}

		delete[] pcol;
	}

	// free the temporary memory
	for( i = 0 ; i < row ; i ++ )
		delete[] m_pprElt[i];
	delete[] m_pprElt;
	delete[] m_pnIndex;

	dbDet = exp( dbDet );
	return (dbDet * m_rParity);
}
