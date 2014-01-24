
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mesh.h"

/*__________________________________________________________________________________________________
 */
int main( int argc, char* argv[] ) {
	
	size_t i;
	size_t n = atoi( argv[1] );
	int sgn;
	size_t* p;

	p = ( size_t* ) malloc( n * sizeof( size_t ) );

	i = 1;
	while (	nextPrmt( p, &sgn, n ) ) {
		printf( "%ld\t%d\t", i, sgn );
		printPrmt( p, n );
		printf("\n");
		i++;
	}
	
	free(p);
	return 0;
}

