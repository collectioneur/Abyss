#pragma once
#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "gamestate.hpp"
#include "monster.hpp"
#include <string>
#include <fstream>
using namespace std;
using namespace sf;

class Statistics {
private:
    vector<Button> statisticsbuttons;
    Text StatisticsName;
    Text statisticsText;
    GameState& gameState;
    int gamesPlayed = 0;
    float bestTime = 0;
    int mostDemonsKilled = 0;
    int sumDemonsKilled = 0;
    int sumDemonsKilledByType[6];
public:
    Statistics(const Font& font, GameState& gameState);
    void draw(RenderWindow& window);
    void update(const Vector2f& mousePos, const Event& event);
    void statistics();
    void setStats(float Time1, int DemonsKilled1, int* DemonsKilledByType1);
    void reset();
    void saveStats();
    void loadStats();
};
