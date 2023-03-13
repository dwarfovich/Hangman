#include "top_bar_section.h"
#include "console_helpers.h"
#include "version.h"
#include "section_rects.h"

#include <iostream>

TopBarSection::TopBarSection() : ConsoleSection { { 0, 0, sections_rects::game.width(), 1 } }
{
}

void TopBarSection::print() const
{
    ch::setCursorPos(rect().x(), rect().y());
    ch::setTextColor(ch::ConsoleColor::LightBlue);
    std::cout << std::string("Hangman ") << version::versionString;
}
