/*__________________________________________________________________________________________________

		autor: Pedro Guarderas
		email: ajusworkopensource@gmail.com
		date: 24-01-2014
		file: permut.hpp
 
	This program is free software; you can redistribute it and/or modify it under the 
	terms of the GNU General Public License as published by the Free Software Foundation; 
	either version 2 of the License, or (at your option) any later version.
____________________________________________________________________________________________________
*/

#ifndef PERMUT
#define PERMUT

#include <cstdbool>
#include <cstdlib>
#include <ostream>
#include <vector>

using namespace std;

/*__________________________________________________________________________________________________
 *		Generate Permutations
 */
class Permut : public vector< size_t > {
public:
	Permut( const size_t n );
	~Permut();
	
	bool next( int sign );
};

ostream& operator<< ( ostream& out, Permut& p );

#endif // PERMUT