#include "JetpackPower.h"
#include <iostream>
#include <cmath>
#include <algorithm> // For std::max

JetPackPower::JetPackPower(int lane, float gameSpeed) 
    : PowerUp(lane, gameSpeed) {
    
    totalDuration = 15.0f; // JetPack default duration
    
    // Load jetpack texture (Assuming 'jetpack.png' exists in assets/textures)
    const std::vector<std::string> texturePaths = {
        "assets/textures/jetpack.png",
        "assets/textures/jet_pack.png", 
        "assets/jetpack.png",
        "assets/textures/boost.png" // Fallback if 'boost.png' is generic
    };
    
    bool textureLoaded = false;
    for (const auto& path : texturePaths) {
        if (texture.loadFromFile(path)) {
            textureLoaded = true;
            //std::cout << "JetPack texture loaded: " << path << std::endl;
            break;
        }
    }
    
    if (textureLoaded) {
        sprite.setTexture(&texture);
        sprite.setSize(sf::Vector2f(50, 60)); // Size for a jetpack item
    } else {
        // Fallback: Blue rectangle
        sprite.setSize(sf::Vector2f(50, 60));
        sprite.setFillColor(sf::Color::Blue); 
        sprite.setOutlineColor(sf::Color::White);
        sprite.setOutlineThickness(2);
        //std::cout << "JetPack texture not found, using blue fallback" << std::endl;
    }
    
    sprite.setOrigin(25, 30);
    sprite.setPosition(position);
    
    elapsedTime = 0.0f;
}

void JetPackPower::update(float deltaTime) {
    PowerUp::update(deltaTime);
    
    if (!isUsed()) {
        // Pulsing animation (similar to other power-ups)
        static float pulseTimer = 0.0f;
        pulseTimer += deltaTime * 4.0f;
        
        float pulseScale = 1.0f + sin(pulseTimer) * 0.15f;
        sprite.setScale(pulseScale, pulseScale);
        
        float floatOffset = sin(pulseTimer * 1.5f) * 8.0f;
        sprite.setPosition(position.x, position.y + floatOffset);
        
        sprite.rotate(60.0f * deltaTime);
    } else if (isActive()) {
        elapsedTime += deltaTime;
    }
}

void JetPackPower::draw(sf::RenderWindow& window) {
    if (!isUsed()) {
        window.draw(sprite);
    }
}

void JetPackPower::activate() {
    PowerUp::activate();
    elapsedTime = 0.0f;
    totalDuration = 15.0f; 
    //std::cout << "JETPACK POWER activated for " << totalDuration << " seconds! 🚀🚀" << std::endl;
}

void JetPackPower::deactivate() {
    PowerUp::deactivate();
    //std::cout << "JetPack power ended!" << std::endl;
}

float JetPackPower::getTimeLeft() const {
    return std::max(0.0f, totalDuration - elapsedTime);
}

bool JetPackPower::isActiveNow() const {
    return isActive() && elapsedTime < totalDuration;
}
