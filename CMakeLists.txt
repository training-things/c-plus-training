cmake_minimum_required(VERSION 3.14)
project(c-plus)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

enable_testing()

set(GTEST_DIR ${PROJECT_SOURCE_DIR}/gtest)

add_subdirectory("${GTEST_DIR}/_deps/googletest-src" _deps) ## 引用外部文件夹 指定需要生成对应的目录
include_directories("${GTEST_DIR}/_deps/googletest-src/googletest/include")

set(TESTS
        gtest/01-TEST/hello_test.cc
        ${GTEST_DIR}/02-TEST_F/queue_test.cc
        ${GTEST_DIR}/03-TEST_P/value_params_test.cc
        )

set(EXE_PREFIX "c_plus_")

foreach (sourcefile ${TESTS})
    get_filename_component(exename ${sourcefile} NAME_WE)
    message("exename " ${exename})
    message("sourcefile " ${sourcefile})
    add_executable(${EXE_PREFIX}${exename} ${sourcefile})
    target_link_libraries(${EXE_PREFIX}${exename} gtest_main)
endforeach (sourcefile ${TESTS})


