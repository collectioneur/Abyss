#pragma once
#include <SFML/Graphics.hpp>
#include "button.hpp"
#include <string>
using namespace sf;
using namespace std;
class characterInfo {
private:
    Sprite sprite;
    Text information;
    Text characteristics;
    Button infoButton, backButton;
    bool showInfo = 0;
    bool stopChange = 0;
public:
    characterInfo(const Texture& texture, const Font& font, const string text_1, const string text_2);
    void draw(RenderWindow& window);
    void update(const Vector2f& mousePos, const Event& event);
    void reset();
};

