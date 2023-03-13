#pragma once

#include <inttypes.h>

enum class GameState : uint8_t
{
    WaitingForStart,
    InProgress,
    PlayerWon,
    PlayerLoosed
};