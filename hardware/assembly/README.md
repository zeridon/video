## Box assembly process

![assembly flowchart](assembly.svg)

Legend (colours to be removed after assembly on 2024-12-28):
- Green means already done before assembly
- Red means skip (will be done later or not at all)
- Yellow means optional (do only for some of the boxes)

### Before we begin

#### Dissassemble old box (`prepare_box`)
When salvaging a pre-2024 FOSDEM box, it should be fully disassembled.

The box should be fully disassembled using a 2mm HEX screwdriver.
The following parts should be salvaged for the new box:

- The lid and bottom
- The 3D-printed inserts that hold the box together
- The HDMI Neutrik connectors, together with their nuts and bolts
- The Hagibis capture card

Everything else can be discarded (not used for the new box).

#### Prepare a new box (`prepare_box`)
In case of using a brand new box ([G17081UBK](https://www.gainta.com/en/g17081ubk.html)), it should be prepared in the following way:

- Discard the unused parts
    - Only the top/bottom halves are used, everything else (front/back covers, planks) is discarded
- Drill the 4mm high screw holes with a 2.8mm drill bit
    - 2.8mm drill bits are very uncommon, make sure you have them available
    - It is best to use a tabletop drill press
    - Do not drill through the whole box, just drill about 3.5mm deep
- Drill through the supports on the bottom half
    - The lid and bottom of the box are identical and each have 4 support columns
    - The bottom supports should be drilled through with a 3mm drill, so that the box can be screwed together
- 3D-printed inserts ([case locks](https://github.com/FOSDEM/video/blob/master/hardware/brackets/case-lock.scad)) for the four corners should be made available

#### Disassemble enclosed Hagibis capture card (`disassemble_hagibis_if_needed`)
If the Hagibis capture card is inside its case, it should be disassembled:
- Remove bumpers on bottom together with any glue residue
- Remove the screws from under the bumper
- Pull on the bottom lid. If needed, insert a thin tool through one of the HDMI port holes and gently push the port downwards.
- Insert the thin tool into the gap between the lid and the case and open the box
- Salvage the board and discard the rest

Discarded parts should be kept in separate containers for further usage.

### Box assembly

#### Attach neutrik connector to back plate (`attach_neutrik_connector_to_back_plate`)
- Use the M3x10 bolts and respective nuts to attach the connector

#### Crimp fan connectors (`crimp_fan_connectors`)
- Cut the fan wires to about 70mm
- Hold the [connector](https://www.te.com/en/product-3-640443-3.html) in a vise with the wire slots pointing up. The vise should have a rubber grip. Do not tighten more than needed (the connector should not deform)
- The wire order is as follows (left to right, wires going into the connector from the point of view of the human outwards):
    1. Tach (Yellow)
    2. +5V (Red)
    3. GND (Black)
- If in doubt about the pin order, take a power board and consult the labels on the board
- Use the [MTA100 crimping tool](https://www.modellbahnunion.com/HO-gauge/Crimping-tool.htm?shop=modellbahn-union-en&a=article&ProdNr=Zimo-CRIMPTOOL&p=802) to crimp the individual wires
- It would be beneficial to hold multiple connectors in one vise grip and pipeline the crimping process

#### Cut power cable (`cut_pwr_cable`)
- Prepare 2x1.5mm² red-black low voltage copper cable
- Cut 260mm of cable

#### Strip ends of power cable (`strip_ends_of_pwr_cable`)
- Use a [wire stripping tool](https://www.knipex.com/products/wire-strippers-and-stripping-tools/knipex-precistrip16/knipex-precistrip16/1252195) to strip about 5mm on each side

#### Tin ends of power cable (`tin_ends_of_pwr_cable`)
- Hold the cable in a vise with the stripped ends pointing upwards or to the side
- Apply flux on wire
- Heat wire with soldering iron while gradually applying enough solder to fill the space between internal strands

#### Remove ring from barrel jack (`remove_ring_from_barrel_jack`)
I always forget to do this and then curse when I get to inserting the barrel jack into the panel.
This should be done before soldering because otherwise the thread might lock because of the heat.

#### Solder power cable to barrel jack (`solder_pwr_cable_to_barrel_jack`)
- Hold the [barrel jack](https://www.schurter.com/en/datasheet/4840.2200) in a vise
- Solder the wires to the pins in the following configuration:
    - The bigger plank is the (+) wire (red cable)
    - The pin opposite that plank is the (-)
    - The third pin is unused


#### Insert power cable through back panel (`insert_pwr_cable_through_back_panel`)
Do not forget to do this before attaching the terminal!

#### Insert ring on barrel jack (`insert_ring_on_barrel_jack`)
Do not forget to do this before attaching the terminal!

#### Attach terminal to power cable (`attach_terminal_to_pwr_cable`)
- Attach a [Plug-in terminal](https://store.comet.bg/Catalogue/Product/45028/) to the wires.
Looking at the terminal from the front (holes), the pin order is the following:
    - Left pin is +12V (red)
    - Right pin is GND (black)
- If in doubt about the pin order, take a power board and consult the labels on the board

#### Strip ends of radxa power cable (`strip_ends_of_radxa_pwr_cable`)
- The cables come with the ends stripped to about 2mm - they should instead be stripped to 5mm

#### Attach terminal to radxa power cable (`attach_terminal_to_radxa_pwr_cable`)
- **FIXME**: undocumented

#### Mount fuse on power brd (`mount_fuse_on_pwr_brd`)
- **FIXME**: undocumented

#### Mount teensy on audio brd (`mount_teensy_on_audio_brd`)
- **FIXME**: undocumented

#### Place display on display hat (`place_display_on_display_hat`)
- **FIXME**: undocumented

#### Prepare thermal pad (`prepare_thermal_pad`)
- **FIXME**: undocumented

#### Remove artifacts from display holders (`remove_artifacts_from_display_holders`)
- **FIXME**: undocumented

#### Connect micro hdmi cable (`connect_micro_hdmi_cable`)
- **FIXME**: undocumented

#### Dilate radxa holes (`dilate_radxa_holes`)
- Use a 3mm drill to drill through the holes on the Radxa X4
- Use a paintbrush/vacuum cleaner to remove dust

#### Clean radxa cpu (`clean_radxa_cpu`)
- Use a cotton swab and isopropyl alcohol to clean the CPU crystal

#### Clean baseplate thermal area (`clean_baseplate_thermal_area`)
- Use a cotton swab and isopropyl alcohol to clean the area where the CPU will contact the baseplate.
This is between the two rectangular cutouts under the Radxa X4.

#### Stick thermal pad on radxa (`stick_thermal_pad_on_radxa`)
- Cut an approx 18x20mm rectangle of 1.5mm thick thermal pad
- Remove protecting films from both sides
- Stick thermal pad onto CPU crystal

#### Mount radxa on baseplate (`mount_radxa_on_baseplate`)
- Without tightening, screw the Radxa board with M3x5 bolts and serrated washers to the baseplate
- Tighten diagonally

#### Mount display holders on baseplate (`mount_display_holders_on_baseplate`)
- Screw the display holders onto the baseplate with M3x5 bolts

#### Mount hagibis rear on baseplate (`mount_hagibis_rear_on_baseplate`)
- Use M4x5 bolts in the two rear holes of the Hagibis capture card. They might require some effort to screw in - this is fine.
- This must be done before bolting the front holes, since the rear holes use thicker bolts that guide the board orientation.

#### Mount hagibis front on baseplate (`mount_hagibis_front_on_baseplate`)
- Use M3x5 bolts and serrated washers

#### Mount switch, power and audio boards on baseplate (`mount_sap_on_baseplate`)
- Use M3x5 bolts and serrated washers to mount boards to the baseplate
- Tighten diagonally

#### Place display hat on display holders (`place_display_hat_on_display_holders`)
- The display hat PCB slides into the rear slit, while the display slides into the front slit
- The MTA100 connectors should be on top

#### Place radxa hat on radxa without connecting (`place_radxa_hat_on_radxa_without_connecting`)
- We will later have to click the bootsel button that is under the radxa hat, so
there's no need to plug the hat in now - just place it on top of the Radxa, so that the
cabling layout can be realistic.

#### Base assembled (`base_assembled`)
Preparation is now done, and we can begin cable management.

#### Connect power cable to power board (`connect_pwr_cable_to_pwr_board`)
- Insert the terminal into the right terminal (labeled "PWR IN").
- Do not swap the two terminals!

#### Connect radxa to power board (`connect_radxa_to_pwr_board`)
- Insert the terminal into the left terminal (labeled "PWR OUT").
- Do not swap the two terminals!

#### [Mark](https://github.com/markvdb) confusing MTA100 cables (`mark_duped_mta100_cables`):
- Use red paint (or nail polish) to mark the two end connectors of the following MTA100 cables:
    - The AudioBoard:DisplayHat cable (8pins, 225mm; the longer 8pin one)
    - The PowerBoard:Switch cable (2pins, 215mm; this is half of the 2pin cables)

#### [Mark](https://github.com/markvdb) confusing MTA100 connectors (`mark_duped_mta100_connectors`):
- Use red paint (or nail polish) to mark the two end connectors of the following MTA100 cables:
    - The 8-pin connector on the Audio Board
    - The 8-pin connector labeled "SIDE" on the Display Hat
    - The 2-pin connector on the Switch Board
    - The 2-pin connector on the Power Board labeled "+5V"

#### Connect all 6 mta100 cables (`connect_all_6_mta100_cables`)
- Connect The following cables:
    - RadxaHat:Switch, 6pin, 275mm
    - RadxaHat:DisplayHat, 8pin, 185mm
    - RadxaHat:PowerBoard, 4pin, 180mm
    - PowerBoard:Switch, marked red, 2pin, 215mm
    - PowerBoard:DisplayHat, 2pin, 215mm
    - AudioBoard:DisplayHat, marked red, 8pin, 225mm

#### Connect audio jack cable (`connect_audio_jack_cable`)
- **FIXME**: undocumented

#### Connect fans to power brd (`connect_fans_to_pwr_brd`)
- **FIXME**: undocumented

#### Connect micro usb cable (`connect_micro_usb_cable`)
- **FIXME**: undocumented

#### Connect ptru usb cable (`connect_ptru_usb_cable`)
- **FIXME**: undocumented

#### Connect hagibis usb cable (`connect_hagibis_usb_cable`)
- **FIXME**: undocumented

#### Connect ethernet cable (`connect_ethernet_cable`)
- **FIXME**: undocumented

#### Attach cables to baseplate (`attach_cables_to_baseplate`)
- **FIXME**: undocumented

#### Base wired (`base_wired`)
- **FIXME**: undocumented

#### Attach front panel to audio brd (`attach_front_panel_to_audio_brd`)
- **FIXME**: undocumented

#### Slide base and panels into box (`slide_base_and_panels_into_box`)
- **FIXME**: undocumented

#### Attach onlyfans to box (`attach_onlyfans_to_box`)
- **FIXME**: undocumented

#### Attach base to box (`attach_base_to_box`)
- **FIXME**: undocumented

#### Stick battery to baseplate (`stick_battery_to_baseplate`)
- **FIXME**: undocumented

#### Connect box to power and network (`connect_box_to_power_and_network`)
- **FIXME**: undocumented

#### Verify blue smoke still inside (`verify_blue_smoke_still_inside`)
- **FIXME**: undocumented

#### Record box id and MAC address (`record_box_id_and_mac_address`)
- Check DHCP for the mac address of the box
- Record it with its number in a file
- Label the box with its number

#### Click both bootsel btns (`click_both_bootsel_btns`)
- **FIXME**: undocumented

#### Attach radxa hat (`attach_radxa_hat`)
- **FIXME**: undocumented

#### Run provisioning script (`run_provisioning_script`)
- **FIXME**: undocumented

#### Verify status on display (`verify_status_on_display`)
- **FIXME**: undocumented

#### Insert 3D printed case locks into box slits (`insert_case_locks`)
- **FIXME**: undocumented

#### Close box (`close_box`)
- **FIXME**: undocumented

#### Screw box shut (`screw_box_shut`)
- **FIXME**: undocumented

#### Done (`done`)
