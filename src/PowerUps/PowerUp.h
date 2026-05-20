#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>

class PowerUp {
protected:
    sf::Vector2f position;
    int lane;
    sf::RectangleShape sprite;
    float speed;
    bool isActiveFlag;    // Changed from 'active' to avoid conflict with method
    bool isUsedFlag;      // Changed from 'used' to avoid conflict with method
    float duration;
    
public:
    PowerUp(int lane, float gameSpeed);
    virtual ~PowerUp() {}
    
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow& window);
    virtual void activate();
    virtual void deactivate();
    
    
    
    // Getters
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    bool isActive() const;    // Getter method
    bool isUsed() const;      // Getter method
    void setUsed(bool value);
    
    // Setters
    void setPosition(float x, float y);
};

#endif
