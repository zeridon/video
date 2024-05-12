add_executable(box_rp2040)

target_include_directories(box_rp2040 PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_sources(box_rp2040 PRIVATE
        main.c
        display.c
        network_switch_status_reader.c
)

# pull in common dependencies
target_link_libraries(box_rp2040 PRIVATE
        pico_stdlib
        pico_st7789
)

# create map/bin/hex file etc.
pico_add_extra_outputs(box_rp2040)
