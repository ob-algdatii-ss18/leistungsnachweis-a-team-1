file(GLOB SRCS *.cpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

include_directories(${PROJECT_ENGINE_SRC_DIR})

add_executable(testEngineRun ${SRCS})

target_link_libraries(testEngineRun engine gtest gmock)
add_test(NAME TestEngine COMMAND testEngineRun)
