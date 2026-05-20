#ifndef FENCE_H
#define FENCE_H

#include "Obstacle.h"

class Fence : public Obstacle {
private:
    sf::Texture texture;  // ✅ TEXTURE ADD KARO
    
public:
    Fence(int lane, float gameSpeed);
    void update(float deltaTime) override;
    
    bool isLowObstacle() const override { return true; } // Fence is Low Obstacle    
};

#endif
