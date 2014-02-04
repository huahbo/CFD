/*__________________________________________________________________________________________________

		autor: Pedro Guarderas
		email: ajusworkopensource@gmail.com
		date: 24-01-2014
		file: permut.cpp
 
	This program is free software; you can redistribute it and/or modify it under the 
	terms of the GNU General Public License as published by the Free Software Foundation; 
	either version 2 of the License, or (at your option) any later version.
____________________________________________________________________________________________________
*/

#include "permut.hpp"


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
