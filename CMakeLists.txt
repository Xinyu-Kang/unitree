# CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(UnitreeProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录（可选）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Boost 配置
find_package(Boost REQUIRED COMPONENTS system)
if(Boost_FOUND)
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found")
endif()

# Unitree SDK 配置
set(UnitreeSDK_INCLUDE_DIR "/path/to/unitree_sdk/include") # 修改为 Unitree SDK 的 include 路径
set(UnitreeSDK_LIBRARY_DIR "/path/to/unitree_sdk/lib")     # 修改为 Unitree SDK 的库路径

# 确保路径存在
if(NOT EXISTS ${UnitreeSDK_INCLUDE_DIR})
    message(FATAL_ERROR "Unitree SDK include path not found: ${UnitreeSDK_INCLUDE_DIR}")
endif()

if(NOT EXISTS ${UnitreeSDK_LIBRARY_DIR})
    message(FATAL_ERROR "Unitree SDK library path not found: ${UnitreeSDK_LIBRARY_DIR}")
endif()

# Qt 配置
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network)
if(Qt5_FOUND)
    message(STATUS "Qt5 found: ${Qt5_DIR}")
else()
    message(FATAL_ERROR "Qt5 not found")
endif()

# 包含头文件路径
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${UnitreeSDK_INCLUDE_DIR}
)

# 链接库文件路径
link_directories(
    ${Boost_LIBRARY_DIRS}
    ${UnitreeSDK_LIBRARY_DIR}
)

# 定义 unitree_client 可执行文件
add_executable(unitree_client src/unitree_client.cpp)
target_link_libraries(unitree_client
    ${Boost_LIBRARIES}
    unitree_sdk
    pthread # 如果需要多线程支持
)

# 定义 qt_interface 可执行文件
add_executable(qt_interface src/qt_interface.cpp)

# Enable automatic `moc` generation for `Q_OBJECT`
set_target_properties(qt_interface PROPERTIES
    AUTOMOC ON
)

target_link_libraries(qt_interface
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
)
