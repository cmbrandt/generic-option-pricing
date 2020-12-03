
add_library(oop.pricing
  convergence_table.cpp
  statistics.cpp
  statistics_bridge.cpp
  parameters.cpp
  payoff.cpp
  payoff_bridge.cpp
  random.cpp
  monte_carlo.cpp
  vanilla_option.cpp)

set(CMAKE_CXX_FLAGS "-std=c++1z -fconcepts")

add_executable(oop.vanilla main_vanilla.cpp)
target_link_libraries(oop.vanilla oop.pricing)
