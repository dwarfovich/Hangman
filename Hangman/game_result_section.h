#pragma once

#include "console_section.h"
#include "game_state.h"

#include <string>

class GameResultSection : public ConsoleSection
{
public:
    GameResultSection();

    void print() const override;

    void setResult(const std::string& word, GameState state);

private:
    std::string   word;
    GameState gameState;
};
