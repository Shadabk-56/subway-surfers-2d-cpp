#ifndef TRACKMANAGER_H
#define TRACKMANAGER_H

#include "../Obstacles/Obstacle.h"
#include "../Obstacles/Train.h"
#include "../Obstacles/Barrier.h"
#include "../Obstacles/Cone.h"
#include "../Obstacles/Fence.h"
#include "../Coin/Coin.h"
#include "../PowerUps/MagnetPower.h"
#include "../Utils/GameList.h"
#include <random>
#include <vector>

class TrackManager {
private:
    GameList<Obstacle*> obstacles;
    GameList<Coin*> coins;
    GameList<PowerUp*> powerUps;  // NEW: For power-ups
    float spawnTimer;
    float coinSpawnTimer;
    float powerUpSpawnTimer;  // NEW: Separate timer for power-ups
    float gameSpeed;
    std::mt19937 rng;
    
    void spawnObstacle();
    void spawnVerticalCoinColumn();
    void spawnPowerUp();  // NEW: Spawn power-ups
    bool isPositionSafeForCoin(float x, float y);
    bool isPositionSafeForPowerUp(float x, float y);
    
public:
    TrackManager();
    ~TrackManager();
    
    void update(float deltaTime);
    void increaseSpeed();
    void draw(sf::RenderWindow& window);
    
    // Getters
    GameList<Obstacle*>& getObstacles();
    GameList<Coin*>& getCoins();
    GameList<PowerUp*>& getPowerUps();  // NEW: Get power-ups
    float getGameSpeed() const;
    
    // Cleanup
    void cleanupCollectedCoins();
    void cleanupUsedPowerUps();  // NEW: Clean up used power-ups
    
    // Magnet functionality
    void applyMagnetEffect(sf::Vector2f playerPosition, float magnetStrength, float deltaTime);
    
};

#endif
