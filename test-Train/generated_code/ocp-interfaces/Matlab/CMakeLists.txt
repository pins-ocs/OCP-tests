#-----------------------------------------------------------------------#
#  file: CMakeLists.txt                                                 #
#                                                                       #
#  version: 1.0   date 5/4/2022                                         #
#                                                                       #
#  Copyright (C) 2022                                                   #
#                                                                       #
#      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             #
#      Dipartimento di Ingegneria Industriale                           #
#      Universita` degli Studi di Trento                                #
#      Via Sommarive 9, I-38123, Trento, Italy                          #
#      email: enrico.bertolazzi@unitn.it                                #
#             francesco.biral@unitn.it                                  #
#             paolo.bosetti@unitn.it                                    #
#-----------------------------------------------------------------------#


cmake_minimum_required( VERSION 3.14 )

project( Train_Mex )

find_package( Matlab REQUIRED )

message( STATUS "Matlab_ROOT_DIR = ${Matlab_ROOT_DIR}" )
message( STATUS "PROJECT_NAME    = ${PROJECT_NAME}" )

## COMPONENTS MX_LIBRARY ENG_LIBRARY MEX_COMPILER )

# set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING INTERNAL FORCE)
#set( CMAKE_CXX_STANDARD 11  )
#set( CMAKE_CXX_COMPILER mex )
#set( CMAKE_C_COMPILER   mex )

exec_program( pins ARGS --cflags     OUTPUT_VARIABLE CFLAGS   )
exec_program( pins ARGS --cppflags   OUTPUT_VARIABLE CXXFLAGS )
exec_program( pins ARGS --lflags     OUTPUT_VARIABLE LFLAGS   )
exec_program( pins ARGS --libs       OUTPUT_VARIABLE LIBS     )
exec_program( pins ARGS --frameworks OUTPUT_VARIABLE LIBS2    )
exec_program( pins ARGS --includes   OUTPUT_VARIABLE INCLUDE  )

set( CMAKE_C_FLAGS_DEBUG    "${CFLAGS} ${INCLUDE}" )
set( CMAKE_C_FLAGS          "${CFLAGS} ${INCLUDE}" )
set( CMAKE_CXX_FLAGS_DEBUG  "${CXXFLAGS} ${INCLUDE}" )
set( CMAKE_CXX_FLAGS        "${CXXFLAGS} ${INCLUDE}" )

set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${LFLAGS} ${LIBS} ${LIBS2}" )
set( CMAKE_EXE_LINKER_FLAGS    "${LFLAGS} ${LIBS} ${LIBS2}" )

set( SOURCES ${PROJECT_NAME}.cc GenericContainerMatlabInterface.cc )
file( GLOB S ${CMAKE_CURRENT_SOURCE_DIR}/../../ocp-src/*.cc )
foreach(F ${S})
  file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  list( APPEND SOURCES ${RF} )
endforeach()

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../../ocp-src ${INCLUDE} )

if ( (UNIX OR LINUX) AND NOT APPLE )
  set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
  set(CMAKE_SHARED_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()

matlab_add_mex( NAME ${PROJECT_NAME} SRC ${SOURCES} )

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
  "$<TARGET_FILE:${PROJECT_NAME}>"
  "${CMAKE_CURRENT_SOURCE_DIR}"
)

