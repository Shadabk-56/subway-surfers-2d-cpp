#include "PowerUp.h"
#include <iostream>

PowerUp::PowerUp(int lane, float gameSpeed) 
    : lane(lane), speed(gameSpeed), isActiveFlag(false), isUsedFlag(false), duration(0.0f) {
    
    // ✅ ALL POWER-UPS RIGHT SHIFTED
    float rightShiftAmount = 25.0f;
    
    // Set position based on lane WITH RIGHT SHIFT
    if (lane == 0) position.x = 175 + rightShiftAmount;
    else if (lane == 1) position.x = 375 + rightShiftAmount;
    else if (lane == 2) position.x = 575 + rightShiftAmount;
    
    position.y = -50;
    
    // Default sprite setup
    sprite.setSize(sf::Vector2f(40, 40));
    sprite.setFillColor(sf::Color::White);
    sprite.setPosition(position);
}

void PowerUp::update(float deltaTime) {
    // Move downward
    position.y += speed * deltaTime * 100;
    sprite.setPosition(position);
}

void PowerUp::draw(sf::RenderWindow& window) {
    if (!isUsedFlag) {
        window.draw(sprite);
    }
}

void PowerUp::activate() {
    isActiveFlag = true;
    duration = 10.0f;
}

void PowerUp::deactivate() {
    isActiveFlag = false;
}

sf::Vector2f PowerUp::getPosition() const {
    return position;
}

sf::FloatRect PowerUp::getBounds() const {
    return sprite.getGlobalBounds();
}

bool PowerUp::isActive() const {
    return isActiveFlag;    // Return the flag, not call itself
}

bool PowerUp::isUsed() const {
    return isUsedFlag;      // Return the flag, not call itself
}

void PowerUp::setUsed(bool value) {
    isUsedFlag = value;
}

void PowerUp::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
    sprite.setPosition(position);
}
