#include "console_helpers.h"
#include "coord.h"

#include <Windows.h>

#include <cassert>
#include <limits>
#include <iostream>

#undef min
#undef max

namespace ch {

void setTextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setTextColor(ConsoleColor color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(color));
}

unsigned short currentConsoleColor()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
        return -1;
    return info.wAttributes;
}

void setBackgroundColor(ConsoleColor color)
{
    auto currentColor = currentConsoleColor();
    currentColor = (static_cast<unsigned short>(color) << 4) | (currentColor & 0x000f);
    setTextColor(currentColor);
}

void setBackgroundColor(int color)
{
    auto currentColor = currentConsoleColor();
    currentColor = (static_cast<unsigned short>(color) << 4) | (currentColor & 0x000f);
    setTextColor(currentColor);
}

void printAt(int x, int y, const std::string& text)
{
    setCursorPos(x, y);
    std::cout << text; 
}

void printAt(int x, int y, const std::string& text, char delimiter)
{
    auto currentY = y;
    ch::setCursorPos(x, y);
    bool      stop           = false;
    size_t delimiterIndex = 0;
    for (auto c : text) {
        if (c == delimiter) {
            ch::setCursorPos(x, ++currentY);
        } else {
            std::cout << c;
        }
    }
}

void setCursorPos(int x, int y)
{
    assert(x <= std::numeric_limits<short>::max() && x >= std::numeric_limits<short>::min());
    assert(y <= std::numeric_limits<short>::max() && y >= std::numeric_limits<short>::min());

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(x), static_cast<short>(y) });
}

void setCursorPos(Coord coord)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

Coord getCursorPosition()
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi)) {
        return cbsi.dwCursorPosition;
    } else {
        COORD invalid = { 0, 0 };
        return invalid;
    }
}

void clearRect(const Rect& rect)
{
    setBackgroundColor(ConsoleColor::Black);
    std::string emptyString(rect.width() + 1, ' ');
    for (size_t i = rect.y(); i <= rect.bottom(); ++i) {
        ch::setCursorPos(rect.x(), i);
        std::cout << emptyString;
    }
}

} // namespace ch