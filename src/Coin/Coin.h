#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>

class Coin {
private:
    sf::Vector2f position;
    int lane;
    sf::RectangleShape sprite;
    sf::Texture texture;
    float speed;
    bool collected;  // To mark if coin is collected
    float animationTimer;  // For rotation animation
    float rotationSpeed;   // How fast coin rotates
    
public:
    Coin(int lane, float gameSpeed, float yPosition = -50.0f);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);
    bool isCollected() const;
    void collect();
    
};

#endif
