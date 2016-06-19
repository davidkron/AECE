cmake_minimum_required(VERSION 3.5)
project(AECE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")

set(SOURCE_FILES AefFile.cpp AefFile.h SongWithAef.cpp SongWithAef.h Engine.cpp Engine.h)

include_directories(gsl)


add_library(AECE STATIC ${SOURCE_FILES} ${HEADER_FILES})

find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(AECE ${SFML_LIBRARIES})
endif()


find_package(YamlCpp REQUIRED)
if(YAMLCPP_FOUND)
    include_directories(${YAMLCPP_INCLUDE_DIR})
    target_link_libraries(AECE ${YAMLCPP_LIBRARY})
endif()