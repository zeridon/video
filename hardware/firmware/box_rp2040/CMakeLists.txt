cmake_minimum_required(VERSION 3.12)

include(./vendor/pico-sdk/pico_sdk_init.cmake)

project(box_rp2040)

pico_sdk_init()

add_subdirectory(./src)
add_subdirectory(vendor/st7789 EXCLUDE_FROM_ALL)
add_subdirectory(vendor/rp2040_tca9534/tca9534 EXCLUDE_FROM_ALL)
