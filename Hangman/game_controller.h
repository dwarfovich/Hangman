#pragma once

#include "game_controller_state.h"
#include "main_menu_section.h"
#include "top_bar_section.h"
#include "console_reader.h"
#include "dictionaries_map.h"
#include "dictionaries_menu.h"
#include "selected_dictionary_section.h"
#include "hangman_section.h"
#include "game_result_section.h"
#include "game_over_menu.h"
#include "game_state.h"
#include "hangman.h"

class GameController
{
public:
    GameController();

    void setDictionaries(const DictionariesUmap& dictionaries);
    void start();
    void handleKey(char c);

private:
    void initializeMainMenu();
    void initializeGameOverMenu();
    void onStartGameRequested(size_t index = 0);
    void onDictionariesMenuRequested();
    void onExitGameRequested();
    void onNewDictionarySelected(size_t index);
    void onExitMenu();
    void onExitCurrentGameSession();
    void onGameStateChanged(GameState newState);
    void onPlayAgainRequest();
    void onExitToMainMenuRequest();

private:
    GameState                 currentGameState = GameState::WaitingForStart;
    game::Hangman             game;
    DictionariesUmap          dictionaries;
    ConsoleReader             consoleReader;
    ConsoleSection*           previousSection = nullptr;
    ConsoleSection*           currentSection  = nullptr;
    TopBarSection             versionSection;
    SelectedDictionarySection selectedDictionarySection;
    MainMenuSection           mainMenu;
    DictionariesMenu          dictionariesMenu;
    HangmanSection            hangmanSection;
    GameOverMenu              gameOverMenu;
    GameResultSection         gameResultSection;

};
