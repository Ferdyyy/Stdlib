CMAKE_MINIMUM_REQUIRED (VERSION 3.3)

PROJECT (sac-stdlib)
#FIXME(artem) we can create a definitoin for language "SAC" which will
#             automatically pull sac2c compiler.

# Where the compiled sac modules result
SET (DLL_BUILD_DIR  "${PROJECT_BINARY_DIR}/lib")

# For what targets we build modules
SET (TARGETS            seq mt_pth  CACHE STRING "Build stdlib-jpeg for these targets")
SET (SAC2C_EXEC                     CACHE STRING "A path to sac2c compiler")
SET (LINKSETSIZE        "500"       CACHE STRING "Set a value for -linksetsize parameter of sac2c")
SET (SAC2C_EXTRA_INC
     -DHAVE_CONFIG_H -DEXT_STDLIB
     -I${PROJECT_BINARY_DIR}/include
     -I${PROJECT_SOURCE_DIR}/include)

SET (SAC2C_CPP_INC
     -DHAVE_CONFIG_H -DEXT_STDLIB
     -cppI${PROJECT_BINARY_DIR}/include
     -cppI${PROJECT_SOURCE_DIR}/include)
     
# Check whether sac2c is operational
INCLUDE ("cmake-common/check-sac2c.cmake")

INCLUDE ("cmake/config.cmake")

# For every target run CMakeLists.txt in src
SET (TARGET_COUNT 1)
FOREACH (TARGET IN ITEMS ${TARGETS})
    #MESSAGE ("target #${TARGET_COUNT} = ${TARGET}")
    ADD_SUBDIRECTORY (src   src-${TARGET})
    MATH (EXPR TARGET_COUNT "${TARGET_COUNT} + 1")
ENDFOREACH ()

# This build target is responsible for generating the package sac2crc file
ADD_CUSTOM_TARGET (create-sac2crc-file ALL
    COMMAND ${CMAKE_COMMAND}
        -DUSER_HOME="$ENV{HOME}"
        # XXX ideally we should use PROJECT_NAME, but sadly this has a dash `-'
        #     which sac2crc does not support within target names
        -DPACKAGE_NAME="stdlib"
        -DLIB_PATH="${DLL_BUILD_DIR}"
        -DTREE_PATH="${DLL_BUILD_DIR}"
        -P "${PROJECT_SOURCE_DIR}/cmake-common/generate-sac2crc-file.cmake"
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Creating package sac2crc file in user's home directory")

