#include <json_logger/details/Shim.hpp>

//
// ... JSON Logger header files
//
#include <json_logger/details/import.hpp>
#include <json_logger/details/Logger.hpp>

namespace JSONLogger::Details
{
  
  void
  Shim::log(json const& j){ Logger::log( j ); }

  void
  Shim::log(json && j ){ Logger::log( move( j )); }

  void
  Shim::scope(json const& j){ Logger::scope( j ); }

  void
  Shim::scope(json && j){ Logger::scope(move( j )); }

  void
  Shim::descope(){ Logger::descope(); }

  
  
} // end of namespace JSONLogger::Details
