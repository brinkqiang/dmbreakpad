cmake_minimum_required(VERSION 3.2)

PROJECT(dmbreakpad)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src/client)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src/common)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src/google_breakpad)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src/google_breakpad/common)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src/google_breakpad/processor)	
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/third_party)

IF (WIN32)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/client/windows)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/common/windows)
ELSEIF (APPLE)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/client/mac)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/common/mac)
ELSEIF(UNIX)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/client/linux)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/common/linux)
ENDIF ()

FILE(GLOB_RECURSE SOURCES
)

IF (WIN32)
    FILE(GLOB_RECURSE DMBREAKPAD_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client/windows/handler/exception_handler.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client/windows/crash_generation/crash_generation_client.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/windows/guid_string.cc
    )
ELSEIF (APPLE)
    FILE(GLOB_RECURSE DMBREAKPAD_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client/mac/handler/exception_handler.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client/mac/handler/minidump_generator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client/mac/handler/dynamic_images.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/mac/string_utilities.cc

    ${CMAKE_CURRENT_SOURCE_DIR}/src/client/mac/handler/breakpad_nlist_64.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/mac/file_id.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/mac/macho_id.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/mac/macho_walker.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/mac/macho_utilities.cc

    ${CMAKE_CURRENT_SOURCE_DIR}/src/client/minidump_file_writer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/md5.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/string_conversion.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/convert_UTF.cc
    )
ELSEIF(UNIX)
    ENABLE_LANGUAGE(ASM)
    FILE(GLOB_RECURSE DMBREAKPAD_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client/linux/*.cc

    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/linux/*.S
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/linux/*.cc
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client/minidump_file_writer.cc

    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/convert_UTF.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/md5.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/string_conversion.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/path_helper.cc
    )

    LIST(FILTER DMBREAKPAD_SOURCES EXCLUDE REGEX "test.cc$")
    LIST(FILTER DMBREAKPAD_SOURCES EXCLUDE REGEX "minidump_writer_unittest_utils.cc$")
    LIST(FILTER DMBREAKPAD_SOURCES EXCLUDE REGEX "google_crash_report_sender.cc$")
ENDIF()

IF(WIN32)
    ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
ENDIF(WIN32)

ADD_LIBRARY(dmbreakpad ${DMBREAKPAD_SOURCES})

ADD_EXECUTABLE(dmbreakpadtest ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cc)

TARGET_LINK_LIBRARIES(dmbreakpadtest dmbreakpad)

IF (UNIX)
    ADD_EXECUTABLE(minidump-2-core ${CMAKE_CURRENT_SOURCE_DIR}/src/tools/linux/md2core/minidump-2-core.cc)

    TARGET_LINK_LIBRARIES(minidump-2-core dmbreakpad)

    ADD_CUSTOM_COMMAND(
    TARGET minidump-2-core
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/script/debug.sh
    $<TARGET_FILE_DIR:minidump-2-core>
    )
ENDIF(UNIX)


