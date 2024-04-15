cmake_minimum_required(VERSION 3.24)
project(
  RX-Warning
  VERSION 1.0
  LANGUAGES CXX
)

add_definitions( -DSOURCE_DIR="${PROJECT_SOURCE_DIR}" )

find_package( Boost 1.82.0 REQUIRED COMPONENTS system thread regex container)

ADD_EXECUTABLE( rx-server src/server.cpp)

target_include_directories(rx-server PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(rx-server PUBLIC
  Boost::system
  Boost::thread
  Boost::regex
  Boost::container
)

target_compile_options(rx-server PRIVATE "/wd4566")
