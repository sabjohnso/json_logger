#pragma once

//
// ... Standard header files
//
#include <utility>

//
// ... JSON Logger header files
//
#include <json_logger/details/json.hpp>
#include <json_logger/details/shim.hpp>



namespace JSONLogger
{

  enum class LogLevel {NONE, ERROR, WARN, INFO, DEBUG, TRACE, ALL};

  to_json(json& j, LogLevel level){
    switch(level){
    case LogLevel::NONE: j = {{"LogLevel","NONE"}}; break;
    case LogLevel::ERROR: j = {{"LogLevel","ERROR"}}; break;
    case LogLevel::WARN: j = {{"LogLevel","WARN"}}; break;
    case LogLevel::INFO: j = {{"LogLevel","INFO"}}; break;
    case LogLevel::DEBUG: j = {{"LogLevel","DEBUG"}}; break;
    case LogLevel::TRACE: j = {{"LogLevel","TRACE"}}; break;
    case LogLevel::ALL: j = {{"LogLevel","ALL"}}; break;
    }
  };

  template<LogLevel level>
  struct Level{};

  template<LogLevel level>
  to_json(json& j, LogLevel<level> const& ){
    to_json(j, level);
  }

  constexpr Level<NONE> NONE{};
  constexpr Level<ERROR> ERROR{};
  constexpr Level<WARN> WARN{};
  constexpr Level<INFO> INFO{};
  constexpr Level<DEBUG> DEBUG{};
  constexpr Level<TRACE> TRACE{};
  constexpr Level<ALL> ALL{};

  template<LogLevel level>
  class Scope;

  template<LogLevel level>
  class Logger
  {
  public:
    
    template<
      LogLevel message_level, typename T,
      typename Check = enable_if_t<int(message_level) > int(level), void >>
    static void
    log(Level<message_level> const&, T&&)
    {
      static_assert(message_level != LogLevel::NONE);
    }

    template<
      LogLevel message_level, typename T,
      typename Check = enable_if_t<int(message_level) <= int(level), void >>
    static void
    log(Level<message_level> const&, T&& input){
      Details::Shim::log( std::forward<T>(input));
      static_assert(message_level != LogLevel::NONE);
    }
  }; // end of class Logger


  
} // end of namespace JSONLogger
