#pragma once
#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "gamestate.hpp"

using namespace std;
using namespace sf;

class Menu {
private:
    vector<Button> menubuttons;
    vector<Button> playbuttons;
    vector<Button> gamebuttons;
    bool showPlayButtons = false;
    GameState& gameState;
public:
    Menu(const Font& font, GameState& gameState);
    void draw(RenderWindow& window, Texture& gameLogoTexture);
    void update(const Vector2f& mousePos, const Event& event);
    Sprite createLogo(Texture gameLogoTexture);
};
