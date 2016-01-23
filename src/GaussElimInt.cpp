///////////////////////////////////////////////////////
// File: main.cpp
// Desc: Integer Gaussian Elimination
//
// Author: Zhang Kang
// Date: 2014/03/05
///////////////////////////////////////////////////////

/* Here is a pseudo code form wiki
for k = 1 ... m:
   Find pivot for column k:
   i_max  := argmax (i = k ... m, abs(A[i, k]))
   if A[i_max, k] = 0
     error "Matrix is singular!"
   swap rows(k, i_max)
   Do for all rows below pivot:
    for i = k + 1 ... m:
     Do for all remaining elements in current row:
      for j = k ... n:
       A[i, j]  := A[i, j] - A[k, j] * (A[i, k] / A[k, k])
     Fill lower triangular matrix with zeros:
     A[i, k]  := 0
*/

#include<iostream>
#include<fstream>
using namespace std;

// lcm -- lowest common multple
int lcm( int x, int y )
{
	while( y != 0 ) {
		int t = x % y;
		x = y;
		y = t;
	}
	return x;
}


// print mat
void PrintMat( int* A, const int m, const int n )
{
	for( int i = 0; i < m; i ++ ) {
		for( int j = 0; j < n; j ++ ) {
			cout << A[ i * n + j ] << " ";
		}
		cout << endl;
	}
}
// swap two rows
void SwapRow( int* A, const int n, const int k, const int iMax )
{
	int* pK = A + k * n;
	int* pI = A + iMax * n;
	for( int j = 0; j < n; j ++ ) {
		int tmp = pK[ j ];
		pK[ j ] = pI[ j ];
		pI[ j ] = tmp;
	}
}
// Integer Gaussian Elimiation
void GaussElimInt( int* A, const int m, const int n )
{
	for( int k = 0; k < m; k ++ ) {
		// find pivot row (partial pivoting)
		int iMax = k;
		int aMax = A[ k * n + k ];
		for( int i = k; i < m; i ++ ) {
			if( abs( A[ i * n + k ] ) > aMax ) {
				aMax = abs( A[ i * n + k ] );
				iMax = i;
			} 
		}
		if( aMax == 0 ) {
			cout << "Matrix is singular" << endl;
		}
		// swap pivot row with current row
		SwapRow( A, n, k, iMax );
#ifdef _DEBUG
		PrintMat( A, m, n );
#endif
		// eliminate remaining row
		for( int i = k + 1; i < m; i ++ ) {
			int l = lcm( A[ i * n + k ], A[ k * n + k ] );
			int multiK = A[ i * n + k ] / l;
			int multiI = A[ k * n + k ] / l;
			
			for( int j = k; j < n; j ++ ) {
				A[ i * n + j ] = A[ i * n + j ] * multiI -
					A[ k * n + j ] * multiK;
			}
			// set bottom to zero
			// A[ i * n + k ] = 0;
		}

#ifdef _DEBUG
		PrintMat( A, m, n );
#endif
	}
}
int main( void )
{
	int m, n;

	cout << "Matrix dim: ";
#ifdef _DEBUG
	ifstream fin( "in.txt" );
	fin >> m >> n;
	int* A = new int[ m * n ];
	for( int i = 0; i < m; i ++ ) {
		for( int j = 0; j < n; j ++ ) {
			fin >> A[ i * n + j ];
		}
	}
#else
	cin >> m >> n;
	int* A = new int[ m * n ];
	for( int i = 0; i < m; i ++ ) {
		for( int j = 0; j < n; j ++ ) {
			cin >> A[ i * n + j ];
		}
	}
#endif
	cout << "Input Mat: " << endl;
	PrintMat( A, m, n );
	cout << "Gaussian Elimination: " << endl;
	GaussElimInt( A, m, n );
	PrintMat( A, m, n );
	delete [] A;
	return 0;
}