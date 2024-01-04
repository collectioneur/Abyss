#include <SFML/Graphics.hpp>
#include "endscreen.hpp"

using namespace sf;
using namespace std;

EndScreen::EndScreen(const Font& font, GameState& gameState) : gameState(gameState) {
    endscreenbuttons.emplace_back("Restart", font, 50);
    endscreenbuttons.emplace_back("Exit", font, 50);
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(100); 
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(450, 50);
    float y = 600;
    for (auto& button : endscreenbuttons) {
        button.setPosition(600, y);
        y += 70;
    }
    statisticsText.setFont(font);
    statisticsText.setCharacterSize(50);
    statisticsText.setFillColor(Color::White);
}

void EndScreen::draw(RenderWindow& window) {
                for (auto& button : endscreenbuttons) {
                    button.draw(window);
                }
    window.draw(gameOverText);
    window.draw(statisticsText);
}
void EndScreen::statistics(int killedDemons, float timeSpent) {
    string text = "Demons killed: ";
    text += to_string(killedDemons);
    text += "\nTime spent: ";
    text += to_string(timeSpent);
    text += " s";
    statisticsText.setString(text);
    statisticsText.setPosition(400, 300);
}
void EndScreen::update(const Vector2f& mousePos, const Event& event) {
    for (auto& button : endscreenbuttons) {
        button.update(mousePos);
        if (button.isClicked(mousePos, event)) {
            if(button.getTitle() == "Restart") {
                gameState = GameState::GAME;
            }
            if(button.getTitle() == "Exit") {
                gameState = GameState::MENU;
            }
        }
    }
}
    

