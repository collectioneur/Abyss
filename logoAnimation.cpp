#include "logoAnimation.hpp"

using namespace sf;
using namespace std;
LogoAnimation::LogoAnimation(const Texture& logoTexture, const Texture& logoTextTexture) {
    logoSprite.setTexture(logoTexture);
    logoTextSprite.setTexture(logoTextTexture);

    alpha = 0.f;
    increasing = true;
    seconds = 0.f;
}

void LogoAnimation::setPosition(float x, float y, float textYOffset) {
    logoSprite.setPosition(x, y);
    logoTextSprite.setPosition(x + 350, y + textYOffset);
}

FloatRect LogoAnimation::getLocalBounds() const {
    FloatRect logoBounds = logoSprite.getLocalBounds();
    FloatRect textBounds = logoTextSprite.getLocalBounds();

    float width = max(logoBounds.width, textBounds.width);
    float height = logoBounds.height + textBounds.height;
    return FloatRect(0.f, 0.f, width, height);
}

void LogoAnimation::update(Time elapsed) {
    seconds += elapsed.asSeconds();
    if (increasing && seconds > 2.f) {
        alpha += 255.f * elapsed.asSeconds();
        if (alpha >= 255.f) {
            alpha = 255.f;
            increasing = false;
        }
    } else if (seconds > 5.f) {
        alpha -= 255.f * elapsed.asSeconds();
        if (alpha <= 0.f) {
            alpha = 0.f;
            if (seconds > 7.f) increasing = true;
        }
    }
    logoSprite.setColor(Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
    logoTextSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
}

void LogoAnimation::draw(RenderWindow& window) {
    window.draw(logoSprite);
    window.draw(logoTextSprite);
}

bool LogoAnimation::isFinished() const {
    return seconds > 7.f;
}
