#pragma once

//
// ... JSON Logger header files
//
#include <json_logger/details/import.hpp>
#include <json_logger/details/TimeStamper.hpp>

namespace JSONLogger::Details
{
  class Log
  {
    using pointer = unique_ptr<json>;
    using time_stamp_type = typename TimeStamper::time_stamp_type;
  public:
    using ID_type = size_t;

    Log(ID_type logID);

    void
    log(json const& input);

    void
    log(json && input);


    void
    scope( json const& input );
    
    void
    scope( json&& input );

    void
    descope();

    json
    get() const;

    ID_type
    getID()const;
    
  private:
    TimeStamper stamper;
    ID_type ID;
    time_stamp_type time_stamp;
    pointer current_scope;
    pointer current;
    stack<tuple<time_stamp_type, pointer, pointer>> context;

  }; // end of class Log
  
} // end of namespace JSONLogger::Details
