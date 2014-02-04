
#include <cmath>
#include <iostream>

#include "permut.hpp"

using namespace std;

/*__________________________________________________________________________________________________
 */
int main( int argc, char* argv[] ) {
	
	size_t i;
	size_t n = atoi( argv[1] );
	int sgn;
	Permut p( n );

	i = 1;
	while (	p.next( sgn ) ) {
		cout << i << "\t" << sgn << "\t";
		cout << p << endl;
		i++;
	}
	
	return 0;
}

