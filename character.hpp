#pragma once
#include <SFML/Graphics.hpp>
#include "bullet.hpp"
#include "monster.hpp"
#include "healthBar.hpp"
#include <vector>
using namespace sf;
using namespace std;

class Character {
private:
    Sprite sprite;
    Vector2f destination;
    float speed;
    vector<Bullet> bullets;
    Texture bulletTexture;
    float health;
    bool life;
    bool isInvulnerable;
    Time invulnerabilityTimer;
    Time invulnerabilityDuration;
    HealthBar healthBar;
    RectangleShape attackArea;
    bool katanaMode = 0;
public:
    Character(const Texture& texture, const Vector2u& windowSize,  const Texture& bulletTexture);
    void setDestination(const Vector2f& newDestination);
    void update(const Time& deltaTime, const FloatRect& playArea);
    void draw(RenderWindow& window);
    Vector2f getPosition();
    int getHealth();
    void faceTowards(const sf::Vector2f& targetPosition);
    void shoot(const Vector2f& direction);
    void updateBullets(const Time& deltaTime, const FloatRect& playArea);
    void drawBullets(RenderWindow& window);
    void checkCollisionWithMonsters(vector<Monster>& monsters);
    void makeInvulnerable();
    void updateInvulnerability(const Time& deltaTime);
    void reset(const Vector2u& windowSize);
    void checkBulletMonsterCollisions(vector<Monster>& monsters);
    void attackWithKatana(const sf::Vector2f& cursorPosition, vector<Monster>& monsters);
    RectangleShape getAttackArea(const Vector2f& cursorPosition);
};
