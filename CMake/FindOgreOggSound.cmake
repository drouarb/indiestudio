include(FindPkgMacros)
findpkg_begin(OgreOggSound)

getenv_path(OGRE_HOME)

set(OgreOggSound_PREFIX_PATH
        ${CMAKE_BINARY_DIR}
	${ENV_OGRE_HOME}
        /usr/local
        /usr/lib
)
create_search_paths(OgreOggSound)

set(OgreOggSound_LIBRARY_NAMES OgreOggSound)
get_debug_names(OgreOggSound_LIBRARY_NAMES)

findpkg_framework(OgreOggSound)

find_path(OgreOggSound_INCLUDE_DIR NAMES OgreOggSound.h PATHS ${OgreOggSound_INC_SEARCH_PATH})

find_library(OgreOggSound_LIBRARY NAMES ${OgreOggSound_LIBRARY_NAMES} PATHS ${OgreOggSound_LIB_SEARCH_PATH} PATH_SUFFIXES "" "Release" "RelWithDebInfo" "MinSizeRel")

findpkg_finish(OgreOggSound)
