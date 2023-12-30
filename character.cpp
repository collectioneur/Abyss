#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "character.hpp"

using namespace sf;
Character::Character(const Texture& texture, const sf::Vector2u& windowSize, const Texture& bulletTexture) : speed(200.f), health(1000.f), life(1), healthBar(100.f) {
    sprite.setTexture(texture);
    this->bulletTexture = bulletTexture;
    FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);
    sprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
    destination = sprite.getPosition();
    isInvulnerable = false;
    invulnerabilityDuration = seconds(1.f);
    allHealth = health;
    for(int i = 0; i < 6; i++) {
        killedDemonsbyType[i] = 0;
    }
}

void Character::setDestination(const Vector2f& newDestination) {
    if (!katanaMode) destination = newDestination;
}

void Character::update(const Time& deltaTime, const FloatRect& playArea) {
    Vector2f direction = destination - sprite.getPosition();
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
    Vector2f nextPosition = sprite.getPosition() + (direction / distance * speed * deltaTime.asSeconds());
    if (playArea.contains(nextPosition)) {
        if (distance > 1.f) {
            direction /= distance;
            sprite.move(direction * speed * deltaTime.asSeconds());
        } else {
            katanaMode = 0;
            speed = 200.f;
        }
    } else {
        katanaMode = 0;
        speed = 200.f;
    }
    Vector2f healthPosition = Vector2f(sprite.getPosition().x - 50, sprite.getPosition().y - 100);
    healthBar.setPosition(healthPosition);
}

void Character::draw(RenderWindow& window) {
    window.draw(sprite);
    healthBar.draw(window);
}
int Character::getHealth() { return health; }
Vector2f Character::getPosition() { return sprite.getPosition(); }
void Character::faceTowards(const Vector2f& mousePosition) {
    Vector2f direction = mousePosition - sprite.getPosition();
    float angle = atan2(direction.y, direction.x) * 180 / M_PI;
    sprite.setRotation(angle + 90);
}

void Character::shoot(const Vector2f& mousePosition) {
    Vector2f bulletDirection = mousePosition - sprite.getPosition();
    float distance = sqrt(bulletDirection.x * bulletDirection.x + bulletDirection.y * bulletDirection.y);
    bulletDirection /= distance;
    bullets.emplace_back(bulletTexture, sprite.getPosition(), bulletDirection, 500.0f);
}

void Character::updateBullets(const Time& deltaTime, const FloatRect& playArea) {
    for (auto it = bullets.begin(); it != bullets.end();) {
        it->update(deltaTime);
        if (it->isOffScreen(playArea)) {
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }
}
void Character::drawBullets(sf::RenderWindow& window) {
    for (auto& bullet : bullets) {
        bullet.draw(window);
    }
}
void Character::checkCollisionWithMonsters(vector<Monster>& monsters) {
    for (auto& monster : monsters) {
        if (sprite.getGlobalBounds().intersects(monster.getGlobalBounds()) && !isInvulnerable) {
            health -= monster.getMonsterDamage();
            healthBar.setHealthPercent(health / allHealth);
            makeInvulnerable();
            if (health < 0) life = 0;
        }
    }
}
void Character::makeInvulnerable() {
    isInvulnerable = true;
    invulnerabilityTimer = Time::Zero;
}
void Character::updateInvulnerability(const Time& deltaTime) {
    if (isInvulnerable) {
        invulnerabilityTimer += deltaTime;
        if (invulnerabilityTimer >= invulnerabilityDuration) {
            isInvulnerable = false;
        }
    }
}
void Character::reset(const Vector2u& windowSize) {
    sprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
    health = allHealth;
    life = 1;
    healthBar.setHealthPercent(1.f);
    destination = sprite.getPosition();
    killedDemons = 0;
    for (auto it = bullets.begin(); it != bullets.end();) {
        bullets.erase(it);
    }
    for(int i = 0; i < 6; i++) {
        killedDemonsbyType[i] = 0;
    }
}
void Character::checkBulletMonsterCollisions(vector<Monster>& monsters) {
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        bool bulletHit = false;

        for (auto monsterIt = monsters.begin(); monsterIt != monsters.end() && !bulletHit;) {
            if (bulletIt->getGlobalBounds().intersects(monsterIt->getGlobalBounds())&&monsterIt->checkIsVisible()) {
                monsterIt->takeDamage(50);
                bulletHit = true;

                if (!monsterIt->isStillAlive()) {
                    checkMonster_2(monsterIt);
                    killedDemonsbyType[monsterIt -> getType()]++;
                    monsterIt = monsters.erase(monsterIt);
                    killedDemons++;
                } else {
                    ++monsterIt;
                }
            } else {
                ++monsterIt;
            }
        }

        if (bulletHit) {
            bulletIt = bullets.erase(bulletIt);
        } else {
            ++bulletIt;
        }
    }
}
void Character::attackWithKatana(const Vector2f& cursorPosition, vector<Monster>& monsters) {
    Vector2f attackDirection = cursorPosition - sprite.getPosition();
    float attackDistance = 200.0f;
    float attackDamage = 100.f;
    getAttackArea(cursorPosition);
    speed = 500.f;
    float length = sqrt(attackDirection.x * attackDirection.x + attackDirection.y * attackDirection.y);
    attackDirection /= length;
    setDestination(sprite.getPosition() + attackDirection * attackDistance);
    if (!katanaMode) {
        for (auto monsterIt = monsters.begin(); monsterIt != monsters.end();) {
            if (attackArea.getGlobalBounds().intersects(monsterIt->getGlobalBounds())) {
                monsterIt->takeDamage(attackDamage);
                if (!monsterIt->isStillAlive()) {
                    killedDemonsbyType[monsterIt -> getType()]++;
                    killedDemons++;
                    checkMonster_2(monsterIt);
                    monsterIt = monsters.erase(monsterIt);
                } else {
                    ++monsterIt;
                }
            } else {
                ++monsterIt;
            }
        }
    }
    katanaMode = 1;
    makeInvulnerable();
}
RectangleShape Character::getAttackArea(const Vector2f& cursorPosition) {
    Vector2f attackDirection = cursorPosition - sprite.getPosition();
    float attackDistance = 200.0f;
    float length = sqrt(attackDirection.x * attackDirection.x + attackDirection.y * attackDirection.y);
    attackDirection /= length;
    float angle = atan2(attackDirection.y, attackDirection.x) * 180 / M_PI;
    if (!katanaMode)
        attackArea.setSize(Vector2f(attackDistance / 2, -attackDistance));
    else
        attackArea.setSize(Vector2f(0, 0));
    attackArea.setOrigin(attackDistance / 4, 0);
    attackArea.setPosition(sprite.getPosition());
    attackArea.setRotation(angle + 90);
    attackArea.setFillColor(Color(255, 0, 0, 128));
    return attackArea;
}
FloatRect Character::getGlobalBounds() {
    return sprite.getGlobalBounds();
}
int Character::howManyKilled() {
 return killedDemons;
}
void Character::checkMonster_2(vector<Monster>::iterator monsterIt) {
    if(monsterIt->getType() == 2) {
        monster2_killed = 1;
        coordMonster2 = monsterIt -> getPosition();
        dirMonster2 = monsterIt -> getDirection();
    }
}
bool Character::checkKilledMonster_2(){
    return monster2_killed;
}
Vector2f Character::getPosKilledMonster_2(){
    return coordMonster2;
}
void Character::resetKilledMonster_2(){
    monster2_killed = 0;
}
Vector2f Character::getDirKilledMonster_2(){
    return dirMonster2;
}
void Character::takeDamage(float damage) {
    if(!isInvulnerable) health -= 50;
    makeInvulnerable();
    healthBar.setHealthPercent(health/allHealth);
    if (health < 0) life = 0;
}
int Character::amountKilledDemonType(int demonType) {
    return killedDemonsbyType[demonType];
}
