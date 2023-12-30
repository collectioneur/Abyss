#include "helpPanel.hpp"


helpPanel::helpPanel(const Texture& texture_1, const Font& font, const Texture& texture_2, const Vector2f& position_1) {
    sprite_1.setTexture(texture_1);
    sprite_1.setPosition(position_1);
    sprite_2.setTexture(texture_2);
    sprite_2.setPosition(Vector2f(gunSize().left+gunSize().width, gunSize().top));
    sprite_2.setColor(Color(255, 255, 255, 128));
    hitsLeftText.setFont(font);
    bulletsLeftText.setFont(font);
    bulletsLeftText.setFillColor(Color::White);
    hitsLeftText.setFillColor(Color::White);
    bulletsLeftText.setPosition(gunSize().left, gunSize().top + 20 + gunSize().height);
    hitsLeftText.setPosition(gunSize().left, gunSize().top + 20 + gunSize().height);
    bulletsLeftText.setCharacterSize(30);
    hitsLeftText.setCharacterSize(30);
    bulletsLeftText.setOutlineColor(Color::Black);
    bulletsLeftText.setOutlineThickness(5.f);
    hitsLeftText.setOutlineColor(Color::Black);
    hitsLeftText.setOutlineThickness(5.f);
}
void helpPanel::change() {
    if(showGun) {
        showGun = 0;
        showKatana = 1;
        sprite_2.setColor(Color(255, 255, 255, 255));
        sprite_1.setColor(Color(255, 255, 255, 128));
    }
    else {
        showGun = 1;
        showKatana = 0;
        sprite_2.setColor(Color(255, 255, 255, 128));
        sprite_1.setColor(Color(255, 255, 255, 255));
    }
}
void helpPanel::draw(RenderWindow& window) {
    window.draw(sprite_1);
    window.draw(sprite_2);
    setText();
    if(showGun == 1) {
        window.draw(bulletsLeftText);
    }
    else {
        window.draw(hitsLeftText);
    }
}
FloatRect helpPanel::gunSize() const {
    return sprite_1.getGlobalBounds();
}
void helpPanel::reset() {
    showGun = 1;
    showKatana = 0;
    sprite_2.setColor(Color(255, 255, 255, 128));
    sprite_1.setColor(Color(255, 255, 255, 255));
}
void helpPanel::weaponsLeft(int bulletsLeft1, int hitsLeft1) {
    bulletsLeft = bulletsLeft1;
    hitsLeft = hitsLeft1;
}
void helpPanel::setText() {
    string katanaText = to_string(hitsLeft);
    katanaText += " hits left";
    string bulletText = to_string(bulletsLeft);
    bulletText += " bullets left";
    hitsLeftText.setString(katanaText);
    bulletsLeftText.setString(bulletText);
}
