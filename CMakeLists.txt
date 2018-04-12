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
set(CMAKE_PREFIX_PATH "F:\\LIBRARIES\\Qt\\5.10.1\\mingw53_32")

add_subdirectory(src/Editor)
add_subdirectory(src/Engine)

# http://www.kaizou.org/2014/11/gtest-cmake/
# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
        gtest
        URL https://github.com/google/googletest/archive/master.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        # Disable install step
        INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

message(STATUS "Gtest ${source_dir}")

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
        "${source_dir}/googlemock/include")

add_subdirectory(test)
