#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>

#include "monsterspawner.hpp"
#include "bullet.hpp"
#include "button.hpp"
#include "character.hpp"
#include "gamestate.hpp"
#include "healthBar.hpp"
#include "logoAnimation.hpp"
#include "menu.hpp"
#include "monster.hpp"

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(1920, 1080), "Abyss");
    Font font;
    if (!font.loadFromFile("/Users/egorharchenko/Desktop/gra/NightinTokyo.ttf")) {
        cerr << "Error loading font" << endl;
        return -1;
    }

    GameState gameState = GameState::MENU;
    Menu menu(font, gameState);
    Texture logoTexture, logoText, menuTexture, gameTexture, characterTexture, bulletTexture, monsterTexture;
    if (!logoTexture.loadFromFile("/Users/egorharchenko/Desktop/gra/graphics/logo.png") ||
        !logoText.loadFromFile("/Users/egorharchenko/Desktop/gra/graphics/textlogo.png") ||
        !menuTexture.loadFromFile("/Users/egorharchenko/Desktop/gra/graphics/menulogo.WEBP") ||
        !gameTexture.loadFromFile("/Users/egorharchenko/Desktop/gra/graphics/gamebackground.png") ||
        !characterTexture.loadFromFile("/Users/egorharchenko/Desktop/gra/graphics/character2.png") ||
        !bulletTexture.loadFromFile("/Users/egorharchenko/Desktop/gra/graphics/bullet.png") ||
        !monsterTexture.loadFromFile("/Users/egorharchenko/Desktop/gra/graphics/monsterbasic.png")) {
        cerr << "Error loading image" << endl;
        return -1;
    }
    vector<Monster> monsters;
    Character character(characterTexture, window.getSize(), bulletTexture);
    LogoAnimation logoAnimation(logoTexture, logoText);
    FloatRect bounds = logoAnimation.getLocalBounds();
    float xLogo = (window.getSize().x - bounds.width) / 2;
    float yLogo = (window.getSize().y - bounds.height) / 2;
    logoAnimation.setPosition(xLogo, yLogo, 800);

    Sprite menuSprite(menuTexture);
    float yScale = (window.getSize().y / menuSprite.getLocalBounds().height);
    float xScale = (window.getSize().x / menuSprite.getLocalBounds().width);
    menuSprite.setScale(xScale, yScale);

    Sprite gameBackground(gameTexture);
    yScale = (window.getSize().y / gameBackground.getLocalBounds().height);
    xScale = (window.getSize().x / gameBackground.getLocalBounds().width);
    gameBackground.setScale(xScale, yScale);

    Clock spawnClock;
    Time decreasingTime = seconds(0.f);
    Time spawnInterval = seconds(2.f);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(2, 3);

    Clock clock;
    FloatRect playArea(100.f, 70.f, window.getSize().x - 200.f, window.getSize().y - 150.f);
    FloatRect spawnArea1(600.f, -50.f, 100.f, 0.f), spawnArea2(window.getSize().x, 250.f, 1.f, 100.f);
    MonsterSpawner spawner(monsterTexture, spawnArea1, spawnArea2);
    int swapWeapons = 0;
    Clock limitKatana;
    float katanaCooldown = 0.5;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed && gameState == GameState::GAME) {
                character.setDestination(window.mapPixelToCoords(Mouse::getPosition(window)));
            } else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space && !swapWeapons) {
                    character.shoot(window.mapPixelToCoords(Mouse::getPosition(window)));
                } else if (event.key.code == Keyboard::Space && swapWeapons) {
                    if (limitKatana.getElapsedTime() >= seconds(katanaCooldown)) {
                        character.attackWithKatana(window.mapPixelToCoords(Mouse::getPosition(window)), monsters);
                        limitKatana.restart();
                    }
                } else if (event.key.code == Keyboard::M) {
                    swapWeapons++;
                    swapWeapons %= 2;
                }
            }
        }
        if (gameState == GameState::GAME) {
            Time deltaTime = clock.restart();
            character.faceTowards(window.mapPixelToCoords(Mouse::getPosition(window)));
            character.update(deltaTime, playArea);
            character.updateBullets(deltaTime, playArea);
            Time elapsed = spawnClock.getElapsedTime();
            if (elapsed >= spawnInterval - decreasingTime) {
                spawner.spawnMonster(monsters);
                if (decreasingTime < seconds(1)) decreasingTime += seconds(0.05);
                spawnClock.restart();
                spawnInterval = seconds(dis(gen)) - decreasingTime;
            }
            for (auto& monster : monsters) {
                monster.update(deltaTime, character, monsters);
            }
            character.checkCollisionWithMonsters(monsters);
            if (character.getHealth() <= 0) gameState = GameState::END_GAME;
            character.updateInvulnerability(deltaTime);
            character.checkBulletMonsterCollisions(monsters);
        }
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        menu.update(mousePos, event);
        Time elapsed = clock.restart();
        if (!logoAnimation.isFinished()) {
            logoAnimation.update(elapsed);
        }

        window.clear();
        if (!logoAnimation.isFinished()) {
            logoAnimation.draw(window);
        } else {
            if (gameState == GameState::MENU) {
                window.draw(menuSprite);
                menu.draw(window);
            } else if (gameState == GameState::GAME) {
                window.draw(gameBackground);
                if (swapWeapons) window.draw(character.getAttackArea(mousePos));
                character.draw(window);
                character.drawBullets(window);
                for (auto& monster : monsters) {
                    monster.draw(window);
                }
            } else if (gameState == GameState::END_GAME) {
                for (auto it = monsters.begin(); it != monsters.end();) {
                    monsters.erase(it);
                }
                swapWeapons = 0;
                decreasingTime = seconds(0.f);
                character.reset(window.getSize());
                gameState = GameState::MENU;
            }
        }
        window.display();
    }

    return 0;
}
