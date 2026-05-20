#include "Obstacle.h"

Obstacle::Obstacle(int lane, float gameSpeed) 
    : lane(lane), speed(gameSpeed) {
    
    if (lane == 0) position.x = 160;   // Left lane center
    else if (lane == 1) position.x = 360; // Middle lane center
    else if (lane == 2) position.x = 560; // Right lane center
    
    position.y = -50; // Start above screen
    
    sprite.setSize(sf::Vector2f(50, 50));
    sprite.setPosition(position);
}



void Obstacle::update(float deltaTime) {
    
    position.y += speed * deltaTime * 300.0f; 
    
    
    sprite.setPosition(position);
}
// ==========================================

void Obstacle::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Obstacle::checkCollision(const sf::FloatRect& playerBounds) const {
    return getBounds().intersects(playerBounds);
}

// Getters
sf::Vector2f Obstacle::getPosition() const { return position; }
int Obstacle::getLane() const { return lane; }
sf::FloatRect Obstacle::getBounds() const { 
    return sprite.getGlobalBounds();
}
