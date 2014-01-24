/*__________________________________________________________________________________________________
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#include "field.h"
#include "grid.h"

/*__________________________________________________________________________________________________
 * u = array of dimension M - 1
 * f = return array of dimension M - 1
 */
real* f( real* u ) {
	return u;
}

/*__________________________________________________________________________________________________
 * x = array of dimension N - 1
 */
real* u0( const real* x, const int M ) {
	int i;
	real* u0 = ( real* ) malloc( M * sizeof( real ) );
	for ( i = 0; i < M; i++ ) {
		u0[i] = 0.0;
	}
	return u0;
}

/*__________________________________________________________________________________________________
  Calculus scheme
*/
void Scheme( real** u, real** x, const int* N, const int D, const int M,
			 real* (*f)( const real* ) ) {
}

/*__________________________________________________________________________________________________
 * Set k-bit
 */
// void setBit( boot* b, const int k ) {
// 	b[k] == 1;
// }

/*__________________________________________________________________________________________________
  Distribute parallel calculation
*/

void gridMPI( const int procs, const int* dist, const int D, const real* a, const real* b ) {

	grid* grd;
	
	MPI_Datatype gridType, oldtypes;
	MPI_Aint offsets, extent;
	int blocks;
	MPI_Status stat;
	
	
	MPI_Type_extent( );
	MPI_Type_struct( 2, blocks, offsets, oldtypes, &gridType );
	MPI_Type_commit( &gridType );
}

void gridDomain( grid* grd, const int procs, const real* a, const real* b, const int* N, 
				 const int D ) {

    int i, it, P, prc;
	int *I, *sz;
    long int k;
	real *h;

	I = ( int* ) malloc( D * sizeof( int ) );
	sz = ( int* ) malloc( D * sizeof( int ) );
	h = ( real* ) malloc( D * sizeof( real ) );
	P = N[0];
	for ( i = 0; i < D; i++ ) {
		h[i] = ( b[i] - a[i] ) / ( N[i] - 1 );
		sz[i] = 0;
		if ( i > 0 ) {
			P *= N[i]; 
		}
	}

    for ( k = 0; k < P; k++ ) {
		// reallocate size of the grid
		getIdx( I, k, N, D );
		prc = k % procs;
        for ( i = 0; i < D; i++ ) {
			grid[prc].x[sz[i]][i] = a[i] + I[i] * h[i];
			grid[prc].y[sz[i]][i] = a[i] + II[i] * h[i];
        }
    }

    return test;
}

/*__________________________________________________________________________________________________
  Main program
*/
int main( int argc, char** argv ) {

	int D, M;
	int *N;
	real *a, *b, *h;
	int stat, procs, pid;
	
	D = 3;
	N = ( int* ) malloc( D * sizeof( int ) );
	a = ( real* ) malloc( D * sizeof( real ) );
	b = ( real* ) malloc( D * sizeof( real ) );
	h = ( real* ) malloc( D * sizeof( real ) );
	
	N[0] = 102;
	N[1] = 102;
	N[2] = 101;
// 	N[3] = 101;
	
	a[0] = 0.0;
	a[1] = 0.0;
	a[2] = 0.0;
// 	a[3] = 0.0;
	
	b[0] = 1.0;
	b[1] = 1.0;
	b[2] = 1.0;
// 	b[3] = 1.0;

	int i;
	bool* r = ( bool* ) malloc( 5 * sizeof( bool ) );
// 	for ( i = 0; i < 5; i++ ) {
// 		if ( i > 2 ) {
// 			r[i] = 1;
// 		}
// 	}
	
	real** x;
	x = gridAllocate( N, D );
	gridGenUnif( x, h, a, b, N, D );
	gridPrint( x, N, D );
	gridFree( x, D );
	free( N );
	free( a );
	free( b );
	free( h );

}


