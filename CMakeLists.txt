cmake_minimum_required(VERSION 2.8)
project(gauntlet)
enable_testing()

option(INDIE_TESTS "Enable test compilation" OFF)

set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -std=c++11")

find_package(Threads)

include_directories(include)
include_directories(include/core)
include_directories(include/world)
include_directories(include/gameData)
include_directories(include/gameData/Spell)

FILE(
        GLOB_RECURSE
        INDIE
        src/*.cpp
        src/**/*.cpp
        include/*.h*
        include/**/*.h*
)

add_executable(gauntlet ${INDIE})

target_link_libraries(gauntlet ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(gauntlet ${OGRE_LIBRARY})
target_link_libraries(gauntlet ${PTHREAD_LIBRARY})

if (INDIE_TESTS)
    add_subdirectory(tests)
endif ()
