// src/Obstacles/Barrier.h

#ifndef BARRIER_H
#define BARRIER_H

#include "Obstacle.h"
#include <SFML/Graphics.hpp>
#include <string>

class Barrier : public Obstacle {
private:
    sf::Texture barrierTexture; // 👈 Barrier ki image load karne ke liye
    
public:
    // Constructor: Lane aur gameSpeed ko Obstacle class mein pass karega
    Barrier(int lane, float gameSpeed); 

    // Update, Draw, Collision functions Cone ki tarah override kiye jayenge
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    bool checkCollision(const sf::FloatRect& playerBounds) const override;
    
    bool isLowObstacle() const override { return true; } // Fence is Low Obstacle    
};

#endif // BARRIER_H
