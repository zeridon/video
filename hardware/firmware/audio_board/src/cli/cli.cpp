#include "cli.h"

Cli::Cli(Stream* _port) : port(_port) {}

void Cli::exec_cmd() {
    if (this->hop_word("ping")) {
        this->port->printf("pong %s\n", this->cmd);
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

uint16_t Cli::parse_number() {
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
