#include <SFML/Graphics.hpp>
#include "menu.hpp"

using namespace sf;
using namespace std;

Menu::Menu(const Font& font, GameState& gameState) : gameState(gameState) {
    menubuttons.emplace_back("Play", font, 50);
    menubuttons.emplace_back("Settings", font, 50);
    menubuttons.emplace_back("Characters", font, 50);
    menubuttons.emplace_back("End", font, 50);
    playbuttons.emplace_back("Gate\nto\nHell", font, 50);
    playbuttons.emplace_back("Demonic\nresidences", font, 50);
    playbuttons.emplace_back("Back", font, 50);
    float y = 100;
    for (auto& button : menubuttons) {
        button.setPosition(500, y);
        y += 80;
    }
    playbuttons[0].setPosition(630, 150);
    playbuttons[1].setPosition(1000, 300);
    playbuttons[2].setPosition(650, 680);
}

void Menu::draw(RenderWindow& window) {
    if (showPlayButtons) {
                for (auto& button : playbuttons) {
                    button.draw(window);
                }
    }
    else {
            for (auto& button : menubuttons) {
                    button.draw(window);
            }
        }
}

void Menu::update(const Vector2f& mousePos, const Event& event) {
    if(showPlayButtons){
        for (auto& button : playbuttons) {
            button.update(mousePos);
            if (button.isClicked(mousePos, event)) {
                if(button.getTitle() == "Back") {
                    showPlayButtons = false;
                }
                if(button.getTitle() == "Gate\nto\nHell") {
                    gameState = GameState::GAME;
                }
            }
        }
    }
    else {
        for (auto& button : menubuttons) {
        button.update(mousePos);
        if (button.isClicked(mousePos, event)) {
            if(button.getTitle() == "Play") {
                showPlayButtons = true;
            }
            if(button.getTitle() == "End") {
                exit(0);
            }
        }
    }
    }
};

