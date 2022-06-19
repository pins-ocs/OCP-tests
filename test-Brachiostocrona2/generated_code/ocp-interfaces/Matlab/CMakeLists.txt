#-----------------------------------------------------------------------#
#  file: CMakeLists.txt                                                 #
#                                                                       #
#  version: 1.0   date 19/6/2022                                        #
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

project( Brachiostocrona2_Mex )

find_package( Matlab REQUIRED )

message( STATUS "Matlab_ROOT_DIR = ${Matlab_ROOT_DIR}" )
message( STATUS "PROJECT_NAME    = ${PROJECT_NAME}" )

## COMPONENTS MX_LIBRARY ENG_LIBRARY MEX_COMPILER )

# set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING INTERNAL FORCE)
set( CMAKE_CXX_STANDARD 11  )

set(
  SOURCES
  ${PROJECT_NAME}.cc
  Brachiostocrona2_Mex_user.cc
  Brachiostocrona2_Mex_class.cc
  Brachiostocrona2_Mex_methods.cc
  GenericContainerMatlabInterface.cc
)
file( GLOB S ${CMAKE_CURRENT_SOURCE_DIR}/../../ocp-src/*.cc )
foreach(F ${S})
  file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  list( APPEND SOURCES ${RF} )
endforeach()

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../../ocp-src ${INCLUDE} )

if( APPLE )
  set(POSTFIX "_osx_static")
  include_directories( /usr/local/PINS/include )
elseif( UNIX OR LINUX )
  include_directories( /usr/local/PINS/include )
  link_directories( /usr/local/PINS/lib /usr/local/PINS/dll )
  set(POSTFIX "_linux_static")
else()
  set(POSTFIX "_win_static")
endif()

if( APPLE )
  add_compile_options(-F/Library/Frameworks )
  set( ALL_LIBS "-F/Library/Frameworks")
  set( ALL_LIBS "${ALL_LIBS} -framework MechatronixODE" )
  set( ALL_LIBS "${ALL_LIBS} -framework MechatronixSolver" )
  set( ALL_LIBS "${ALL_LIBS} -framework MechatronixVehicle" )
  set( ALL_LIBS "${ALL_LIBS} -framework MechatronixManufacturing" )
  set( ALL_LIBS "${ALL_LIBS} -framework MechatronixRoad" )
  set( ALL_LIBS "${ALL_LIBS} -framework MechatronixInterfaceMruby" )
  set( ALL_LIBS "${ALL_LIBS} -framework MechatronixNLSolver" )
  set( ALL_LIBS "${ALL_LIBS} -framework MechatronixSolver" )
  set( ALL_LIBS "${ALL_LIBS} -framework MechatronixCore" )
  set( ALL_LIBS "${ALL_LIBS} -framework Accelerate" )
else()
  set( ALL_LIBS "-L/usr/local/PINS/lib -L/usr/local/PINS/dll" )
  set( ALL_LIBS "${ALL_LIBS} -lMechatronixODE${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lMechatronixSolver${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lMechatronixVehicle${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lMechatronixManufacturing${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lMechatronixRoad${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lMechatronixInterfaceMruby${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lMechatronixNLSolver${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lMechatronixSolver${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lMechatronixCore${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lAlglin${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lHSL${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -llapack_wrapper${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lCommunication${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lsuperlu${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lSplines${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lClothoids${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lquarticRootsFlocke${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lGenericContainer${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lmruby${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lmruby_core${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lonig${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lyaml${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lUtils${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lreplxx${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lLua${POSTFIX}" )
  set( ALL_LIBS "${ALL_LIBS} -lembedFiglet${POSTFIX}" )
endif()

if ( (UNIX OR LINUX) AND NOT APPLE )
  set( ALL_LIBS "${ALL_LIBS} -lopenblas_linux -lgomp -lpthread -lreadline -l${CMAKE_DL_LIBS}" )
  set( ALL_LIBS "${ALL_LIBS} -lquadmath -lgfortran -static-libstdc++ -static-libgcc -Wl,--no-undefined")
endif()

matlab_add_mex(
  NAME ${PROJECT_NAME}
  SRC ${SOURCES}
  LINK_TO "${ALL_LIBS}"
)

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
  "$<TARGET_FILE:${PROJECT_NAME}>"
  "${CMAKE_CURRENT_SOURCE_DIR}"
)

