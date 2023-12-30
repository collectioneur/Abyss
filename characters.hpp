#pragma once
#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "characterInfo.hpp"
#include "gamestate.hpp"
#include <string>
#include <vector>
#include <iostream>
using namespace sf;
using namespace std;
class characters {
private:
    Button leftButton, rightButton, exitButton;
    bool stopChange = 0;
    int characterNumber = 0;
    GameState& gameState;
public:
    characters(const Font& font, GameState& gameState);
    void draw(RenderWindow& window);
    void update(const Vector2f& mousePos, const Event& event);
    void reset();
    int getcharacterNum();
};
