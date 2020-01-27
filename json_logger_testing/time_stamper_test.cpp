//
// ... Standard header files
//
#include <thread>
#include <chrono>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... JSON Logger header files
//
#include <json_logger/details/TimeStamper.hpp>



namespace JSONLogger::Testing
{
  namespace // anonymous
  {

    using JSONLogger::Details::TimeStamper;

    using std::this_thread::sleep_for;
    using std::chrono::milliseconds;

  } // end of anonymous namespace

  TEST(TimeStamper, Works){
    TimeStamper ts{};
    
    auto t1 = ts.stamp();
    sleep_for(milliseconds(100));
    auto t2 = ts.stamp();

    EXPECT_LT( t1, t2 );

  }
  
} // end of namespace JSONLogger::Testing
