//
// ... Standard header files
//
#include <fstream>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... External header files
//
#include <json-schema.hpp>


//
// ... JSONLogger header files
//
#include <json_logger/config.hpp>
#include <json_logger/details/import.hpp>

namespace JSONLogger::Testing
{
  namespace // anonymous
  {
    using std::ifstream;
    using nlohmann::json_schema::json_validator;
    using JSONLogger::Details::json;
    constexpr auto schema_location = JSONLogger::Config::Info::build_schema_location;
    
    
  } // end of anonymous  namespace

  TEST(Schema, Parse){
    ifstream in(schema_location);
    auto schema = json::parse(in);
    json_validator validator;
    ASSERT_NO_THROW(validator.set_root_schema(schema));
  }
  
} // end of namespace JSONLogger::Testing
