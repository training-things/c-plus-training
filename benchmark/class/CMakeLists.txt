cmake_minimum_required(VERSION 3.14)
project(test_1)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_executable(
  class_init_benchmark
  class_init_benchmark.cc
)

target_link_libraries(
    class_init_benchmark
    benchmark_main
)

get_filename_component(PARENT_DIR ../ ABSOLUTE) ## 获取父路径
message(${PARENT_DIR})
message("${PARENT_DIR}/_deps")

add_subdirectory("${PARENT_DIR}/_deps/googletest-src" gtest_main) ## 引用外部文件夹 指定需要生成对应的目录
include_directories("${PARENT_DIR}/_deps/googletest-src/googletest/include")


add_subdirectory("${PARENT_DIR}/_deps/benchmark-src" benchmark_main) ## 引用外部文件夹 指定需要生成对应的目录
include_directories("${PARENT_DIR}/_deps/benchmark-src/include")



# /Users/develop/bootcamp2021/c-plus/benchmark/_deps