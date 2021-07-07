cmake_minimum_required(VERSION 3.14)
project(test_1)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_executable(
  hello_test
  hello_test.cc
)

target_link_libraries(
  hello_test
  gtest_main ## 依赖了 googletest gtest_main static libaray
)


get_filename_component(PARENT_DIR ../ ABSOLUTE) ## 获取父路径
message(${PARENT_DIR})
message("${PARENT_DIR}/_deps/googletest-src")
add_subdirectory("${PARENT_DIR}/_deps/googletest-src" _deps) ## 引用外部文件夹 指定需要生成对应的目录
include_directories("${PARENT_DIR}/_deps/googletest-src/googletest/include")

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
# target_include_directories(test_1
#   PUBLIC 
#         ${PROJECT_SOURCE_DIR}/_deps/googletest-src/googletest/include/gtest
# )

# Cannot specify include directories for target "test_1" which is not built
# gtest_discover_tests(hello_test)