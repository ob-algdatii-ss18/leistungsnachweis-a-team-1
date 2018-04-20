cmake_minimum_required(VERSION 3.6)

project(Engine)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

add_library(engine foo1.cpp foo2.cpp Graph.cpp Graph.h)

if (COVERALLS)
    set(COVERAGE_SRCS ${PROJECT_SOURCE_DIR}/Graph.cpp ${PROJECT_SOURCE_DIR}/foo1.cpp)
    coveralls_setup(
        "${COVERAGE_SRCS}"
        ON
    )
endif()
