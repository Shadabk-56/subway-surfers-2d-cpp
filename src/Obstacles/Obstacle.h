#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle {
protected:
    sf::Vector2f position;
    int lane;
    sf::RectangleShape sprite;
    float speed;
    
public:
    Obstacle(int lane, float gameSpeed);
    virtual ~Obstacle() = default;
    
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window);
    virtual bool checkCollision(const sf::FloatRect& playerBounds) const;
    
    virtual bool isLowObstacle() const { return false; }   
    // Getters
    sf::Vector2f getPosition() const;
    int getLane() const;
    sf::FloatRect getBounds() const;
};

#endif
