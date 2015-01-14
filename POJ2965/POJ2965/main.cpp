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
						A[ i * n + j ] = ( ( A[ i * n + j ] * multiI )  -
							( A[ k * n + j ] * multiK )  );
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
  int rank = m;
  int flag = 1;
	for( int i = m - 1; i >= 0 && flag; i -- ) {
		int* pA = A + i * n;
		for( int j = 0; j < n - 1; j ++ ) {
			if( pA[ j ] != 0 ) {
        flag = 0;
        break;
			}
		}
    rank--;
	}
  if (rank >= n) {
    return true;
  }
  else {
    return false;
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
		if( pA[ i ] == 0 ) {
			// free variable no need to solve
			continue;;
		}
		int sum = pA[ n - 1 ] % 2;
		for( int j = varNum  - 1; j > i; j --  ) {
			sum = ( sum -  ( pA[ j ] * xSol[ j ] ) % 2 + 2 ) % 2;
		}
		xSol[ i ] = ( sum / pA[ i ] ) % 2;
	}
}

// global var to record solution
int  minStep = 1e10;
int* minSol = 0;
void EnumSol( int* A, int m, int n, int* nonFree, int nfNum, int* xSol )
{
	if( nfNum == 0 ) {
		// no free variable --> back sub
		BackSub( A, m, n, xSol );
		// stat result
		int curStep = 0;
		for( int i = 0; i < n - 1; i ++ ) {
			if( xSol[ i ] ) {
				curStep ++;
			}
		}
		if( curStep < minStep ) {
			// record new min sol
			minStep = curStep;
			memcpy( minSol, xSol, ( n - 1 ) * sizeof( int ) );
		}
	} else {
		// enumarate all non free var
		for( int i = 0; i < n - 1; i ++ ) {
			if( nonFree[ i ] == 0 ) {
				nonFree[ i ] = 1;
				xSol[ i ] = 0; 
				EnumSol( A, m, n, nonFree, nfNum - 1, xSol );
				xSol[ i ] = 1; 
				EnumSol( A, m, n, nonFree, nfNum - 1, xSol );
				nonFree[ i ] = 0;
			}
		}
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
#ifdef _DEBUG
			cout << "Multi Solution" << endl;
			PrintMat( A, m, n );
#endif
			// get non free num
			int nfNum = 0;
			for( int i = 0; i < varNum; i ++ ) {
				if( nonFree[ i ] == 0 ) {
					nfNum ++;
				}
			}
			EnumSol( A, m, n, nonFree, nfNum, xSol );
		} else{
			// single solution
			BackSub( A, m, n, xSol );
			// stat result
			int curStep = 0;
			for( int i = 0; i < n - 1; i ++ ) {
				if( xSol[ i ] ) {
					curStep ++;
				}
			}
			if( curStep < minStep ) {
				// record new min sol
				minStep = curStep;
				memcpy( minSol, xSol, ( n - 1 ) * sizeof( int ) );
			}
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
		brd.push_back( buf );
		lineNum ++;
		if( lineNum >= BRD_HEI ) {
			break;
		}
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
		// same row
		int curRow = i / brdWid;
		for( int j = 0; j < brdWid; j ++ ) {
			pA[ curRow * brdWid + j ] = 1;
		}
		// same col
		int curCol = i % brdWid;
		for( int j = 0; j < brdHei; j ++ ) {
			pA[ j * brdWid + curCol ] = 1;
		}
		// set b
		if( brd[ i / brdWid ][ i % brdWid ] == '+' ) {
			pA[ n ] = 1;
		}
	}

#ifdef _DEBUG
	cout << "A: \n";
	PrintMat( A, n, n + 1 );
#endif
	// Gauss Elimination
	GaussElimInt( A, n, n + 1 );

	// Get solution
	minSol = new int [ n ] ();

	int* aSol = new int [ n ] ();
	bool aFease = false;
	GetSolution( A, n, n + 1, aFease, aSol );
	int minA = 0;
	for( int i = 0; i < n; i ++ ) {
		minA += minSol[ i ];
	}

	if( aFease  ) {
		cout << minStep << endl;
		for( int i = 0; i < n; i ++ ) {
			if( minSol[ i ] ) {
				cout << i / brdWid + 1 << " " << i % brdWid + 1 << endl;
			}
		}
	} else {
		cout << "Impossible" << endl;
	}

#ifdef _DEBUG
	cout << "aFease: " << aFease << " minA: " << minA << endl;
	// restore cin buf
	cin.rdbuf( cinBuf );
#endif

	delete [] A;
	delete [] aSol;
	return 0;
}
