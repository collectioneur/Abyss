#pragma once
#include <SFML/Graphics.hpp>
#include "monster.hpp"
#include <vector>
#include <random>

using namespace sf;
using namespace std;

class MonsterSpawner {
private:
    FloatRect spawnArea1;
    FloatRect spawnArea2;
    Texture monsterTexture;

    Vector2f getRandomSpawnPosition(const FloatRect& area);

public:
    MonsterSpawner(const Texture& texture, const FloatRect& area1, const FloatRect& area2);
    void spawnMonster(vector<Monster>& monsters);
};
