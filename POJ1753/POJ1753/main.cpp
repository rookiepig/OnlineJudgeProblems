///////////////////////////////////////////////////////
// File: main.cpp
// Desc: POJ1753 -- gaussian elimination
//
// Author: Zhang Kang
// Date: 2014/03/06
///////////////////////////////////////////////////////

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iomanip>
using namespace std;

// #define _DETAIL

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
			cout << setw( 6 ) << A[ i * n + j ];
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
		if( aMax != 0 ) {
			// aMax == 0 --> no need to elim

			// swap pivot row with current row
			SwapRow( A, n, k, iMax );
#ifdef _DETAIL
			PrintMat( A, m, n );
#endif
			// eliminate remaining row
			for( int i = k + 1; i < m; i ++ ) {
				if( A[ i * n + k ] != 0 ) {
					int l = lcm( A[ i * n + k ], A[ k * n + k ] );
					int multiK = A[ i * n + k ] / l;
					int multiI = A[ k * n + k ] / l;

					for( int j = k; j < n; j ++ ) {
						A[ i * n + j ] = ( ( A[ i * n + j ] * multiI ) % 2 -
							( A[ k * n + j ] * multiK ) % 2 + 2 ) % 2;
					}
					// set bottom to zero
					// A[ i * n + k ] = 0;
				}
			}

#ifdef _DETAIL
			PrintMat( A, m, n );
#endif
		}
	}
}

// is feasible (A is augment matrix, last col is b)
bool IsFeasible( int* A, int m, int n )
{
	for( int i = m - 1; i >= 0; i -- ) {
		int* pA = A + i * n;
		for( int j = 0; j < n - 1; j ++ ) {
			if( pA[ j ] != 0 ) {
				return true;
			}
		}
		if( pA[ n - 1 ] != 0 ) {
			return false;
		}
	}
}

// set non-free vriable flag
void SetNonFreeVar( int* A, int m, int n, int* xFlag )
{
	for( int i = 0; i < m; i ++ ) {
		int* pA = A + i * n;
		for( int j = 0; j < n - 1; j ++ ) {
			if( pA[ j ] != 0 ) {
				xFlag[ j ] = 1;
				break;
			}
		}
	}
}

void BackSub( int* A, int m, int n, int*  xSol )
{
	// m == n -1
	int varNum = n - 1;
	for( int i = varNum - 1; i >= 0; i -- ) {
		int* pA = A + i * n;
		int sum = pA[ n ] % 2;
		for( int j = varNum  - 1; j > i; j --  ) {
			sum = ( sum -  ( pA[ j ] * xSol[ j ] ) % 2 + 2 ) % 2;
		}
		xSol[ i ] = ( sum / pA[ i ] ) % 2;
	}
}
// get solution
void GetSolution( int* A, int m, int n, bool& bFease, int* xSol )
{
	bFease = IsFeasible( A, m, n );
	if( bFease ) {
		int varNum = n - 1;
		int* nonFree = new int[ varNum ] ();
		SetNonFreeVar( A, m, n, nonFree );
		bool multiSol = false;
		for( int i = 0; i < varNum; i ++ ) {
			if( nonFree[ i ] == 0 ) {
				multiSol = true;
				break;
			}
		}
		if( multiSol ) {
			// multiple solution
			cout << "Multi Solution" << endl;
		} else{
			// single solution
			BackSub( A, m, n, xSol );
		}

		delete [] nonFree;
	}
}
int main( void )
{
#ifdef _DEBUG
	// redirect file stream to cin
	fstream fIn( "in.txt" );
	streambuf* cinBuf = cin.rdbuf( );
	cin.rdbuf( fIn.rdbuf() );
#endif
	// input board
	vector<string> brd;
	string buf;
	int lineNum = 0;
	const int BRD_HEI = 4;
	while( cin >> buf ) {
		if( lineNum >= BRD_HEI ) {
			break;
		}
		brd.push_back( buf );
		lineNum ++;
	}
	// init augment matrix
	int brdWid = buf.length();
	int brdHei = BRD_HEI;
	int n = brdHei * brdWid;
	// value initialization
	int* A = new int[ n * ( n + 1 ) ] ();
	for( int i = 0; i < n; i ++ ) {
		int* pA = A + i * ( n + 1 );
		int iR = i / brdWid;
		// set coefficient
		pA[ i ] = 1;
		// left
		if( ( i - 1 ) >= brdWid * iR ) {
			pA[ i - 1 ] = 1;
		}
		// right
		if( ( i + 1 ) < brdWid * ( iR + 1 ) ) {
			pA[ i + 1 ] = 1;
		}
		// top
		if(  i - 4  >= 0  ) {
			pA[ i - 4 ] = 1;
		}
		// top
		if( i + 4  < n ) {
			pA[ i + 4 ] = 1;
		}
		// set b
		if( brd[ i / brdWid ][ i % brdWid ] == 'w' ) {
			pA[ n ] = 1;
		}
	}
	// two possible solution
	int* B = new int[ n * ( n + 1 ) ] ();
	memcpy( B, A, n * ( n + 1 ) * sizeof( int ) );
	for( int i = 0; i < n; i ++ ) {
		int* pB = B + i * ( n + 1 );
		// set b
		if( brd[ i / brdWid ][ i % brdWid ] == 'b' ) {
			pB[ n ] = 1;
		} else {
			pB[ n ] = 0;
		}
	}
	// Gauss Elimination
	GaussElimInt( A, n, n + 1 );
	GaussElimInt( B, n, n + 1 );

	// Get solution
	int* aSol = new int [ n ] ();
	bool aFease;
	GetSolution( A, n, n + 1, aFease, aSol );
	int minA = 0;
	for( int i = 0; i < n; i ++ ) {
		minA += aSol[ i ];
	}
	
	int* bSol = new int [ n ] ();
	bool bFease;
	GetSolution( B, n, n + 1, bFease, bSol );
	int minB = 0;
	for( int i = 0; i < n; i ++ ) {
		minB += bSol[ i ];
	}

#ifdef _DEBUG
	cout << "aFease: " << aFease << " minA: " << minA << endl;
	cout << "bFease: " << bFease << " minB: " << minB << endl;
	cout << "B: \n";
	PrintMat( B, n, n + 1 );
	cout << "After GE:\n";
	PrintMat( A, n, n + 1 );
	// restore cin buf
	cin.rdbuf( cinBuf );
#endif

	delete [] A;
	delete [] B;
	delete [] aSol;
	delete [] bSol;
	return 0;
}
