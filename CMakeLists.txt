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
# Project definition
cmake_minimum_required(VERSION 2.8)

set( CMAKE_MODULE_PATH 
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  ${CMAKE_MODULE_PATH} )

include( CMakeForceCompiler )

set( CMAKE_SYSTEM_NAME Generic )

#___________________________________________________________________________________________________
# Find LLVM
# find_package( LLVM )
# 
# if( LLVM_FOUND )
#   set( CMAKE_C_COMPILER             ${CLANG} )
#   set( CMAKE_C_FLAGS                "-Wall")
#   set( CMAKE_C_FLAGS_DEBUG          "-g")
#   set( CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
#   set( CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
#   set( CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
#   
#   set( CMAKE_CXX_COMPILER             ${CLANG_PLUS} )
#   set( CMAKE_CXX_FLAGS                "-Wall -std=c++11")
#   set( CMAKE_CXX_FLAGS_DEBUG          "-g")
#   set( CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
#   set( CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
#   set( CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
#   
#   set( CMAKE_AR "/usr/bin/llvm-ar" )
#   set( CMAKE_LINKER "/usr/bin/llvm-ld" )
#   set( CMAKE_RANLIB "/usr/bin/llvm-ranlib" )
#   set( CMAKE_NM "/usr/bin/llvm-nm" )
#   set( CMAKE_OBJDUMP "/usr/bin/llvm-objdump" )
#   #set(CMAKE_C_LINKER ${LLVM_LD} )
#   #set(CMAKE_CXX_LINKER ${LLVM_LD} )
#   
#   #set(CMAKE_C_LINK_EXECUTABLE "/usr/bin/llvm-ld <OBJECTS> -o  <TARGET> <CMAKE_C_LINK_FLAGS>
#<LINK_FLAGS> <LINK_LIBRARIES>")
#   #set(CMAKE_CXX_LINK_EXECUTABLE "/usr/bin/llvm-ld <OBJECTS> -o  <TARGET> <CMAKE_CXX_LINK_FLAGS>
#<LINK_FLAGS> <LINK_LIBRARIES>")
#   
# else( LLVM_FOUND )
#   message( SEND_ERROR "LLVM don't work" )
# endif( LLVM_FOUND )

project( cfd )

set( CMAKE_COLOR_MAKEFILE ON )
#CMAKE_FORCE_C_COMPILER ( /usr/bin/clang clang )
#CMAKE_FORCE_CXX_COMPILER ( /usr/bin/clang++ clang_plus )

#___________________________________________________________________________________________________
# Search MPI
find_package(MPI REQUIRED)
if(MPI_FOUND)
  set(CMAKE_C_COMPILER ${MPI_C_COMPILER} )
  set(CMAKE_CXX_COMPILER ${MPI_CXX_COMPILER} )
  set(CMAKE_Fortran_COMPILER ${MPI_Fortran_COMPILER} )
endif(MPI_FOUND)

#___________________________________________________________________________________________________
# Windows configuration
if( WIN32 )
  if( MSVC )
    add_definitions( "-DGUI_EXPORT=__declspec(dllimport)" )
    add_definitions( "-DCORE_EXPORT=__declspec(dllimport)" )
  else( MSVC )
    add_definitions( "\"-DGUI_EXPORT=__declspec(dllimport)\"" )
    add_definitions( "\"-DCORE_EXPORT=__declspec(dllimport)\"" )
  endif( MSVC )
else( WIN32 )
  add_definitions( -DGUI_EXPORT= )
  add_definitions( -DCORE_EXPORT= )
endif( WIN32 )

if( CMAKE_BUILD_TYPE MATCHES Debug )
  add_definitions( -DpolynomeDEBUG=1 )
endif( CMAKE_BUILD_TYPE MATCHES Debug )

#add_definitions( -std=c++11 )

#___________________________________________________________________________________________________
# Include Subdirectories
subdirs( src test )
