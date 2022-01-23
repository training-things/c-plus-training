cmake_minimum_required(VERSION 3.14)
project(c-plus-performance)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)

enable_testing()

# set(GTEST_DIR ${PROJECT_SOURCE_DIR}/gtest)

# add_subdirectory("${GTEST_DIR}/_deps/googletest-src" _deps) ## 引用外部文件夹 指定需要生成对应的目录
# include_directories("${GTEST_DIR}/_deps/googletest-src/googletest/include")
include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(util)

file(GLOB_RECURSE SOURCE_CASES "*.cc")
file(GLOB_RECURSE UTIL_SOURCE_FILES "util/*.cc")

list(REMOVE_ITEM SOURCE_CASES ${UTIL_SOURCE_FILES})


message("SOURCE_CASES: " ${SOURCE_CASES})
message("UTIL_SOURCE_FILES: " ${UTIL_SOURCE_FILES})


set(EXE_PREFIX "performance_")

foreach (CASE ${SOURCE_CASES})
    get_filename_component(EXENAME ${CASE} NAME_WE)
    set(EXEC ${EXE_PREFIX}${EXENAME})
    add_executable(${EXEC} ${CASE})
    target_link_libraries(${EXEC} performance-util)
    add_dependencies(${EXEC} performance-util)
    message(
            "EXENAME: " ${EXENAME}
            " CASE: " ${CASE}
            " EXEC: " ${EXEC}
    )

endforeach (CASE ${SOURCE_CASES})


# set(TESTS
#         gtest/01-TEST/hello_test.cc
#         ${GTEST_DIR}/02-TEST_F/queue_test.cc
#         ${GTEST_DIR}/03-TEST_P/value_params_test.cc
#         )

# set(EXE_PREFIX "c_plus_")

# foreach (sourcefile ${TESTS})
#     get_filename_component(exename ${sourcefile} NAME_WE)
#     message("exename " ${exename})
#     message("sourcefile " ${sourcefile})
#     add_executable(${EXE_PREFIX}${exename} ${sourcefile})
#     target_link_libraries(${EXE_PREFIX}${exename} gtest_main)
# endforeach (sourcefile ${TESTS})


