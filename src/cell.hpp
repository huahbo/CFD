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

#include "face.hpp"
#include "point.hpp"

using namespace std;

/*__________________________________________________________________________________________________
 *		Cell class
 */
template < typename Field = float >
class Cell : public list< Face< Field >* > {
public:
	Cell( const size_t& dim = 3 );
	~Cell();
	Field orient();
// 	Field reorient();
	Field inball( const Point< Field >& x );
	Point< Field >* _point;
};

// template < typename Field = float >
// ostream& operator<< ( ostream& out, Cell< Field >& x );

// template < typename Field = float >
// istream& operator>> ( istream& in, Cell< Field >& x );


/*__________________________________________________________________________________________________
 *		External operations
 */

/*__________________________________________________________________________________________________
 *		Include for template compilation
 */
#include "cell.cpp"


#endif // CELL