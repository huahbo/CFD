/*__________________________________________________________________________________________________
 * 
 *  autor: Pedro Guarderas
 *  email: ajusworkopensource@gmail.com
 *  date: 07-01-2014
 *  file: mesh.c
 * 
 *  This program is free software; you can redistribute it and/or modify it under the 
 *  terms of the GNU General Public License as published by the Free Software Foundation; 
 *  either version 2 of the License, or (at your option) any later version.
 *__________________________________________________________________________________________________
 */

#include "mesh.h"


/*__________________________________________________________________________________________________
 */
void pointAllocate( point* p, size_t dim ) {
	if ( !p ) {
		p = ( point* ) malloc( sizeof( point ) );
	}
	p->x = ( real* ) malloc( dim * sizeof( real ) );
	p->nfaces = 0;
	p->faces = NULL;
}

void pointFree( point* p ) {
	if ( p ) {
		if ( p->x ) {
			free( p->x );
		}
		if ( p->faces ) {
			free( p->faces );
		}
		free( p );
	}
}

real sqrdistance( point* p, point* q, const size_t dim ) {
	size_t i;
	real dst = 0.0;
	
	for ( i = 0; i < dim; i++ ) {
		dst += ( p->x[i] - q->x[i] ) * ( p->x[i] - q->x[i] );
	}
	return dst;
}

real distance( point* p, point* q, const size_t dim ) {
	size_t i;
	real dst = 0.0;
	
	for ( i = 0; i < dim; i++ ) {
		dst += ( p->x[i] - q->x[i] ) * ( p->x[i] - q->x[i] );
	}
	return sqrt( dst );
}

// void point_MPI_Send( point* m, const size_t dim, int dest, int tag ) {
// 	int i;
// 	MPI_Send( &dim, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
// }
// 
// void point_MPI_Recv( point* m, const size_t dim, int src, int tag, MPI_Status* stat ) {
// 
// }


/*__________________________________________________________________________________________________
 */
void faceAllocate( face* f, const size_t dim ) {
	if ( !f ) {
		f = ( face* ) malloc( sizeof( face ) );
	}
	
	f->nfaces = 0;
	f->points = ( uintptr_t* ) malloc( dim * sizeof( uintptr_t ) );
	f->lsimplex = NULL;
	f->rsimplex = NULL;
	f->faces = NULL;
}

void faceFree( face* f ) {
	if ( f ) {
		free( f->points );
		free( f->lsimplex );
		free( f->rsimplex );
		free( f->faces );
		free( f );
	}
}

/*__________________________________________________________________________________________________
 */
void simplexAllocate( simplex* s, const size_t dim ) {
	if ( !s ) {
		s = ( simplex* ) malloc( sizeof( simplex ) );
		s->faces = ( uintptr_t* ) malloc( dim * sizeof( uintptr_t ) );
	}
}

void simplexFree( simplex* s ) {
	if ( s ) {
		free( s->faces );
		free( s );
	}
}

real orient( simplex* smp, const size_t dim ) {
	size_t i;
	size_t* p;
	int sgn;
	real orient, minor;
	
	p = ( size_t* ) malloc( dim * sizeof( size_t ) );
	orient = 0.0;
	minor = 1.0;
	while ( nextPrmt( p, &sgn, dim ) ) {
		for ( i = 0; i < dim; i++ ) { 
			minor =  minor * ( smp->face->points[i]->x[p[i]] - smp->point->x[p[i]] );
		}
		orient += sgn * minor;
		minor = 1.0;
	}
	free(p);
	return( orient );
}

real inball( simplex* smp, point* pnt, const size_t dim ) {
	size_t i;
	size_t* p;
	int sgn;
	real inball, minor;
	real* lft;
	
	lft = ( real* ) malloc( ( dim + 1 ) * sizeof( real ) );
	p = ( size_t* ) malloc( ( dim + 1 ) * sizeof( size_t ) );
	
	lft[dim] = sqrdistance( smp->point, pnt, dim );
	for ( i = 0; i < dim; i++ ) {
		lft[i] = sqrdistance( smp->face->points[i], pnt, dim );
	}
	
	inball = 0.0;
	minor = 1.0;
	while ( nextPrmt( p, &sgn, dim + 1 ) ) {
		for ( i = 0; i <= dim; i++ ) {
			if ( p[i] < dim && i < dim ) {
				minor = minor * ( smp->face->points[i]->x[p[i]] - pnt->x[p[i]] );
			} else if ( p[i] < dim && i == dim ) {
				minor = minor * ( smp->point->x[p[i]] - pnt->x[p[i]] );
			} else {
				minor = minor * lft[i];
			}
		}
		inball += sgn * minor;
		minor = 1.0;
	}
	
	free(lft);
	free(p);
	return inball;
}

/*__________________________________________________________________________________________________
 */
void meshAllocate( mesh* m, const size_t dim ) {
	if ( !m ) {
		m = ( mesh* ) malloc( sizeof( mesh ) );
	}
	m->dim = dim;
	m->deep = 0;
	m->nchilds = 0;
	m->cell = NULL;
	m->parent = NULL;
	m->childs = NULL;
}

void meshFree( mesh* m ) {
	size_t i;
	
	if ( m ) {
		
		if ( m->cell ) {
			free( m->cell );
		}

		if ( m->parent ) {
			free( m->parent );
		}
		// Recursive free
		if ( m->nchilds > 0 ) {
			for ( i = 0; i < m->nchilds; i++ ) {
				meshFree( m->childs[i] );
			}
			free( m->childs );
		}

		free( m );
	}
}

bool addpoint( mesh* m, point* p, const size_t dim ) {
	bool added;

	if ( m->dim == dim ) {
		bool isin;
		isin = false;
		
		if ( inball( m->cell, p, dim ) <= 0.0 ) { // if zero is in the border
			size_t i;
			simplex* s = NULL;
			isin = true;

			for ( i = 0; i < dim; i++ ) {
				if ( m->cell->face[i]->lsimplex != m->cell ) {
					s = m->cell->face[i]->lsimplex;
				} else {
					s = m->cell->face[i]->rsimplex;
				}
				if ( inball( s, p, dim ) <= 0.0 ) {
					
				}
			}
		} else {
		}
		
		added = true;
	} else {
		added = false;
	}
	return added;
}

/*
void mesh_MPI_Send( mesh* m, int dest, int tag ) {

}

void mesh_MPI_Recv( mesh* m, int src, int tag, MPI_Status* stat ) {

}*/
