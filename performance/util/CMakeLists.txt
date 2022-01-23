# Set the project name
project(performance-util)


message("PROJECT_NAME " ${PROJECT_NAME})
message("PROJECT_SOURCE_DIR " ${PROJECT_SOURCE_DIR})


file(GLOB_RECURSE UTIL_SOURCE_FILES "*.cc")
add_library(${PROJECT_NAME} STATIC ${UTIL_SOURCE_FILES})


