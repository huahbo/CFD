/*__________________________________________________________________________________________________

		autor: Pedro Guarderas
		email: ajusworkopensource@gmail.com
		date: 09-04-2010
		file: point.cpp
 
	This program is free software; you can redistribute it and/or modify it under the 
	terms of the GNU General Public License as published by the Free Software Foundation; 
	either version 2 of the License, or (at your option) any later version.
____________________________________________________________________________________________________
*/

#include "point.hpp"


template< typename Field >
Point< Field >::Point( const size_t& dim ) :
    vector< Field >(),
    _faces() {
}

template< typename Field >
Point< Field >::Point( const Field& val, const size_t& dim ) :
    vector< Field >( dim, val ),
    _faces() {
}

template< typename Field >
Point< Field >::~Point() {
}

template< typename Field >
size_t Point< Field >::dim() const {
    return this->size();
}

template< typename Field >
list< Field >& Point< Field >::faces() {
	return _faces;
}

template< typename Field >
Point< Field >& Point< Field >::operator+= ( const Point< Field >& x ) {
	for ( size_t i = 0; i < this->size(); i++ ) {
		this->assign( i, this->at[i] + x[i] );
	}
	return *this;
}

template< typename Field >
Point< Field >& Point< Field >::operator-= ( const Point< Field >& x ) {
	for ( size_t i = 0; i < this->size(); i++ ) {
		this->assign( i, this->at[i] - x[i] );
	}
	return *this;
}

template< typename Field >
Point< Field >& Point< Field >::operator*= ( const Field& a ) {
	for ( size_t i = 0; i < this->size(); i++ ) {
		this->assign( i, a * (*this)[i] );
	}
	return *this;
}

template< typename Field >
ostream& operator<< ( ostream& out, Point< Field >& x ) {
	out << x[0];
	for ( size_t i = 1; i < x.size(); i++ ) {
		out << " " << x[i];
	}
}

// template< typename Field >
// istream& Point< Field >::operator>> ( istream& in, Point< Field >& x ) {
// }

/*__________________________________________________________________________________________________
 */
template< typename Field >
inline Field scalar( const Point< Field >& x, const Point< Field >& y ) {
	Field scalar( 0.0 );
	size_t sz;
	if ( x.size() <= y.size() ) {
		sz = x.size();
	} else {
		sz = y.size();
	}
	for( size_t i = 0; i < sz; i++ ) {
		scalar += x[i] * y[i];
	}
	return scalar;
}

template< typename Field >
inline Field norm( const Point< Field >& x ) {
	Field norm( 0 );
	for ( size_t i = 0; i < x.size(); i++ ) {
		norm += x[i] * x[i];
	}
	return sqrt( norm );
}

template< typename Field >
inline Field sum( const Point< Field >& x ) {
	Field sum( 0 );
	for ( size_t i = 0; i < x.size(); i++ ) {
		sum += x[i];
	}
	return sum;
}

template< typename Field = float >
inline Field distance( const Point< Field >& x, const Point< Field >& y ) {
	Field dist;
	for ( size_t i = 0; i < x.size(); i++ ) {
		dist += ( x[i] - y[i] ) * ( x[i] - y[i] );
	}
	return sqrt( dist );
}

template< typename Field = float >
inline Point< Field > proj( const Point< Field >& x, const Point< Field >& y ) {
	Point< Field > proj;
	Field scalar = scalar( x, y );
	Field normy = norm( y, y );

	if ( y.size() ==  x.size() && normy > Field( 0 ) ) {
		for ( size_t i = 0; i < x.size(); i++ ) {
			proj.push_back( scalar *  y[i] / normy );
		}
	}
	return proj;
}

template< typename Field = float >
inline Point< Field > cproj( const Point< Field >& x ) {
	Point< Field > cproj = x;
	cproj.push_back( scalar( x, x ) );
	return cproj;
}

template< typename Field >
inline Point< Field > operator+ ( const Point< Field >& x, const Point< Field >& y ) {
	Point< Field > sum;
	for ( size_t i = 0; i < x.size(); i++ ) {
		sum.push_back( x[i] + y[i] );
	}
	return sum;
}

template< typename Field >
inline Point< Field > operator- ( const Point< Field >& x, const Point< Field >& y ) {
	Point< Field > rest;
	for ( size_t i = 0; i < x.size(); i++ ) {
		rest.push_back( x[i] - y[i] );
	}
	return rest;
}

template< typename Field >
inline Point< Field > operator* ( const Field& a, const Point< Field >& x ) {
	Point< Field > scaled;
	for ( size_t i = 0; i < x.size(); i++ ) {
		scaled.push_back( a * x[i] );
	}
	return scaled;
}
