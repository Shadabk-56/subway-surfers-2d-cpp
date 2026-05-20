#include "MagnetPower.h"
#include <iostream>
#include <cmath>

MagnetPower::MagnetPower(int lane, float gameSpeed) 
    : PowerUp(lane, gameSpeed) {
    
    // Load magnet texture
    const std::vector<std::string> texturePaths = {
        "assets/textures/magnet.png",
        "assets/magnet.png",
        "assets/textures/powerup_magnet.png",
        "assets/powerup_magnet.png"
    };
    
    bool textureLoaded = false;
    for (const auto& path : texturePaths) {
        if (texture.loadFromFile(path)) {
            textureLoaded = true;
            std::cout << "✅ Magnet texture loaded: " << path << std::endl;
            break;
        }
    }
    
    if (textureLoaded) {
        sprite.setTexture(&texture);
        sprite.setSize(sf::Vector2f(40, 40));
    } else {
        // Fallback: Yellow rectangle
        sprite.setSize(sf::Vector2f(40, 40));
        sprite.setFillColor(sf::Color(255, 255, 0));
        sprite.setOutlineColor(sf::Color(0, 0, 0));
        sprite.setOutlineThickness(2);
        std::cout << "❌ Magnet texture not found, using fallback" << std::endl;
    }
    
    sprite.setOrigin(20, 20);
    sprite.setPosition(position);
}

void MagnetPower::update(float deltaTime) {
    // Call parent update first
    PowerUp::update(deltaTime);
    
    // Rotate magnet slowly for visual effect
    static float rotationAngle = 0.0f;
    rotationAngle += 90.0f * deltaTime;
    sprite.setRotation(rotationAngle);
    
    // Floating animation
    float floatOffset = std::sin(rotationAngle * 0.1f) * 5.0f;
    sprite.setPosition(position.x, position.y + floatOffset);
}

void MagnetPower::draw(sf::RenderWindow& window) {
    if (!isUsed()) {  // Use the getter method
        window.draw(sprite);
    }
}

void MagnetPower::activate() {
    PowerUp::activate();
    std::cout << "🧲 Magnet activated! Coins will attract for " << duration << " seconds." << std::endl;
}

void MagnetPower::deactivate() {
    PowerUp::deactivate();
    std::cout << "🧲 Magnet deactivated!" << std::endl;
}
