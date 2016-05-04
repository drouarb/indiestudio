cmake_minimum_required(VERSION 2.8)
project(cpp_indie_studio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/")

set(CMAKE_CXX_FLAGS "-Wall -W -Werror -ansi -pedantic -O0")

find_package(OGRE REQUIRED)
include_directories (${OGRE_INCLUDE_DIRS})

link_libraries(pthread)
include_directories(includes)

FILE(
        GLOB_RECURSE
        INDIE
        srcs/*.cpp
        srcs/**/*.cpp
        includes/*.h*
)

add_executable(cpp_indie_studio ${INDIE})

target_link_libraries(cpp_indie_studio  ${OGRE_LIBRARY})
target_link_libraries(cpp_indie_studio  ${PTHREAD_LIBRARY})