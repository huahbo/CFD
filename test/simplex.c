
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "field.h"
#include "mesh.h"


int main( int argc, char* argv[] ) {
	int i, dim;
	point p[3], q;
	face f;
	simplex s;

	dim = 2;
	for ( i = 0; i < dim+1; i++ ) {
		pointAllocate( &p[i], dim );
	}
	pointAllocate( &q, dim );
	
	p[0].x[0] = 0.0; 
	p[0].x[1] = 0.0; 
	
	p[1].x[0] = 1.0; 
	p[1].x[1] = 0.0; 
	
	p[2].x[0] = 0.0; 
	p[2].x[1] = 1.0;
	
	q.x[0] = 1.0;
	q.x[1] = 0.00000001;
	
	faceAllocate( &f, dim );
	f.points[0] = &p[1]; f.points[1] = &p[2];
	
	s.point = &p[0];
	s.face = &f;
	
	printf( _real_print_, orient( &s, dim ) );
	printf("\n");
	printf( _real_print_, inball( &s, &q, dim ) );
	
// 	pointFree( &p );
// 	pointFree( &q );
// 	faceFree( &f );
	
	return 0;
}
