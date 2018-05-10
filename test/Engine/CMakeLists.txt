file(GLOB SRCS *.cpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

include_directories(${PROJECT_ENGINE_SRC_DIR})

add_executable(testEngineRun ${SRCS})

find_package(Threads)
target_link_libraries(testEngineRun PUBLIC engine gtest gmock ${CMAKE_THREAD_LIBS_INIT})

if (MSVC)
    target_compile_options(testEngineRun PRIVATE /std:c++17 /W4 /WX)
else()
    target_compile_options(testEngineRun PRIVATE -std=c++17 -g -Wall -Werror -Wextra -Wpedantic -Wswitch-default -Wswitch-enum -Wunreachable-code -Wwrite-strings -Wcast-align -Wshadow -Wundef)
    if (COVERALLS)
        target_compile_options(testEngineRun PRIVATE --coverage)
        target_link_libraries(testEngineRun PRIVATE --coverage)
    endif()
endif()