#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class LogoAnimation {
private:
    Sprite logoSprite, logoTextSprite;
    float alpha;
    bool increasing;
    float seconds;
public:
    LogoAnimation(const Texture& logoTexture, const Texture& logoTextTexture);
    void setPosition(float x, float y, float textYOffset);
    FloatRect getLocalBounds() const;
    void update(Time elapsed);
    void draw(RenderWindow& window);
    bool isFinished() const;
};
