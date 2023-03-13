#pragma once

#include "console_section.h"
#include "coord.h"
#include "char.h"

#include <vector>
#include <string>

class AlphabetSection : public ConsoleSection
{
public:
    AlphabetSection();

    void setAlphabet(const std::string& newAlphabet);
    void print() const override;

    void markMistakeLetter(Char c);
    void markCorrectLetter(Char c);

    private: // methods
    Coord findLetterCoords(Char c);

    private: // data
    std::string alphabet;
    mutable    std::vector<Coord> lettersCoords;
};
