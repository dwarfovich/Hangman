#include "console_reader.h"

#include <conio.h>
#include <cassert>

void ConsoleReader::setOnKeyPressedCallback(const std::function<void(Char)>& callback)
{
    onKeyPressedCallback = callback;
}

void ConsoleReader::run()
{
    assert(onKeyPressedCallback);

    stopRequested = false;
    while (!stopRequested) {
        Char c = _getch();
        onKeyPressedCallback(c);
    }
}

void ConsoleReader::stop()
{
    stopRequested = true;
}
