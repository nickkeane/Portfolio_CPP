###########################################################
# FixOldVerPolicy
###########################################################
# Policies for CMake Versions older than 3.12 need to be
# adjusted manually to match their version. Newer versions 
# handle this automatically.
###########################################################
if (${CMAKE_VERSION} VERSION_LESS 3.12) # Manually set CMake policy for Vs less than 3.12 
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()