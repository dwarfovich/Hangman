#include "dictionaries_menu.h"
#include "dictionary_restrictions.h"
#include "section_rects.h"

#include <iostream>

DictionariesMenu::DictionariesMenu()
    : MenuSectionWithSingleCallback { sections_rects::dictionariesMenuRect }
    , dictionaryDescriptionRect { sections_rects::description }
{
}

DictionariesMenu::DictionariesMenu(const DictionariesUmap& dictionaries)
    : MenuSectionWithSingleCallback { sections_rects::dictionariesMenuRect }
    , dictionaryDescriptionRect { sections_rects::description }
{
    setDictionaries(dictionaries);
}

void DictionariesMenu::print() const
{
    MenuSection::print();
    printDescription();
}

void DictionariesMenu::setDictionaries(const DictionariesUmap& dictionaries_)
{
    clearMenu();
    for (const auto& dictionary : dictionaries_) {
        MenuEntry entry;
        entry.text = dictionary.first;
        addEntry(std::move(entry));
        dictionaries.push_back(dictionary.second);
    }

    addEntry({ "Exit", [this](size_t index) {
                  this->exitCallback();
              } });
}

void DictionariesMenu::clearSection() const
{
    ConsoleSection::clearSection();
    clearDescriptionRect();
}

void DictionariesMenu::clearDescriptionRect() const
{
    ch::setBackgroundColor(ch::ConsoleColor::LightAqua);
    ch::clearRect(dictionaryDescriptionRect);
}

void DictionariesMenu::printDescription() const
{
    if (currentEntry == menu::invalidMenuEntryIndex) {
        return;
    }
    clearDescriptionRect();
    if (currentEntry >= entries.size() - 1) {
        return;
    }

    ch::setTextColor(descriptionForeground);
    ch::setBackgroundColor(descriptionBackground);
    ch::setCursorPos(descriptionXOffset, dictionaryDescriptionRect.y());
    std::cout << "Dictionary description:";
    ch::setCursorPos(descriptionXOffset, dictionaryDescriptionRect.y() + 1);
    std::cout << "Words: " + std::to_string(dictionaries[currentEntry]->wordsCount());

    const size_t maxLettersPerLine = dictionaryDescriptionRect.width();
    const auto&  text              = dictionaries[currentEntry]->description();
    size_t       currentIndex      = 0;
    for (size_t line = dictionaryDescriptionRect.y() + descriptionYOffsetForText;
         line < dictionaryDescriptionRect.height() && currentIndex < text.size();
         ++line) {
        ch::setCursorPos(descriptionXOffset, line);
        size_t currentLetter = 0;
        while (currentLetter < maxLettersPerLine && currentIndex < text.size()) {
            std::cout << text[currentIndex];
            ++currentIndex;
            ++currentLetter;
        }
    }
}
