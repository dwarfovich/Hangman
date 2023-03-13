#pragma once

#include "char.h"
#include "console_section.h"

#include <string>

namespace details {
// TODO: move into some namespace.
inline constexpr Char closedChar = '_';
} // namespace details

class TargetWordSection : public ConsoleSection
{
public:
    TargetWordSection();

    void print() const override;
    void setWord(const std::string& word);
    void printLetter(Char letter) const;

private:
    std::string word;
};