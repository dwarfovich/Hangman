#pragma once

#include <string>

namespace version {
inline constexpr int major = 0;
inline constexpr int minor = 7;
inline constexpr int build = 8;

inline const std::string versionString =
    'v' + std::to_string(major) + '.' + std::to_string(minor) + '.' + std::to_string(build);
}