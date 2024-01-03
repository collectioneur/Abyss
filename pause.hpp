#pragma once
#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "gamestate.hpp"
#include <string>
using namespace std;
using namespace sf;

class pause {
private:
    vector<Button> pausebuttons;
    Text pauseText;
    GameState& gameState;
    int buttonEnd = 0;
public:
    pause(const Font& font, GameState& gameState);
    void draw(RenderWindow& window);
    void update(const Vector2f& mousePos, const Event& event);
    int showButtonEnd();
    void returnButtonEndToZero();
};
