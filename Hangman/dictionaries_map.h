#pragma once

#include "dictionary.h"

#include <memory>
#include <unordered_map>

using DictionariesUmap = std::unordered_map<std::string, std::shared_ptr<game::Dictionary>>;