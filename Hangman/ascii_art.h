#pragma once

#include <string>

namespace art {

inline constexpr size_t headXOffset = 14;
inline constexpr size_t  headYOffset = 2;
inline constexpr size_t leftHandXOffset = 13;
inline constexpr size_t  leftHandYOffset = 5;
inline constexpr size_t  rightHandXOffset = 17;
inline constexpr size_t  rightHandYOffset = 5;
inline constexpr size_t  bodyXOffset = 16;
inline constexpr size_t  bodyYOffset = 5;
inline constexpr size_t  leftLegXOffset  = 13;
inline constexpr size_t  leftLegYOffset  = 8;
inline constexpr size_t  rightLegXOffset = 17;
inline constexpr size_t  rightLegYOffset = 8;

inline const std::string gallows = "    _____________\n"
                               "    |           |\n"
                               "    |\n"
                               "    |\n"
                               "    |\n"
                               "    |\n"
                               "    |\n"
                               "    |\n"
                               "    |\n"
                               "   /|\\\n"
                               "  / | \\\n"
                               " /  |  \\\n"
                               "==========";

inline const std::string head = " /~\\\n"
                            "(o o)\n"
                            " \\=/\n";

inline const std::string endHead = " /~\\\n"
                               "(x x)\n"
                               " \\=/\n";

inline const std::string body = "|\n"
                            "|\n"
                            "|\n";

inline const std::string leftHand = "  /\n"
                                " /\n"
                                "/\n";

inline const std::string rightHand = "\\\n"
                                 " \\\n"
                                 "  \\\n";

inline const std::string leftLeg = "  /\n"
                               " /\n"
                               "/\n";

inline const std::string rightLeg = "\\\n"
                                " \\\n"
                                "  \\\n";

} // namespace art