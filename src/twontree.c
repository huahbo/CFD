/*__________________________________________________________________________________________________
 * 
 *  autor: Pedro Guarderas
 *  email: ajusworkopensource@gmail.com
 *  date: 02-01-2014
 *  file: twontree.c
 * 
 *  This program is free software; you can redistribute it and/or modify it under the 
 *  terms of the GNU General Public License as published by the Free Software Foundation; 
 *  either version 2 of the License, or (at your option) any later version.
 *__________________________________________________________________________________________________
 */

#include "twontree.h"

void twonTreeSet( twontree* twnt, const real* range[2], const size_t dim, 
				  const size_t capacity, const real ratio ) {
	twnt->_deep = 0;
	twnt->_ratio = ratio;
	twnt->_capacity = capacity;
	twnt->_dim = dim;
	twnt->_size = pow( 2, dim );
	twnt->_npoints = 0;
	twnt->_childs = 0;
	memcpy( twnt->_range[0], range[0], dim );
	memcpy( twnt->_range[1], range[1], dim );
	twnt->_parent = NULL;
	twnt->_childs = NULL;
	twnt->_points = NULL;
}

twontree* twonTreeAllocate( const real* range[2], const size_t dim, 
							const size_t capacity, const real ratio ) {
	
	twontree* twnt = ( twontree* ) malloc( sizeof( twontree ) );
	
	twnt->_deep = 0;
	twnt->_ratio = ratio;
	twnt->_capacity = capacity;
	twnt->_dim = dim;
	twnt->_size = pow( 2, dim );
	twnt->_npoints = 0;
	twnt->_childs = 0;
	memcpy( twnt->_range[0], range[0], dim );
	memcpy( twnt->_range[1], range[1], dim );
	twnt->_parent = NULL;
	twnt->_childs = NULL;
	twnt->_points = NULL;
	
	return twnt;
}

// void twonTreeFree( twontree* twnt ) {
// 
// }

void increase_deep( twontree* twnt ) {
    twnt->_deep++;
    if ( twnt->_parent ) {
        increase_deep( twnt->_parent );
    }
}

bool insert( twontree* twnt, const real* x, const size_t dim ) {
	bool test = false;
	
	if ( dim == twnt->_dim ) {
		if ( contains( twnt, x, dim ) ) {
			real surf = area( twnt );
			
			if ( twnt->_npoints < twnt->_capacity ) {
				twnt->_npoints++;
				twnt->_points = ( real** ) realloc( twnt->_points, 
													twnt->_npoints * sizeof( real* ) );
				twnt->_points[ twnt->_npoints - 1 ] = x;
				test = true;
			}
			else if ( twnt->_npoints >= twnt->_capacity &&  surf <= twnt->_ratio ) {
				twnt->_npoints++;
				twnt->_points = ( real** ) realloc( twnt->_points, 
													twnt->_npoints * sizeof( real* ) );
				twnt->_points[ twnt->_npoints - 1 ] = x;
				test = true;
			}
			else {
				if ( twnt->_nchilds > 0 ) {
					size_t i;
					
					for ( i = 0; i < twnt->_nchilds; i++ ) {
						if ( insert( twnt->_childs[i], x, dim ) ) {
							test = true;
							break;
						}
					}
				}
				else if ( subdivide( twnt ) ) {
					size_t i;
					
					for ( i = 0; i < twnt->_nchilds; i++ ) {
						if ( insert( twnt->_childs[i], x, dim ) ) {
							test = true;
							break;
						}
					}
				}
			}
		}
	}
	return test;
}

bool contains( twontree* twnt, const real* x, const size_t dim ) {
	bool test = false;
	
	size_t i;
	i = 0;
	
	if ( twnt->_dim == dim  ) {
		while ( i < twnt->_dim ) {
			if ( x[i] < twnt->_range[0][i] || x[i] > twnt->_range[1][i] ) {
				test = false;
				break;
			}
			i++;
		}
		if ( i == twnt->_dim ) {
			test = true;
		}
	}
	return test;
}

real area( twontree* twnt ) {
	size_t i;
	real* area = twnt->_range[1][0] - twnt->_range[0][0];
	
	for ( i = 1; i < twnt->_dim; i++ ) {
		area = area * ( twnt->_range[1][i] - twnt->_range[0][i] );
	}
	return area;
}

bool subdivide( twontree* twnt ) {
	bool test = false;
	size_t i;
	size_t k;
	boost::dynamic_bitset<>::size_type it = 0;
	
	for ( k = 0; k < twnt->_size; k++ ) {
		real* x[2];
		x[0] = ( real* ) malloc( twnt->_dim * sizeof( real ) );
		x[1] = ( real* ) malloc( twnt->_dim * sizeof( real ) );

		boost::dynamic_bitset<> bits( _dim, k );
		it = 0;
		for ( i = ( twnt->_dim - 1 ); i >= 0; i-- ) {
			if ( bits[it] ) {
				x[0][i] = ( twnt->_range[0][i] + twnt->_range[1][i] ) / 2.0;
				x[1][i] = twnt->_range[1][i];
			}
			else {
				x[0][i] = twnt->_range[0][i];
				x[1][i] = ( twnt->_range[0][i] + twnt->_range[1][i] ) / 2.0;
			}
			it++;
		}
		
		if ( !append( twnt, twonTreeAllocate( x, twnt->_dim, twnt->_capacity, twnt->_ratio ) ) ) {
			break;
		}
	}
	if ( k == twnt->_size ) {
		test = true;
	}
	return test;
}

bool append( twontree* twnt, twontree* child ) {
    bool test = false;

    // would be better use exception
    if ( twnt->_size > twnt->_nchilds ) {
        if ( twnt->_nchilds == 0 ) {
            increase_deep( twnt );
        }

		twnt->_nchilds++;
        twnt->_childs = ( twontree** ) realloc( twnt->_childs, 
												twnt->_nchilds * sizeof( twontree* ) );
        twnt->_childs[ twnt->_nchilds - 1 ] = child;
		twnt->_childs[ twnt->_nchilds - 1 ]->_parent = twnt;
        test = true;
    }
    return test;
}



