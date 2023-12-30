#include "healthBar.hpp"

HealthBar::HealthBar(float maxWidth)
    : maxWidth(maxWidth), currentHealthPercent(1.f) {
    healthBarBackground.setSize(Vector2f(maxWidth, 10.f));
    healthBarBackground.setFillColor(Color(0, 0, 0));

    healthBar.setSize(Vector2f(maxWidth, 10.f));
    healthBar.setFillColor(Color(255, 153, 153));
}

void HealthBar::setPosition(const Vector2f& newPosition) {
    position = newPosition;
    healthBarBackground.setPosition(position);
    healthBar.setPosition(position);
}

void HealthBar::setHealthPercent(float percent) {
    currentHealthPercent = percent;
    healthBar.setSize(Vector2f(maxWidth * currentHealthPercent, 10.f));
}

void HealthBar::draw(RenderWindow& window) {
    window.draw(healthBarBackground);
    window.draw(healthBar);
}
Vector2f HealthBar::getSize() {
    return Vector2f(maxWidth, 10.f);
}
