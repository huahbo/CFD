/*__________________________________________________________________________________________________

		autor: Pedro Guarderas
		email: ajusworkopensource@gmail.com
		date: 03-02-2014
		file: face.hpp
 
	This program is free software; you can redistribute it and/or modify it under the 
	terms of the GNU General Public License as published by the Free Software Foundation; 
	either version 2 of the License, or (at your option) any later version.
____________________________________________________________________________________________________
*/

#ifndef FACE
#define FACE

#include <cstdint>
#include <cmath>
#include <list>

#include "cell.hpp"
#include "point.hpp"

using namespace std;

/*__________________________________________________________________________________________________
 *		Face class
 */
template < typename Field = float >
class Face : public list< Point< Field >* > {
public:
	Face( const size_t& dim = 3 );
	~Face();

	size_t dim() const;
	list< Face< Field >* >& faces();

public:
	Cell< Field >* _lcell;
	Cell< Field >* _rcell;
	list< Face< Field >* > _faces;
};

// template < typename Field = float >
// ostream& operator<< ( ostream& out, Face< Field >& x );
// template < typename Field = float >
// istream& operator>> ( istream& in, Face< Field >& x );


/*__________________________________________________________________________________________________
 *		External operations
 */

/*__________________________________________________________________________________________________
 *		Include for template compilation
 */
#include "face.cpp"


#endif // FACE