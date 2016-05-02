cmake_minimum_required(VERSION 3.3)
project(cpp_indie_studio)

include_directories(includes)

link_libraries(pthread)

FILE(
        GLOB_RECURSE
        INDIE
        src/*.cpp
        src/**/*.cpp
        includes/*.h*
)

add_executable(cpp_indie_studio ${INDIE})
