///////////////////////////////////////////////////////
// File: Matrix.h
// Desc: A simple Matrix class
//
// Author: Zhang Kang
// Date: 2014/03/05
///////////////////////////////////////////////////////

template <class Type>
class Matrix {
private:
	int     m;		// row number
	int     n;	    // col number
	Type* _rep;     // data

public:
	//
	// Constructor & Desctructor
	//
	Matrix( int r, int c ) : m( r ), n( c )  { _rep = new Type [ n * n ]; }
	Matrix( int r, int c, Type  M[ ] );
	Matrix( const Matrix& );
	const Matrix& operator = ( const Matrix& );
	~Matrix( ) { if( _rep ) delete [] _rep; }

	const Type& operator () ( int r, int c ) const { return _rep[ r * n + c ]; }
	Type& operator () ( int r, int c) { return _rep[ r * n + c ]; }
	// output
	friend ostream& operator << ( ostream& o, const Matrix<Type>& M ) {
		int i, j;
		for (i = 0; i < M.m; i++) {
			for (j = 0; j < M.n; j++) {
				o << M(i, j) << " ";
			}
			o << endl;
		}
		return o;
	}
};

template <class Type>
Matrix<Type>::Matrix( int r, int c, Type M[] ) : m( r ), n( c ) {
	int i, j;
	_rep   = new Type [ m * n ];
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			_rep[i * n + j] = M[i * n + j];
}


template <class Type>
Matrix<Type>::Matrix(const Matrix& M) : m( M.n ), n( M.n ) {
	int i, j;
	_rep   = new Type [n*n];
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			_rep[i * n + j] = M._rep[i * n + j];
}
template <class Type>
const Matrix<Type>& Matrix<Type>::operator = ( const Matrix& M ) {
	int i, j;
	if ( m != M.m || n != M.n) {
		delete [] _rep;
		m = M.m;
		n = M.n;
		_rep = new Type [ m * n];
	}
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			_rep[ i * n + j ] = M._rep[i * n + j];
	return *this;
}


