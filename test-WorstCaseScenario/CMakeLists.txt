############################################################################
#                                                                          #
#  file: CMakeLists.txt                                                    #
#  Copyright (C) 2016                                                      #
#      Enrico Bertolazzi                                                   #
#      Dipartimento di Ingegneria Industriale                              #
#      Universita` degli Studi di Trento                                   #
#      email: enrico.bertolazzi@ing.unitn.it                               #
#                                                                          #
############################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
SET( TARGET WorstCaseScenario )
PROJECT( ${TARGET} CXX )

SET( CMAKE_VERBOSE_MAKEFILE FALSE )
SET( CMAKE_INSTALL_MESSAGE NEVER )
SET( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

SET( CXX_WARN   "-Weverything -Wno-weak-vtables -Wno-implicit-fallthrough -Wno-float-equal -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-reserved-id-macro -Wno-unreachable-code-break -Wno-format-nonliteral -Wno-cast-qual -Wno-unused-macros -Wno-switch-enum -Wno-conversion -Wno-cast-align -Wno-sign-conversion -Wno-documentation" )
SET( CLANG_WARN "-Wall -Wno-float-equal -Wno-padded" )
SET( VS_WARN    "" )

EXEC_PROGRAM( pins ARGS --cflags     OUTPUT_VARIABLE CFLAGS )
EXEC_PROGRAM( pins ARGS --cppflags   OUTPUT_VARIABLE CXXFLAGS )
EXEC_PROGRAM( pins ARGS --lflags     OUTPUT_VARIABLE LFLAGS )
EXEC_PROGRAM( pins ARGS --libs       OUTPUT_VARIABLE LIBS )
EXEC_PROGRAM( pins ARGS --frameworks OUTPUT_VARIABLE LIBS2 )
EXEC_PROGRAM( pins ARGS --includes   OUTPUT_VARIABLE INCLUDE )

SET( CMAKE_FLAGS  "${CXXFLAGS} ${INCLUDE}" )
SET( CMAKE_LINKER "${LFLAGS} ${LIBS} ${LIBS2}" )

SET( CMAKE_CXX_FLAGS_DEBUG     ${CMAKE_FLAGS}  )
SET( CMAKE_CXX_FLAGS           ${CMAKE_FLAGS}  )
SET( CMAKE_EXE_LINKER_FLAGS    ${CMAKE_LINKER} )
SET( CMAKE_SHARED_LINKER_FLAGS ${CMAKE_LINKER} )

#SET( CMAKE_C_FLAGS_RELEASE       ${CMAKE_CXX} )
#SET( CMAKE_C_FLAGS_RELEASE       ${CMAKE_CXX} )
#SET( CMAKE_C_FLAGS_DEBUG         ${CMAKE_CXX} )
#SET( CMAKE_C_LINKER_WRAPPER_FLAG ${CMAKE_LINKER} )

SET( CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR} )

SET( SOURCES )
FILE( GLOB S ${CMAKE_CURRENT_SOURCE_DIR}/ocp-src/*.cc )
FOREACH (F ${S})
  FILE( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  LIST( APPEND SOURCES ${RF} )
ENDFOREACH (F ${S})

SET( HEADERS )
FILE( GLOB S ${CMAKE_CURRENT_SOURCE_DIR}/ocp-src/*.h )
FOREACH (F ${S})
  FILE( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  LIST( APPEND HEADERS ${RF} )
ENDFOREACH (F ${S})
FILE( GLOB S ${CMAKE_CURRENT_SOURCE_DIR}/ocp-src/*.hh )
FOREACH (F ${S})
  FILE( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  LIST( APPEND HEADERS ${RF} )
ENDFOREACH (F ${S})
FILE( GLOB S ${CMAKE_CURRENT_SOURCE_DIR}/ocp-src/*.hxx )
FOREACH (F ${S})
  FILE( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  LIST( APPEND HEADERS ${RF} )
ENDFOREACH (F ${S})

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/ocp-src )

ADD_LIBRARY( ${TARGET}        SHARED ${SOURCES} ${HEADERS} )
ADD_LIBRARY( ${TARGET}_static STATIC ${SOURCES} ${HEADERS} )

ADD_EXECUTABLE( main            ocp-interfaces/cpp/${TARGET}_Main.cc )
ADD_EXECUTABLE( main_standalone ocp-interfaces/cpp/${TARGET}_StandaloneMain.cc )

INSTALL( TARGETS main main_standalone DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )
INSTALL(
  TARGETS ${TARGET} ${TARGET}_static
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

TARGET_LINK_LIBRARIES( main            ${TARGET}_static )
TARGET_LINK_LIBRARIES( main_standalone ${TARGET}_static )

MESSAGE( STATUS "CMAKE_FLAGS  = ${CMAKE_FLAGS}" )
MESSAGE( STATUS "CMAKE_LINKER = ${CMAKE_LINKER}" )
