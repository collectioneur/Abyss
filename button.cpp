#include <SFML/Graphics.hpp>
#include <string>
#include "button.hpp"

using namespace sf;
using namespace std;

Button::Button(const string& title, const Font& font, unsigned int fontSize) {
    text.setFont(font);
    text.setString(title);
    text.setCharacterSize(fontSize);
    isHovered = false;
}

void Button::setPosition(float x, float y) {
    text.setPosition(x, y);
}

void Button::draw(RenderWindow& window) {
    window.draw(text);
}

void Button::update(const Vector2f& mousePos) {
    isHovered = text.getGlobalBounds().contains(mousePos);
    text.setFillColor(isHovered ? Color(255, 0, 0) : Color::White);
}

bool Button::isClicked(const Vector2f& mousePos, const Event& event) const {
    return isHovered && event.type == Event::MouseButtonPressed &&
           event.mouseButton.button == Mouse::Left;
}
const string Button::getTitle() const {
    return text.getString();
}
