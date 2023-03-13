#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace game {

namespace details {
    // TODO: move to dictionary_restrictions.h
inline constexpr size_t maxWordsCountForLength  = 10'000;
inline constexpr size_t maxDictionaryLines      = 100'000;
inline constexpr size_t infoLines            = 3;
inline constexpr size_t     maxLineLength           = 2'000;
inline const std::string    nameKey                 = "name";
inline const std::string    descriptionKey          = "description";
inline const std::string    alphabetKey             = "alphabet";
} // namespace details

class Dictionary
{
public:
    friend std::istream& operator>>(std::istream& stream, game::Dictionary& dictionary);

    std::string                     getRandomWord(size_t length = 0) const;
    size_t                      wordsCount() const;
    bool                            load(std::istream& stream);
    const std::string&              name() const;
    const std::string&              description() const;
    const std::string&              alphabet() const;
    const std::vector<std::string>& errors() const;
    void                        clear();
    bool                        addWord(const std::string& word);

private: // methods
    void   addInfo(const std::pair<std::string, std::string>& keyvalue);
    bool   isCorrectWord(const std::string& word);
    size_t loadInfo(std::istream& stream);
    void   loadWords(std::istream& stream, size_t lineNumber);

private: // data
    using WordMapping = std::unordered_map<size_t, std::vector<std::string>>;
    WordMapping          wordMapping;
    size_t               size = 0;
    std::string              dictionaryName;
    std::string              dictionaryDescription;
    std::string              languageAlphabet;
    std::vector<std::string> dictionaryErrors;
};

} // namespace game
