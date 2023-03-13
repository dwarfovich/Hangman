#pragma once

#include "console_section.h"

#include <string>

class SelectedDictionarySection : public ConsoleSection
{
public:
    SelectedDictionarySection();

    void print() const override;
    void setDictionaryname(const std::string& name);
    const std::string& selectedDictionary() const;
    private:
    std::string dictionaryName;
};
