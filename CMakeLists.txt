cmake_minimum_required(VERSION 3.17)
project(test)

set(CMAKE_CXX_STANDARD 14)

# 添加头文件的库
include_directories(./include)

# aux_source_directory(<dir> <variable>)
# 查找指定目录下的所有源文件
aux_source_directory(./src DIR_SRCS)

# link_directories("/usr/local/lib")
# link_libraries(apue)

add_executable(test main.c ${DIR_SRCS})

target_link_libraries(test libapue.a)
