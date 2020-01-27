configure_file(config.hpp.in config.hpp)

add_library(json_logger
  details/TimeStamper.hpp details/TimeStamper.cpp
  details/Log.hpp details/Log.cpp
  details/Logger.hpp details/Logger.cpp
  details/Shim.hpp details/Shim.cpp)

target_include_directories(json_logger
  PUBLIC
  $<BUILD_INTERFACE:${json_logger_SOURCE_DIR}>
  $<BUILD_INTERFACE:${json_logger_BINARY_DIR}>)

add_library(json_logger::json_logger ALIAS json_logger)

add_executable(json_logger_config config.cpp)

install(TARGETS json_logger json_logger_config
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES json_logger.json
  DESTINATION ${CMAKE_INSTALL_DATAROOT_DIR}/json_logger)
  
  
