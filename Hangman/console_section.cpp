#include "console_section.h"
#include "console_helpers.h"

ConsoleSection::ConsoleSection(const Rect& sectionRect_) : sectionRect {sectionRect_}
{
}

void ConsoleSection::handleKey(char c)
{
}

const Rect& ConsoleSection::rect() const
{
    return sectionRect;
}

void ConsoleSection::clearSection() const
{
    ch::clearRect(sectionRect);
}
