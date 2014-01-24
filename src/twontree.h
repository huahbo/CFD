/*__________________________________________________________________________________________________
 * 
 *  autor: Pedro Guarderas
 *  email: ajusworkopensource@gmail.com
 *  date: 01-01-2014
 *  file: twontree.h
 * 
 *  This program is free software; you can redistribute it and/or modify it under the 
 *  terms of the GNU General Public License as published by the Free Software Foundation; 
 *  either version 2 of the License, or (at your option) any later version.
 *__________________________________________________________________________________________________
 */

#ifndef TWONTREE
#define TWONTREE

#include <math.h>
#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "field.h"

/*__________________________________________________________________________________________________
 * Two N Tree structure
 */
typedef struct {
public:
	int _deep;
	const real _ratio;
	const size_t _capacity;
	const size_t _dim;
	const size_t _size;
	size_t _npoints;
	size_t _nchilds;
	
	real* _range[2];
	real** _points;
	
	twontree* _parent;
	twontree** _childs;

} twontree;

/*__________________________________________________________________________________________________
 */
void twonTreeSet( twontree* twnt, const real* range[2], const size_t dim = 3, 
				  const size_t capacity = 1, const real ratio = 0.000001 );

twontree* twonTreeAllocate( const real* range[2], const size_t dim = 3, 
							const size_t capacity = 1, const real ratio = 0.000001 );

void twonTreeFree( twontree* twnt );

bool insert( twontree* twnt, const real* x, const size_t dim );

bool contains( twontree* twnt, const real* x, const size_t dim );

real area( twontree* twnt );

bool subdivide( twontree* twnt );

void insertPoint( real** X, real* x, const size_t dim );

#endif // TWONTREE
