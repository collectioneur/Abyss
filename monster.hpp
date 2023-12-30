#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <vector>
#include "healthBar.hpp"
#include "bullet.hpp"

using namespace std;
using namespace sf;
class Character;

class Monster {
private:
    Sprite sprite;
    Vector2f direction;
    vector <Vector2f> dir_2;
    vector<Bullet> bullets;
    Texture bulletTexture;
    int directNum_2;
    float speed;
    float health;
    bool isAlive;
    HealthBar healthBar;
    int monsterType;
    float monsterDamage;
    float fullHealth;
    Texture texture;
    bool isVisibleMonster3 = 1;
    float timerMonster3;
    bool shoot3;
public:
    Monster(const Texture& texture, const Vector2f& position, const int monsterType, const Texture& bulletTexture);
    void update(const Time& deltaTime, Character& character, vector<Monster>& monsters, const FloatRect& playArea);
    void draw(RenderWindow& window);
    FloatRect getGlobalBounds() const;
    void checkCollisionWithBullets();
    bool isStillAlive() const;
    void takeDamage(float damage);
    Vector2f getPosition();
    void faceTowards();
    float getMonsterDamage();
    int getType();
    const Texture& getTextureForBabyMonster_2() const;
    void setDirectionForBabyMonster_1(Vector2f dir);
    Vector2f getDirection();
    Vector2f randPos(const FloatRect& area);
    void updateBullets(const Time& deltaTime, const FloatRect& playArea);
    void drawBullets(RenderWindow& window);
    void checkBulletCharacterCollisions(Character& character);
    void shoot(const Vector2f& characterPosition);
    bool checkIsVisible();
};
