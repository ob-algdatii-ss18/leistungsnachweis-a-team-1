file(GLOB SRCS *.cpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

include_directories(${PROJECT_EDITOR_SRC_DIR})

add_executable(testEditorRun ${SRCS})

find_package(Threads)
target_link_libraries(testEditorRun PUBLIC mainwindow gtest gmock ${CMAKE_THREAD_LIBS_INIT})

if (MSVC)
    target_compile_options(testEditorRun PRIVATE /std:c++17 /W4 /WX)
else()
    target_compile_options(testEditorRun PRIVATE -std=c++17 -g -Wall -Werror -Wextra -Wpedantic -Wconversion -Wswitch-default -Wswitch-enum -Wunreachable-code -Wwrite-strings -Wcast-align -Wshadow -Wundef)
    if (COVERALLS)
        target_compile_options(testEditorRun PRIVATE --coverage)
        target_link_libraries(testEditorRun PRIVATE --coverage)
    endif()
endif()