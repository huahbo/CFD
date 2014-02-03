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
set( CFD_SRCS
	function.c
	grid.c
	permut.c
	twontree.c
	)

set( CFD_HDRS
	field.h
	function.h
	grid.h
	twontree.c
	permut.h
	)

#___________________________________________________________________________________________________
# Build
include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${MPI_INCLUDE_PATH}
  .
  )

#___________________________________________________________________________________________________
# Adding cfd library
add_library( cfd MODULE 
  ${CFD_SRCS}
  ${CFD_HDRS}
  )
  
target_link_libraries( cfd ${MPI_LIBRARIES} )

#___________________________________________________________________________________________________
# Install
install( TARGETS cfd
	LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)
