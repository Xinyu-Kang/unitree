# CMake Minimum Version
cmake_minimum_required(VERSION 3.10)

# Project Name
project(UnitreeProject)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Boost Configuration
find_package(Boost REQUIRED COMPONENTS system)
if(Boost_FOUND)
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found")
endif()

# Unitree SDK Configuration
set(UnitreeSDK_INCLUDE_DIR "/path/to/unitree_sdk/include") # Update to actual path
set(UnitreeSDK_LIBRARY_DIR "/path/to/unitree_sdk/lib")     # Update to actual path

# Ensure Paths Exist
if(NOT EXISTS ${UnitreeSDK_INCLUDE_DIR})
    message(FATAL_ERROR "Unitree SDK include path not found: ${UnitreeSDK_INCLUDE_DIR}")
endif()
if(NOT EXISTS ${UnitreeSDK_LIBRARY_DIR})
    message(FATAL_ERROR "Unitree SDK library path not found: ${UnitreeSDK_LIBRARY_DIR}")
endif()

# Qt Configuration
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network)
if(Qt5_FOUND)
    message(STATUS "Qt5 found: ${Qt5_DIR}")
else()
    message(FATAL_ERROR "Qt5 not found")
endif()

# Path Variables
set(BOOST_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
set(BOOST_LIBRARY_DIRS ${Boost_LIBRARY_DIRS})
set(UNITREE_INCLUDE_DIR ${UnitreeSDK_INCLUDE_DIR})
set(UNITREE_LIBRARY_DIR ${UnitreeSDK_LIBRARY_DIR})

# Include and Link Directories
include_directories(${BOOST_INCLUDE_DIRS} ${UNITREE_INCLUDE_DIR})
link_directories(${BOOST_LIBRARY_DIRS} ${UNITREE_LIBRARY_DIR})

# Define unitree_client Executable
add_executable(unitree_client src/unitree_client.cpp)
target_link_libraries(unitree_client
    ${Boost_LIBRARIES}
    unitree_sdk
    pthread # Multithreading support
)

# Define qt_interface Executable
add_executable(qt_interface src/qt_interface.cpp)
target_link_libraries(qt_interface
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
    unitree_sdk_main
)

# Global AUTOMOC for Qt Targets
set(CMAKE_AUTOMOC ON)
