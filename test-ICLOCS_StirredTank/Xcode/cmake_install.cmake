# Install script for directory: /Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

set(CMAKE_BINARY_DIR "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode")

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin" TYPE EXECUTABLE MESSAGE_NEVER FILES "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/Debug/main")
    if(EXISTS "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin" TYPE EXECUTABLE MESSAGE_NEVER FILES "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/Release/main")
    if(EXISTS "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin" TYPE EXECUTABLE MESSAGE_NEVER FILES "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/MinSizeRel/main")
    if(EXISTS "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin" TYPE EXECUTABLE MESSAGE_NEVER FILES "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/RelWithDebInfo/main")
    if(EXISTS "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/bin/main")
      endif()
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib" TYPE SHARED_LIBRARY MESSAGE_NEVER FILES "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/Debug/libICLOCS_StirredTank.dylib")
    if(EXISTS "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "libICLOCS_StirredTank.dylib"
        "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib" TYPE SHARED_LIBRARY MESSAGE_NEVER FILES "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/Release/libICLOCS_StirredTank.dylib")
    if(EXISTS "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "libICLOCS_StirredTank.dylib"
        "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib" TYPE SHARED_LIBRARY MESSAGE_NEVER FILES "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/MinSizeRel/libICLOCS_StirredTank.dylib")
    if(EXISTS "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "libICLOCS_StirredTank.dylib"
        "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib" TYPE SHARED_LIBRARY MESSAGE_NEVER FILES "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/RelWithDebInfo/libICLOCS_StirredTank.dylib")
    if(EXISTS "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "libICLOCS_StirredTank.dylib"
        "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank.dylib")
      endif()
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib" TYPE STATIC_LIBRARY MESSAGE_NEVER FILES "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/Debug/libICLOCS_StirredTank_static.a")
    if(EXISTS "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a")
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib" TYPE STATIC_LIBRARY MESSAGE_NEVER FILES "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/Release/libICLOCS_StirredTank_static.a")
    if(EXISTS "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a")
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib" TYPE STATIC_LIBRARY MESSAGE_NEVER FILES "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/MinSizeRel/libICLOCS_StirredTank_static.a")
    if(EXISTS "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a")
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib" TYPE STATIC_LIBRARY MESSAGE_NEVER FILES "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/RelWithDebInfo/libICLOCS_StirredTank_static.a")
    if(EXISTS "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/lib/libICLOCS_StirredTank_static.a")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/enrico/Ricerca/develop/C++/pins-mechatronix/tests/OCP/test-ICLOCS_StirredTank/Xcode/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
