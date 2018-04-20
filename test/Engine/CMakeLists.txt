file(GLOB SRCS *.cpp)

enable_testing()

message(STATUS "Editor src: ${PROJECT_EDITOR_SRC_DIR}")

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

include_directories(${PROJECT_ENGINE_SRC_DIR})

add_executable(testEngineRun ${SRCS})

target_link_libraries(testEngineRun gtest gmock)
add_test(NAME testEngineRun COMMAND testEngineRun)
