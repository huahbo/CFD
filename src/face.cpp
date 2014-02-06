/*__________________________________________________________________________________________________

		autor: Pedro Guarderas
		email: ajusworkopensource@gmail.com
		date: 03-02-2014
		file: face.cpp
 
	This program is free software; you can redistribute it and/or modify it under the 
	terms of the GNU General Public License as published by the Free Software Foundation; 
	either version 2 of the License, or (at your option) any later version.
____________________________________________________________________________________________________
*/

#include "face.hpp"


template < typename Field >
Face< Field >::Face( const size_t& dim ) : 
	list< Point< Field >* >( dim ) {
}

template < typename Field >
Face< Field >::~Face() {
}

template < typename Field >
size_t Face< Field >::dim() const {
	return this->size();
}

template < typename Field >
list< Face< Field >* >& Face< Field >::faces() {
	return _faces;
}

