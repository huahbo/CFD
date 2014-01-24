/*__________________________________________________________________________________________________
 * 
 *  autor: Pedro Guarderas
 *  email: ajusworkopensource@gmail.com
 *  date: 01-01-2014
 *  file: grid.c
 * 
 *  This program is free software; you can redistribute it and/or modify it under the 
 *  terms of the GNU General Public License as published by the Free Software Foundation; 
 *  either version 2 of the License, or (at your option) any later version.
 *__________________________________________________________________________________________________
 */

#include "grid.h"

/*__________________________________________________________________________________________________
 * Grid allocation
 */
grid* gridAllocate( const size_t* N, const size_t D ) {
	size_t i;
	grid* grd = ( grid* ) malloc( sizeof( grid ) );
	
	grd->D = D;
	grd->N = ( size_t* ) malloc( D * sizeof( size_t* ) );
	grd->x = ( real** ) malloc( D * sizeof( real* ) );

	for ( i = 0; i < D; i++ ) {
		grd->x[i] = ( real* ) malloc( N[i] * sizeof( real ) );
		grd->N[i] = N[i];
	}
	return grd;
}

/*__________________________________________________________________________________________________
 * Grid free memory
 */
void gridFree( grid* grd ) {
	size_t i;
	
	for ( i = 0; i < grd->D; i++ ) {
		free( grd->x[i] );
	}
	free( grd->x );
	free( grd->N );
	free( grd );
}

/*__________________________________________________________________________________________________
 * Grid print
 */
void gridPrint( grid* grd ) {
	size_t i, j;
	
	for ( i = 0; i < grd->D; i++ ) {
		for ( j = 0; j < grd->N[i]; j++ ) {
			printf( _real_print_, grd->x[i][j] );
			printf( " " );
		}
		printf( "\n" );
	}
}

void gridXML( grid* grd, char* name, char* kind ) {
	size_t i;
	FILE *out;
	
	out = fopen( name, "w" );
	fprintf( out, "<?xml version=\"1.0\"?>\n" );
	fprintf( out, "<VTKFile type=\"" );
	fprintf( out, kind );
	fprintf( out, "\" version=\"0.1\" byte_order=\"LittleEndian\">\n" );
	
	fprintf( out, "<" );
	fprintf( out, kind );
	fprintf( out, " WholeExtent=\"");
	for ( i = 0; i < grd->D; i++ ) {
		fprintf( out, _real_print_, grd->x[i][0] );
		fprintf( out, " " );
		fprintf( out, _real_print_, grd->x[i][ grd->N[i] - 1 ] );
		fprintf( out, " " );
	}
	fprintf( out, "\">\n" );
	
	fprintf( out, "<Piece Extent=\"" );
	for ( i = 0; i < grd->D; i++ ) {
		fprintf( out, _real_print_, grd->x[i][0] );
		fprintf( out, " " );
		fprintf( out, _real_print_, grd->x[i][ grd->N[i] - 1 ] );
		fprintf( out, " " );
	}
	fprintf( out, "\">\n" );
	
	fprintf( out, "<PointData>\n" );
	fprintf( out, "</PointData>\n" );
	
	fprintf( out, "<CellData>\n" );
	fprintf( out, "</CellData>\n" );
	
	fprintf( out, "<Coordinates>\n" );
	fprintf( out, "</Coordinates>\n" );
	
	fprintf( out, "</Piece>\n" );
	fprintf( out, "</" );
	fprintf( out, kind );
	fprintf( out, ">\n" );
	
	fprintf( out, "</VTKFile>\n" );

	fclose( out );
}

void gridVTK( grid* grd, char* name ) {
	size_t i;
	FILE *out;
	
	out = fopen( name, "w" );
	fprintf( out, "# vtk DataFile Version 2.0\n");
	fprintf( out, "grid\n" );
	fprintf( out, "ASCII\n" );
// 	fprintf( out, "UTF8\n" );
	fprintf( out, "DATASET RECTILINEAR_GRID\n" );
	fprintf( out, "DIMENSIONS" );
	for ( i = 0; i < grd->D; i++ ) {
		fprintf( out, " " );
		fprintf( out, "%ld", grd->N[i] );
	}
	fprintf( out, "\n" );
	if ( grd->D == 2 || grd->D == 3 ) {
		fprintf( out, "X_COORDINATES " );
		fprintf( out, "%ld", grd->N[0] );
		fprintf( out, " double\n" );
		printVector( grd, out, 0 );
		fprintf( out, "\n" );
		
		fprintf( out, "Y_COORDINATES " );
		fprintf( out, "%ld", grd->N[1] );
		fprintf( out, " double\n" );
		printVector( grd, out, 1 );
		fprintf( out, "\n" );
		
		if ( grd->D == 3 ) {
			fprintf( out, "Z_COORDINATES " );
			fprintf( out, "%ld", grd->N[2] );
			fprintf( out, " double\n" );
			printVector( grd, out, 2 );
			fprintf( out, "\n" );
		}
	}
	else {
		for ( i = 0; i < grd->D; i++ ) {
			fprintf( out, "X" );
			fprintf( out, "%ld", i+1 );
			fprintf( out, "_COORDINATES " );
			fprintf( out, "%ld", grd->N[i] );
			fprintf( out, " double\n" );
			printVector( grd, out, i );
			fprintf( out, "\n" );
		}
	}
	fclose( out );
}

void printVector( grid* grd, FILE* out, const int i ) {
	size_t k;
	
	for ( k = 0; k < grd->N[i]; k++ ) {
		fprintf( out, _real_print_, grd->x[i][k] );
		if ( k < ( grd->N[i] - 1 ) ) {
			fprintf( out, " " );
		}
	}
}



/*__________________________________________________________________________________________________
 * Send grid
 */
// void MPI_Send_Grid( grid* grd, int dest, int tag ) {
// 	size_t i;
// 	
// 	MPI_Send( &grd->D, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
// 	MPI_Send( grd->N, grd->D, MPI_INT, dest, tag, MPI_COMM_WORLD );
// 	
// 	for ( i = 0; i < grd->D; i++ ) {
// 		MPI_Send( grd->x[i], grd->N[i], MPI_DOUBLE, dest, tag, MPI_COMM_WORLD );
// 	}
// }

/*__________________________________________________________________________________________________
 * Receive grid
 */
// void MPI_Recv_Grid( grid* grd, int src, int tag, MPI_Status* stat ) {
// 	size_t i, N, D;
// 
// 	MPI_Recv( &grd->D, 1, MPI_INT, src, tag, MPI_COMM_WORLD, stat );
// 	grd->N = ( int* ) malloc( grd->D * sizeof( int ) );
// 	
// 	MPI_Recv( grd->N, grd->D, MPI_INT, src, tag, MPI_COMM_WORLD, stat );
// 	gridAllocate( grd, grd->N, grd->D );
// 	
// 	for ( i = 0; i < grd->D; i++ ) {
// 		MPI_Recv( grd->x[i], grd->N[i], MPI_DOUBLE, src, tag, MPI_COMM_WORLD, stat );
// 	}
// }

/*__________________________________________________________________________________________________
 * Grid generation
 */
void gridGen( grid* grd, const real* h, const real* a ) {
	size_t i, j;

	for ( i = 0; i < grd->D; i++ ) {
		grd->x[i][0] = a[i];
		for ( j = 1; j < grd->N[i]; j++ ) {
			grd->x[i][j] = grd->x[i][j-1] + h[i];
		}
	}
}

void gridGenUnif( grid* grd, real* h, const real* a, const real* b ) {
	size_t i, j;

	for ( i = 0; i < grd->D; i++ ) {
		grd->x[i][0] = a[i];
		h[i] = ( b[i] - a[i] ) / ( grd->N[i] - 1 );
		for ( j = 1; j < grd->N[i]; j++ ) {
			grd->x[i][j] = grd->x[i][j-1] + h[i];
		}
	}
}

/*__________________________________________________________________________________________________
 * Get point in the grid
 */
real* get( const size_t idx, const grid* grd ) {
	size_t i, ia, I;
	
	real* X = ( real* ) malloc( grd->D * sizeof( real ) );
	ia = idx;
	
	for ( i = 0; i < grd->D; i++ ) {
		I = ia % grd->N[i];
		X[i] = grd->x[i][I];
		ia = ( ia - I ) / grd->N[i];
	}
	return X;
}

real* get2( const size_t idx, grid* grd, bool bndry ) {
	size_t i, ia, I;
	
	real* X = ( real* ) malloc( grd->D * sizeof( real ) );
	ia = idx;
	bndry = false;
	for ( i = 0; i < grd->D; i++ ) {
		I = ia % grd->N[i];
		X[i] = grd->x[i][I];
		if ( I == 0 || I == grd->N[i] - 1 ) {
			bndry = true;
		}
		ia = ( ia - I ) / grd->N[i];
	}
	return X;
}

size_t size( grid* grd ) {
	size_t i, N;
	
	N = 1.0;
	for ( i = 0; i < grd->D; i++ ) {
		N *= grd->N[i];
	}
	return N;
}

/*__________________________________________________________________________________________________
 * Index numbering
 */
int idx( const size_t* i, const size_t* N, const size_t D ) {
	size_t k, I;

	I = i[D-1];

// 	i[0] + N[0] * ( i[1] + N[1] * ( i[2] + N[2] * i[3] );
	for ( k = D - 2; k >= 0; k-- ) {
		I = i[k] + N[k] * I;
	}
	
	return I; 
}

void getIdx( size_t* I, const size_t i, const size_t* N, const size_t D ) {
	size_t k, ia;
	
	ia = i;

	for ( k = 0; k < D; k++ ) {
		I[k] = ia % N[k];
		ia = ( ia - I[k] ) / N[k];
	}
}
