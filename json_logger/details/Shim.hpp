#pragma once

//
// ... JSON Logger header files
//
#include <json_logger/details/json.hpp>

namespace JSONLogger::Details
{

  struct Shim{

    static void
    log(json const& j);

    static void
    log(json && j );

    static void
    scope(json const& j);

    static void
    scope(json && j);

    static void
    descope();
  };
  
} // end of namespace JSONLogger::Details
