cmake_minimum_required(VERSION 3.24)
project(
  CrowTest3
  VERSION 1.0
  LANGUAGES CXX
)

file( COPY templates DESTINATION Debug/)
find_package( Boost 1.82.0 REQUIRED COMPONENTS system thread regex )
ADD_EXECUTABLE( CrowTesting src/test.cpp )
target_include_directories(CrowTesting PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(CrowTesting PUBLIC
  Boost::system
  Boost::thread
  Boost::regex
)
message(DEBUG "debug test")
message(Boost_INCLUDE_DIRS="${Boost_INCLUDE_DIRS}")
