#include "characterInfo.hpp"

characterInfo::characterInfo(const Texture& texture, const Font& font, const string text_1, const string text_2) : infoButton("Get info", font, 50), backButton("Back", font, 50){
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);
    sprite.setScale(2.f, 2.f);
    sprite.setPosition(700, 350);
    characteristics.setString(text_1);
    information.setString(text_2);
    information.setFont(font);
    characteristics.setFont(font);
    characteristics.setFillColor(Color::White);
    information.setFillColor(Color::White);
    characteristics.setPosition(700 - sprite.getGlobalBounds().width/2, 350 + sprite.getGlobalBounds().height/2 + 40);
    //information.setOrigin(information.getGlobalBounds().width/2, information.getGlobalBounds().height/2);
    information.setPosition(500, 300);
    characteristics.setCharacterSize(60);
    information.setCharacterSize(30);
    //characteristics.setOutlineColor(Color::Black);
    //characteristics.setOutlineThickness(5.f);
    information.setOutlineColor(Color::Black);
    information.setOutlineThickness(5.f);
    infoButton.setPosition(600, 50);
    backButton.setPosition(600, 50);
}
void characterInfo::draw(RenderWindow& window) {
    window.draw(sprite);
    window.draw(characteristics);
    if(showInfo) {
        window.draw(information);
        backButton.draw(window);
    }
    else infoButton.draw(window);
}
void characterInfo::update(const Vector2f& mousePos, const Event& event) {
    backButton.update(mousePos);
    infoButton.update(mousePos);
    if(infoButton.isClicked(mousePos, event) && !showInfo) {
        if(!stopChange) showInfo = 1;
        stopChange = 1;
    }
    else if(backButton.isClicked(mousePos, event) && showInfo) {
        if(!stopChange) showInfo = 0;
        stopChange = 1;
    }
    else stopChange = 0;
}
void characterInfo::reset() {
    showInfo = 0;
}
