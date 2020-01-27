#pragma once

//
// ... Standard header files
//
#include <cstddef>
#include <utility>
#include <type_traits>
#include <stack>
#include <unordered_map>
#include <memory>

//
// ... JSON Logger header files
//
#include <json_logger/details/json.hpp>

namespace JSONLogger::Details
{
  using std::size_t;

  using std::move;
  using std::forward;
  using std::tuple;
  using std::make_tuple;
  
  using std::unique_ptr;
  using std::make_unique;
  using std::stack;
  using std::unordered_map;

} // end of namespace JSONLogger::Details
