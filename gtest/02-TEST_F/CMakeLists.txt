cmake_minimum_required(VERSION 3.14)
project(test_2)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

enable_testing()

# set(SOURCES
#     queue
# )

add_executable(
    queue_test
    queue_test.cc
)

target_link_libraries(
    queue_test
    gtest_main ## 依赖了 googletest gtest_main static libaray
)

get_filename_component(PARENT_DIR ../ ABSOLUTE) ## 获取父路径
message(${PARENT_DIR})
message("${PARENT_DIR}/_deps/googletest-src")
add_subdirectory("${PARENT_DIR}/_deps/googletest-src" _deps) ## 引用外部文件夹 指定需要生成对应的目录
include_directories("${PARENT_DIR}/_deps/googletest-src/googletest/include")

