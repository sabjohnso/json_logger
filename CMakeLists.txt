cmake_minimum_required(VERSION 3.12)
project(json_logger VERSION 0.1.0)

option(build_json_logger_testing "Build the tests for json_logger" ON)

list(INSERT CMAKE_MODULE_PATH 0 ${json_logger_SOURCE_DIR}/cmake_utilities)
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
find_package(CMakeUtilities)

find_package(nlohmann_json REQUIRED)

add_subdirectory(json_logger)

if(build_json_logger_testing)
  enable_testing()
  add_subdirectory(json_logger_testing)
endif()







