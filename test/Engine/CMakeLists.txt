file(GLOB SRCS *.cpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/Engine)

add_executable(testEngineRun ${SRCS})

target_link_libraries(testEngineRun gtest gmock)
