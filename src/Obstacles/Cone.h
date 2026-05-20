#ifndef CONE_H
#define CONE_H

#include "Obstacle.h"
#include <SFML/Graphics.hpp>
#include <string>

class Cone : public Obstacle {
private:
    sf::Texture coneTexture; // Cone ki image load karne ke liye
    
public:
    // Constructor: Ab sirf 2 arguments base class ko dega
    Cone(int lane, float gameSpeed); 

    // Virtual functions ko override karna zaroori hai
    void update(float deltaTime) override; 
    void draw(sf::RenderWindow& window) override;
    bool checkCollision(const sf::FloatRect& playerBounds) const override;
};

#endif // CONE_H
