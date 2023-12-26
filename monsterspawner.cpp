#include "monsterspawner.hpp"

MonsterSpawner::MonsterSpawner(const Texture& texture, const FloatRect& area1, const FloatRect& area2)
    : monsterTexture(texture), spawnArea1(area1), spawnArea2(area2) {}

Vector2f MonsterSpawner::getRandomSpawnPosition(const FloatRect& area) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> disX(area.left, area.left + area.width);
    uniform_real_distribution<> disY(area.top, area.top + area.height);

    return Vector2f(disX(gen), disY(gen));
}

void MonsterSpawner::spawnMonster(vector<Monster>& monsters) {
    Vector2f spawnPos;
    if (rand() % 2 == 0) {
        spawnPos = getRandomSpawnPosition(spawnArea1);
    } else {
        spawnPos = getRandomSpawnPosition(spawnArea2);
    }
    monsters.emplace_back(monsterTexture, spawnPos, 50.0f); 
}
