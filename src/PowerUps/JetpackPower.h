#ifndef JETPACKPOWER_H
#define JETPACKPOWER_H

#include "PowerUp.h"
#include <SFML/Graphics.hpp>

class JetPackPower : public PowerUp {
private:
    sf::Texture texture;
    float elapsedTime;    // Track elapsed time
    float totalDuration;  // Total duration of effect
    
public:
    // Constructor (Default duration 15.0f)
    JetPackPower(int lane, float gameSpeed);
    
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void activate() override;
    void deactivate() override;
    
    // Getters
    float getTimeLeft() const;      // Get remaining time
    bool isActiveNow() const;       // Check if currently activ
    
};

#endif
