
add_library(gp.pricing
  concepts.cpp
  function.cpp
  random.cpp
  payoff.cpp
  option.cpp
  parameter.cpp
  statistics.cpp
  monte_carlo.cpp)

set(CMAKE_CXX_FLAGS "-std=c++1z -fconcepts")

add_executable(gp.vanilla main_vanilla.cpp)
target_link_libraries(gp.vanilla gp.pricing)
