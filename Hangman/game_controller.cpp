#include "game_controller.h"
#include "hangman_draw_controller.h"

GameController::GameController()
{
    consoleReader.setOnKeyPressedCallback([this](Char c) {
        this->handleKey(c);
    });
    initializeMainMenu();
    initializeGameOverMenu();
    currentSection = &mainMenu;
    dictionariesMenu.setCallback([this](size_t index) {
        this->onNewDictionarySelected(index);
    });
    dictionariesMenu.setExitCallback([this]() {
        this->onExitMenu();
    });
    hangmanSection.setExitCallback([this]() {
        this->onExitCurrentGameSession();
    });
}

void GameController::setDictionaries(const DictionariesUmap& dictionaries_)
{
    dictionaries = dictionaries_;
    dictionariesMenu.setDictionaries(dictionaries);
}

void GameController::start()
{
    versionSection.print();
    selectedDictionarySection.print();
    mainMenu.print();
    consoleReader.run();
}

void GameController::handleKey(char c)
{
    if (currentGameState == GameState::InProgress) {
        auto result = game.openLetter(c);
        if (result == OpenLetterResult::AlreadyOpened) {
            return;
        } else if (result == OpenLetterResult::CorrectGuess) {
            hangmanSection.markCorrectLetter(c);
            if (game.state() == GameState::PlayerWon) {
                onGameStateChanged(game.state());
            }
        } else if (result == OpenLetterResult::Mistake) {
            game::drawHangman(game.mistakes(), hangmanSection);
            hangmanSection.markMistakeLetter(c);
            if (game.state() == GameState::PlayerLoosed) {
                onGameStateChanged(game.state());
            }
        } else {
            currentSection->handleKey(c);
        }
    } else if (currentSection) {
        currentSection->handleKey(c);
    }
}

void GameController::initializeMainMenu()
{
    mainMenu.addEntry({ "Start game", [this](size_t index) {
                           this->onStartGameRequested(index);
                       } });

    mainMenu.addEntry({ "Select dictionary", [this](size_t index) {
                           this->onDictionariesMenuRequested();
                       } });

    mainMenu.addEntry({ "Exit", [this](size_t index) {
                           this->onExitGameRequested();
                       } });
}

void GameController::initializeGameOverMenu()
{
    gameOverMenu.addEntry({ "Play again", [this](size_t index) {
                               this->onPlayAgainRequest();
                           } });
    gameOverMenu.addEntry({ "Exit to main menu", [this](size_t index) {
                               this->onExitToMainMenuRequest();
                           } });
}

void GameController::onStartGameRequested(size_t index)
{
#ifdef _DEBUG
    if (selectedDictionarySection.selectedDictionary().empty()) {
        onNewDictionarySelected(0);
    }
#endif // !_DEBUG

    if (selectedDictionarySection.selectedDictionary().empty()) {
        return;
    }

    currentSection->clearSection();
    previousSection = currentSection;
    currentSection  = &hangmanSection;
    hangmanSection.setAlphabet(dictionaries[selectedDictionarySection.selectedDictionary()]->alphabet());

    currentGameState = GameState::InProgress;

    game.setAlphabet(dictionaries[selectedDictionarySection.selectedDictionary()]->alphabet());
#ifdef _DEBUG
    auto word = dictionaries[selectedDictionarySection.selectedDictionary()]->getRandomWord(5);
#else
    auto word = dictionaries[selectedDictionarySection.selectedDictionary()]->getRandomWord();
#endif

    game.startGame(word);
    hangmanSection.setTargetWord(word);
    hangmanSection.print();
}

void GameController::onDictionariesMenuRequested()
{
    previousSection = currentSection;
    currentSection->clearSection();
    dictionariesMenu.setDictionaries(dictionaries);
    currentSection = &dictionariesMenu;
    currentSection->print();
}

void GameController::onExitGameRequested()
{
    consoleReader.stop();
}

void GameController::onNewDictionarySelected(size_t index)
{
    if (index == dictionaries.size()) {
        onExitMenu();
    } else {
        auto iter = dictionaries.cbegin();
        advance(iter, index);

        selectedDictionarySection.setDictionaryname(iter->first);
    }
}

void GameController::onExitMenu()
{
    if (previousSection) {
        currentSection->clearSection();
        currentSection = previousSection;
        currentSection->print();
        previousSection = nullptr;
    }
}

void GameController::onExitCurrentGameSession()
{
    currentSection->clearSection();
    previousSection = nullptr;
    currentSection  = &mainMenu;
    currentSection->print();
}

void GameController::onGameStateChanged(GameState newState)
{
    hangmanSection.clearSection();
    gameResultSection.setResult(game.word(), game.state());
    gameResultSection.print();
    currentSection = &gameOverMenu;
    previousSection = nullptr;
    gameOverMenu.print();

}

void GameController::onPlayAgainRequest()
{
    gameOverMenu.clearSection();
    gameResultSection.clearSection();
    onStartGameRequested();
}

void GameController::onExitToMainMenuRequest()
{
    gameOverMenu.clearSection();
    gameResultSection.clearSection();
    previousSection = nullptr;
    currentSection = &mainMenu;
    mainMenu.print();
}
