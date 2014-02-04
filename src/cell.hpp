/*__________________________________________________________________________________________________

		autor: Pedro Guarderas
		email: ajusworkopensource@gmail.com
		date: 03-02-2014
		file: cell.hpp
 
	This program is free software; you can redistribute it and/or modify it under the 
	terms of the GNU General Public License as published by the Free Software Foundation; 
	either version 2 of the License, or (at your option) any later version.
____________________________________________________________________________________________________
*/

#ifndef CELL
#define CELL

#include <cstdint>
#include <cmath>
#include <list>
#include <vector>

#include "face.hpp"
#include "point.hpp"

using namespace std;

/*__________________________________________________________________________________________________
 *		Cell class
 */
class Cell : public list< uintptr_t > {
public:
	Cell( const size_t& dim = 3 );
	~Cell();

// 	friend ostream& operator<< ( ostream& out, Cell& x );
// 	friend istream& operator>> ( istream& in, Cell& x );
};

template< typename Field = float >
Field orient( const Cell& x );

template< typename Field = float >
Field inball( const Cell& c, const Point< Field >& x );

/*__________________________________________________________________________________________________
 *		External operations
 */


#endif // CELL