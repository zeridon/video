## Parallel work of teams to assemble boxes

### Team 1 - Disassembly

As described in the disassembly.

### Team 2 - Fan preparation

- Input: fans, connectors
- Output: crimped fans with 70mm cables
- Steps: `crimp_fan_connectors`

### Team 3 - power cables

- Input: Copper cable, flux
- Output: 260mm tinned power cables with barrel jack
- Steps: `cut_pwr_cable`, `strip_ends_of_pwr_cable`, `tin_ends_of_pwr_cable`, `solder_pwr_cable_to_barrel_jack`
 
This requires soldering!

### Team 4 - radxa power cables

- Input: small cables, terminals
- Output: terminated radxa power cables
- Steps: `strip_ends_of_radxa_pwr_cable`, `attach_terminal_to_radxa_pwr_cable`

### Team 5 - mark MTA100 cables

- Input: MTA100 cables, marking tool
- Output: marked MTA100 cables
- Steps: `mark_duped_mta100_cables`, `mark_duped_mta100_connectors`

### Team 6 - back panel

- Input: back panel, HDMI neturik, barrel jack with soldered wires
- Output: back panel with stuff on it
- Steps: `attach_neutrik_connector_to_back_plate`, `remove_ring_from_barrel_jack`, `insert_pwr_cable_through_back_panel`, `insert_ring_on_barrel_jack`, `attach_terminal_to_pwr_cable`

### Team 7 - radxa holes

- Input: radxa x4
- Output: radxa x4 with larger holes
- Steps: `dilate_radxa_holes`

Requires a drill.

### Team 8 - boards prep

- Input: teensy, audiomixer, fuse, power board, radxa x4, radxa hat, thermal pad
- Output: prepared boards for installation
- Steps: `mount_fuse_on_pwr_brd`, `mount_teensy_on_audio_brd`, `prepare_thermal_pad`, `clean_radxa_cpu`, `stick_thermal_pad_on_radxa`, `place_radxa_hat_on_radxa_without_connecting`

### Team 9 - misc cleanup

- Input: display holders
- Output: cleaned display holders
- Steps: `remove_artifacts_from_display_holders`

### Team 10 - overall assembly on baseplate

- Input: a lot
- Output: assembled baseplate
- Steps: `clean_baseplate_thermal_area`, `mount_radxa_on_baseplate`, `mount_display_holders_on_baseplate`, `mount_hagibis_rear_on_baseplate`, `mount_hagibis_front_on_baseplate`, `mount_display_holders_on_baseplate`, `mount_sap_on_baseplate`, `place_display_hat_on_display_holders`, `place_display_on_display_hat`

### Team 11 - prep for cabling

- Input: baseplate with mounted boards, back panel, USB-3 USB-A cable, USB2 micro-USB to USB-A cable, radxa power cable, 6 MTA100 cables, ethernet cable
- Output: baseplate with cables on top

### Team 12 - cabling

- Input: baseplate and box with all boards, cables
- Output: cabled box
- Steps: `connect_pwr_cable_to_pwr_board`, `connect_radxa_to_pwr_board`, `connect_all_6_mta100_cables`, `connect_fans_to_pwr_brd`, `connect_micro_usb_cable`, `connect_hagibis_usb_cable`, `connect_ethernet_cable`, `attach_cables_to_baseplate`

### Team 13 - boxing

- Input: cabled baseplate, box, fans
- Output: completed unclosed box
- Steps: `attach_front_panel_to_audio_brd`, `slide_base_and_panels_into_box`, `attach_onlyfans_to_box`, `attach_base_to_box`, `stick_battery_to_baseplate`

### Team 14 - provisioning

- Input: open box
- Output: provisioned box
- Steps: `connect_box_to_power_and_network`, `verify_blue_smoke_still_inside`, `record_box_id_and_mac_address`, `click_both_bootsel_btns`, `attach_radxa_hat`, `run_provisioning_script`, `verify_status_on_display`

### Team 15 - finish

- Input: box
- Output: closed box
- Steps: `insert_3d_printed_aligners_into_box_slits`, `close_box`

