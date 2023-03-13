#pragma once

#include "console_section.h"
#include "alphabet_section.h"
#include "target_word_section.h"
#include "console_helpers.h"

#include <functional>

class HangmanSection : public ConsoleSection
{
public:
    HangmanSection();

    void handleKey(char c) override;
    void print() const override;
    void clearSection() const override;

    void setTargetWord(const std::string& word);
    void setAlphabet(const std::string& alphabet);
    void setExitCallback(const std::function<void()>& callback);
    void markMistakeLetter(Char c);
    void markCorrectLetter(Char c);
    void printHangman(size_t mistakesCount) const;
    void printAlphabet() const;
    void printGallows() const;
    void printHead() const;
    void printEndHead() const;
    void printLeftHand() const;
    void printRightHand() const;
    void printBody() const;
    void printLeftLeg() const;
    void printRightLeg() const;

private: // data
    std::function<void()> exitCallback;
    AlphabetSection       alphabetSection;
    TargetWordSection      targetWordSection;
    const ch::ConsoleColor      hangmanColor = ch::ConsoleColor::LightYellow;
    const ch::ConsoleColor hangmanBackgroundColor = ch::ConsoleColor::Black;
};
