#include "Color.h"
#include <string>

// Generates ANSI character sequence given a color and a bold boolean
std::string Color::ANSI(Color::Code fg, Color::Code bg, bool bold) {
    const char* format_attribute = bold ? "2" : "0";

    std::string sequence = std::string(ansi_header_) + format_attribute + ";" + std::to_string(fg) + ";" + std::to_string(bg) + "m";
    return sequence;
}

// Generates ANSI character sequence given a color, always non-bold
std::string Color::ANSI(Color::Code fg, Color::Code bg) {
    return Color::ANSI(fg, bg, false);
}

// Returns ANSI RESET character sequence
std::string Color::end() {
    return std::string(ansi_reset_);
}