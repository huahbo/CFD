/*__________________________________________________________________________________________________

		autor: Pedro Guarderas
		email: ajusworkopensource@gmail.com
		date: 07-01-2014
		file: mesh.hpp
 
	This program is free software; you can redistribute it and/or modify it under the 
	terms of the GNU General Public License as published by the Free Software Foundation; 
	either version 2 of the License, or (at your option) any later version.
____________________________________________________________________________________________________
*/

#ifndef MESH
#define MESH

#include <cstdbool>
#include <cstdint>
#include <cmath>
#include <list>
#include <ostream>
#include <string>
#include <vector>

#include "cell.hpp"
#include "face.hpp"
#include "permut.hpp"
#include "point.hpp"


using namespace std;

/*__________________________________________________________________________________________________
 *		Mesh class
 */
template < typename Field = float >
class Mesh {
public:
	Mesh();
	~Mesh();

	bool addpoint( const Point< Field >& x );
	size_t dim;
	list< Point< Field > > _points;
	list< Face > _faces;
	list< Cell > _cells;
};

// /*__________________________________________________________________________________________________
//  * PLC
//  */
// typedef struct plc {
// 	size_t dim;
// 	size_t ncells;
// 	size_t** obj;
// 	point*** cells;
// } plc;
// 
// /*__________________________________________________________________________________________________
//  * Conflict graph
//  */
// typedef struct conflict {
// 	size_t npoints;
// 	size_t nsimplex;
// 	struct point** point;
// 	struct simplex** simplex;
// } conflict;

#endif // MESH