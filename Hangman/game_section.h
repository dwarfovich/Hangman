#pragma once

#include "console_section.h"
#include "hangman_section.h"

class GameSection : public ConsoleSection
{
public:
    GameSection();

    void print() const override;

    private:
    HangmanSection hangmanSection;
};
