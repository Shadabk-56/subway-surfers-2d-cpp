#ifndef TRAIN_H
#define TRAIN_H

#include "Obstacle.h"

class Train : public Obstacle {
private:
    sf::Texture texture;
    
public:
    Train(int lane, float gameSpeed);
    void update(float deltaTime) override;
    
    bool isLowObstacle() const override { return false; } // Train is NOT a Low Obstacle    
};

#endif
