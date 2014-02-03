#___________________________________________________________________________________________________
# 
#		autor: Pedro Guarderas
#		email: ajusworkopensource@gmail.com
#		date: 02-02-2014
#		file: CMakeLists.txt
#
#	This program is free software; you can redistribute it and/or modify it under the 
#	terms of the GNU General Public License as published by the Free Software Foundation; 
#	either version 2 of the License, or (at your option) any later version.
#___________________________________________________________________________________________________
#

#___________________________________________________________________________________________________
# Files
set( GRID_TEST_SRCS
	gridfile.c
)

set( MPI_TEST_SRCS
	mpitest.c
)

set( PERM_TEST_SRCS
	permut.c
)

set( SIMP_TEST_SRCS
	simplex.c
)

#___________________________________________________________________________________________________
# Build
include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${MPI_INCLUDE_PATH}
  ../src
  )

#___________________________________________________________________________________________________
# Adding cfd tests
add_executable( grdtst ${GRID_TEST_SRCS} )
add_executable( mpitst ${MPI_TEST_SRCS} )
add_executable( prmtst ${PERM_TEST_SRCS} )
add_executable( smptst ${SIMP_TEST_SRCS} )

target_link_libraries( grdtst ${MPI_LIBRARIES} )
target_link_libraries( mpitst ${MPI_LIBRARIES} )
target_link_libraries( prmtst ${MPI_LIBRARIES} )
target_link_libraries( smptst ${MPI_LIBRARIES} )

#___________________________________________________________________________________________________
# Install
install( TARGETS grdtst mpitst prmtst smptst
	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/test
)
