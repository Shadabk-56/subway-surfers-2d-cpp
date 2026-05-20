#include "Fence.h"
#include <iostream>

Fence::Fence(int lane, float gameSpeed) 
    : Obstacle(lane, gameSpeed) {
    
    // ✅ FENCE PNG LOAD KARO
    if (!texture.loadFromFile("assets/textures/fence.png")) {
        //std::cout << "Failed to load fence.png! Using fallback color." << std::endl;
        sprite.setFillColor(sf::Color::Magenta); // Fallback color
    } else {
        sprite.setTexture(&texture);
        // Size set karo according to PNG
        sprite.setSize(sf::Vector2f(90, 40)); // Fence size
        //std::cout << "Fence PNG loaded successfully!" << std::endl;
    }
}

void Fence::update(float deltaTime) {
    position.y += speed * deltaTime * 100;
    sprite.setPosition(position);
}
