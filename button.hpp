#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;
class Button {
private:
    Text text;
    bool isHovered;

public:
    Button(const string& title, const Font& font, unsigned int fontSize);

    void setPosition(float x, float y);
    void draw(RenderWindow& window);
    void update(const Vector2f& mousePos);
    bool isClicked(const Vector2f& mousePos, const Event& event) const;
    const string getTitle() const;
};
