cmake_minimum_required(VERSION 2.8)
project(gauntlet)

option(INDIE_TESTS "Enable test compilation" OFF)
option(OGRE_STATIC "Use statically compiled OGRE (HUGE Binary!!)" ON)
option(OGRE_PROGRESS "Show ogre download progress" OFF)
option(Boost_USE_STATIC_LIBS "Boost static" ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

if (NOT WIN32)
  set(CMAKE_CXX_FLAGS "-W -std=c++11 -Wunused-result -g -Wall -Wextra -Wno-unused-parameter")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-ignored-qualifiers -Wno-unused-variable")
  set(CMAKE_EXE_LINKER_FLAGS "-rdynamic")
endif()

set(OGRE_REPOSITORY "http://minewolf.tf/ogre")
set(OGRE_FILE "${CMAKE_BINARY_DIR}/ogre.tar.xz")
set(OGRE_URL "${OGRE_REPOSITORY}/ogre-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}.tar.xz")

FILE(
        GLOB_RECURSE
        INDIE
        src/*.cpp
        src/**/*.cpp
        include/*.h*
        include/**/*.h*
)

find_package(Threads)

link_directories(${CMAKE_BINARY_DIR}/lib)

add_executable(gauntlet ${INDIE})

include_directories(include)
include_directories(include/core)
include_directories(include/core/menu)
include_directories(include/core/listeners)
include_directories(include/world)
include_directories(include/world/network)
include_directories(include/gameData)
include_directories(include/gameData/Spell)
include_directories(include/helpers)
include_directories(include/helpers/JSON)
include_directories(include/network)
include_directories(include/network/listener)
include_directories(include/network/packet)
include_directories(include/graph)

if (${OGRE_STATIC})

    message("Searching OGRE static files...")
    message("  - Downloading sha1sum")
    file(DOWNLOAD ${OGRE_URL}.sha1sum ${OGRE_FILE}.sha1sum)
    file(STRINGS ${OGRE_FILE}.sha1sum OGRE_SUM)
    message("  - Done ${OGRE_SUM}")
    if (EXISTS ${OGRE_FILE})
        file(SHA1 ${OGRE_FILE} OGRE_FILE_SUM)
    else ()
        set(OGRE_FILE_SUM "N/A")
    endif ()

    if (NOT EXISTS ${OGRE_FILE} OR NOT ${OGRE_SUM} STREQUAL ${OGRE_FILE_SUM})
        message("  - Files not found downloading")
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
    else ()
        message("  - ogre.tar.xz found and up-to-date")
    endif ()

    set(CMAKE_EXE_LINKER_FLAGS "-z muldefs")
    set(OGRE_PREFIX_GUESSES ${CMAKE_BINARY_DIR})

    find_package(OGRE REQUIRED)

    target_link_libraries(gauntlet ${OGRE_RenderSystem_GL_LIBRARIES})
    target_link_libraries(gauntlet ${OGRE_Plugin_ParticleFX_LIBRARIES})
    target_link_libraries(gauntlet ${OGRE_Plugin_BSPSceneManager_LIBRARIES})
    target_link_libraries(gauntlet ${OGRE_Plugin_PCZSceneManager_LIBRARIES})
    target_link_libraries(gauntlet ${OGRE_Plugin_OctreeSceneManager_LIBRARIES})
    target_link_libraries(gauntlet ${OGRE_Plugin_OctreeZone_LIBRARIES})
    target_link_libraries(gauntlet ${OgreOggSound_LIBRARIES})

    target_link_libraries(gauntlet Xrandr Xrender Xt X11 Xext Xaw)

    include_directories(${OGRE_RenderSystem_GL_INCLUDE_DIRS})
    include_directories(${OGRE_Plugin_ParticleFX_INCLUDE_DIRS})
    include_directories(${OGRE_Plugin_BSPSceneManager_INCLUDE_DIRS})
    include_directories(${OGRE_Plugin_PCZSceneManager_INCLUDE_DIRS})
    include_directories(${OGRE_Plugin_OctreeZone_INCLUDE_DIRS})
    include_directories(${OGRE_Plugin_OctreeSceneManager_INCLUDE_DIRS})

    include_directories(${OIS_INCLUDE_DIRS})
    include_directories(${CMAKE_BINARY_DIR}/include/)

    add_definitions(-DOGRE_STATIC)
    add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
    message("-> OK")

else ()
    find_package(OGRE REQUIRED)
endif ()

find_package(OIS REQUIRED)
find_package(OgreOggSound REQUIRED)

include_directories(${OIS_INCLUDE_DIRS})
include_directories(${OGRE_Overlay_INCLUDE_DIRS})
include_directories(${OGRE_INCLUDE_DIRS})
include_directories(${OgreOggSound_INCLUDE_DIR})

target_link_libraries(gauntlet ${OGRE_Overlay_LIBRARIES})
target_link_libraries(gauntlet ${OgreOggSound_LIBRARIES})
target_link_libraries(gauntlet ${OGRE_LIBRARIES})
target_link_libraries(gauntlet ${OIS_LIBRARIES})

if (WIN32)
    target_link_libraries(gauntlet wsock32 ws2_32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
else()
    target_link_libraries(gauntlet zzip freeimage boost_system boost_thread dl openal vorbisfile vorbis vorbisenc ogg)
endif()

target_link_libraries(gauntlet ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(gauntlet ${PTHREAD_LIBRARY})

if (INDIE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif (INDIE_TESTS)
