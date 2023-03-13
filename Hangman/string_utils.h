#pragma once

#include "char.h"

#include <string>
#include <vector>

namespace string_utils {

std::string toUpper(const std::string& str);
Char        toUpper(Char c);
size_t      findFirstNotWhiteSpace(const std::string& str);
std::vector<std::string_view> split(const std::string& str, char delimiter);
void                          leftTrim(std::string& str);
void                          rightTrim(std::string& str);
void                          trim(std::string& str);

} // namespace string_utils
