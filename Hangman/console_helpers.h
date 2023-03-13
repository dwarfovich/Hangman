#pragma once

#include "coord.h"
#include "rect.h"

#include <string>
#include <cinttypes>

namespace ch {
// Windows console color codes
// 0 = Black
// 1 = Blue
// 2 = Green
// 3 = Aqua
// 4 = Red
// 5 = Purple
// 6 = Yellow
// 7 = White
// 8 = Gray
// 9 = Light Blue
// 10/a = Light Green
// 11/b = Light Aqua
// 12/c = Light Red
// 13/d = Light Purple
// 14/e = Light Yellow
// 15/f = Bright White

enum class ConsoleColor : uint8_t
{
    Black,
    Blue,
    Green,
    Aqua,
    Red,
    Purple,
    Yellow,
    White,
    Gray,
    LightBlue,
    LightGreen,
    LightAqua,
    LightRed,
    LightPurple,
    LightYellow,
    BrightWhite
};

void           setTextColor(int color);
void           setTextColor(ConsoleColor color);
void           setBackgroundColor(ConsoleColor color);
void           setBackgroundColor(int color);
unsigned short currentConsoleColor();
void           setCursorPos(int x, int y);
void           setCursorPos(Coord coord);
Coord   getCursorPosition();
void           clearRect(const Rect& rect);
void           printAt(int x, int y, const std::string& text);
void           printAt(int x, int y, const std::string& text, char separator);
} // namespace ch