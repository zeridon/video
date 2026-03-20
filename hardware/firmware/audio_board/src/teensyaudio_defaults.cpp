#define MIC (5.0f)

const PROGMEM float default_bus_volumes[BUSES] = {
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
};

const PROGMEM float default_channel_input_gains_db[CHANNELS] = {
    MIC,  MIC,  MIC, 1.0f, 1.0f, 1.0f
};
// see helpers/generate_mutes.py
const PROGMEM uint64_t default_mutes = 52361428992;

const PROGMEM uint16_t default_phantoms = 0;

const PROGMEM float default_matrix[CHANNELS][BUSES] = {
    // outputs: OUT1, OUT2, HP1, HP2, USB1, USB2
    // IN1
    {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
    // IN2
    {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
    // IN3
    {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
    // PC
    {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
    // USB1
    {1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
    // USB2
    {1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f}};
