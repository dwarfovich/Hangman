#include "dictionary.h"
#include "dictionary_helpers.h"
#include "string_utils.h"

#include <istream>

#include <QRandomGenerator>
#include <QTextStream>

namespace game {

std::string Dictionary::getRandomWord(size_t length) const
{
    WordMapping::const_iterator mapIter;
    if (length) {
        mapIter = wordMapping.find(length);
    } else {
        mapIter = wordMapping.cbegin();
        std::advance(mapIter, QRandomGenerator::global()->bounded(size_t(0), (size_t)wordMapping.size()));
    }

    if (mapIter == wordMapping.cend()) {
        return {};
    }

    const auto& wordsCount = mapIter->second.size();
    if (wordsCount == 0) {
        return {};
    }

    return mapIter->second[QRandomGenerator::global()->bounded(size_t(0), wordsCount)];
}

size_t Dictionary::wordsCount() const
{
    return size;
}

bool Dictionary::load(std::istream& stream)
{
    clear();

    size_t lineNumber = loadInfo(stream);

    if (languageAlphabet.empty()) {
        dictionaryErrors.push_back("Cann't find alphabet");
        return false;
    }

    loadWords(stream, lineNumber);

    return dictionaryErrors.empty();
}

const std::string& Dictionary::name() const
{
    return dictionaryName;
}

const std::string& Dictionary::description() const
{
    return dictionaryDescription;
}

const std::string& Dictionary::alphabet() const
{
    return languageAlphabet;
}

const std::vector<std::string>& Dictionary::errors() const
{
    return dictionaryErrors;
}

void Dictionary::clear()
{
    size = 0;
    wordMapping.clear();
    dictionaryName.clear();
    dictionaryDescription.clear();
    languageAlphabet.clear();
    dictionaryErrors.clear();
}

bool Dictionary::addWord(const std::string& word)
{
    auto upperCaseWord = string_utils::toUpper(word);
    if (isCorrectWord(upperCaseWord)) {
        wordMapping[upperCaseWord.size()].push_back(upperCaseWord);
        ++size;
        return true;
    } else {
        return false;
    }
}

void Dictionary::addInfo(const std::pair<std::string, std::string>& keyValue)
{
    if (keyValue.first == details::nameKey) {
        dictionaryName = keyValue.second;
    } else if (keyValue.first == details::descriptionKey) {
        dictionaryDescription = keyValue.second;
    } else if (keyValue.first == details::alphabetKey) {
        languageAlphabet = string_utils::toUpper(keyValue.second);
        std::sort(languageAlphabet.begin(), languageAlphabet.end());
    } else {
        dictionaryErrors.push_back("Unknown info key: " + keyValue.first);
    }
}

bool Dictionary::isCorrectWord(const std::string& word)
{
    return dictionary_helpers::wordContainsOnlySymbolsFromAlphabet(word, languageAlphabet);
}

size_t Dictionary::loadInfo(std::istream& stream)
{
    size_t lineNumber = 0;
    while (lineNumber < details::infoLines && stream.peek() != EOF) {
        std::string infoLine;
        std::getline(stream, infoLine);
        if (!infoLine.empty()) {
            auto keyValuePair = dictionary_helpers::parseInfoLine(infoLine);
            if (dictionary_helpers::isProperKeyValuePair(keyValuePair)) {
                addInfo(keyValuePair);
            }
        }
        ++lineNumber;
    }

    return lineNumber;
}

void Dictionary::loadWords(std::istream& stream, size_t lineNumber)
{
    while (lineNumber < details::maxDictionaryLines && stream.peek() != EOF) {
        std::string word;
        std::getline(stream, word);
        if (!addWord(word)) {
            dictionaryErrors.push_back("Incorrect word: " + word + ", (line " + std::to_string(lineNumber) + ")");
        }
        ++lineNumber;
    }
}

std::istream& operator>>(std::istream& stream, game::Dictionary& dictionary)
{
    dictionary.load(stream);
    
    return stream;
}

} // namespace game
