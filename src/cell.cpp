/*__________________________________________________________________________________________________

		autor: Pedro Guarderas
		email: ajusworkopensource@gmail.com
		date: 03-02-2014
		file: cell.cpp
 
	This program is free software; you can redistribute it and/or modify it under the 
	terms of the GNU General Public License as published by the Free Software Foundation; 
	either version 2 of the License, or (at your option) any later version.
____________________________________________________________________________________________________
*/

#include <vector>

#include "cell.hpp"
#include "permut.hpp"


template < typename Field >
Cell< Field >::Cell( const size_t& dim ) :
	list( dim ) {
}

template < typename Field >
Cell< Field >::~Cell() {
}

template< typename Field >
Field Cell< Field >::orient() {
	size_t i, n;
	int sgn;
	n = this->_point->size();
	Permut p( n );
	Field orient, minor;
	
	orient = Field( 0.0 );
	minor = Field( 1.0 );
	while ( p.next( sgn ) ) {
		for ( i = 0; i < n; i++ ) { 
			minor =  minor * ( (*(*this)[0])[i][p[i]] - (*this->_point)[p[i]] );
		}
		orient += sgn * minor;
		minor = 1.0;
	}
	return( orient );
}

template< typename Field >
Field Cell< Field >::inball( const Point< Field >& x ) {
	size_t i, n;
	int sgn;
	Field inball, minor;
	
	n = this->_point->size();
	Permut p( n + 1 );
	vector< Field > lft( n + 1 );
	

	lft[n] = sqrdistance< Field >( *this->_point, x );
	for ( i = 0; i < n; i++ ) {
		lft[i] = sqrdistance< Field >( (*(*this)[0])[i], x );
	}
	
	inball = 0.0;
	minor = 1.0;
	while ( p.next( sgn ) ) {
		for ( i = 0; i <= n; i++ ) {
			if ( p[i] < n && i < n ) {
				minor = minor * ( (*(*this)[0])[i][p[i]] - x[p[i]] );
			} else if ( p[i] < n && i == n) {
				minor = minor * ( (*this->_point)[p[i]] - x[p[i]] );
			} else {
				minor = minor * lft[i];
			}
		}
		inball += sgn * minor;
		minor = 1.0;
	}

	return inball;
}


