#include <json_logger/details/Log.hpp>

//
// ... JSON Logger header files
//

namespace JSONLogger::Details
{

  Log::Log(size_t logID)
    : stamper()
    , ID(logID)
    , time_stamp(stamper.stamp())
    , current_scope(make_unique<json>(json{{"name", "TopLevel"}, {"ID", logID}}))
    , current(make_unique<json>(json::array()))
  {}

  void
  Log::log(json const& input){
    current->push_back({stamper.stamp(), input});
  }

  void
  Log::log(json && input ){
    current->push_back({stamper.stamp(), move(input)});
  }

  void
  Log::scope( json const& input ){
    context.push(make_tuple(time_stamp, move(current_scope), move(current)));
    time_stamp = stamper.stamp();
    current_scope = make_unique<json>( input );
    current = make_unique<json>(json{stamper.stamp(),input});
  }

  void
  Log::scope( json && input ){
    context.push(make_tuple(time_stamp, move(current_scope), move(current)));
    time_stamp = stamper.stamp();
    current_scope = make_unique<json>(move(input));
    current = make_unique<json>(json::array()); 
  }

  void
  Log::descope(){
    std::get<2>( context.top())->push_back(
      json{{"scope", *current_scope},
           {"begin", time_stamp},
           {"end", stamper.stamp()},
           {"content", *current}});
    
    delete current_scope.release();
    delete current_scope.release();
    time_stamp = std::get<0>(context.top());
    current_scope = move(std::get<1>(context.top()));
    current = move(std::get<2>(context.top()));
    context.pop();
  }

  json
  Log::get() const {
    return {{"content", *current}, {"scope", *current_scope}};
  }
  
  
} // end of namespace JSONLogger::Details
