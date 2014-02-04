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

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mpi.h>

#include "field.h"
#include "permut.h"


/*__________________________________________________________________________________________________
 * Point structure for mesh
 */
typedef struct point {
	real* x;
	uintptr_t nfaces;
	uintptr_t* faces; // simplexes containing the point
} point;

void pointAllocate( point* p, const size_t dim );
void pointFree( point* p );
real sqrdistance( point* p, point* q, const size_t dim );
real distance( point* p, point* q, const size_t dim );
// void point_MPI_Send( point* m, const size_t dim, int dest, int tag );
// void point_MPI_Recv( point* m, const size_t dim, int src, int tag, MPI_Status* stat );


/*__________________________________________________________________________________________________
 * Face structure for mesh
 */l
typedef struct face {
	uintptr_t* points;
	uintptr_t* lsimplex;
	uintptr_t* rsimplex;
	uintptr_t nfaces;
	uintptr_t* faces;
} face;

void faceAllocate( face* fc, const size_t dim );
void faceFree( face* fc );
// void face_MPI_Send( face* m, int dest, int tag );
// void face_MPI_Recv( face* m, int src, int tag, MPI_Status* stat );


/*__________________________________________________________________________________________________
 * Simplex structure for mesh
 */
typedef struct simplex {
	uintptr_t* faces;
} simplex;

void simplexAllocate( simplex* s, const size_t dim );
void simplexFree( simplex* s );
real orient( simplex* s, const size_t dim ); // check orientation of the simplex
real inball( simplex* smp, point* pnt, const size_t dim ); // check if point is in bla
// void refine( simplex* s, )
// void simplex_MPI_Send( simplex* m, int dest, int tag );
// void simplex_MPI_Recv( simplex* m, int src, int tag, MPI_Status* stat );

/*__________________________________________________________________________________________________
 */
typedef struct pointrecord {
	point p;
	pointrecord* pn;
	pointrecord* pp;
} pointdrecord;

typedef struct pointlist {
	size_t size;
	struct pointrecord* first;
	struct pointrecord* last;
} pointlist;

void pointlistAllocate( pointlist* pl ) {
	if ( !pl ) {
		pl = ( pointlist* ) malloc( sizeof( pointlist ) );
	}
	pl->size = 0;
	pl->first = NULL;
	pl->last = NULL;
}

void pointlistFree( pointlist* pl ) {
	if ( pl ) {
		free( pl );
	}
}

void push( pointlist* pl, point* p, const size_t dim ) {
	
	if ( pl ) {
		pointrecord* pr = ( pointrecord* ) malloc( sizeof( pointrecord ) );
		pointAllocate( &pr->p, dim );
		memcpy( pr->p.x, p->x, sizeof( real ) * dim );
		memcpy( pr->p.faces, p->faces, sizeof( uintptr_t ) * p->nfaces );
		pr->p.nfaces = p->nfaces;
		
		if ( pl->size == 0 ) {
			pl->first = pr;
			pl->last = pr;
			pr->pn = NULL;
			pr->pp = NULL;
		} else {
			pl->last->pn = pr->pp;
			pr->pp = pl->last;
			pr->pn = NULL;
			pl->last = ( pointrecord* ) malloc( sizeof( pointrecord ) );
			pl->last = pr;
		}
		pl->size++;
	}
}

void pop( pointlist* pl, const size_t i ) {
	if ( i < pl->size - 1 )  {
		if ( i == 0 ) {
			pl->first->pn->pp = NULL;
			free( pl->first );
			pl->size--;
		} else if ( i == pl->size - 1 ) {
			pl->last->pp->pn = NULL;
			free( pl->last );
			pl->size--;
		} else {
			size_t k;
			pointrecord* pr =pl->first;
			for ( k = 1; k <= i; k++ ) {
				pr = pr->pn;
			}
			pr->pp->pn = pr->pn;
			pr->pn->pp = pr->pp;
			free( pr );
		}
	}
}

/*__________________________________________________________________________________________________
 * Mesh structure
 */
typedef struct mesh {
	size_t dim;
	size_t npoints;
	size_t nfaces;
	size_t ncells;
	struct pointlist points;
	struct face* faces;
	struct simplex* cells;
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