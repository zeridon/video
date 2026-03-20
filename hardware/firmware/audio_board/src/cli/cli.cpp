#include "cli.h"

#include "../config.h"
#include "../teensyaudio.h"
#include "../helpers.h"

Cli::Cli(Stream* _port) : port(_port) {}

void Cli::exec_cmd() {
    if (this->hop_word("ping")) {
        this->port->printf("pong %s\n", this->cmd);
        return;
    }
    if (this->hop_word("levels.db")) {
        Levels &levels = audio_get_levels();
        this->port->print("ok");
        for (uint8_t i = 0; i < CHANNELS + BUSES; i++) {
            this->port->print(" ");
            this->print_float_fixed(rmsToDb(levels.rms[i]), 3, 5);
            this->port->print(" ");
            this->print_float_fixed(rmsToDb(levels.peak[i]), 3, 5);
            this->port->print(" ");
            this->print_float_fixed(rmsToDb(levels.smooth[i]), 3, 5);
        }
        this->port->println();
        return;
    }
    if (this->hop_word("levels")) {
        Levels &levels = audio_get_levels();
        this->port->print("ok");
        for (uint8_t i = 0; i < CHANNELS + BUSES; i++) {
            this->port->print(" ");
            this->print_float_fixed(levels.rms[i], 3, 5);
            this->port->print(" ");
            this->print_float_fixed(levels.peak[i], 3, 5);
            this->port->print(" ");
            this->print_float_fixed(levels.smooth[i], 3, 5);
        }
        this->port->println();
        return;
    }
    if (this->hop_word("matrix")) {
        this->port->print("ok");
        for (uint8_t chan = 0; chan < CHANNELS; chan++) {
            for (uint8_t bus = 0; bus < BUSES; bus++) {
                if (is_muted(chan, bus)) {
                    this->port->print(" 0*");
                } else {
                    this->port->print(" 1*");
                }
                this->print_float_fixed(get_gain(chan, bus), 3, 3);
            }
        }
        this->port->println();
        return;
    }
    if (this->hop_word("gains")) {
        this->port->print("ok");
        for (uint8_t chan = 0; chan < CHANNELS; chan++) {
            this->port->print(" ");
            this->print_float_fixed(get_channel_multiplier(chan), 3, 3);
        }
        this->port->println();
        return;
    }
    if (this->hop_word("bus-levels")) {
        this->port->print("ok");
        for (uint8_t bus = 0; bus < BUSES; bus++) {
            this->port->print(" ");
            this->print_float_fixed(get_bus_multiplier(bus), 3, 3);
        }
        this->port->println();
        return;
    }
    if (this->hop_word("set-send")) {
        uint16_t chan = parse_uint();
        uint16_t bus = parse_uint();
        uint16_t want_send = parse_uint();
        if (chan >= CHANNELS) {
            this->port->printf("fail (chan %d is invalid)\n", chan);
            return;
        }
        if (bus >= BUSES) {
            this->port->printf("fail (bus %d is invalid)\n", bus);
            return;
        }
        if (want_send > 0) {
            unmute(chan, bus);
        } else {
            mute(chan, bus);
        }
        this->port->println("ok");
        return;
    }
    if (this->hop_word("set-fader")) {
        uint16_t chan = parse_uint();
        uint16_t bus = parse_uint();
        float vol = parse_float();

        if (chan >= CHANNELS) {
            this->port->printf("fail (chan %d is invalid)\n", chan);
            return;
        }
        if (bus >= BUSES) {
            this->port->printf("fail (bus %d is invalid)\n", bus);
            return;
        }
        if (vol < 0) {
            this->port->printf("fail (vol should not be negative)\n");
            return;
        }

        set_gain(chan, bus, vol);

        this->port->print("ok");
        return;
    }
    if (this->hop_word("set-gain")) {
        uint16_t chan = parse_uint();
        float vol = parse_float();

        if (chan >= CHANNELS) {
            this->port->printf("fail (chan %d is invalid)\n", chan);
            return;
        }
        if (vol < 0) {
            this->port->printf("fail (vol should not be negative)\n");
            return;
        }

        set_channel_multiplier(chan, vol);

        this->port->print("ok");
        return;
    }
    if (this->hop_word("set-bus-level")) {
        uint16_t bus = parse_uint();
        float vol = parse_float();

        if (bus >= BUSES) {
            this->port->printf("fail (bus %d is invalid)\n", bus);
            return;
        }
        if (vol < 0) {
            this->port->printf("fail (vol should not be negative)\n");
            return;
        }

        set_bus_multiplier(bus, vol);

        this->port->print("ok");
        return;
    }
    if (this->hop_word("factory-reset")) {
        audio_reset_default_state();
        audio_eeprom_save_all();
        this->port->println("ok");
        return;
    }
}

void Cli::print_float_fixed(float x, uint8_t whole_digits, uint8_t frac_digits) {
    char buf[whole_digits + frac_digits + 3];

    bool sign = x < 0;
    if (sign) {
        x = -x;
    }

    buf[0] = sign ? '-' : '+';

    if (x >= 10 * whole_digits) {
        buf[1] = 'i';
        buf[2] = 'n';
        buf[3] = 'f';
        buf[4] = '\0';
    } else {
        uint32_t whole = (uint32_t)x;
        float frac = x - whole;

        for (uint8_t i = whole_digits; i >= 1; i--) {
            buf[i] = '0' + (whole % 10);
            whole /= 10;
        }

        buf[whole_digits + 1] = '.';

        for (uint8_t i = 0; i < frac_digits; i++) {
            frac *= 10;
            buf[whole_digits + 2 + i] = '0' + (uint32_t)frac;
            frac -= (uint32_t)frac;
        }

        buf[frac_digits + whole_digits + 2] = '\0';
    }

    // FIXME: give this function to a year 1 uni student to make prettier
    if (sign) {
        this->port->print(buf);
    } else {
        this->port->print(buf + 1);
    }
}

bool Cli::is_terminator(char c) {
    return c == '\n' || c == '\r' || c == '\0';
}

bool Cli::is_terminator_or_whitespace(char c) {
    return is_terminator(c) || c == ' ' || c == '\t';
}

void Cli::skip_whitespace_in(char** buf) {
    while (**buf == ' ') {
        (*buf)++;
    }
}

void Cli::skip_whitespace() {
    skip_whitespace_in(&this->cmd);
}

uint16_t Cli::parse_uint() {
    skip_whitespace();
    uint16_t result = 0;
    while (*this->cmd >= '0' && *this->cmd <= '9') {
        result *= 10;
        result += (*this->cmd) - '0';
        this->cmd++;
    }

    if (*this->cmd == ' ') {
        this->cmd++;
    }
    return result;
}

float Cli::parse_float() {
    skip_whitespace();

    float sign = 1.0f;
    if (*this->cmd == '-') {
        sign = -1.0f;
        this->cmd++;
    } else if (*this->cmd == '+') {
        this->cmd++;
    }

    float result = 0.0f;
    while (*this->cmd >= '0' && *this->cmd <= '9') {
        result *= 10.0f;
        result += (*this->cmd) - '0';
        this->cmd++;
    }

    if (*this->cmd == '.') {
        this->cmd++;
        float place = 0.1f;
        while (*this->cmd >= '0' && *this->cmd <= '9') {
            result += ((*this->cmd) - '0') * place;
            place *= 0.1f;
            this->cmd++;
        }
    }

    if (*this->cmd == ' ') {
        this->cmd++;
    }

    return sign * result;
}

bool Cli::hop_word(const char* word) {
    char* buf = this->cmd;
    skip_whitespace_in(&buf);

    while (*word != 0 && !is_terminator_or_whitespace(*buf) && *buf == *word) {
        buf++;
        word++;
    }


    if (*word != '\0' || !is_terminator_or_whitespace(*buf)) {
        return false;
    }

    skip_whitespace_in(&buf);

    this->cmd = buf;
    return true;
}

void Cli::eat(char chr) {
    if (this->input_pos > sizeof(this->input_buf) - 2) {
        if (is_terminator(chr)) {
            this->input_pos = 0;
            this->input_buf[0] = '\0';
            this->port->write("fail line too long\n");
        }
        return;
    }
    this->input_buf[this->input_pos] = chr;
    if (!is_terminator(chr)) {
        this->input_pos++;
        return;
    }
    this->input_buf[this->input_pos] = '\0';
    this->input_pos = 0;
    if (this->input_buf[0] == '\0') {
        return; // empty line
    }

    this->cmd = &this->input_buf[0];

    exec_cmd();
}

void Cli::update() {
    while (this->port->available()) {
        int c = this->port->read();
        if (c > 0) {
            this->eat((char)c);
        }
    }
}
