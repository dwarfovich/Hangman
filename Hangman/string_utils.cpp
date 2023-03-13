#include "string_utils.h"

#include <algorithm>

namespace string_utils {

std::string toUpper(const std::string& str)
{
    auto result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

Char toUpper(Char c)
{
    return std::toupper(c);
}

size_t findFirstNotWhiteSpace(const std::string& str)
{
    auto iter = std::find_if(str.cbegin(), str.cend(), [](char c) {
        return !::isspace(c);
    });

    return (iter == str.cend() ? std::string::npos : std::distance(iter, str.cbegin()));
}

std::vector<std::string_view> split(const std::string& str, char delimiter)
{
    std::vector<std::string_view> result;
    auto                          begin = 0;
    auto                          end   = str.find(delimiter);
    while (end != std::string::npos) {
        result.emplace_back(std::string_view { &str[begin], end - begin });
        begin = end + 1;
        end   = str.find(delimiter, begin);
    }
    result.emplace_back(std::string_view { &str[begin], str.size() - begin });

    return result;
}

void leftTrim(std::string& str)
{
    auto iter = std::find_if_not(str.cbegin(), str.cend(), [](char c) {
        return std::isspace(static_cast<unsigned char>(c));
    });
    str.erase(0, std::distance(str.cbegin(), iter));
}

void rightTrim(std::string& str)
{
    auto riter = std::find_if_not(str.crbegin(), str.crend(), [](char c) {
        return std::isspace(static_cast<unsigned char>(c));
    });

    auto firstIndexToErase = std::distance(riter, str.crend());
    str.erase(firstIndexToErase);
}

void trim(std::string& str)
{
    rightTrim(str);
    leftTrim(str);
}

} // namespace string_utils
