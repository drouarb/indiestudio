cmake_minimum_required(VERSION 2.8)
project(gauntlet)

option(INDIE_TESTS "Enable test compilation" OFF)
option(OGRE_STATIC "Use statically compiled OGRE (HUGE Binary!!)" OFF)
option(OGRE_PROGRESS "Show ogre download progress" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
set(CMAKE_CXX_FLAGS "-std=c++11")

set(OGRE_REPOSITORY "http://minewolf.tf/ogre")
set(OGRE_FILE "${CMAKE_BINARY_DIR}/ogre.tar.xz")
set(OGRE_URL "${OGRE_REPOSITORY}/ogre-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}.tar.xz")

FILE(
        GLOB_RECURSE
        INDIE
        OgreUI.cpp
        TutorialApplication.cpp
)

find_package(Threads)

link_directories(${CMAKE_BINARY_DIR}/lib)

add_executable(gauntlet ${INDIE})

include_directories(include)
include_directories(include/core)
include_directories(include/world)
include_directories(include/gameData)
include_directories(include/gameData/Spell)

if (${OGRE_STATIC})

    message("Searching OGRE static files...")
    if (NOT EXISTS ${OGRE_FILE})
        message("  - Files not found downloading")
        message("    - Downloading sha1sum")
        file(DOWNLOAD ${OGRE_URL}.sha1sum ${OGRE_FILE}.sha1sum)
        file(STRINGS ${OGRE_FILE}.sha1sum OGRE_SUM)
        message("    - Done ${OGRE_SUM}")
        message("    - Downloading ogre.tar.xz")
        if (${OGRE_PROGRESS})
            file(DOWNLOAD ${OGRE_URL} ${OGRE_FILE} EXPECTED_HASH SHA1=${OGRE_SUM} SHOW_PROGRESS)
        else ()
            file(DOWNLOAD ${OGRE_URL} ${OGRE_FILE} EXPECTED_HASH SHA1=${OGRE_SUM})
        endif ()
        message("    - Done")
        message("  - Extracting ogre.tar.xz")
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xjf ${OGRE_FILE})
        message("  - Done")
    endif ()


    set(OGRE_PREFIX_GUESSES ${CMAKE_BINARY_DIR})
    find_package(OGRE)
    message("${OGRE_FOUND}")

    target_link_libraries(gauntlet ${OGRE_LIBRARIES})
    target_link_libraries(gauntlet ${OGRE_Overlay_LIBRARIES})
    target_link_libraries(gauntlet dl zzip freeimage Xrandr Xt X11 OIS Xaw)

    include_directories(${CMAKE_BINARY_DIR}/include/OGRE)
    include_directories(${CMAKE_BINARY_DIR}/include/OGRE/Overlay)
    include_directories(${CMAKE_BINARY_DIR}/include/OIS)
    include_directories(${CMAKE_BINARY_DIR}/include/)
    message("-> OK")

else ()

    find_package(OGRE)
    find_package(OIS)

    include_directories(${OIS_INCLUDE_DIRS})
    include_directories(${OGRE_INCLUDE_DIRS})
    include_directories(${OGRE_Overlay_INCLUDE_DIRS})

    target_link_libraries(gauntlet ${OGRE_LIBRARIES})
    target_link_libraries(gauntlet ${OIS_LIBRARIES})
    target_link_libraries(gauntlet ${OGRE_Overlay_LIBRARIES})

endif (${OGRE_STATIC})

target_link_libraries(gauntlet ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(gauntlet ${PTHREAD_LIBRARY})

if (INDIE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif (INDIE_TESTS)
