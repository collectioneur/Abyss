#include <SFML/Graphics.hpp>
#include "statistics.hpp"

using namespace sf;
using namespace std;

Statistics::Statistics(const Font& font, GameState& gameState) : gameState(gameState) {
    statisticsbuttons.emplace_back("Reset", font, 50);
    statisticsbuttons.emplace_back("Back", font, 50);
    StatisticsName.setFont(font);
    StatisticsName.setString("Statistics");
    StatisticsName.setCharacterSize(100); 
    StatisticsName.setFillColor(sf::Color::White);
    StatisticsName.setPosition(450, 50);
    float y = 600;
    for (auto& button : statisticsbuttons) {
        button.setPosition(600, y);
        y += 70;
    }
    statisticsText.setFont(font);
    statisticsText.setCharacterSize(30);
    statisticsText.setFillColor(Color::White);
    for (int i = 0; i<6; i++) {
        sumDemonsKilledByType[i] = 0;
    }
}

void Statistics::draw(RenderWindow& window) {
                for (auto& button : statisticsbuttons) {
                    button.draw(window);
                }
    window.draw(StatisticsName);
    window.draw(statisticsText);
}
void Statistics::statistics() {
    string text = "Games Played: ";
    text += to_string(gamesPlayed);
    text += "\nBest Time: ";
    text += to_string(bestTime);
    text += " s\n";
    text += "The most killed demons in one game: ";
    text += to_string(mostDemonsKilled);
    text += "\nAmount of demons killed in all games: ";
    text += to_string(sumDemonsKilled);
    text += "\nAmount of demonic mans killed in all games: ";
    text += to_string(sumDemonsKilledByType[1]);
    text += "\nAmount of demonic spiders killed in all games: ";
    text += to_string(sumDemonsKilledByType[2]);
    text += "\nAmount of demonic sunflowers killed in all games: ";
    text += to_string(sumDemonsKilledByType[3]);
    text += "\nAmount of demonic baby spiders killed in all games: ";
    text += to_string(sumDemonsKilledByType[5]);
    statisticsText.setString(text);
    statisticsText.setPosition(400, 250);
}
void Statistics::update(const Vector2f& mousePos, const Event& event) {
    for (auto& button : statisticsbuttons) {
        button.update(mousePos);
        if (button.isClicked(mousePos, event)) {
            if(button.getTitle() == "Reset") {
                reset();
            }
            if(button.getTitle() == "Back") {
                gameState = GameState::MENU;
            }
        }
    }
    statistics();
}
void Statistics::setStats(float Time1, int DemonsKilled1, int* DemonsKilledByType1) {
    gamesPlayed++;
    bestTime = max(bestTime, Time1);
    mostDemonsKilled = max(mostDemonsKilled, DemonsKilled1);
    sumDemonsKilled += DemonsKilled1;
    for(int i = 0; i<6; i++){
        sumDemonsKilledByType[i] += DemonsKilledByType1[i];
    }
    statistics();
}
void Statistics::reset(){
    gamesPlayed = 0;
    bestTime = 0;
    mostDemonsKilled = 0;
    sumDemonsKilled = 0;
    for(int i = 0; i<6; i++){
        sumDemonsKilledByType[i] = 0;
    }
    statistics();
}
void Statistics::saveStats() {
    ofstream file("Abyssstats.txt");
    file << gamesPlayed << "\n";
    file << bestTime << "\n";
    file << mostDemonsKilled << "\n";
    file << sumDemonsKilled << "\n";
    for (int i = 0; i < 6; i++) {
        file << sumDemonsKilledByType[i] << "\n";
    }
    file.close();
}
void Statistics::loadStats() {
    ifstream file("Abyssstats.txt");
    if (file.is_open()) {
        file >> gamesPlayed;
        file >> bestTime;
        file >> mostDemonsKilled;
        file >> sumDemonsKilled;
        for (int i = 0; i < 6; i++) {
            file >> sumDemonsKilledByType[i];
        }
    }
    file.close();
}

