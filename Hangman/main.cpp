#include "console_helpers.h"
#include "dictionary.h"
#include "dictionary_helpers.h"
#include "dictionaries_map.h"
#include "top_bar_section.h"
#include "main_menu_section.h"
#include "dictionaries_menu.h"
#include "console_reader.h"
#include "game_controller.h"
#include "rect.h"

#include <Windows.h>

#include <filesystem>
#include <fstream>
#include <iostream>

std::pair<DictionariesUmap, std::vector<std::string>> loadDictionaries();
bool           dictionariesHaveErrors(const std::pair<DictionariesUmap, std::vector<std::string>>& dictionaries);
ConsoleReader* consoleReader;
void           exitGame()
{
    consoleReader->stop();
}

inline constexpr Rect             gameRect           = { 0, 0, 80, 80 };
std::shared_ptr<game::Dictionary> selectedDictionary = nullptr;
ConsoleSection*                   currentMenu        = nullptr;
MainMenuSection                   mainMenu;
DictionariesMenu                  dictionariesMenu;

void newGameSelected()
{
}

void onDictionarySelected(size_t index)
{
}

void showDictionariesMenu()
{
    mainMenu.clearSection();
    currentMenu = &dictionariesMenu;
    dictionariesMenu.print();
}

GameController gameController;

void onKeyPressed(char c)
{
    gameController.handleKey(c);
}

std::string exeDir()
{
    char buffer[MAX_PATH] = { 0 };
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

int main(int argc, char* argv[])
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD  mode   = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

    HANDLE              consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize   = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);

    auto dictionariesAndErrors = loadDictionaries();
    if (dictionariesHaveErrors(dictionariesAndErrors)) {
        // TODO: show errors
    }

    GameController gameController;
    gameController.setDictionaries(std::move(dictionariesAndErrors.first));
    dictionariesAndErrors.first.clear();
    dictionariesAndErrors.second.clear();
    gameController.start();
    /*consoleReader = new ConsoleReader();
    QObject::connect(consoleReader, &ConsoleReader::keyPressed, &onKeyPressed);
    consoleReader->run();*/

    delete consoleReader;
    return 0;
}

std::pair<DictionariesUmap, std::vector<std::string>> loadDictionaries()
{
    std::pair<DictionariesUmap, std::vector<std::string>> dictionaries;
    std::filesystem::path dictionaryDir = exeDir();
    dictionaryDir /= dictionary_helpers::dictionariesFolder;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(dictionaryDir.string())) {
            if (entry.is_regular_file()) {
                std::ifstream stream;
                stream.open(entry.path(), std::ios::in);
                auto dictionary = std::make_shared<game::Dictionary>();
                stream >> *dictionary;
                dictionaries.first[dictionary->name()] = std::move(dictionary);
            }
        }
    } catch (const std::exception& e) {
        dictionaries.second.push_back("Exception happened while reading dictionary from file " + dictionaryDir.string()
                                      + ": " + e.what());
    }

    return dictionaries;
}

bool dictionariesHaveErrors(const std::pair<DictionariesUmap, std::vector<std::string>>& dictionaries)
{
    if (!dictionaries.second.empty()) {
        return true;
    }

    for (const auto& dictionary : dictionaries.first) {
        if (!dictionary.second->errors().empty()) {
            return true;
        }
    }

    return false;
}
