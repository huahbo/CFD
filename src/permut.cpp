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


Permut::Permut( const size_t n ) :
	vector< size_t >( n ) {
}

Permut::~Permut() {
}

ostream& operator<<( ostream& out, Permut& p ) {
	for ( size_t i = 0; i < p.size(); i++ ) {
		out << p[i];
	}
}

// Ives algorithm
bool Permut::next( int sign ) {	
	size_t a;
	static int sgn;
	static size_t i;
	static size_t* c;
	static bool first = true;
	
	if ( first ) {
		c = new size_t[ this->size() ];
		for ( i = 0; i < this->size(); i++ ) {
			c[i] = i;
			(*this)[i] = i;
		}
		sgn = 1;
		sign = sgn;
		first = false;
		return true;
	} else {
		i = 0;
		jump:
		if( i < this->size()-1-i ) {
			if ( c[i] < this->size()-1-i ) {
				a = (*this)[c[i]];
				(*this)[c[i]] = (*this)[c[i]+1];
				(*this)[c[i]+1] = a;
				c[i]++;
				i = 0;
				sgn *= -1.0; 
				sign = sgn;
				return true;
			} else {
				a = (*this)[i];
				(*this)[i] = (*this)[ this->size()-1-i ];
				(*this)[ this->size()-1-i] = a;
				c[i] = i;
				if ( (*this)[this->size()-1-i] == this->size()-1-i  ) {
					i++;
					goto jump;
				} else {
					i = 0;
					sgn *= -1.0;
					sign = sgn;
					return true;
				}
			}
		} else {
			delete[] c;
			return false;
		}
	}
}
