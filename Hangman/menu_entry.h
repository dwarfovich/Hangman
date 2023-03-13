#pragma once

#include "menu_entry_callback.h"

#include <string>
#include <functional>

struct MenuEntry
{
    std::string text;
    MenuEntryCallback callback;
};
