#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Bullet {
private:
    Sprite sprite;
    Vector2f direction;
    float speed;

public:
    Bullet(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& direction, float speed);
    void update(const Time& deltaTime);
    void draw(RenderWindow& window);
    bool isOffScreen(const FloatRect& playArea);
    FloatRect getGlobalBounds() const;
};
