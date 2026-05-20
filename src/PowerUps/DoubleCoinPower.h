#ifndef DOUBLECOINPOWER_H
#define DOUBLECOINPOWER_H

#include "PowerUp.h"
#include <SFML/Graphics.hpp>

class DoubleCoinPower : public PowerUp {
private:
    sf::Texture texture;
    float multiplier;
    float elapsedTime;    // Track elapsed time
    float totalDuration;  // Total duration of effect
    
public:
    DoubleCoinPower(int lane, float gameSpeed);
    
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void activate() override;
    void deactivate() override;
    
    // Getters
    float getMultiplier() const;
    float getTimeLeft() const;      // Get remaining time
    bool isActiveNow() const;       // Check if currently active
};

#endif
