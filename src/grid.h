/*__________________________________________________________________________________________________
 * 
 *  autor: Pedro Guarderas
 *  email: ajusworkopensource@gmail.com
 *  date: 01-01-2014
 *  file: grid.h
 * 
 *  This program is free software; you can redistribute it and/or modify it under the 
 *  terms of the GNU General Public License as published by the Free Software Foundation; 
 *  either version 2 of the License, or (at your option) any later version.
 *__________________________________________________________________________________________________
 */

#ifndef GRID
#define GRID

#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "field.h"

/*__________________________________________________________________________________________________
 */
typedef struct {
	size_t D;
	size_t* N;
	real** x;
} grid;

/*__________________________________________________________________________________________________
 * Grid allocation
 */
grid* gridAllocate( const size_t* N, const size_t D );

// real** gridAllocate2( const size_t N, const size_t D );

// void gridAllocate3( grid* grd, const int* N, const int D );

/*__________________________________________________________________________________________________
 * Grid free memory
 */
void gridFree( grid* grd );

/*__________________________________________________________________________________________________
 * Grid print
 */
void gridPrint( grid* grd );
void gridXML( grid* grd, char* name, char* kind );
void gridVTK( grid* grd, char* name );
void printVector( grid* grd, FILE* out, const int i );

/*__________________________________________________________________________________________________
 * Send grid
 */
// void MPI_Send_Grid( grid* grd, int dest, int tag );

/*__________________________________________________________________________________________________
 * Receive grid
 */
// void MPI_Recv_Grid( grid* grd, int src, int tag, MPI_Status* stat );

/*__________________________________________________________________________________________________
 * Grid generation
 */
void gridGen( grid* grd, const real* h, const real* a );

void gridGenUnif( grid* grd, real* h, const real* a, const real* b );

/*__________________________________________________________________________________________________
 * Get point in the grid
 */
real* get( const size_t idx, const grid* grd );

real* get2( const size_t idx, grid* grd, bool bndry );

size_t size( grid* grd );

/*__________________________________________________________________________________________________
 * Index numbering
 */
int idx( const size_t* i, const size_t* N, const size_t D );

void getIdx( size_t* I, const size_t k, const size_t* N, const size_t D );


#endif // GRID
