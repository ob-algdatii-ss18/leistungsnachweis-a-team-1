file(GLOB SRCS *.cpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

include_directories(${PROJECT_EDITOR_SRC_DIR})

add_executable(testEditorRun ${SRCS})

target_link_libraries(testEditorRun mainwindow gtest gmock)
add_test(NAME TestEditor COMMAND testEditorRun)