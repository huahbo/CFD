#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grid.h"
#include "function.h"


int main( int argc, char* argv[] ) {
	size_t D, V, *N;
	grid *grd;
 	function *u;
	real *a, *b, *h;
	
	V = 4;
	D = 3;
	N = ( size_t* ) malloc( D * sizeof( size_t ) );
	a = ( real* ) malloc( D * sizeof( real ) );
	b = ( real* ) malloc( D * sizeof( real ) );
	h = ( real* ) malloc( D * sizeof( real ) );
	
	N[0] = 102; N[1] = 102; N[2] = 102;
	a[0] = 0.0; a[1] = 0.0; a[2] = 0.0;
	b[0] = 1.0; b[1] = 1.0; b[2] = 1.0;
	
	grd = gridAllocate( N, D );
 	u = functionAllocate( V, grd );
	gridGenUnif( grd, h, a, b );
	gridPrint( grd );
	
	gridFree( grd );
 	functionFree( u );

	return 0;
}