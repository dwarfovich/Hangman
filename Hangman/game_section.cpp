#include "game_section.h"
#include "section_rects.h"

GameSection::GameSection() : ConsoleSection {sections_rects::game}
{
}

void GameSection::print() const
{
    hangmanSection.print();
}
