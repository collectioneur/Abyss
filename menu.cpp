#include <SFML/Graphics.hpp>
#include "menu.hpp"

using namespace sf;
using namespace std;

Menu::Menu(const Font& font, GameState& gameState) : gameState(gameState) {
    menubuttons.emplace_back("Play", font, 50);
    //menubuttons.emplace_back("Settings", font, 50);
    menubuttons.emplace_back("Statistics", font, 50);
    menubuttons.emplace_back("Characters", font, 50);
    menubuttons.emplace_back("End", font, 50);
    playbuttons.emplace_back("Gate\nto\nHell", font, 50);
   // playbuttons.emplace_back("Demonic\nresidences", font, 50);
    playbuttons.emplace_back("Back", font, 50);
    float y = 300.f;
    for (auto& button : menubuttons) {
        button.setPosition(500, y);
        y += 80;
    }
    playbuttons[0].setPosition(650, 150);
   // playbuttons[1].setPosition(1000, 300);
    playbuttons[1].setPosition(650, 680);
}

void Menu::draw(RenderWindow& window, Texture& gameLogoTexture) {
    if (showPlayButtons) {
                for (auto& button : playbuttons) {
                    button.draw(window);
                }
    }
    else {
            for (auto& button : menubuttons) {
                    button.draw(window);
            }
        window.draw(createLogo(gameLogoTexture));
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
            if(button.getTitle() == "Statistics") {
                gameState = GameState::STATISTICS;
            }
            if(button.getTitle() == "Characters") {
                gameState = GameState::CHARACTERS;
            }
        }
    }
    }
}

Sprite Menu::createLogo(Texture gameLogoTexture) {
    Sprite gamelogo(gameLogoTexture);
    float xLogo = 700;
    float yLogo = 50;
    gamelogo.setScale(1.5, 1.5);
    gamelogo.setPosition(xLogo, yLogo);
    return gamelogo;
}

