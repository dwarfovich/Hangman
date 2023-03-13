#pragma once

#include <cinttypes>

enum class OpenLetterResult : uint8_t
{
    AlreadyOpened,
    CorrectGuess,
    Mistake,
    NotInAlphabet,
    GameIsNotStartedYet
};