#include "hangman_draw_controller.h"
#include "hangman_section.h"

void game::drawHangman(size_t mistakeCount, const HangmanSection& hangmanSection)
{
    switch (mistakeCount) {
        case 1: hangmanSection.printHead(); break;
        case 2:
            hangmanSection.printHead();
            hangmanSection.printBody();
            break;
        case 3:
            hangmanSection.printHead();
            hangmanSection.printBody();
            hangmanSection.printLeftHand();
            break;
        case 4:
            hangmanSection.printHead();
            hangmanSection.printBody();
            hangmanSection.printLeftHand();
            hangmanSection.printRightHand();
            break;
        case 5:
            hangmanSection.printHead();
            hangmanSection.printBody();
            hangmanSection.printLeftHand();
            hangmanSection.printRightHand();
            hangmanSection.printLeftLeg();
            break;
        default:
            hangmanSection.printEndHead();
            hangmanSection.printBody();
            hangmanSection.printLeftHand();
            hangmanSection.printRightHand();
            hangmanSection.printLeftLeg();
            hangmanSection.printRightLeg();
            break;
    }
}
