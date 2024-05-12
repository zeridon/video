cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)
pico_sdk_init()

project(box_rp2040)

add_subdirectory(./src)
add_subdirectory(./vendor/st7789 EXCLUDE_FROM_ALL)
