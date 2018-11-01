cmake_minimum_required(VERSION 2.8)

PROJECT(dmbreakpad)

IF (WIN32)  
    MESSAGE(STATUS "Now is windows")

    SET(DMOS_NAME "win")
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )

    ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
    ADD_DEFINITIONS(-D_WIN32_WINNT=0x0501)
ELSEIF (APPLE)  
    MESSAGE(STATUS "Now is Apple systems")  

    SET(DMOS_NAME "mac") 
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" )    
ELSEIF (UNIX)  
    MESSAGE(STATUS "Now is UNIX-like OS")  
 
    SET(DMOS_NAME "lin")
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" )    
ENDIF ()

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)
    
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/src)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/src)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad/common)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad/processor)	
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/third_party)

IF (WIN32)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/windows)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/windows)
ELSE (WIN32)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/linux)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/linux)
ENDIF ()

FILE(GLOB_RECURSE SOURCES
)

IF (WIN32)
    FILE(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/src/*.cc 
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/src/*.cc 
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad/*.cc

    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/windows/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/windows/*.cc 
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/windows/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/windows/*.cc)
ELSE (WIN32)
    FILE(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/src/*.cc 
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/src/*.cc 
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad/*.cc

    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/minidump_file_writer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/string_conversion.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/convert_UTF.cc
    
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/linux/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/linux/*.cc 
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/linux/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/linux/*.cc)
ENDIF()

ADD_LIBRARY(dmbreakpad ${SOURCES})

ADD_EXECUTABLE(dmbreakpadtest ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cc)

TARGET_LINK_LIBRARIES(dmbreakpadtest dmbreakpad)

IF (UNIX)
    ADD_EXECUTABLE(minidump-2-core google_breakpad/tools/linux/md2core/minidump-2-core.cc)

    TARGET_LINK_LIBRARIES(minidump-2-core)
ENDIF(UNIX)
