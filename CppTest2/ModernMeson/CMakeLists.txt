### For CMake 3.x
cmake_minimum_required(VERSION 3.1...3.15 FATAL_ERROR)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

### Define Project
project(
                    ModernCMakeExample 
    VERSION         1.0.0.0
    DESCRIPTION     "Modern CMake Project"
    LANGUAGES       C CXX
)

### For Out-Of-Source Builds Only
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory, or use '-B <build_dir>'. Please remove CMakeCache.txt and CMakeFiles.")
endif()

### With Settings
##################################################################
set(DEFAULT_BUILD_TYPE "Debug")
option(MCM_DOSTUFF "Should we do stuff?" ON)
option(MCM_ENABLE_TESTING "Should we enable testing?" OFF)
##################################################################
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

### With Complete Warnings
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"
    OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(WARNING_FLAGS -Wall -Wextra -Werror -pedantic-errors)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(WARNING_FLAGS /W4 /WX /EHsc)
else()
    message(FATAL_ERROR "Unrecognized CXX compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

### With Optimizations
#include(CheckIPOSupported)
#check_ipo_supported(RESULT is_ipo_enabled)

### With Packages/Libraries/Programs/Files
## CCache
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    MESSAGE(STATUS "CCache: Found\n\t${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CUDA_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

## libSodium
set(sodium_DIR "C:/Users/nkeane/Desktop/CppTest/libs/libsodium")
find_path(sodium_INC_DIR NAMES include PATHS "${sodium_DIR}" NO_DEFAULT_PATH)
find_library(sodium_LIB NAMES sodium PATHS "${sodium_DIR}" NO_DEFAULT_PATH)
if (sodium_LIB)
    MESSAGE(STATUS "Sodium: Found\n\t${sodium_LIB}\n\t${sodium_INC_DIR}")
endif()

### Creating Library
# add_library(MyLibExample simple_lib.cpp simple_lib.h)
# target_compile_features(MyLibExample PUBLIC cxx_std_20)
# set_target_properties(MyLibExample PROPERTIES CXX_EXTENSIONS OFF)
#if (is_ipo_enabled)
    # set_target_properties(MyLibExample PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)
    # set_target_properties(MyLibExample PROPERTIES SOVERSION 1)
    # set_target_properties(MyLibExample PROPERTIES VERSION 1.0.0.0)
#endif()
# include(GNUInstallDirs)
# install(TARGETS MyLibExample
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT MyLibExample_Runtime
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT MyLibExample_Runtime NAMELINK_COMPONENT MyLibExample_Development
#     ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT MyLibExample_Development
# )

### Linked To
## TODO

### Creating Executable
add_executable(             MyExample main.cpp)
target_compile_features(    MyExample PUBLIC cxx_std_17)
set_target_properties(      MyExample PROPERTIES CXX_EXTENSIONS OFF)
target_compile_options(     MyExample PUBLIC ${WARNING_FLAGS})
target_compile_definitions( MyExample PUBLIC -DTEST_DEF)
#if (is_ipo_enabled)
    set_target_properties(MyExample PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)
#endif()
# target_link_libraries(MyExample PRIVATE MyLibExample)

### With Testing
if (MCM_ENABLE_TESTING)
    enable_testing()
    add_test(NAME MyExample COMMAND MyExample)
endif()

### Then Cleanup
## Remove Cached Vars
unset(MCM_ENABLE_TESTING)
unset(MCM_DOSTUFF)
## And Mark as RUN_BEFORE
set(RUN_BEFORE TRUE CACHE INTERNAL "Flag showing that CMake has configured at least once before.")
