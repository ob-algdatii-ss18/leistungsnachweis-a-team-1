cmake_minimum_required(VERSION 3.6)

# The version number.
set (Algdat_labyrinth_VERSION_MAJOR 0)
set (Algdat_labyrinth_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 14)

# Set the QT Library
# set(CMAKE_PREFIX_PATH "F:\\LIBRARIES\\Qt\\5.9.1\\msvc2017_64")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

project (Algodat)

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src/Editor)
add_subdirectory(src/Engine)
