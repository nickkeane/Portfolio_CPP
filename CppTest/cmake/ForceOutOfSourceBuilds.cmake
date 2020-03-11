###########################################################
# ForceOutOfSourceBuilds
###########################################################
# Force CMake to perform only out of source builds
###########################################################
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-Source builds are not allowed. Please make a new directory and run CMake from there. You may need to remove CMakeCache.txt")
endif()