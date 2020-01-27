#pragma once

//
// ... Standard header files
//
#include <mutex>

//
// ... JSON Logger header files
//
#include <json_logger/details/import.hpp>
#include <json_logger/details/Log.hpp>

namespace JSONLogger::Details
{

  class Logger
  {

    friend class Shim;
    using ID_type = typename  Log::ID_type;

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

    static void
    initialize();

    static json
    aggregate();

    static void
    dumplog();


    static ID_type
    currentID();

    static Log&
    currentLog();

    static std::mutex mex;
    static bool initialized;
    static unordered_map<ID_type,Log> table;
  };

} // end of namespace JSONLogger::Details
