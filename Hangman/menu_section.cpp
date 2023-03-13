#include "menu_section.h"
#include "console_helpers.h"
#include "key_codes.h"

#include <iostream>

void MenuSection::print() const
{
    const size_t firstLine = (entries.size() >= rect().height() ? 0 : sectionRect.y());
    size_t       x         = sectionRect.x();
    for (size_t line = firstLine; line < firstLine + entries.size(); ++line) {
        if (line - firstLine == currentEntry) {
            ch::setTextColor(selectedForeground);
            ch::setBackgroundColor(selectedBackground);
        } else {
            ch::setTextColor(normalForeground);
            ch::setBackgroundColor(normalBackground);
        }
        ch::setCursorPos(x, line);
        std::cout << entries[line - firstLine].text << '\n';
    }
}

void MenuSection::addEntry(const MenuEntry& entry)
{
    try {
        entries.push_back(entry);
        recalculateParameters(entry);
        if (currentEntry == menu::invalidMenuEntryIndex) {
            currentEntry = 0;
        }
    } catch (const std::exception&) {
    }
}

size_t MenuSection::getCurrentEntry() const
{
    return currentEntry;
}

void MenuSection::selectEntry(size_t n)
{
    print();
}

void MenuSection::selectNextEntry()
{
    if (currentEntry >= entries.size() - 1) {
        currentEntry = 0;
    } else {
        currentEntry++;
    }
    selectEntry(currentEntry);
}

void MenuSection::clearMenu()
{
    entries.clear();

}

void MenuSection::selectPreviousEntry()
{
    if (currentEntry == 0) {
        currentEntry = entries.size() - 1;
    } else {
        currentEntry--;
    }
    selectEntry(currentEntry);
}

void MenuSection::executeCurrentEntry()
{
    if (entries[currentEntry].callback) {
        entries[currentEntry].callback(currentEntry);
    }
}

void MenuSection::setExitCallback(const std::function<void(void)>& callback)
{
    exitCallback = callback;
}

MenuSection::MenuSection(const Rect& rect) : ConsoleSection {rect}
{
}

void MenuSection::handleKey(char c)
{
    if (c == key_codes::arrowUp) {
        selectPreviousEntry();
    } else if (c == key_codes::arrowDown) {
        selectNextEntry();
    } else if (c == key_codes::enter) {
        executeCurrentEntry();
    } else if (c == key_codes::escape) {
        if (exitCallback) {
            exitCallback();
        }
    }
}

void MenuSection::recalculateParameters(const MenuEntry& newEntry)
{
    if (newEntry.text.size() > maxEntryTextLength) {
        maxEntryTextLength = newEntry.text.size();
    }
}
