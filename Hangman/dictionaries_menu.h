#pragma once

#include "menu_section_with_single_callback.h"
#include "dictionaries_map.h"

#include "rect.h"

class DictionariesMenu : public MenuSectionWithSingleCallback
{
public:
    DictionariesMenu();
    DictionariesMenu(const DictionariesUmap& dictionaries);

    void print() const override;
    void setDictionaries(const DictionariesUmap& dictionaries);
    void clearSection() const override;

private: // methods
    void clearDescriptionRect() const;
    void printDescription() const;

private: // data
    static constexpr int                                  descriptionXOffset    = 22;
    static constexpr int                           descriptionYOffsetForText    = 3;
    std::vector<std::shared_ptr<game::Dictionary>> dictionaries;
    Rect                                           dictionaryDescriptionRect;
    ch::ConsoleColor                               descriptionForeground = ch::ConsoleColor::Black;
    ch::ConsoleColor                               descriptionBackground = ch::ConsoleColor::Gray;
};
