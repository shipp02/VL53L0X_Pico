cmake_minimum_required (VERSION 3.12)


add_subdirectory(lib/VL53L0X)

project (Continuous)




add_executable(Continuous Continuous)


target_link_libraries(Continuous
	pico_stdlib
	hardware_i2c
	VL53L0X
	
)

# enable usb output, disable uart output
pico_enable_stdio_usb(Continuous 1)
pico_enable_stdio_uart(Continuous 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(Continuous)

# add url via pico_set_program_url
example_auto_set_url(Continuous)
