/*__________________________________________________________________________________________________
 * 
 *  autor: Pedro Guarderas
 *  email: ajusworkopensource@gmail.com
 *  date: 01-16-2014
 *  file: function.h
 * 
 *  This program is free software; you can redistribute it and/or modify it under the 
 *  terms of the GNU General Public License as published by the Free Software Foundation; 
 *  either version 2 of the License, or (at your option) any later version.
 *__________________________________________________________________________________________________
 */


#ifndef FUNC
#define FUNC

#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "grid.h"


/*__________________________________________________________________________________________________
 * Function struct
 */
typedef struct function {
	size_t N;
	real** f;
	grid* grd;
} function;

/*__________________________________________________________________________________________________
 * Function allocation
 */
function* functionAllocate( const size_t N, grid* grd );

/*__________________________________________________________________________________________________
 * Function deallocate
 */
void functionFree( function* u );

/*__________________________________________________________________________________________________
 * Establishing inicial conditions
 */
void IC( function* u, real* (* u0)( const real* ) );

/*__________________________________________________________________________________________________
 * Establishing boundary conditions
 */
void BD( function* u, real* (*g)( const real* ) );

/*__________________________________________________________________________________________________
 * Scheme
 */
void Scheme( function* u, real** (*f)( const real * ) );


#endif