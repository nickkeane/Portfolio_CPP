cmake_minimum_required(VERSION 3.15...3.16 FATAL_ERROR)

project(
    MyLibExampleProject
    VERSION 1.0.0.0
    DESCRIPTION "A test library"
    LANGAUGES C CXX
)

if (WIN32 AND MSVC)
elseif(WIN32) # MinGW/Cygwin(?)
endif() # Linux/Cygwin(?)

### For Out-Of-Source Builds Only
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory, or use '-B <build_dir>'. Please remove CMakeCache.txt and CMakeFiles.")
endif()

### With Settings
##################################################################
set(PRJ_DEFAULT_BUILD_TYPE "RelWithDebInfo")
option(MCM_DOSTUFF "Should we do stuff?" ON)
option(MCM_ENABLE_TESTING "Should we enable testing?" OFF)
##################################################################
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${PRJ_DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${PRJ_DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
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
include(CheckIPOSupported)
check_ipo_supported(RESULT is_ipo_enabled)

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
find_library(sodium_LIB NAMES sodium.a sodium.lib PATHS "${sodium_DIR}/lib" NO_DEFAULT_PATH)
if (sodium_LIB)
    MESSAGE(STATUS "Sodium: Found\n\t${sodium_LIB}\n\t${sodium_INC_DIR}")
endif()

### Creating Library
add_library(                MyLibExample simple_lib.cpp simple_lib.h)
target_compile_features(    MyLibExample PUBLIC cxx_std_17)
set_target_properties(      MyLibExample PROPERTIES CXX_EXTENSIONS OFF)
#if (is_ipo_enabled)
    set_target_properties(  MyLibExample PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)
#endif()
set_target_properties(      MyLibExample PROPERTIES SOVERSION 1)
set_target_properties(      MyLibExample PROPERTIES VERSION 1.0.0.0)
# include(GNUInstallDirs)
# install(
#     TARGETS MyLibExample EXPORT MyLibExampleTargets
#     LIBRARY DESTINATION lib COMPONENT MyLibExample_Runtime NAMELINK_COMPONENT MyLibExample_Development
#     ARCHIVE DESTINATION lib COMPONENT MyLibExample_Development
#     RUNTIME DESTINATION bin COMPONENT MyLibExample_Runtime
#     INCLUDES DESTINATION include 
# )
# install(
#     EXPORT MyLibExampleTargets
#     FILE MyLibExampleTargets.cmake
#     NAMESPACE MyLibExample::
#     DESTINATION lib/cmake/MyLibExample
# )
# include(CMakePackageConfigHelpers)
# write_basic_package_version_file(
#                     "MyLibExampleVersion.cmake"
#     VERSION         ${MyLibExample_VERSION}
#     COMPATIBILITY   SameMajorVersion
# )
# install(FILES 
#     "MyLibExample.cmake"
#     "MyLibExampleVersion.cmake"
#     DESTINATION lib/cmake/MyLibExample
# )

# include(CMakeFindDependencyMacro)
# find_dependency(MyOtherLibExample 1.1.4)
# include("${CMAKE_CURRENT_LIST_DIR}/MyLibExample.cmake")
# target_include_directories(MyLibExample
#     PUBLIC
#     $<BUILD_INTERFACE:${MyLibExample_BINARY_DIR}/include>
#     $<BUILD_INTERFACE:${MyLibExample_SOURCE_DIR}/include>
#     $<INSTALL_INTERFACE:include>
# )

### Linked To
## TODO

### Creating Executable
add_executable(             MyExample main.cpp)
target_compile_features(    MyExample PRIVATE cxx_std_17)
set_target_properties(      MyExample PROPERTIES CXX_EXTENSIONS OFF)
target_compile_options(     MyExample PRIVATE ${WARNING_FLAGS})
target_compile_definitions( MyExample PUBLIC -DTEST_DEF)
#if (is_ipo_enabled)
    set_target_properties(  MyExample PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)
#endif()
target_include_directories( MyExample PUBLIC include)
target_link_libraries(      MyExample PRIVATE MyLibExample)

### With Testing
if (MCM_ENABLE_TESTING)
    enable_testing()
endif()

### Then Cleanup
## Remove Cached Vars
unset(MCM_ENABLE_TESTING)
unset(MCM_DOSTUFF)
## And Mark as RUN_BEFORE
set(RUN_BEFORE TRUE CACHE INTERNAL "Flag showing that CMake has configured at least once before.")
