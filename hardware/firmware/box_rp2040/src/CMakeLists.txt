add_executable(box_rp2040)

pico_generate_pio_header(box_rp2040 ${CMAKE_CURRENT_LIST_DIR}/st7789_lcd.pio)

target_include_directories(box_rp2040 PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_sources(box_rp2040 PRIVATE
        main.c
        # network_switch_status_reader.c
)

# pull in common dependencies
target_link_libraries(box_rp2040 PRIVATE
        pico_stdlib
        hardware_pio
        hardware_interp
)

# create map/bin/hex file etc.
pico_add_extra_outputs(box_rp2040)
