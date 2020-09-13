#pragma once
#include <string_view>

class Color
{
public:
    enum Code {
        FG_WHITE = 97,
        FG_BLACK = 30,
        FG_RED = 31,
        FG_GREEN = 32,
        FG_BLUE = 34,
        FG_DEFAULT = 39,
        BG_WHITE = 107,
        BG_BLACK = 40,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_BLUE = 44,
        BG_DEFAULT = 49,
        BG_GRAY = 43,
    };

    // Generates ANSI character sequence given a color and a bold boolean
    static std::string ANSI(Code fg, Color::Code bg, bool bold);
    static std::string ANSI(Color::Code fg, Color::Code bg);
    static std::string end();

private:
    static constexpr char ansi_header_[]{ 0x1B,'[','\0' };
    static constexpr char ansi_reset_[]{ 0x1B,'[','0','m','\0' };
};


