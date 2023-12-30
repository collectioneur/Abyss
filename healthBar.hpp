#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class HealthBar {
private:
    RectangleShape healthBar;
    RectangleShape healthBarBackground;
    Vector2f position;
    float maxWidth;
    float currentHealthPercent;

public:
    HealthBar(float maxWidth);
    void setPosition(const Vector2f& position);
    void setHealthPercent(float percent);
    void draw(RenderWindow& window);
    Vector2f getSize();
};
