#ifndef MAGNETPOWER_H
#define MAGNETPOWER_H

#include "PowerUp.h"
#include <SFML/Graphics.hpp>

class MagnetPower : public PowerUp {
private:
    sf::Texture texture;
    
public:
    MagnetPower(int lane, float gameSpeed);
    
    // Override methods from PowerUp
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void activate() override;
    void deactivate() override;
    
};

#endif
