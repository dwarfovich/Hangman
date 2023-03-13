#pragma once

#include "console_helpers.h"
#include "console_section.h"
#include "menu_entry.h"

#include <vector>

namespace menu {
inline constexpr size_t invalidMenuEntryIndex = -1;
}

class MenuSection : public ConsoleSection
{
public:
    MenuSection() = default;
    MenuSection(const Rect& rect);

    virtual void handleKey(char c);
    virtual void executeCurrentEntry();

    void   setExitCallback(const std::function<void()>& callback);
    void   print() const override;
    void   addEntry(const MenuEntry& entry);
    size_t getCurrentEntry() const;
    void   selectEntry(size_t n);
    void   selectPreviousEntry();
    void   selectNextEntry();
    void   clearMenu();

private: // methods
    void recalculateParameters(const MenuEntry& newEntry);

protected: // data
    std::function<void(void)> exitCallback;
    std::vector<MenuEntry>    entries;
    size_t                    maxEntryTextLength = 20;
    size_t                    currentEntry       = menu::invalidMenuEntryIndex;
    ch::ConsoleColor          normalForeground   = ch::ConsoleColor::Yellow;
    ch::ConsoleColor          selectedForeground = ch::ConsoleColor::Red;
    ch::ConsoleColor          normalBackground   = ch::ConsoleColor::Black;
    ch::ConsoleColor          selectedBackground = ch::ConsoleColor::Yellow;
};
