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

#include "cell.hpp"


Cell::Cell( const size_t& dim ) :
	list( dim ) {
}

Cell::~Cell() {

}

template< typename Field >
Field orient( const Cell& x ) {
}

template< typename Field >
Field inball( const Cell& x, const Point< Field >& x ) {

}


