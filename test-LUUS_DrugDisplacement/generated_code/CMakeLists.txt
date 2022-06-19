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

cmake_minimum_required(VERSION 3.14)
set( TARGET LUUS_DrugDisplacement )
project( ${TARGET} CXX )

set( CMAKE_VERBOSE_MAKEFILE           FALSE )
set( CMAKE_INSTALL_MESSAGE            NEVER )
set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON    )
set( CMAKE_MACOSX_RPATH               ./lib )

set( CXX_WARN   "-Weverything -Wno-alloca -Wno-cast-align -Wno-cast-qual -Wno-conversion -Wno-c++2a-compat -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-format-nonliteral -Wno-implicit-fallthrough -Wno-documentation -Wno-float-equal -Wno-padded -Wno-reserved-id-macro -Wno-unreachable-code-break -Wno-unused-macros -Wno-switch-enum -Wno-sign-conversion -Wno-signed-enum-bitfield -Wno-weak-vtables" )
set( CLANG_WARN "-Wall -Wno-float-equal -Wno-padded -Wno-comment" )
set( VS_WARN    "" )

if (NOT APPLE)
  set( CMAKE_INSTALL_RPATH $ORIGIN )
endif()

if( NOT UNIX )
  set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
endif()

# Always include cmath defines globally
add_compile_definitions(_USE_MATH_DEFINES)

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

set( CMAKE_SHARED_LINKER_FLAGS ${LFLAGS} )
set( CMAKE_EXE_LINKER_FLAGS    ${LFLAGS} )

set( CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR} )

set( SOURCES )
file( GLOB S ${CMAKE_CURRENT_SOURCE_DIR}/ocp-src/*.cc )
foreach (F ${S})
  file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  list( APPEND SOURCES ${RF} )
endforeach (F ${S})

set( HEADERS )
file( GLOB S ${CMAKE_CURRENT_SOURCE_DIR}/ocp-src/*.h )

foreach (F ${S})
  file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  list( APPEND HEADERS ${RF} )
endforeach()

file( GLOB S ${CMAKE_CURRENT_SOURCE_DIR}/ocp-src/*.hh )
foreach(F ${S})
  file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  list( APPEND HEADERS ${RF} )
endforeach()

file( GLOB S ${CMAKE_CURRENT_SOURCE_DIR}/ocp-src/*.hxx )
foreach (F ${S})
  file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  list( APPEND HEADERS ${RF} )
endforeach()

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/ocp-src )

# https://stackoverflow.com/questions/2152077/is-it-possible-to-get-cmake-to-build-both-a-static-and-shared-library-at-the-sam

add_library( objlib OBJECT ${SOURCES})
# shared libraries need PIC
set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library( ${TARGET}        SHARED $<TARGET_OBJECTS:objlib> )
add_library( ${TARGET}_static STATIC $<TARGET_OBJECTS:objlib> )

add_executable( main ocp-interfaces/cpp/${TARGET}_Main.cc )

if( ${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.17.0" AND (CMAKE_GENERATOR STREQUAL "Xcode") )
  set_target_properties(
    main PROPERTIES
    XCODE_GENERATE_SCHEME TRUE
    XCODE_SCHEME_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  )
endif()

install( TARGETS main DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )
install(
  TARGETS ${TARGET} ${TARGET}_static
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

target_link_libraries( ${TARGET} ${LIBS2} ${LIBS} )
target_link_libraries( main $<TARGET_OBJECTS:objlib> ${LIBS2} ${LIBS}  )

message( STATUS "CMAKE_FLAGS     = ${CMAKE_FLAGS}" )
message( STATUS "CMAKE_LINKER    = ${CMAKE_LINKER}" )
message( STATUS "CMAKE_GENERATOR = ${CMAKE_GENERATOR}" )
