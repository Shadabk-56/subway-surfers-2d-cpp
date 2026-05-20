// src/Obstacles/Barrier.cpp

#include "Barrier.h"
#include <iostream>

// Barrier Constructor
Barrier::Barrier(int lane, float gameSpeed) 
    : Obstacle(lane, gameSpeed) { 

    //std::cout << "Barrier created in lane " << lane << std::endl;

    
    float barrierWidth = 80.0f; 
    float barrierHeight = 40.0f;
    
    
    float rightShift = 45.0f; 

    
    position.x += rightShift; 

    // Set Barrier Dimensions
    sprite.setSize(sf::Vector2f(barrierWidth, barrierHeight)); 
    
  
    sprite.setPosition(position); 

    
    if (barrierTexture.loadFromFile("assets/textures/barrier.png")) {
        sprite.setTexture(&barrierTexture);
        sprite.setFillColor(sf::Color::White); 
        
        // Origin ko center par set karein
        sprite.setOrigin(barrierWidth / 2.0f, barrierHeight / 2.0f);
        
        // Final position y adjust karein (Bottom par lane ke liye)
        float finalY = 600.0f - barrierHeight;
        sprite.setPosition(position.x, finalY);
        
    } else {
        //std::cout << "ERROR: Barrier texture assets/textures/barrier.png not found! Using default color." << std::endl;
        sprite.setFillColor(sf::Color::Red); // Fallback color
    }
}

void Barrier::update(float deltaTime) {
  
    float originalSpeed = speed;
    speed = originalSpeed * 0.4f; 
    
    
    Obstacle::update(deltaTime); 
    

    speed = originalSpeed;
}

void Barrier::draw(sf::RenderWindow& window) {
    Obstacle::draw(window);
}

bool Barrier::checkCollision(const sf::FloatRect& playerBounds) const {
    return Obstacle::checkCollision(playerBounds);
}
