#pragma once
#include <SFML/Graphics.hpp>
#include "healthBar.hpp"
using namespace std;
using namespace sf;
class Character;

class Monster {
private:
    Sprite sprite;
    Vector2f direction;
    float speed;
    float health;
    bool isAlive;
    HealthBar healthBar;
public:
    Monster(const Texture& texture, const Vector2f& position, float speed);
    void update(const Time& deltaTime, Character& character, vector<Monster>& monsters);
    void draw(RenderWindow& window);
    FloatRect getGlobalBounds() const;
    void checkCollisionWithBullets();
    bool isStillAlive() const;
    void takeDamage(float damage);
    Vector2f getPosition();
};
