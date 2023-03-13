#include "target_word_section.h"
#include "console_helpers.h"
#include "section_rects.h"
#include "string_utils.h"

#include <iostream>

TargetWordSection::TargetWordSection() : ConsoleSection {sections_rects::targetWord}
{
}

void TargetWordSection::print() const
{
    auto width = word.size() * 2 - 1;
    auto x     = sectionRect.x() + (sectionRect.width() - width) / 2;
    auto y     = sectionRect.y();
    ch::setCursorPos(x, sectionRect.y());
    ch::setTextColor(ch::ConsoleColor::Aqua);
    ch::setBackgroundColor(ch::ConsoleColor::Black);
    for (size_t i = 0; i < word.size(); ++i) {
        std::cout << details::closedChar;
        if (i < word.size() - 1) {
            std::cout << ' ';
        }
    }
}

void TargetWordSection::setWord(const std::string& word_)
{
    word = word_;
}

void TargetWordSection::printLetter(Char letter) const
{
    letter = string_utils::toUpper(letter);

    // TODO: move common to print() code into method.
    auto width = word.size() * 2 - 1;
    auto x     = sectionRect.x() + (sectionRect.width() - width) / 2;
    auto y     = sectionRect.y();
    ch::setCursorPos(x, sectionRect.y());
    ch::setTextColor(ch::ConsoleColor::Aqua);
    ch::setBackgroundColor(ch::ConsoleColor::Black);
    for (size_t i = 0; i < word.size(); ++i) {
        if (word[i] == letter) {
            std::cout << word[i];
        }
        if (i < word.size() - 1) {
            ++x;
        }
        ++x;
        ch::setCursorPos(x, sectionRect.y());
    }
}
