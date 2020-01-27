#pragma once

namespace JSONLogger::Details
{

  class TimeStamper
  {
  public:
    using time_stamp_type = double;    
    time_stamp_type
    stamp() const;
  }; // end of class TimeStamper
  
} // end of namespace JSONLogger::Details
