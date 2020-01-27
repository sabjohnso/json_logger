//
// ... Standard header files
//
#include <cstddef>
#include <string>
#include <fstream>

//
// ... Standard header files
//
#include <iostream>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... External header files
//
#include <json-schema.hpp>

//
// ... JSON Logger header files
//
#include <json_logger/config.hpp>
#include <json_logger/details/Log.hpp>



namespace JSONLogger::Testing
{
  namespace // anonymous
  {
    using std::size_t;
    using std::string;
    using std::ifstream;

    using nlohmann::json_schema::json_validator;
    
    using JSONLogger::Details::Log;
    using JSONLogger::Details::json;
    constexpr auto schema_location =  JSONLogger::Config::Info::build_schema_location;
    

    using ID_type = typename Log::ID_type;
  } // end of anonymous namespace

  
  TEST(Log, Construction){
    size_t id = 0;
    Log log(id);
    std::cout << log.get().dump(2) << std::endl;
    EXPECT_EQ(log.get(), 
              json({{"content", json::array()}, 
                    {"scope",
                     {{"name", "TopLevel"},
                      {"ID", 0}}}}));
  }

  TEST(Log, Logging){
    size_t id = 0;
    string message1 = "first message";
    string message2 = "second message";

    Log log(id);
    log.log(message1);
    log.log(message2);

    json output = log.get();
    EXPECT_EQ( output["content"][0][1], message1);
    EXPECT_EQ( output["content"][1][1], message2);
  }

  TEST(Log, Scope)
  {
    ID_type ID = 0;
    Log log(ID);
    string message1 = "first message";    
    string scope_name = "new scope";
    string scoped_message1 = "first message in scope";
    string scoped_message2 = "second message in scope";
    string message2 = "second message";

    log.log(message1);
    {
      log.scope(scope_name);
      log.log(scoped_message1);
      log.log(scoped_message2);

      json scope_output = log.get();
      EXPECT_EQ(scope_output["scope"], scope_name);
      EXPECT_EQ(scope_output["content"].size(), 2);
      EXPECT_EQ(scope_output["content"][0][1], scoped_message1);
      EXPECT_EQ(scope_output["content"][1][1], scoped_message2);

      log.descope();
    };

    log.log(message2);

    json output = log.get();
    
    EXPECT_EQ(output["scope"]["name"], "TopLevel");
    EXPECT_EQ(output["scope"]["ID"], ID);
    EXPECT_EQ(output["content"].size(), 3);
    
    EXPECT_TRUE(output["content"][0].is_array());
    EXPECT_TRUE(output["content"][0][0].is_number());
    EXPECT_EQ(output["content"][0][1], message1);

    
    EXPECT_TRUE(output["content"][1].is_object());
    {
      json scope_output = output["content"][1];
      EXPECT_TRUE( scope_output["begin"].is_number());
      EXPECT_TRUE( scope_output["end"].is_number());
      EXPECT_LE( scope_output["begin"], scope_output["end"]);
      EXPECT_EQ( scope_output["scope"], scope_name);

      EXPECT_TRUE( scope_output["content"].is_array());
      EXPECT_EQ( scope_output["content"].size(), 2);
      
      EXPECT_TRUE( scope_output["content"][0].is_array());
      EXPECT_EQ( scope_output["content"][0].size(),2);
    }
    
    EXPECT_TRUE(output["content"][2].is_array());
    EXPECT_TRUE(output["content"][2][0].is_number());
    EXPECT_EQ(output["content"][2][1], message2);

    json_validator validator;
    {
      ifstream in(schema_location);
      json schema = json::parse(in);
      validator.set_root_schema(schema);
      std::cout << schema.dump() << std::endl;
    }
    validator.validate(log.get());

    

  }
  
} // end of namespace JSONLogger::Testing
