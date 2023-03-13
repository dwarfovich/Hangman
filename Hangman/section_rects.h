#pragma once

#include "dictionary_restrictions.h"
#include "rect.h"

namespace sections_rects {

inline constexpr Rect game               = { 0, 1, 50, 30 };
inline constexpr Rect hangman            = { 0, 2, 20, 30 };
inline constexpr Rect selectedDictionary = { 20, 0, 20, 1 };
inline constexpr Rect alphabet           = { 30, 5, 15, 15 };
inline constexpr Rect targetWord         = { 5, 17, 40, 1 };
inline constexpr Rect gameOverMenu       = { 15, 10, 20, 3 };
inline constexpr Rect gameResult         = { 10, 2, 30, 5 };
inline constexpr Rect        dictionariesMenuRect = { 0, 1, dictionary_restrictions::maxNameLength, 5 };
inline constexpr Rect        description      = { 21, 2, 80 - 21 - 1, 10 };

} // namespace sections_rects