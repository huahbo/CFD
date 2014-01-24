/*__________________________________________________________________________________________________
 * 
 *  autor: Pedro Guarderas
 *  email: ajusworkopensource@gmail.com
 *  date: 01-16-2014
 *  file: function.c
 * 
 *  This program is free software; you can redistribute it and/or modify it under the 
 *  terms of the GNU General Public License as published by the Free Software Foundation; 
 *  either version 2 of the License, or (at your option) any later version.
 *__________________________________________________________________________________________________
 */

#include "function.h"


function* functionAllocate( const size_t N, grid* grd ) {
	size_t i, M;
	function* u = ( function* ) malloc( sizeof( function ) );
	
	M = size( grd );
	u->f = ( real** ) malloc( M * sizeof( real* ) );
	u->grd = grd;
	u->N = N;

	for ( i = 0; i < M; i++ ) {
		u->f[i] = ( real* ) malloc( N * sizeof( real ) );
	}
	
	return u;
}

void functionFree( function* u ) {
	size_t i;
	
	for ( i = 0; i < u->N; i++ ) {
		free( u->f[i] );
	}
	free( u->grd );
	free( u );
}

void IC( function* u, real* (* u0)( const real* ) ) {
	size_t i, j, N;
	
	N = size( u->grd );
	for ( i = 0; i < N; i++ ) {
		for ( j = 0; j < u->N; j++ ) {
			u->f[i][j] = u0( get( i, u->grd ) )[j];
		}
	}
}

void BD( function* u, real* (*g)( const real* ) ) {
	
	size_t i, j, N;
	bool bndry = false;
	
	real* X = ( real* ) malloc( u->grd->D * sizeof( real ) );
	N = size( u->grd );
	
	for ( i = 0; i < N; i++ ) {
		X = get2( i, u->grd, bndry );
		if ( bndry ) {
			for ( j = 0; j < u->N; j++ ) {
				u->f[i][j] = g( X )[j];
			}
			
		}
	}
	free(X);
}

void Scheme( function* u, real** (*f)( const real * ) ) {
	size_t i, j, k, N, M, *I;
	
	N = size( u->grd );
	M = N / u->grd->N[ u->grd->D - 1 ];
	I = ( size_t* ) malloc( u->grd->D * sizeof( size_t ) );
	for ( i = M; i < N; i++ ) {
		getIdx( I, i, u->grd->N, u->grd->D );
		for ( j = 0; j < u->grd->D; j++ ) {
			I[j]--; 
			k = idx( I, u->grd->N, u->grd->D );
			u->f[i] = u->f[k]
			I[j]++;
		}
	}
	free(I);
}