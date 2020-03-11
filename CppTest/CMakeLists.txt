cmake_minimum_required(VERSION 3.15...3.16)
include(cmake/FixOldVerPolicy.cmake)
project(
    CppTest
    DESCRIPTION "A simple CppTest app"    
    VERSION 1.0.0.0
    LANGUAGES C CXX
)
# Calling project above also sets
# CppTest_SOURCE_DIR  - C:/Users/<User>/Desktop/CppTest | Root of project directory / workdir
# CppTest_BINARY_DIR  - C:/Users/<User>/Desktop/CppTest/build-mingw | Root of build directory
# CppTest_VERSION     - 1.0.0.0 | Also, <MAJOR|MINOR|PATCH|TWEAK>_VERSION
# CppTest_DESCRIPTION - A simple CppTest app
# TODO: Export project vars to file, or find a way to auto-import them into placeholders in app
# TODO: Platform, Compiler/Toolset, Build Type
include(cmake/ForceOutOfSourceBuilds.cmake)
include(cmake/SetDefaultBuildType.cmake)
include(cmake/WarningFlags.cmake)

add_executable(             CppTest main.cpp)
add_executable(             BT::CppTest ALIAS CppTest)
set_target_properties(      CppTest PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(    CppTest PUBLIC cxx_std_17)
target_compile_definitions( CppTest PUBLIC -DMY_VAR)
target_compile_options(     CppTest PUBLIC ${WARNING_FLAGS})

# Check Build Type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
    message(STATUS "Build Type was not specified. Setting default to ${CMAKE_BUILD_TYPE}")
    message(STATUS "Selections include Debug, Release, RelWithDebInfo, and MinRelSize")
endif()

# Include Conan Dependencies
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()
#TODO: Is this necessary, or does CONAN_LIBS resolve this?
#target_include_directories(CppTest PUBLIC ${CONAN_INCLUDE_DIRS})
target_link_libraries(CppTest ${CONAN_LIBS})

# Define External Dependencies
file(GLOB PROJ_Deps "cmake/deps/*.cmake")
foreach(PROJ_Dep ${PROJ_Deps})
    include(${PROJ_Dep})
endforeach()

# Apply External Dependencies
if (easy_profiler_FOUND)
    target_include_directories(CppTest PUBLIC ${easy_profiler_INCLUDE})
    target_link_libraries(CppTest ${easy_profiler_LIBS})
endif()

if (Qt5_FOUND)
    target_link_libraries(CppTest Qt5::Core)
    target_link_libraries(CppTest Qt5::Widgets)
endif()

if (Boost_FOUND)
    target_include_directories(CppTest PUBLIC ${Boost_INCLUDE_DIRS})
    target_link_libraries(CppTest ${Boost_LIBRARIES})
endif()