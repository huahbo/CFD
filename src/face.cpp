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


Face::Face( const size_t& dim ) : 
	list< uintptr_t >( dim ) {
}

Face::~Face() {
}

size_t Face::dim() const {
	return this->size();
}

list< uintptr_t >& Face::faces() {
	return _faces;
}

