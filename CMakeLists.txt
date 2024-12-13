cmake_minimum_required(VERSION 3.10)  # 指定最低版本
project(UnitreeClient)                # 项目名称

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置 Boost 的查找路径（如果 Boost 已安装在系统默认路径中，可以省略）
set(Boost_INCLUDE_DIR /path/to/boost/include)
set(Boost_LIBRARY_DIR /path/to/boost/lib)

# 查找 Boost 库（以 Boost.Asio 为例，需要 Boost.System 支持）
find_package(Boost REQUIRED COMPONENTS system)

# 设置 Unitree SDK 的路径
set(UnitreeSDK_INCLUDE_DIR /path/to/unitree_sdk/include)
set(UnitreeSDK_LIBRARY_DIR /path/to/unitree_sdk/lib)

# 添加 include 目录
include_directories(${Boost_INCLUDE_DIR} ${UnitreeSDK_INCLUDE_DIR})

# 添加库目录
link_directories(${Boost_LIBRARY_DIR} ${UnitreeSDK_LIBRARY_DIR})

# 添加可执行文件
add_executable(unitree_client unitree_client.cpp)

# 链接所需的库
target_link_libraries(unitree_client
    ${Boost_LIBRARIES}
    unitree_sdk
    pthread  # 如果需要多线程支持
)
