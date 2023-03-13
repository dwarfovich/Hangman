#include "selected_dictionary_section.h"
#include "section_rects.h"
#include "console_helpers.h"

#include "rect.h"

#include <iostream>

SelectedDictionarySection::SelectedDictionarySection() : ConsoleSection {sections_rects::selectedDictionary}
{
}

void SelectedDictionarySection::print() const
{   
    ch::setTextColor(ch::ConsoleColor::Aqua);
    ch::setBackgroundColor(ch::ConsoleColor::Black);
        ch::setCursorPos(sectionRect.x(), sectionRect.y());
    std::cout << "Selected dictionary: " << dictionaryName;
}

void SelectedDictionarySection::setDictionaryname(const std::string& name)
{
    dictionaryName = name;
    clearSection();
    print();
}

const std::string& SelectedDictionarySection::selectedDictionary() const
{
    return dictionaryName;
}
