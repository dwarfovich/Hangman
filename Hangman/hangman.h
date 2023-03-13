#pragma once

#include "char.h"
#include "open_letter_result.h"
#include "game_state.h"

#include <string>
#include <functional>

namespace game {

namespace details {
inline constexpr Char closedLetter = '#';

} // namespace details

class Hangman
{
public:
    void             setAlphabet(const std::string& alphabet);
    void             startGame(const std::string& word);
    void             reset();
    OpenLetterResult openLetter(Char letter);
    size_t           mistakes() const;
    GameState        state() const;
    void             setOnGameStateChangedCallback(const std::function<void(GameState)>& callback);
    const std::string&  word() const;

private: // methods
    bool letterAlreadyOpened(Char c) const;
    bool isLetterInAlphabet(Char letter) const;
    bool targetWordGuessed() const;
    bool maxMistakesCountReached() const;
    void setGameState(GameState newState);

private: // data
    GameState gameState = GameState::WaitingForStart;
    std::function<void(GameState)> onGameStateChangedCallback;
    size_t    mistakesCount = 0;
    size_t    maxMistakes   = 6;
    std::string   targetWord;
    std::string   openedWord;
    std::string   alphabet;
    std::string   openedLetters;
};

} // namespace game