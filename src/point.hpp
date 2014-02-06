/*__________________________________________________________________________________________________

		autor: Pedro Guarderas
		email: ajusworkopensource@gmail.com
		date: 08-04-2010
		file: point.hpp
 
	This program is free software; you can redistribute it and/or modify it under the 
	terms of the GNU General Public License as published by the Free Software Foundation; 
	either version 2 of the License, or (at your option) any later version.
____________________________________________________________________________________________________
*/

#ifndef POINT
#define POINT

#include <cstdint>
#include <cmath>
#include <list>
#include <ostream>
#include <vector>

#include "face.hpp"
#include "cell.hpp"

using namespace std;


/*__________________________________________________________________________________________________
 *		Point class
 */
template< typename Field = float >
class Point : public vector< Field > {
public:
	Point( const size_t& dim = 3 );
	Point( const Field& val = Field( 0 ), const size_t& dim = 3 );
// 	Point( const Point< Field >& x );
	~Point();

	size_t dim() const;
	list< Field >& faces();
	Point< Field >& operator+= ( const Point< Field >& x );
	Point< Field >& operator-= ( const Point< Field >& x );
	Point< Field >& operator*= ( const Field& a );

public:
	list< Face< Field >* > _faces;
	list< Cell< Field >* > _cells;
};

/*__________________________________________________________________________________________________
 *		External operations
 */
template< typename Field = float >
ostream& operator<< ( ostream& out, Point< Field >& x );

// template< typename Field = float >
// istream& operator>> ( istream& in, Point< Field >& x );

template< typename Field = float >
inline Field scalar( const Point< Field >& x, const Point< Field >& y );

template< typename Field = float >
inline Field norm( const Point< Field >& x );

template< typename Field = float >
inline Field sum( const Point< Field >& x );

template< typename Field = float >
inline Field distance( const Point< Field >& x, const Point< Field >& y );

template< typename Field = float >
inline Field sqrdistance( const Point< Field >& x, const Point< Field >& y );

template< typename Field = float >
inline Point< Field > proj( const Point< Field >& x, const Point< Field >& y );

template< typename Field = float >
inline Point< Field > cproj( const Point< Field >& x );

template< typename Field = float >
inline Point< Field > operator+ ( const Point< Field >& x, const Point< Field >& y );

template< typename Field = float >
inline Point< Field > operator- ( const Point< Field >& x, const Point< Field >& y );

template< typename Field = float >
inline Point< Field > operator* ( const Field& a, const Point< Field >& x );

/*__________________________________________________________________________________________________
 *		Include for template compilation
 */
#include "point.cpp"

#endif // POINT
