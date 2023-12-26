#include "bullet.hpp"

using namespace sf;
Bullet::Bullet(const Texture& texture, const Vector2f& position, const Vector2f& direction, float speed)
    : direction(direction), speed(speed) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Bullet::update(const Time& deltaTime) {
    sprite.move(direction * speed * deltaTime.asSeconds());
}

void Bullet::draw(RenderWindow& window) {
    window.draw(sprite);
}

bool Bullet::isOffScreen(const FloatRect& playArea) {
    Vector2f position = sprite.getPosition();
        return !playArea.contains(position);
}
FloatRect Bullet::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
