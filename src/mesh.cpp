/*__________________________________________________________________________________________________

		autor: Pedro Guarderas
		email: ajusworkopensource@gmail.com
		date: 07-01-2014
		file: mesh.cpp
 
	This program is free software; you can redistribute it and/or modify it under the 
	terms of the GNU General Public License as published by the Free Software Foundation; 
	either version 2 of the License, or (at your option) any later version.
____________________________________________________________________________________________________
*/

#include "mesh.hpp"


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
