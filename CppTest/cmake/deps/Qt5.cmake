#Include Qt Libraries
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
if(Qt5_FOUND)
    message(STATUS "Found: Qt5")
    message(STATUS "\tQt5::Core")
    message(STATUS "\tQt5::Widgets")
else()
    message(FATAL_ERROR "Not Found: Qt5")
endif()
