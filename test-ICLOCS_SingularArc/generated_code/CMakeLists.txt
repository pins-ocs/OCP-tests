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

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
SET( TARGET ICLOCS_SingularArc )
PROJECT( ${TARGET} CXX )

SET( CMAKE_VERBOSE_MAKEFILE           TRUE  )
SET( CMAKE_INSTALL_MESSAGE            NEVER )
SET( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON    )
SET( CMAKE_MACOSX_RPATH               ./lib )

SET( CXX_WARN   "-Weverything -Wno-alloca -Wno-cast-align -Wno-cast-qual -Wno-conversion -Wno-c++2a-compat -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-format-nonliteral -Wno-implicit-fallthrough -Wno-documentation -Wno-float-equal -Wno-padded -Wno-reserved-id-macro -Wno-unreachable-code-break -Wno-unused-macros -Wno-switch-enum -Wno-sign-conversion -Wno-signed-enum-bitfield -Wno-weak-vtables" )
SET( CLANG_WARN "-Wall -Wno-float-equal -Wno-padded -Wno-comment" )
SET( VS_WARN    "" )

EXEC_PROGRAM( pins ARGS --cflags     OUTPUT_VARIABLE CFLAGS   )
EXEC_PROGRAM( pins ARGS --cppflags   OUTPUT_VARIABLE CXXFLAGS )
EXEC_PROGRAM( pins ARGS --lflags     OUTPUT_VARIABLE LFLAGS   )
EXEC_PROGRAM( pins ARGS --libs       OUTPUT_VARIABLE LIBS     )
EXEC_PROGRAM( pins ARGS --frameworks OUTPUT_VARIABLE LIBS2    )
EXEC_PROGRAM( pins ARGS --includes   OUTPUT_VARIABLE INCLUDE  )

SET( CMAKE_C_FLAGS_DEBUG    "${CFLAGS} ${INCLUDE}" )
SET( CMAKE_C_FLAGS          "${CFLAGS} ${INCLUDE}" )
SET( CMAKE_CXX_FLAGS_DEBUG  "${CXXFLAGS} ${INCLUDE}" )
SET( CMAKE_CXX_FLAGS        "${CXXFLAGS} ${INCLUDE}" )

SET( CMAKE_SHARED_LINKER_FLAGS ${LFLAGS} )
SET( CMAKE_EXE_LINKER_FLAGS    ${LFLAGS} )

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

ADD_EXECUTABLE( main ocp-interfaces/cpp/${TARGET}_Main.cc )

INSTALL( TARGETS main DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )
INSTALL(
  TARGETS ${TARGET} ${TARGET}_static
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

TARGET_LINK_LIBRARIES( ${TARGET} ${LIBS2} ${LIBS} )
TARGET_LINK_LIBRARIES( main ${TARGET}_static ${LIBS2} ${LIBS}  )

MESSAGE( STATUS "CMAKE_FLAGS  = ${CMAKE_FLAGS}" )
MESSAGE( STATUS "CMAKE_LINKER = ${CMAKE_LINKER}" )
