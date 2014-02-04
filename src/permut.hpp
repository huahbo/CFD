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

/*__________________________________________________________________________________________________
 * Generate Permutations
 */
void printPrmt( size_t* p, const size_t n );
bool nextPrmt( size_t* p, int* sign, const size_t n );


#endif // PERMUT