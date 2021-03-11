


add_library(VL53L0X INTERFACE)

target_sources(VL53L0X INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/VL53L0X.cpp
)

target_include_directories(VL53L0X INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Pull in pico libraries that we need
target_link_libraries(VL53L0X INTERFACE pico_stdlib hardware_i2c)
