#include "Coin.h"
#include <iostream>
#include <cmath>

Coin::Coin(int lane, float gameSpeed, float yPosition) 
    : lane(lane), speed(gameSpeed), collected(false), 
      animationTimer(0.0f), rotationSpeed(180.0f) {
    
    // Set X position based on lane (will be overridden by TrackManager)
    if (lane == 0) position.x = 175;
    else if (lane == 1) position.x = 375;
    else if (lane == 2) position.x = 575;
    
    position.y = yPosition;
    
    // Load texture
    if (!texture.loadFromFile("assets/textures/coin.png")) {
        // Try alternative paths
        const std::vector<std::string> coinPaths = {
            "assets/textures/coin.png",
            "assets/coin.png"
        };
        
        bool loaded = false;
        for (const auto& path : coinPaths) {
            if (texture.loadFromFile(path)) {
                loaded = true;
                break;
            }
        }
        
        if (!loaded) {
            sprite.setSize(sf::Vector2f(25, 25));
            sprite.setFillColor(sf::Color::Yellow);
        } else {
            sprite.setTexture(&texture);
            sprite.setSize(sf::Vector2f(25, 25));
        }
    } else {
        sprite.setTexture(&texture);
        sprite.setSize(sf::Vector2f(25, 25));
    }
    
    sprite.setOrigin(12.5f, 12.5f);
    sprite.setPosition(position);
}

void Coin::update(float deltaTime) {
    if (!collected) {
        // Move coin downward
        position.y += speed * deltaTime * 100;
        
        // Rotate coin
        animationTimer += deltaTime;
        sprite.setRotation(animationTimer * rotationSpeed);
        
        // Update position with rotation
        sprite.setPosition(position);
    }
}

void Coin::draw(sf::RenderWindow& window) {
    if (!collected) {
        window.draw(sprite);
    }
}

sf::FloatRect Coin::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Coin::getPosition() const {
    return position;
}

void Coin::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
    sprite.setPosition(position);
}

bool Coin::isCollected() const {
    return collected;
}

void Coin::collect() {
    collected = true;
}
