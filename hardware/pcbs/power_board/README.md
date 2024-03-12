## power board

This is a PCB with the following features:
- Passthrough, filtering and fusing of 12V power from the PSU
- GPIO passthrough and level shifting for:
    - PWM fans
    - Buttons with LEDs (or just buttons, or just LEDs) - like [this one](https://eu.mouser.com/ProductDetail/Shin-Chin/R13-508BL-05-BRR12V?qs=gZXFycFWdAOqSBZAzEyqbA%3D%3D)
- A temperature sensor
- USB3 passthrough
- External USBs with isolated grounds for charging, designed to be able to power Sennheiser AVX receivers

Internal connections:
- 1x 12V input (2-pin screw terminal), connects to PSU's 12V output
- 3x 12V outputs (2-pin screw terminals), one of which powers an SBC like the [Radxa X2L](https://radxa.com/products/x/x2l/), the others are spare
- 2x 5V outputs (2-pin screw terminals), for misc purposes
- 1x USB3-micro-B port for USB3 passthrough
- 1x 3-pin I²C header that connects to the SBC's GPIO
- 4x 4-pin fan connectors with pwm
- 4x 4-pin connectors for buttons-with-LEDs or leds (VDD-LED-BTN-VDD)

Panel components:
- 1x optional 12V input barrel connector, in case we use an external PSU
- 1x USB3-A passthrough port
- 4x USB2-A charging connectors

