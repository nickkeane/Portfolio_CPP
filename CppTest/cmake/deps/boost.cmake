# TODO: Moved to conan pkg management
# # Include Boost Libraries
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_COMPILER mgw92)
set(Boost_DEBUG ON)
find_package(Boost 1.71.0 REQUIRED PATHS D:/API/CPP/MinGW
    COMPONENTS chrono timer)
if (Boost_FOUND)
    message(STATUS "Found: Boost")
    message(STATUS "Version: ${Boost_VERSION}")
    message(STATUS "\t${Boost_INCLUDE_DIRS}")
    message(STATUS "\t${Boost_LIBRARIES}")
endif()