#-----------------------------------------------------------------------#
#  file: CMakeLists.txt                                                 #
#                                                                       #
#  version: 1.0   date 9/5/2023                                         #
#                                                                       #
#  Copyright (C) 2023                                                   #
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

project( gtocX_2burn_Mex )

#set( CMAKE_VERBOSE_MAKEFILE ON )
set( CMAKE_BUILD_TYPE Release )

find_package( Matlab REQUIRED )

message( STATUS "Matlab_ROOT_DIR = ${Matlab_ROOT_DIR}" )
message( STATUS "PROJECT_NAME    = ${PROJECT_NAME}" )

## COMPONENTS MX_LIBRARY ENG_LIBRARY MEX_COMPILER )

# set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING INTERNAL FORCE)
set( CMAKE_CXX_STANDARD 11  )

set(
  SOURCES
  ${PROJECT_NAME}.cc
  gtocX_2burn_Mex_user.cc
  gtocX_2burn_Mex_class.cc
  gtocX_2burn_Mex_methods.cc
  GenericContainerMatlabInterface.cc
)
file( GLOB S ${CMAKE_CURRENT_SOURCE_DIR}/../../ocp-src/*.cc )
foreach(F ${S})
  file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  list( APPEND SOURCES ${RF} )
endforeach()

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../../ocp-src ${INCLUDE} )

exec_program( pins ARGS --cflags     OUTPUT_VARIABLE CFLAGS   )
exec_program( pins ARGS --cppflags   OUTPUT_VARIABLE CXXFLAGS )
exec_program( pins ARGS --lflags     OUTPUT_VARIABLE LFLAGS   )
#exec_program( pins ARGS --libs       OUTPUT_VARIABLE LIBS     )
#exec_program( pins ARGS --frameworks OUTPUT_VARIABLE LIBS2    )
#exec_program( pins ARGS --includes   OUTPUT_VARIABLE INCLUDE  )

exec_program( pins ARGS --cmake OUTPUT_VARIABLE LIBS_FILE )
file( WRITE CMakefile-libs.txt ${LIBS_FILE} )
include( ./CMakefile-libs.txt )

set( CMAKE_C_FLAGS_DEBUG    "${CFLAGS}" )
set( CMAKE_C_FLAGS          "${CFLAGS}" )
set( CMAKE_CXX_FLAGS_DEBUG  "${CXXFLAGS}" )
set( CMAKE_CXX_FLAGS        "${CXXFLAGS}" )

set( CMAKE_SHARED_LINKER_FLAGS ${LFLAGS} )
set( CMAKE_EXE_LINKER_FLAGS    ${LFLAGS} )

set( CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR} )

if ( (UNIX OR LINUX) AND NOT APPLE )
  set( PINS_LIBS "${PINS_LIBS} -lopenblas_linux -lgomp -lpthread -lreadline -l${CMAKE_DL_LIBS}" )
  set( PINS_LIBS "${PINS_LIBS} -lquadmath -lgfortran -static-libstdc++ -static-libgcc -Wl,--no-undefined")
endif()

matlab_add_mex(
  NAME ${PROJECT_NAME}
  SRC ${SOURCES}
  LINK_TO "${PINS_LIBS}"
)

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
  "$<TARGET_FILE:${PROJECT_NAME}>"
  "${CMAKE_CURRENT_SOURCE_DIR}"
)

