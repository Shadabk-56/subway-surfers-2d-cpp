#include "Cone.h"
#include <iostream>

// Cone Constructor (FIXED: Only 2 arguments passed to Obstacle constructor)
Cone::Cone(int lane, float gameSpeed) 
    : Obstacle(lane, gameSpeed) { 

    //std::cout << "Cone created in lane " << lane << std::endl;

    
    float coneWidth = 40.0f; 
    float coneHeight = 60.0f;
    
    
    float rightShift = 40.0f; 
    
   
    position.x += rightShift; 
    
    // Set Cone Dimensions
    sprite.setSize(sf::Vector2f(coneWidth, coneHeight)); 
    
    
    sprite.setPosition(position); 

    
    if (coneTexture.loadFromFile("assets/textures/cone.png")) {
        sprite.setTexture(&coneTexture);
        sprite.setFillColor(sf::Color::White);

        // Origin ko center par set karein
        sprite.setOrigin(coneWidth / 2.0f, coneHeight / 2.0f);
        
        // Final position y adjust karein (Bottom par lane ke liye)
        float finalY = 600.0f - coneHeight;
        sprite.setPosition(position.x, finalY);
        
    } else {
        //std::cout << "ERROR: Cone texture assets/textures/cone.png not found! Using Orange Box." << std::endl;
        //sprite.setFillColor(sf::Color(255, 165, 0)); 
    }
}
void Cone::update(float deltaTime) {
    
    float originalSpeed = speed; 
    speed = originalSpeed * 0.7f; 
    
    
    Obstacle::update(deltaTime); 

    speed = originalSpeed; 
}


void Cone::draw(sf::RenderWindow& window) {
    
    Obstacle::draw(window);
}

bool Cone::checkCollision(const sf::FloatRect& playerBounds) const {

    return Obstacle::checkCollision(playerBounds);
}
