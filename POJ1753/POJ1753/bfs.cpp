///////////////////////////////////////////////////////
// File: main.cpp
// Desc: POJ1753 Flip Game -- BFS + Bitwise OP
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
			if( brd[ y ][ x ] == 'w' ) {
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
				brd[ y ][ x ] = 'w';
			} else {
				brd[ y ][ x ] = 'b';
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
			char brd[ B_HEI ][ B_WID + 1 ] = { "bbbb", "bbbb", "bbbb", "bbbb"};
			brd[ y ][ x ] = 'w';
			if( y - 1 >= 0 ) {
				// top
				brd[ y - 1 ][ x ] = 'w';
			}
			if( y + 1 < B_HEI ) {
				// bottom
				brd[ y + 1 ][ x ] = 'w';
			}
			if( x - 1 >= 0 ) {
				// left
				brd[ y ][ x - 1 ] = 'w';
			}
			if( x + 1 < B_WID ) {
				// right
				brd[ y ][ x + 1 ] = 'w';
			}
			flip[ y ][ x ] = BrdToInt( brd );
#ifdef _DEBUG
			//PrintBrd( brd );
			//printf( "%x\n", flip[ y ][ x ] );
#endif
		}
	}
}
// board state
typedef struct State {
	uint s;
	int round;
} State;

int bfs( void )
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
		if( curS.s == 0x0000 || curS.s == 0xffff ) {
			// succeed
			printf( "%d\n", curS.round );
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