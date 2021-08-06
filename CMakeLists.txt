cmake_minimum_required(VERSION 3.2)

PROJECT(dmbreakpad)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

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
    FILE(GLOB_RECURSE DMBREAKPAD_SOURCES
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
    FILE(GLOB_RECURSE DMBREAKPAD_SOURCES
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

IF(WIN32)
    ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
ENDIF(WIN32)

ADD_LIBRARY(dmbreakpad ${DMBREAKPAD_SOURCES})

ADD_EXECUTABLE(dmbreakpadtest ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cc)

TARGET_LINK_LIBRARIES(dmbreakpadtest dmbreakpad)

IF (UNIX)
    ADD_EXECUTABLE(minidump-2-core google_breakpad/tools/linux/md2core/minidump-2-core.cc)

    TARGET_LINK_LIBRARIES(minidump-2-core)

    ADD_CUSTOM_COMMAND(
    TARGET minidump-2-core
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/script/debug.sh
    $<TARGET_FILE_DIR:minidump-2-core>
    )
ENDIF(UNIX)
