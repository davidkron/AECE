include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runUnitTests
        basic_check.cpp)

include_directories(AECE)

target_link_libraries(runUnitTests gtest gtest_main)
target_link_libraries(runUnitTests AECE)