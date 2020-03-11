set(GTEST_DIR "../../../googletest" CACHE PATH "The path to GoogleTest framework")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    option(gtest_force_shared_crt "Use Shared DLL run-time lib even when build as static lib" ON)
elseif (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)
endif()

include_directories(SYSTEM ${GTEST_DIR}/include)
link_directories(${GTEST_DIR}/lib)

add_executable(ToDoTest ToDoTest.cpp)
target_link_libraries(ToDoTest ToDoCore gmock gtest)

add_test(ToDoTest2 ToDoTest)