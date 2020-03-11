if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(WARNING_FLAGS "-Wall -Werror -Wextra -pedantic-errors")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(WARNING_FLAGS "/W4")
else()
    MESSAGE(FATAL_ERROR "WarningFlags.cmake : CMAKE_CXX_COMPILER_ID not recognized: ${CMAKE_CXX_COMPILER_ID}")
endif()