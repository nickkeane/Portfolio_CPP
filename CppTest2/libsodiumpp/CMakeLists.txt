### For CMake 3.x
cmake_minimum_required(VERSION 3.1...3.15 FATAL_ERROR)
if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

### Define Project
project(
                    sodiumpp 
    VERSION         1.0
    DESCRIPTION     "A C++ wrapper around libSodium"
    LANGUAGES       CXX
)

### For Out-Of-Source Builds Only
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory, or use '-B <build_dir>'. Please remove CMakeCache.txt and CMakeFiles.")
endif()

### With Settings
##################################################################
set(DEFAULT_BUILD_TYPE "Debug")
option(PROJ_DOSTUFF "Should we do stuff?" ON)
option(PROJ_ENABLE_TESTING "Should we enable testing?" OFF)
##################################################################
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

### With Standard Output Directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

### With Complete Warnings
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"
    OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(WARNING_FLAGS "-Wall -Wextra -Werror")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(WARNING_FLAGS "/W4 /WX /EHsc")
else()
    message(FATAL_ERROR "Unrecognized CXX compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

if (NOT RUN_BEFORE)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARNING_FLAGS}" CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS}" CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

### Creating Library
add_library(sodiumpp sodiumpp.cpp sodiumpp.h)
target_compile_features(sodiumpp PUBLIC cxx_std_20)
set_target_properties(sodiumpp PROPERTIES CXX_EXTENSIONS OFF)
#if (is_ipo_enabled)
    set_target_properties(sodiumpp PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)
#endif()

### With Testing Executable
add_executable(sodiumpp_tests sodiumpp_tests.cpp)
target_compile_features(sodiumpp_tests PUBLIC cxx_std_20)
set_target_properties(sodiumpp_tests PROPERTIES CXX_EXTENSIONS OFF)
#if (is_ipo_enabled)
    set_target_properties(sodiumpp_tests PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)
#endif()
add_dependencies(sodiumpp_tests sodiumpp)
target_link_libraries(sodiumpp_tests sodiumpp)

### With Optimizations
#include(CheckIPOSupported)
#check_ipo_supported(RESULT is_ipo_enabled)

### With Packages/Libraries/Programs/Files
set(LIBDIR "C:/Users/nkeane/Desktop/CppTest/libs")
## CCache
find_program(CCACHE_PROG ccache)
if (CCACHE_PROG)
    MESSAGE(STATUS "CCache: Found\n\t${CCACHE_PROG}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROG}")
    set(CMAKE_CUDA_COMPILER_LAUNCHER "${CCACHE_PROG}")
endif()

## googletest
set(gtest_DIR "${LIBDIR}/googletest")
set(gtest_BIN "${gtest_DIR}/bin")
set(gtest_INC "${gtest_DIR}/include")
set(gtest_LIB "${gtest_DIR}/lib")
find_library(gtest_LIBS NAMES gtest PATHS "${gtest_LIB}" NO_DEFAULT_PATH)
find_library(gmock_LIBS NAMES gmock PATHS "${gtest_LIB}" NO_DEFAULT_PATH)
if (gtest_LIBS AND gmock_LIBS)
    MESSAGE(STATUS "GTest: Found\n\t${gtest_LIBS}\n\t${gmock_LIBS}\n\t${gtest_INC}")
    target_include_directories(sodiumpp_tests PUBLIC ${gtest_INC})
    target_link_libraries(sodiumpp_tests ${gtest_LIBS})
    target_link_libraries(sodiumpp_tests ${gmock_LIBS})
else()
    unset(gtest_BIN)
    unset(gtest_INC)
    unset(gtest_LIB)
    MESSAGE(FATAL_ERROR "GTest: Not Found")
endif()

## libSodium - TODO: Try dll.a version using bin folder (libsodium-23)
set(sodium_DIR "${LIBDIR}/libsodium")
set(sodium_INC "${sodium_DIR}/include")
set(sodium_BIN "${sodium_DIR}/bin")
set(sodium_LIB "${sodium_DIR}/lib")
find_library(sodium_LIBS NAMES libsodium.a PATHS "${sodium_LIB}" NO_DEFAULT_PATH)
if (sodium_LIBS)
    MESSAGE(STATUS "Sodium: Found\n\t${sodium_LIBS}\n\t${sodium_INC}\n\t${sodium_BIN}")
    target_include_directories(sodiumpp PUBLIC ${sodium_INC})
    target_link_libraries(sodiumpp ${sodium_LIBS})
    target_include_directories(sodiumpp_tests PUBLIC ${sodium_INC})
    target_link_libraries(sodiumpp_tests ${sodium_LIBS})
    file(COPY 
        ${sodium_BIN}/libsodium-23.dll
        DESTINATION ${CMAKE_BINARY_DIR}/bin
    )
    # add_custom_target(
    #     TARGET SodiumCopyBinaries
    #     POST_BUILD
    #     COMMAND ${CMAKE_COMMAND} -E copy ${sodium_BIN}/libsodium-23.dll ${CMAKE_BINARY_DIR}/bin
    #     COMMENT "Copying DLLs for sodium to ${CMAKE_BINARY_DIR}" VERBATIM
    # )
else()
    unset(sodium_BIN)
    unset(sodium_INC)
    unset(sodium_LIB)
    MESSAGE(FATAL_ERROR "Sodium: Not Found")    
endif()

## Boost
set(boost_DIR "${LIBDIR}/boost")
set(boost_INC "${boost_DIR}/include")
set(boost_BIN "${boost_DIR}/bin")
set(boost_LIB "${boost_DIR}/lib")
set(boost_CMP chrono timer)
foreach (cmp IN LISTS boost_CMP)
    list(APPEND boost_LIBS "${boost_LIB}/libboost_${cmp}-mgw92-mt-x64-1_72.a")
endforeach()

if (boost_LIBS)
    MESSAGE(STATUS "Boost: Found\n\t${boost_LIBS}\n\t${boost_INC}\n\t${boost_BIN}")
    target_include_directories(sodiumpp PUBLIC ${boost_INC})
    target_link_libraries(sodiumpp ${boost_LIBS}) 
else()
    unset(boost_BIN)
    unset(boost_INC)
    unset(boost_LIB)
    MESSAGE(FATAL_ERROR "Boost: Not Found")    
endif()

### With Testing
if (PROJ_ENABLE_TESTING)
    enable_testing()
    add_test(NAME sodiumpp_tests COMMAND sodiumpp_tests)
endif()

### Then Cleanup
## Remove Cached Vars
unset(PROJ_ENABLE_TESTING)
unset(PROJ_DOSTUFF)
## And Mark as RUN_BEFORE
set(RUN_BEFORE TRUE CACHE INTERNAL "Flag showing that CMake has configured at least once before.")
