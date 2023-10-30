cmake_minimum_required (VERSION 3.12)


add_subdirectory(lib/VL53L0X)

include(pico_sdk_import.cmake)
project (Singel)

pico_sdk_init()



add_executable(Singel Singel.cpp)


target_link_libraries(Singel
	pico_stdlib
	hardware_i2c
	VL53L0X
	
)

# enable usb output, disable uart output
pico_enable_stdio_usb(Singel 1)
pico_enable_stdio_uart(Singel 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(Singel)

# add url via pico_set_program_url
