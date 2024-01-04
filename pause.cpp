#include <SFML/Graphics.hpp>
#include "pause.hpp"

using namespace sf;
using namespace std;

pause::pause(const Font& font, GameState& gameState) : gameState(gameState) {
    pausebuttons.emplace_back("Resume", font, 50);
    pausebuttons.emplace_back("Restart", font, 50);
    pausebuttons.emplace_back("Exit", font, 50);
    pauseText.setFont(font);
    pauseText.setString("Pause");
    pauseText.setCharacterSize(100);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(550, 50);
    float y = 350;
    for (auto& button : pausebuttons) {
        button.setPosition(600, y);
        y += 70;
    }
}

void pause::draw(RenderWindow& window) {
                for (auto& button : pausebuttons) {
                    button.draw(window);
                }
    window.draw(pauseText);
}
void pause::update(const Vector2f& mousePos, const Event& event) {
    for (auto& button : pausebuttons) {
        button.update(mousePos);
        if (button.isClicked(mousePos, event)) {
            if(button.getTitle() == "Resume") {
                gameState = GameState::GAME;
            }
            if(button.getTitle() == "Restart") {
                gameState = GameState::END_GAME;
                buttonEnd = 1;
            }
            if(button.getTitle() == "Exit") {
                gameState = GameState::END_GAME;
                buttonEnd = 2;
            }
        }
    }
}
int pause::showButtonEnd() {
    return buttonEnd;
}
void pause::returnButtonEndToZero() {
    buttonEnd = 0;
}

