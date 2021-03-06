cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME Alogdat_labyrinth)
project (${PROJECT_NAME})

# set the project directories variables
set (PROJECT_EDITOR_SRC_DIR ${PROJECT_SOURCE_DIR}/src/Editor)
set (PROJECT_ENGINE_SRC_DIR ${PROJECT_SOURCE_DIR}/src/Engine)
message(STATUS "asd ${PROJECT_EDITOR_SRC_DIR}")

# set c++17 standard
set(CMAKE_CXX_STANDARD 17)

# -g for debugging and -Wall for all Warnings
set(CMAKE_CXX_FLAGS "-g -Wall")

option(COVERALLS "Generate coveralls data" OFF)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

# Set the QT Library
set(CMAKE_PREFIX_PATH "F:\\LIBRARIES\\Qt\\5.10.1\\mingw53_32;")
add_subdirectory(src/Editor)
add_subdirectory(src/Engine)

# -------------------------------------------
# Testing
# -------------------------------------------
enable_testing()
include(CTest)

# download and build googletest
include(cmake/googletest-download.cmake)

add_subdirectory(test/Editor)
add_subdirectory(test/Engine)
