#pragma once
#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "gamestate.hpp"
#include "monster.hpp"
#include <string>
using namespace std;
using namespace sf;

class EndScreen {
private:
    vector<Button> endscreenbuttons;
    Text gameOverText;
    Text statisticsText;
    GameState& gameState;
public:
    EndScreen(const Font& font, GameState& gameState);
    void draw(RenderWindow& window);
    void update(const Vector2f& mousePos, const Event& event);
    void statistics(int killedDemons, float timeSpent);
};
