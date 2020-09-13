#pragma once
#include <string_view>

class Color
{
public:
    /* source: https://en.wikipedia.org/wiki/ANSI_escape_code */
    enum Code {
        FG_BLACK   = 30, BG_BLACK   = 40,
        FG_RED     = 31, BG_RED     = 41,
        FG_GREEN   = 32, BG_GREEN   = 42,
        FG_BLUE    = 34, BG_BLUE    = 44,
        FG_MAGENTA = 35, BG_MAGENTA = 45,
        FG_CYAN    = 36, BG_CYAN    = 46,
        FG_GRAY    = 90, BG_GRAY    = 100,
        FG_YELLOW  = 93, BG_YELLOW  = 103,
        FG_WHITE   = 97, BG_WHITE   = 107,
    };

    // Generates ANSI character sequence given a color and a bold boolean
    static std::string ANSI(Code fg, Color::Code bg, bool bold);
    static std::string ANSI(Color::Code fg, Color::Code bg);
    static std::string end();

private:
    static constexpr char ansi_header_[]{ 0x1B,'[','\0' };
    static constexpr char ansi_reset_[]{ 0x1B,'[','0','m','\0' };
};


