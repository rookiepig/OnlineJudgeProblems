///////////////////////////////////////////////////////
// File: main.cpp
// Desc: POJ2965 The Pilots Brothers' refrigerator
//
// Author: Zhang Kang
// Date: 2014/03/03
///////////////////////////////////////////////////////
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
#include<ctime>

using namespace std;
#define B_HEI 4
#define B_WID 4
#define MAX_STATE 65537

// state and mask
typedef unsigned int uint;

// print board
void PrintBrd( char brd[ B_HEI ][ B_WID + 1 ] )
{
	for( int y = 0; y < B_HEI; y ++ ) {
		printf( "%s\n", brd[ y ] );
	}
}
// convert board to int
int BrdToInt( char brd[ B_HEI ][ B_WID + 1 ] )
{
	uint s = 0x0000;
	uint m = 0x0001;
	for( int y = 0; y < B_HEI; y ++ ) {
		for( int x = 0; x < B_WID; x ++ ) {
			if( brd[ y ][ x ] == '+' ) {
				s |= m;
			}
			m <<= 1;
		}
	}
	return s;
}
// convert int to board
void IntToBrd( uint s, char brd[ B_HEI ][ B_WID + 1 ] )
{
	uint m = 0x0001;
	for( int y = 0; y < B_HEI; y ++ ) {
		for( int x = 0; x < B_WID; x ++ ) {
			if( s & m ) {
				brd[ y ][ x ] = '+';
			} else {
				brd[ y ][ x ] = '-';
			}
			m <<= 1;
		}
	}
}
// generate flip mask
void GenFlipMask( uint flip[ B_HEI ][ B_WID ] )
{
	for( int y = 0; y < B_HEI; y ++ ) {
		for( int x = 0; x < B_WID; x ++ ) {
			char brd[ B_HEI ][ B_WID + 1 ] = { "----", "----", "----", "----"};
			brd[ y ][ x ] = '+';
			for( int t = 0; t < B_HEI; t ++ ) {
				brd[ t ][ x ] = '+';
			}
			for( int t = 0; t < B_WID; t ++ ) {
				brd[ y ][ t ] = '+';
			}
			flip[ y ][ x ] = BrdToInt( brd );
#ifdef _DEBUG
			//PrintBrd( brd );
			//printf( "%x\n", flip[ y ][ x ] );
#endif
		}
	}
}
// one move [ i, j ]
//typedef struct Move {
//	int i;
//	int j;
//} Move;

// board state
typedef struct State {
	uint s;
	int round;
	int mv[ 10 ];
} State;

int main( void )
{
	char brd[ B_HEI ][ B_WID + 1 ] = { "", "", "", "" };
	uint flip[ B_HEI ][ B_WID ];
	// input checssboard
	for( int i = 0 ; i < B_HEI; i ++ ) {
		scanf( "%s", brd[ i ] );
	}
#ifdef _DEBUG
	time_t st = time( NULL );
#endif
	uint s = BrdToInt( brd );
#ifdef _DEBUG
	printf( "%x\n", s );
#endif
	// generate all flip mask
	GenFlipMask( flip );
	// BFS search
	int chkFlag[ MAX_STATE ];
	memset( chkFlag, 0, MAX_STATE * sizeof( int ) );
	queue<State> bfsQ;
	State curS;
	curS.s = s;
	curS.round = 0;
	bfsQ.push( curS );
	while( !bfsQ.empty() ) {
		curS = bfsQ.front( );
		bfsQ.pop();
		if( curS.s == 0x0000  ) {
			// succeed
			printf( "%d\n", curS.round );
			for( int t = 0;  t < curS.round; t ++ ) {
				printf( "%d %d\n", curS.mv[ t ] / B_WID + 1, curS.mv[ t ] % B_WID + 1 );
			}
			return 0;
		} else {
			if( !chkFlag[ curS.s ] ) {
				// not accessed before
				State old = curS;
				chkFlag[ curS.s ] = 1;
				for( int y = 0; y < B_HEI; y ++ ) {
					for( int x = 0; x < B_WID; x ++ ) {
						// add all possible flips
						curS.s = old.s ^ flip[ y ][ x ];
						if( !chkFlag[ curS.s ] ) {
							// new move unchcked
							curS.round = old.round + 1;
							curS.mv[ curS.round - 1 ] = y * B_WID + x;
							bfsQ.push( curS );
						}
					}
				}
			}
		}
	}

	printf( "Impossible\n" );
#ifdef _DEBUG
	s  ^= flip[ 0 ][ 0 ];
	IntToBrd( s, brd );
	PrintBrd( brd );
	time_t ed = time( NULL );
	printf( "time %d\n", ed - st );
#endif
	return 0;
}