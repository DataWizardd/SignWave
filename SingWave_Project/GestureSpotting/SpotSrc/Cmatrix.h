////////////////////////////////////////////////////////////////////////////
//
//         Programmed by Yun, YoungSun (ysyun@bulsai.kaist.ac.kr)
//
//                  Spoken Language Lab. CS, KAIST
//
//                        Date : 1996/Spring
//
///////////////////////////////////////////////////////////////////////////

#ifndef	_CMATRIX_HPP
#define	_CMATRIX_HPP

class CMatrix
{
	// constructor / destructor
public:
	CMatrix();
	~CMatrix();

	// attributes
	SHORT	m_nRow, m_nCol;
	REAL**	m_pprElt;	// matrix Row x Col
	REAL	m_rParity;	// if Row == Col, rDet is assigned by determinant
			// output as +- 1 depending on whether the number of
			// row interchange was even or odd
	SHORT*	m_pnIndex;	// an output vector that record the row permutation
						// effected by the partial pivoting.
	// implementation
private:
	BOOL	LUdecomp();
	void	LUBacksub(REAL *pb);	// right hand side vector

public:
	// single array of two-dimensional matrix [row][col]
	// return : determinant
	// input, output : pm
	REAL	InverseMatrix(REAL* pm, SHORT row, SHORT col);
	REAL	InverseMatrix(REAL** ppm, SHORT row, SHORT col);
};

#endif
