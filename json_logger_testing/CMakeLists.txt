find_package(GTest REQUIRED)
find_package(json-schema-validator REQUIRED)

macro(json_logger_add_test test_name exe_name)
  add_executable(${exe_name} ${ARGN})
  target_link_libraries(${exe_name} PRIVATE
    GTest::gtest_main
    json_logger::json_logger
    json-schema-validator::json-schema-validator)
  add_test(${test_name} ${exe_name})
endmacro()

json_logger_add_test(schema scheam_test schema_test.cpp)
json_logger_add_test(time_stamper time_stamper_test time_stamper_test.cpp)
json_logger_add_test(log log_test log_test.cpp)
