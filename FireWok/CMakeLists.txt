cmake_minimum_required(VERSION 3.5)
project(FireWok)
set(EXECUTABLE_NAME "FireWok_run")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")

set(SOURCE_FILES main.cpp)

file(COPY Songs DESTINATION .)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

include_directories(AECE)

add_subdirectory(AECE)
add_subdirectory(AECE_tests)

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)