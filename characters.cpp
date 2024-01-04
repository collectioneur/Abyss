#include "characters.hpp"

characters::characters(const Font& font, GameState& gameState) : leftButton("O", font, 100), rightButton("O", font, 100), exitButton("Exit", font, 50), gameState(gameState) {
    leftButton.setPosition(50, 300);
    rightButton.setPosition(1300, 300);
    exitButton.setPosition(600,700);
}
void characters::update(const Vector2f& mousePos, const Event& event) {
    leftButton.update(mousePos);
    rightButton.update(mousePos);
    exitButton.update(mousePos);
    if(leftButton.isClicked(mousePos, event) && characterNumber > 0) {
        if(!stopChange) characterNumber--;
        stopChange = 1;
    }
       else if(rightButton.isClicked(mousePos, event) && characterNumber < 3) {
        if(!stopChange) characterNumber++;
        stopChange = 1;
    }
       else stopChange = 0;
    if(exitButton.isClicked(mousePos, event)) gameState = GameState::MENU;
   // cout << characterNumber << endl;
}
void characters::reset() {
    characterNumber = 0;
}
void characters::draw(RenderWindow& window) {
    if(characterNumber > 0) leftButton.draw(window);
    if(characterNumber < 3) rightButton.draw(window);
    exitButton.draw(window);
}
int characters::getcharacterNum() {
    return characterNumber;
}
