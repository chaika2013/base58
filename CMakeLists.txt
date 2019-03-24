cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")

project(base58)

set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "1")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
    FORCE)
endif()

if(APPLE)
  find_library(COREFOUNDATION CoreFoundation)
  list(APPEND EXTRA_LIBS ${COREFOUNDATION})
endif()

set(CMAKE_C_FLAGS "-Wall -Werror -std=c99")

if(APPLE)
  set(CMAKE_EXE_LINKER_FLAGS "-pagezero_size 10000 -image_base 100000000")
endif()

include_directories("${CMAKE_BINARY_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/src")

add_subdirectory("src")
