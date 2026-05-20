#include "ShieldPower.h"
#include <iostream>


ShieldPower::ShieldPower(int lane, float gameSpeed) 
    : PowerUp(lane, gameSpeed) {
    
    
    if (shieldTexture.loadFromFile("assets/textures/shield.png")) {
        
        sprite.setTexture(&shieldTexture);
        sprite.setFillColor(sf::Color::White); // Original colors dikhane ke liye
        
        
        sprite.setSize(sf::Vector2f(50, 50)); 
    } else {
        
        //std::cout << "Shield texture missing! Using Color Box." << std::endl;
        sprite.setFillColor(sf::Color(0, 200, 255, 220)); 
        sprite.setOutlineColor(sf::Color::White);
        sprite.setOutlineThickness(3);
        sprite.setSize(sf::Vector2f(35, 35));
    }

    //std::cout << "ShieldPower created in lane " << lane << std::endl;
}

void ShieldPower::activate() {
    PowerUp::activate();
    //std::cout << "Shield ACTIVATED!" << std::endl;
}

void ShieldPower::deactivate() {
    PowerUp::deactivate();
    //std::cout << "Shield DEACTIVATED!" << std::endl;
}

