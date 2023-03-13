#pragma once

#include "rect.h"

class ConsoleSection
{
public:
    ConsoleSection() = default;
    ConsoleSection(const Rect& sectionRect);
    virtual ~ConsoleSection() = default;

    virtual void        handleKey(char c);
    virtual const Rect& rect() const;
    virtual void        print() const = 0;
    virtual void        clearSection() const;

protected:
    Rect sectionRect;
};
