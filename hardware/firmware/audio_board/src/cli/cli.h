#include <Arduino.h>

class Cli {
    public:
        Cli(Stream*);
        void update();
    private:
        Stream* port;

        char input_buf[100];
        uint8_t input_pos = 0;

        void exec_cmd();
        bool is_terminator(char c);
        bool is_terminator_or_whitespace(char c);
        void skip_whitespace_in(char** buf);
        void skip_whitespace();
        uint16_t parse_number();
        bool hop_word(const char* word);
        void eat(char chr);

        // state used only during exec_cmd():
        char* cmd;
};
