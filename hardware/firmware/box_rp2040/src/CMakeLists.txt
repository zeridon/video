add_executable(box_rp2040)

target_include_directories(box_rp2040 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        usb
)

target_sources(box_rp2040 PRIVATE
        main.c
        display.c
        io.c
        io_commands.c
        network_switch_status_reader.c

        usb/usb_descriptors.c
        usb/usb.c
)

target_link_libraries(box_rp2040 PRIVATE
        pico_stdlib
        pico_st7789

        tinyusb_device
        tinyusb_board
)

pico_add_extra_outputs(box_rp2040)
