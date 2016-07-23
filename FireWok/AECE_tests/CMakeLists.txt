project(AECE_tests)


add_executable(Testing testing.cpp)

include_directories(AECE)

find_package(YamlCpp REQUIRED)
if(YAMLCPP_FOUND)
    include_directories(${YAMLCPP_INCLUDE_DIR})
    target_link_libraries(Testing ${YAMLCPP_LIBRARY})
endif()

target_link_libraries(Testing AECE)

add_subdirectory(googletest)
add_subdirectory(units)