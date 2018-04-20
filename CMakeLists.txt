cmake_minimum_required(VERSION 3.10.1)

set(PROJECT_NAME Alogdat_labyrinth)
project (${PROJECT_NAME})

# set the project directories variables
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set (PROJECT_EDITOR_SRC_DIR ${PROJECT_SOURCE_DIR}/Editor)
set (PROJECT_ENGINE_SRC_DIR ${PROJECT_SOURCE_DIR}/Engine)

# set c++17 standard
set(CMAKE_CXX_STANDARD 17)

# -g for debugging and -Wall for all Warnings
set(CMAKE_CXX_FLAGS "-g -Wall")

# Set the QT Library
# set(CMAKE_PREFIX_PATH "F:\\LIBRARIES\\Qt\\5.10.1\\mingw53_32;F:\\LIBRARIES\\googletest")
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
