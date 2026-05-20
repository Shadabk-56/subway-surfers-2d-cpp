#include "Train.h"
#include <iostream>

Train::Train(int lane, float gameSpeed) 
    : Obstacle(lane, gameSpeed) {

    // Train PNG load karo
    if (!texture.loadFromFile("assets/textures/train.png")) {
        std::cout << "Failed to load train.png! Using fallback color." << std::endl;
        sprite.setFillColor(sf::Color::Blue);
    } else {
        sprite.setTexture(&texture);
        // Size set karo according to PNG
        sprite.setSize(sf::Vector2f(70, 140)); // 80×60 pixels
        std::cout << "Train PNG loaded successfully!" << std::endl;
    }
}

void Train::update(float deltaTime) {
    position.y += speed * deltaTime * 100;

    sprite.setPosition(position);
}
