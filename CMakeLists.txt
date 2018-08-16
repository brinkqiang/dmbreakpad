cmake_minimum_required(VERSION 2.8)

PROJECT(dmbreakpad)

IF (WIN32)  
    MESSAGE(STATUS "Now is windows")

    SET(DMOS_NAME "win")
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )    
ELSEIF (APPLE)  
    MESSAGE(STATUS "Now is Apple systems")  

    SET(DMOS_NAME "mac") 
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" )    
ELSEIF (UNIX)  
    MESSAGE(STATUS "Now is UNIX-like OS")  
 
    SET(DMOS_NAME "lin")
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" )    
ENDIF ()

IF(UNIX)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/src)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/linux)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/src)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/linux)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad/common)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad/processor)	
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/third_party)

    LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/lib)
    
    SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

    FILE(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/minidump_file_writer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/string_conversion.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/convert_UTF.cc
    
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/src/*.cc 

    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/linux/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/linux/*.cc 

    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/src/*.cc 

    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/linux/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/linux/*.cc 

    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad/*.cc)

    ADD_LIBRARY(dmbreakpad ${SOURCES})

    ADD_EXECUTABLE(dmbreakpadtest ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cc)

    TARGET_LINK_LIBRARIES(dmbreakpadtest dmbreakpad)
    
	ADD_EXECUTABLE(minidump-2-core google_breakpad/tools/linux/md2core/minidump-2-core.cc)

    TARGET_LINK_LIBRARIES(minidump-2-core)
ELSEIF(WIN32)
    ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
    ADD_DEFINITIONS(-D_WIN32_WINNT=0x0501)
	
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/src)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/windows)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/src)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/windows)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad/common)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad/processor)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/third_party)

    LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/lib)
    
    SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

    FILE(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/src/*.cc 

    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/windows/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/client/windows/*.cc 
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/src/*.cc 

    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/windows/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/common/windows/*.cc 

    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/google_breakpad/google_breakpad/*.cc)

    ADD_LIBRARY(dmbreakpad ${SOURCES})

    ADD_EXECUTABLE(dmbreakpadtest ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cc)

    TARGET_LINK_LIBRARIES(dmbreakpadtest dmbreakpad)
ENDIF(UNIX)
