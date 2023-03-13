#include "alphabet_section.h"
#include "section_rects.h"
#include "console_helpers.h"
#include "string_utils.h"

#include <iostream>

AlphabetSection::AlphabetSection() : ConsoleSection { sections_rects::alphabet }
{
}

void AlphabetSection::setAlphabet(const std::string& newAlphabet)
{
    alphabet = newAlphabet;
}

void AlphabetSection::print() const
{
    ch::setCursorPos(sectionRect.x(), sectionRect.y());

    lettersCoords.clear();
    auto   sectionWidth = sectionRect.width();
    auto   y            = sectionRect.y();
    auto   begin        = alphabet.cbegin();
    size_t currentIndex = 0;
    while (true) {
        Coord coords;
        if ((alphabet.size() - currentIndex) * 2 > sectionWidth) {
            coords = { short(sectionRect.x()), short(y) };
        } else {
            size_t restLength = 2 * (alphabet.size() - currentIndex) - 1;
            coords = { short(sectionRect.x() + (sectionRect.width() - restLength) / 2 - (sectionWidth & 1)), short(y) };
        }
        ch::setCursorPos(coords);
        int c = 0;
        for (size_t i = currentIndex; i < currentIndex + (sectionWidth / 2) && i < alphabet.size(); ++i, ++c) {
            std::cout << alphabet[i] << ' ';
            if (i != currentIndex) {
                coords.X += 2;
            }
            lettersCoords.push_back({ coords.X, coords.Y });
        }
        currentIndex += c;
        if (currentIndex >= alphabet.size()) {
            break;
        }
        ++y;
    }
}

void AlphabetSection::markMistakeLetter(Char c)
{
    c                  = string_utils::toUpper(c);
    const auto& coords = findLetterCoords(c);
    ch::setTextColor(ch::ConsoleColor::Black);
    ch::setBackgroundColor(ch::ConsoleColor::LightRed);
    ch::setCursorPos(coords);
    std::cout << c;
}

void AlphabetSection::markCorrectLetter(Char c)
{
    c                  = string_utils::toUpper(c);
    const auto& coords = findLetterCoords(c);
    ch::setTextColor(ch::ConsoleColor::Black);
    ch::setBackgroundColor(ch::ConsoleColor::LightGreen);
    ch::setCursorPos(coords);
    std::cout << c;
}

Coord AlphabetSection::findLetterCoords(Char c)
{
    auto iter = std::find(alphabet.cbegin(), alphabet.cend(), c);
    if (iter == alphabet.cend()) {
        return { -1, -1 };
    }
    auto index = std::distance(alphabet.cbegin(), iter);
    return lettersCoords[index];
}
