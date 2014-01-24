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
void printPrmt( size_t* p, const size_t n ) {
	size_t i;
	for ( i = 0; i < n; i++ ) {
		printf( "%ld", p[i] );
	}
}

// Ives algorithm
bool nextPrmt( size_t* p, int* sign, const size_t n ) {
	
	size_t a;
	static int sgn;
	static size_t i;
	static size_t* c;
	static bool first = true;
	
	if ( first ) {
		c = ( size_t* ) malloc( n * sizeof( size_t ) );
		for ( i = 0; i < n; i++ ) {
			c[i] = i;
			p[i] = i;
		}
		sgn = 1;
		*sign = sgn;
		first = false;
		return true;
	} else {
		i = 0;
		jump:
		if( i < n-1-i ) {
			if ( c[i] < n-1-i ) {
				a = p[c[i]];
				p[c[i]] = p[c[i]+1];
				p[c[i]+1] = a;
				c[i]++;
				i = 0;
				sgn *= -1.0; 
				*sign = sgn;
				return true;
			} else {
				a = p[i];
				p[i] = p[n-1-i];
				p[n-1-i] = a;
				c[i] = i;
				if ( p[n-1-i] == n-1-i  ) {
					i++;
					goto jump;
				} else {
					i = 0;
					sgn *= -1.0;
					*sign = sgn;
					return true;
				}
			}
		} else {
			free(c);
			return false;
		}
	}
}

/*__________________________________________________________________________________________________
 */
void pointAllocate( point* p, size_t dim ) {
	if ( !p ) {
		p = ( point* ) malloc( sizeof( point ) );
	}
	p->x = ( real* ) malloc( dim * sizeof( real ) );
}

void pointFree( point* p ) {
	if ( p ) {
		if ( p->x ) {
			free( p->x );
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
	
	f->points = ( point** ) malloc( dim * sizeof( point* ) );
	f->lsimplex = NULL;
	f->rsimplex = NULL;
}

void faceFree( face* f ) {
	if ( f ) {
		free( f->points );
		f->lsimplex = NULL;
		f->rsimplex = NULL;
		free( f );
	}
}

/*__________________________________________________________________________________________________
 */
void simplexAllocate( simplex* s, const size_t dim ) {
	if ( !s ) {
		s = ( simplex* ) malloc( sizeof( simplex ) );
		s->face = ( face** ) malloc( dim * sizeof( face* ) );
	}
}

void simplexFree( simplex* s ) {
	if ( s ) {
		s->point = NULL;
		free( s->face );
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
		m->dim = dim;
		m->deep = 0;
		m->nchilds = 0;
		m->cells = NULL;
		m->parent = NULL;
		m->childs = NULL;
	}
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
		
		if ( inball( m->cell, p, dim ) <= 0.0 ) {
			size_t i;
			simplex* s;
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
