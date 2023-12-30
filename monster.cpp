#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "monster.hpp"
#include "character.hpp"

using namespace sf;
Monster::Monster(const Texture& texture, const Vector2f& position, const int monsterType, const Texture& bulletTexture)
    : sprite(texture), isAlive(1), healthBar(100.f), monsterType(monsterType), texture(texture) {
    sprite.setPosition(position);
        this->bulletTexture = bulletTexture;
        float coord = 1/sqrt(2.0);
        dir_2.push_back(Vector2f(coord, coord));
        dir_2.push_back(Vector2f(coord, -coord));
        dir_2.push_back(Vector2f(-coord, -coord));
        dir_2.push_back(Vector2f(-coord, coord));
        FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2, bounds.height / 2);
        if(monsterType == 1) {
            health = 300.f;
            fullHealth = health;
            speed = 50.f;
            monsterDamage = 100.f;
        }
        else if(monsterType == 2) {
            directNum_2 = rand()%4;
            direction = dir_2[directNum_2];
            health = 200.f;
            fullHealth = health;
            speed = 150.f;
            monsterDamage = 50.f;
        }
        else if(monsterType == 3) {
            health = 200.f;
            fullHealth = health;
            speed = 0.f;
            monsterDamage = 0.f;
            isVisibleMonster3 = true;
            timerMonster3 = 0;
            shoot3 = 1;
        }
        else if(monsterType == 5) {
            directNum_2 = rand()%4;
            direction = dir_2[directNum_2];
            health = 50.f;
            fullHealth = health;
            speed = 200.f;
            monsterDamage = 30.f;
            sprite.scale(0.5, 0.5);
        }
}

void Monster::update(const Time& deltaTime, Character& character, vector<Monster>& monsters, const FloatRect& playArea) {
    if(monsterType == 1) {
        Vector2f targetPosition = character.getPosition();
        Vector2f currentPosition = sprite.getPosition();
        Vector2f direction = targetPosition - currentPosition;
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
        Vector2f nextPosition = sprite.getPosition() + (direction / distance * speed * deltaTime.asSeconds());
            if (distance > 130.f) {
                direction /= distance;
                sprite.move(direction * speed * deltaTime.asSeconds());
            }
        if(playArea.contains(nextPosition)){
            if(sprite.getGlobalBounds().intersects(character.getGlobalBounds())){
                
                sprite.move((-0.25f)*direction * speed * deltaTime.asSeconds());
            }
            else {
                for(auto& monster : monsters) {
                    if(monster.getPosition() != sprite.getPosition()&&sprite.getGlobalBounds().intersects(monster.getGlobalBounds())&&(!isVisibleMonster3||monsterType!=3)) {
                        direction = monster.getPosition() - sprite.getPosition();
                        distance = sqrt(direction.x * direction.x + direction.y * direction.y);
                        direction /= distance;
                        sprite.move(-direction * speed * deltaTime.asSeconds());
                    }
                }
            }
        }
       }
    else if(monsterType == 2 ||monsterType == 5) {
        Vector2f nextPosition = sprite.getPosition() + (direction * speed * deltaTime.asSeconds());
        if(playArea.contains(nextPosition)) {
            sprite.move(direction * speed * deltaTime.asSeconds());
            faceTowards();
        }
        else {
            Vector2f antidirection = -direction;
            while(!playArea.contains(nextPosition)||direction==antidirection) {
                directNum_2++;
                directNum_2%=4;
                direction = dir_2[directNum_2];
                nextPosition = sprite.getPosition() + (direction * speed * deltaTime.asSeconds());
            }
        }
    }
    else if(monsterType == 3) {
                    timerMonster3 += deltaTime.asSeconds();
                    if (timerMonster3 >= 5.0 && isVisibleMonster3) {
                        isVisibleMonster3 = false;
                        timerMonster3 = 0;
                        sprite.setPosition(randPos(playArea));
                        shoot3 = 1;
                    }
                 else if (timerMonster3 >= 3.0 && !isVisibleMonster3) {
                        isVisibleMonster3 = true;
                        timerMonster3 = 0;
                        shoot3 = 1;
                    }
        if(isVisibleMonster3&&timerMonster3 >= 3.0&&shoot3){
            shoot3 = 0;
            shoot(character.getPosition());
        }
        updateBullets(deltaTime, playArea);
        checkBulletCharacterCollisions(character);
    }
    else if(monsterType == 4) {
        
    }
    else if(monsterType == 5) {
        
    }
    FloatRect monsterBounds = sprite.getGlobalBounds();
    float healthBarOffset = 20.0f;
    Vector2f healthBarPosition(
        monsterBounds.left + monsterBounds.width / 2 - healthBar.getSize().x / 2,
        monsterBounds.top - healthBarOffset - healthBar.getSize().y
    );
    healthBar.setPosition(healthBarPosition);

}

void Monster::draw(RenderWindow& window) {
    if(isVisibleMonster3||monsterType!=3) {
        window.draw(sprite);
        healthBar.draw(window);
    }
    drawBullets(window);
}

FloatRect Monster::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
void Monster::takeDamage(float damage) {
    if(isVisibleMonster3||monsterType!=3) {
        health -= damage;
        healthBar.setHealthPercent(health/fullHealth);
        if (health <= 0) {
            isAlive = false;
        }
    }
}
bool Monster::isStillAlive() const {
    return isAlive;
}
Vector2f Monster::getPosition(){
    return sprite.getPosition();
}
void Monster::faceTowards() {
    float angle = atan2(direction.y, direction.x) * 180 / M_PI;
    sprite.setRotation(angle + 90);
}
float Monster::getMonsterDamage() {
    return monsterDamage;
}
int Monster::getType(){
    return monsterType;
}
const Texture& Monster::getTextureForBabyMonster_2() const{
    return texture;
}
void Monster::setDirectionForBabyMonster_1(Vector2f dir){
    direction = dir;
}
Vector2f Monster::getDirection(){
    return direction;
}
Vector2f Monster::randPos(const FloatRect& area){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> disX(area.left, area.left + area.width);
    uniform_real_distribution<> disY(area.top, area.top + area.height);

    return Vector2f(disX(gen), disY(gen));
}
void Monster::updateBullets(const Time& deltaTime, const FloatRect& playArea) {
    for (auto it = bullets.begin(); it != bullets.end();) {
        it->update(deltaTime);
        if (it->isOffScreen(playArea)) {
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }
}
void Monster::drawBullets(sf::RenderWindow& window) {
    for (auto& bullet : bullets) {
        bullet.draw(window);
    }
}
void Monster::shoot(const Vector2f& characterPosition) {
    Vector2f bulletDirection = characterPosition - sprite.getPosition();
    float distance = sqrt(bulletDirection.x * bulletDirection.x + bulletDirection.y * bulletDirection.y);
    bulletDirection /= distance;
    bullets.emplace_back(bulletTexture, sprite.getPosition(), bulletDirection, 300.0f);
}
void Monster::checkBulletCharacterCollisions(Character& character) {
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        bool bulletHit = false;
            if (bulletIt->getGlobalBounds().intersects(character.getGlobalBounds())) {
                character.takeDamage(50.f);
                bulletHit = true;
        }
        if (bulletHit) {
            bulletIt = bullets.erase(bulletIt);
        } else {
            ++bulletIt;
        }
    }
}
bool Monster::checkIsVisible() {
    return isVisibleMonster3;
}
