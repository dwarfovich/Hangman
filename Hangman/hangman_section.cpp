#include "hangman_section.h"
#include "section_rects.h"
#include "ascii_art.h"
#include "key_codes.h"
#include "hangman_draw_controller.h"

#include <iostream>

HangmanSection::HangmanSection() : ConsoleSection {sections_rects::hangman}
{
}

void HangmanSection::handleKey(char c)
{
    if (c == key_codes::escape) {
        if (exitCallback) {
            exitCallback();
        }
    } 
}

void HangmanSection::print() const
{
    printGallows();
    printAlphabet();
    targetWordSection.print();
}

void HangmanSection::clearSection() const
{
    ch::clearRect(sectionRect);
    alphabetSection.clearSection();
    targetWordSection.clearSection();
}

void HangmanSection::setTargetWord(const std::string& word)
{
    targetWordSection.setWord(word);
    targetWordSection.clearSection();
}

void HangmanSection::setAlphabet(const std::string& alphabet)
{
    alphabetSection.setAlphabet(alphabet);
}

void HangmanSection::printHangman(size_t mistakesCount) const
{
    game::drawHangman(mistakesCount, *this);
}

void HangmanSection::printAlphabet() const
{
    alphabetSection.print();
}

void HangmanSection::setExitCallback(const std::function<void()>& callback)
{
    exitCallback = callback;
}

void HangmanSection::markMistakeLetter(Char c)
{
    alphabetSection.markMistakeLetter(c);
}

void HangmanSection::markCorrectLetter(Char c)
{
    alphabetSection.markCorrectLetter(c);
    targetWordSection.printLetter(c);
}

void HangmanSection::printGallows() const
{
    ch::printAt(sectionRect.x(), sectionRect.y(), art::gallows, '\n');
}

void HangmanSection::printHead() const
{
    ch::setTextColor(hangmanColor);
    ch::setBackgroundColor(hangmanBackgroundColor);
    ch::printAt(sectionRect.x() + art::headXOffset, sectionRect.y() + art::headYOffset, art::head, '\n');
}

void HangmanSection::printEndHead() const
{
    ch::setTextColor(hangmanColor);
    ch::setBackgroundColor(hangmanBackgroundColor);
    ch::printAt(sectionRect.x() + art::headXOffset, sectionRect.y() + art::headYOffset, art::head, '\n');
}

void HangmanSection::printLeftHand() const
{
    ch::setTextColor(hangmanColor);
    ch::setBackgroundColor(hangmanBackgroundColor);
    ch::printAt(sectionRect.x() + art::leftHandXOffset, sectionRect.y() + art::leftHandYOffset, art::leftHand, '\n');
}

void HangmanSection::printRightHand() const
{
    ch::setTextColor(hangmanColor);
    ch::setBackgroundColor(hangmanBackgroundColor);
    ch::printAt(sectionRect.x() + art::rightHandXOffset, sectionRect.y() + art::rightHandYOffset, art::rightHand, '\n');
}

void HangmanSection::printBody() const
{
    ch::setTextColor(hangmanColor);
    ch::setBackgroundColor(hangmanBackgroundColor);
    ch::printAt(sectionRect.x() + art::bodyXOffset, sectionRect.y() + art::bodyYOffset, art::body, '\n');
}

void HangmanSection::printLeftLeg() const
{
    ch::setTextColor(hangmanColor);
    ch::setBackgroundColor(hangmanBackgroundColor);
    ch::printAt(sectionRect.x() + art::leftLegXOffset, sectionRect.y() + art::leftLegYOffset, art::leftLeg, '\n');
}

void HangmanSection::printRightLeg() const
{
    ch::setTextColor(hangmanColor);
    ch::setBackgroundColor(hangmanBackgroundColor);
    ch::printAt(sectionRect.x() + art::rightLegXOffset, sectionRect.y() + art::rightLegYOffset, art::rightLeg, '\n');
}
