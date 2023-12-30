#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;
class helpPanel {
private:
    Sprite sprite_1;
    Sprite sprite_2;
    bool showGun = 1;
    bool showKatana = 0;
    int bulletsLeft = 0;
    int hitsLeft = 0;
    Text hitsLeftText;
    Text bulletsLeftText;
public:
    helpPanel(const Texture& texture_1, const Font& font, const Texture& texture_2, const Vector2f& position_1);
    void change();
    void draw(RenderWindow& window);
    FloatRect gunSize() const;
    void reset();
    void weaponsLeft(int bulletsLeft1, int hitsLeft1);
    void setText();
};
