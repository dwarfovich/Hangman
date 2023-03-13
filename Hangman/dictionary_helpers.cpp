#include "dictionary_helpers.h"
#include "string_utils.h"

#include <vector>
#include <string>
#include <algorithm>

namespace dictionary_helpers {

std::pair<std::string, std::string> parseInfoLine(const std::string& line)
{
    auto strings = string_utils::split(line, keyValueDelimiter);
    if (strings.size() != 2) {
        return {};
    }

    auto infoSignIndex = strings[0].find(infoLineSign);
    if (infoSignIndex != std::string::npos) {
        strings[0] = strings[0].substr(infoSignIndex + 1);
        if (strings[0].empty()) {
            return {};
        }
    }
    
    std::pair<std::string, std::string> result = { std::string(strings[0]), std::string(strings[1]) };
    string_utils::trim(result.first);
    string_utils::trim(result.second);

    return result;
}

bool isProperKeyValuePair(const std::pair<std::string, std::string>& keyValue)
{
    return (!keyValue.first.empty() && !keyValue.second.empty());
}

bool wordContainsOnlySymbolsFromAlphabet(const std::string& word, const std::string& alphabet)
{
    for (const auto& letter : word) {
        if (alphabet.find(letter) == std::string::npos) {
            return false;
        }
    }

    return true;
}

} // namespace dictionary_helpers