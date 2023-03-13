#pragma once
#include "console_section.h"

class TopBarSection : public ConsoleSection
{
public:
    TopBarSection();

    void print() const override;
};
