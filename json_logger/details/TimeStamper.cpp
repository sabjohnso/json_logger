#include <json_logger/details/TimeStamper.hpp>

//
// ... Standard header files
//
#include <chrono>

namespace JSONLogger::Details
{
  namespace // anonymous
  {
    using std::chrono::duration_cast;
    using std::chrono::system_clock;
    using std::chrono::milliseconds;

    using time_stamp_type = typename TimeStamper::time_stamp_type;
  } // end of anonymous namespace 

  time_stamp_type
  TimeStamper::stamp() const {
    auto point = system_clock::now();
    return time_stamp_type(duration_cast<milliseconds>(point.time_since_epoch()).count()) / 1000;
  }
  
} // end of namespace JSONLogger::Details
