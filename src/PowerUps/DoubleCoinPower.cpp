#include "DoubleCoinPower.h"
#include <iostream>
#include <cmath>

DoubleCoinPower::DoubleCoinPower(int lane, float gameSpeed) 
    : PowerUp(lane, gameSpeed), multiplier(2.0f) {
    
    // Load boost.png texture
    const std::vector<std::string> texturePaths = {
        "assets/textures/boost.png",
        "assets/textures/booster.png", 
        "assets/boost.png",
        "assets/booster.png"
    };
    
    bool textureLoaded = false;
    for (const auto& path : texturePaths) {
        if (texture.loadFromFile(path)) {
            textureLoaded = true;
            //std::cout << "Boost texture loaded: " << path << std::endl;
            break;
        }
    }
    
    if (textureLoaded) {
        sprite.setTexture(&texture);
        sprite.setSize(sf::Vector2f(40, 40));
    } else {
        // Fallback: Orange rectangle with "2X"
        sprite.setSize(sf::Vector2f(40, 40));
        sprite.setFillColor(sf::Color(255, 165, 0)); // Orange
        sprite.setOutlineColor(sf::Color::White);
        sprite.setOutlineThickness(2);
        //std::cout << "Boost texture not found, using orange fallback" << std::endl;
    }
    
    sprite.setOrigin(20, 20);
    sprite.setPosition(position);
    
    // Initialize timing
    elapsedTime = 0.0f;
    totalDuration = 10.0f;
}

void DoubleCoinPower::update(float deltaTime) {
    PowerUp::update(deltaTime);
    
    if (!isUsed()) {
        // Pulsing animation
        static float pulseTimer = 0.0f;
        pulseTimer += deltaTime * 4.0f;
        
        float pulseScale = 1.0f + sin(pulseTimer) * 0.15f;
        sprite.setScale(pulseScale, pulseScale);
        
        // Floating animation
        float floatOffset = sin(pulseTimer * 1.5f) * 8.0f;
        sprite.setPosition(position.x, position.y + floatOffset);
        
        // Rotate
        sprite.rotate(60.0f * deltaTime);
    } else if (isActive()) {
        // Update elapsed time when active
        elapsedTime += deltaTime;
    }
}

void DoubleCoinPower::draw(sf::RenderWindow& window) {
    if (!isUsed()) {
        window.draw(sprite);
    }
}

void DoubleCoinPower::activate() {
    PowerUp::activate();
    elapsedTime = 0.0f;
    totalDuration = 10.0f;
    //std::cout << "DOUBLE COIN POWER activated! " << multiplier << "x coins for " << totalDuration << " seconds!" << std::endl;
}

void DoubleCoinPower::deactivate() {
    PowerUp::deactivate();
    //std::cout << "Double coin power ended!" << std::endl;
}

float DoubleCoinPower::getMultiplier() const {
    return multiplier;
}

float DoubleCoinPower::getTimeLeft() const {
    if (!isActive()) return 0.0f;
    return std::max(0.0f, totalDuration - elapsedTime);
}

bool DoubleCoinPower::isActiveNow() const {
    return isActive() && getTimeLeft() > 0.0f;
}
