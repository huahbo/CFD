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


template < typename Field >
Mesh< Field >::Mesh() {
}

template < typename Field >
Mesh< Field >::~Mesh() {
}

template < typename Field >
bool Mesh< Field >::addpoint( const Point< Field >& x ) {
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
