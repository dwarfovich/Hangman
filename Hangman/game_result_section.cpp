#include "game_result_section.h"
#include "section_rects.h"
#include "console_helpers.h"

#include <iostream>

GameResultSection::GameResultSection() : ConsoleSection {sections_rects::gameResult}
{
}

void GameResultSection::print() const
{
    ch::setTextColor(ch::ConsoleColor::Aqua);
    ch::setBackgroundColor(ch::ConsoleColor::Black);
    ch::setCursorPos(sectionRect.x(), sectionRect.y());
    if (gameState == GameState::PlayerWon) {
        std::cout << std::string("Congrats! You guessed the word");
        ch::setCursorPos(sectionRect.x(), sectionRect.y() + 1);
        std::cout << word << std::string("!");
    } else if (gameState == GameState::PlayerLoosed) {
        std::cout << std::string("Oh, no! You loose.");
        ch::setCursorPos(sectionRect.x(), sectionRect.y() + 1);
        std::cout << std::string("The word was:");
        ch::setCursorPos(sectionRect.x(), sectionRect.y() + 2);
        std::cout << word;
    }

    ch::setCursorPos(sectionRect.x(), sectionRect.y() + 4);
    std::cout << std::string("Do you want to play again?");
}

void GameResultSection::setResult(const std::string& word_, GameState state)
{
    word = word_;
    gameState = state;
}
