cmake_minimum_required(VERSION 2.8)
project(cpp_indie_studio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_FLAGS "-W -Wall -Wextra")

link_libraries(pthread)
include_directories(include)
include_directories(include/core)
include_directories(include/gameData)

FILE(
        GLOB_RECURSE
        INDIE
        src/*.cpp
        src/**/*.cpp
        include/*.h*
	include/gameData/*.h*
)

add_executable(cpp_indie_studio ${INDIE})

target_link_libraries(cpp_indie_studio  ${OGRE_LIBRARY})
target_link_libraries(cpp_indie_studio  ${PTHREAD_LIBRARY})
