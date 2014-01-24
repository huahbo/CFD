/*__________________________________________________________________________________________________
 * 
 *  autor: Pedro Guarderas
 *  email: ajusworkopensource@gmail.com
 *  date: 07-01-2014
 *  file: simplex.h
 * 
 *  This program is free software; you can redistribute it and/or modify it under the 
 *  terms of the GNU General Public License as published by the Free Software Foundation; 
 *  either version 2 of the License, or (at your option) any later version.
 *__________________________________________________________________________________________________
 */

#ifndef MESH
#define MESH

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "field.h"


/*__________________________________________________________________________________________________
 * Permutations
 */
void printPrmt( size_t* p, const size_t n );
bool nextPrmt( size_t* p, int* sign, const size_t n );


/*__________________________________________________________________________________________________
 * Point structure for mesh
 */
typedef struct point {
	real* x;
	struct simplex** simplex;
} point;

void pointAllocate( point* p, const size_t dim );
void pointFree( point* p );
real sqrdistance( point* p, point* q, const size_t dim );
// void point_MPI_Send( point* m, const size_t dim, int dest, int tag );
// void point_MPI_Recv( point* m, const size_t dim, int src, int tag, MPI_Status* stat );


/*__________________________________________________________________________________________________
 * Face structure for mesh
 */
typedef struct face {
	struct point** points;
	struct simplex* lsimplex;
	struct simplex* rsimplex;
} face;

void faceAllocate( face* fc, const size_t dim );
void faceFree( face* fc );
// void face_MPI_Send( face* m, int dest, int tag );
// void face_MPI_Recv( face* m, int src, int tag, MPI_Status* stat );


/*__________________________________________________________________________________________________
 * Simplex structure for mesh
 */
typedef struct simplex {
	point* point;
	struct face** face;	
} simplex;

void simplexAllocate( simplex* s, const size_t dim );
void simplexFree( simplex* s );
real orient( simplex* s, const size_t dim );
real inball( simplex* smp, point* pnt, const size_t dim );
// void refine( simplex* s, )
// void simplex_MPI_Send( simplex* m, int dest, int tag );
// void simplex_MPI_Recv( simplex* m, int src, int tag, MPI_Status* stat );


/*__________________________________________________________________________________________________
 * Mesh structure
 */
typedef struct mesh {
	size_t dim;
	size_t deep;
	size_t nchilds;
	struct simplex* cell;
	struct mesh* parent;
	struct mesh** childs;
} mesh;

void meshAllocate( mesh* m, const size_t dim );
void meshFree( mesh* m );
bool addpoint( mesh* m, point* p, const size_t dim );
void conflict( conflict* cflt,  mesh* m, point* p );
// void addPoint( mesh* m, point* p ) {
// 	if ( inball( m->cells, p, dim ) > 0.0 ) {
// 		
// 	}
// }
// void mesh_MPI_Send( mesh* m, int dest, int tag );
// void mesh_MPI_Recv( mesh* m, int src, int tag, MPI_Status* stat );


/*__________________________________________________________________________________________________
 * PLC
 */
typedef struct plc {
	size_t dim;
	size_t ncells;
	size_t** obj;
	point*** cells;
} plc;

/*__________________________________________________________________________________________________
 * Conflict graph
 */
typedef struct conflict {
	size_t npoints;
	size_t nsimplex;
	struct point** point;
	struct simplex** simplex;
} conflict;

#endif // MESH