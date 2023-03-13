#include "hangman.h"
#include "max_hangman_word_length.h"

#include <cassert>

namespace game {

    void Hangman::setAlphabet(const std::string& alphabet_)
{
    alphabet = alphabet_;
}

void Hangman::startGame(const std::string& word)
{
    targetWord = word;
    reset();
    gameState = GameState::InProgress;
}

void Hangman::reset()
{
    mistakesCount = 0;
    openedWord    = std::string ( targetWord.size(), details::closedLetter );
    openedLetters.clear();
}

OpenLetterResult Hangman::openLetter(Char letter)
{
    assert(!alphabet.empty());

    if (gameState != GameState::InProgress) {
        return OpenLetterResult::GameIsNotStartedYet;
    }
    
    letter           = std::toupper(letter);
    if (!isLetterInAlphabet(letter)) {
        return OpenLetterResult::NotInAlphabet;
    }
    if (letterAlreadyOpened(letter)) {
        return OpenLetterResult::AlreadyOpened;
    }

    openedLetters.push_back(letter);

    bool letterFound = false;
    for (size_t i = 0; i < targetWord.size(); ++i) {
        if ((openedWord[i] == details::closedLetter) && (targetWord[i] == letter)) {
            openedWord[i] = letter;
            letterFound   = true;
        }
    }

    if (letterFound) {
        if (targetWordGuessed()) {
            setGameState(GameState::PlayerWon);
        }
        return OpenLetterResult::CorrectGuess;
    } else {
        ++mistakesCount;
        if (maxMistakesCountReached()) {
            setGameState(GameState::PlayerLoosed);
        }
        return OpenLetterResult::Mistake;
    }
}

GameState Hangman::state() const
{
    return gameState;
}

void Hangman::setOnGameStateChangedCallback(const std::function<void(GameState)>& callback)
{
    onGameStateChangedCallback = callback;
}

const std::string& Hangman::word() const
{
    return targetWord;
}

size_t Hangman::mistakes() const
{
    return mistakesCount;
}

bool Hangman::letterAlreadyOpened(Char c) const
{
    return std::find(openedLetters.cbegin(), openedLetters.cend(), c) != openedLetters.cend();
}

bool Hangman::isLetterInAlphabet(Char letter) const
{
    return (alphabet.find(letter) != std::string::npos);
}

bool Hangman::targetWordGuessed() const
{
    return (openedWord.find(details::closedLetter) == std::string::npos);
}

bool Hangman::maxMistakesCountReached() const
{
    return mistakesCount >= maxMistakes;
}

void Hangman::setGameState(GameState newState)
{
    if (gameState != newState) {
        gameState = newState;
        if (onGameStateChangedCallback) {
            onGameStateChangedCallback(gameState);
        }
    }
}

} // namespace game