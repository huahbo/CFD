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

using namespace std;

/*__________________________________________________________________________________________________
 *		Face class
 */
class Face : public list< uintptr_t > {
public:
	Face( const size_t& dim = 3 );
	~Face();

	size_t dim() const;
	list< uintptr_t >& faces();

// 	friend ostream& operator<< ( ostream& out, Face& x );
// 	friend istream& operator>> ( istream& in, Face& x );

public:
	uintptr_t _lcell;
	uintptr_t _rcell;
	list< uintptr_t > _faces;
};

/*__________________________________________________________________________________________________
 *		External operations
 */


#endif // FACE