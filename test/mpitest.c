
#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grid.h"
#include "mesh.h"

/*__________________________________________________________________________________________________
 */
int main( int argc, char* argv[] ) {
	
	int procs, prc;
	MPI_Status stat;
	
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &prc );
	MPI_Comm_size( MPI_COMM_WORLD, &procs );
	
	if ( prc == 0 ) {
		grid grd;
		real *h, *a, *b;

		grd.D = 3;
		grd.N = ( int* ) malloc( grd.D * sizeof( int ) );
		grd.N[0] = 32; grd.N[1] = 32; grd.N[2] = 16;
		grd.x =  gridAllocate( grd.N,  grd.D );
		
		h = ( real* ) malloc( grd.D * sizeof( real ) );
		a = ( real* ) malloc( grd.D * sizeof( real ) );
		b = ( real* ) malloc( grd.D * sizeof( real ) );
		a[0] = 0.0; a[1] = 0.0; a[2] = 0.0;
		b[0] = 5.0; b[1] = 1.0; b[2] = 1.0;
		
		gridGenUnif( &grd, h, a, b );

		gridPrint( grd );
		MPI_Send_Grid( &grd, 1, 109 );
		gridFree( grd );
	}
	else {
		grid grdl;
		
		MPI_Recv_Grid( &grdl, 0, 109, &stat );
 		gridPrint( grdl );
// 		gridXML( grdl, "grid.xml", "RectilinearGrid" );
		gridVTK( grdl, "grid.vtr" );
		gridFree( grdl );
	}
	MPI_Finalize();
	
	size_t n = 5;
	size_t* p;
	p = ( size_t* ) malloc( n * sizeof( size_t ) );

	free(p);
	return 0;
}

