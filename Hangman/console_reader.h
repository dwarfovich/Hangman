#pragma once

#include "char.h"

#include <functional>

class ConsoleReader
{
public:
    void setOnKeyPressedCallback(const std::function<void(Char)>& callback);
    void run();
    void stop();

private:
    std::function<void(Char)> onKeyPressedCallback;
    bool stopRequested = false;
};
