#include <SFML/Graphics.hpp>
#include <cmath>
#include "monster.hpp"
#include "character.hpp"

using namespace sf;

Monster::Monster(const Texture& texture, const Vector2f& position, float speed)
    : sprite(texture), speed(speed), health(300), isAlive(1), healthBar(100.f) {
    sprite.setPosition(position);
}

void Monster::update(const Time& deltaTime, Character& character, vector<Monster>& monsters) {
    Vector2f targetPosition = character.getPosition();
    Vector2f currentPosition = sprite.getPosition();

    Vector2f direction = targetPosition - currentPosition;
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance > 70.f) {
        direction /= distance;
        sprite.move(direction * speed * deltaTime.asSeconds());
    }
    for(auto& monster : monsters) {
        if(monster.getPosition() != sprite.getPosition()&&sprite.getGlobalBounds().intersects(monster.getGlobalBounds())) {
            direction = monster.getPosition() - sprite.getPosition();
            distance = sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= distance;
            sprite.move(-direction * speed * deltaTime.asSeconds());
        }
    }
    Vector2f healthPosition = Vector2f(sprite.getPosition().x,sprite.getPosition().y - 50);
    healthBar.setPosition(healthPosition);
}

void Monster::draw(RenderWindow& window) {
    window.draw(sprite);
    healthBar.draw(window);
}

FloatRect Monster::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
void Monster::takeDamage(float damage) {
    health -= damage;
    healthBar.setHealthPercent(health/300);
    if (health <= 0) {
        isAlive = false;
    }
}
bool Monster::isStillAlive() const {
    return isAlive;
}
Vector2f Monster::getPosition(){
    return sprite.getPosition();
}
