#pragma once
#include "char.h"

#include <string>
 
namespace dictionary_helpers
{
inline constexpr Char      infoLineSign = '$';
inline constexpr Char keyValueDelimiter = '=';
inline const std::string whitespaces  = " \t\n\r";
inline const std::string        dictionariesFolder = "Dictionaries";

std::pair<std::string, std::string> parseInfoLine(const std::string& line);
bool                        isProperKeyValuePair(const std::pair<std::string, std::string>& keyValue);
bool                        wordContainsOnlySymbolsFromAlphabet(const std::string& word, const std::string& alphabet);
}