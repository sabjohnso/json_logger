#include <json_logger/details/Logger.hpp>

//
// ... Standard header files
//
#include <cstdlib>
#include <mutex>
#include <thread>
#include <stdexcept>
#include <sstream>
#include <fstream>

//
// ... External header files
//
#include <unistd.h>

//
// ... JSON Logger header files
//
#include <json_logger/details/Log.hpp>

namespace JSONLogger::Details
{
  namespace // anonymous
  {

    using std::atexit;
    using std::mutex;
    using std::lock_guard;    
    using std::runtime_error;
    using std::stringstream;
    using std::ofstream;
    using std::thread;
    using std::make_pair;

    using ID_type = typename Log::ID_type;

  } // end of anonymous namespace

  ID_type
  Logger::currentID(){
    return std::hash<thread::id>{}(std::this_thread::get_id());
  }

  Log&
  Logger::currentLog(){
    ID_type ID = currentID();
    if(! table.count(ID)){
      table.emplace(make_pair(ID,ID));
    }
    return table.at(ID);
  }

  void
  Logger::log( json const& input){ currentLog().log(input); }

  void
  Logger::log( json && input ){ currentLog().log(move(input)); }

  void
  Logger::scope( json const& input){ currentLog().scope(input); }

  void
  Logger::scope( json && input ){ currentLog().scope( move( input )); }

  void
  Logger::descope(){ currentLog().descope(); }

  bool Logger::initialized = false;
  
  void
  Logger::initialize(){
    if(! initialized ){
      lock_guard<mutex> lock();
      if(! initialized ){
        if( atexit(dumplog) ){
          throw runtime_error( 
            "std::atexit returned a nonzero value when "
            "attempting to register a function to write the "
            "log to a file.");
        }
      }
    }
  }

  json
  Logger::aggregate(){
    json result = json::array();
    for_each(
      begin(table), end(table),
      [&](auto const& thread_log){
        result.push_back({thread_log.first, thread_log.second.get()});
      });
    return result;
  }
  

  void
  Logger::dumplog(){
    stringstream ss;
    ss << "log" << getpid() << ".json";
    ofstream out( ss.str());
    out << aggregate().dump(2);
  }
  
} // end of namespace JSONLogger::Details
