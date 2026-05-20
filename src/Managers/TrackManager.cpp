#include "TrackManager.h"
#include <iostream>
#include <random>
#include <cmath>

// ADD THESE INCLUDES
#include "../PowerUps/ShieldPower.h"
#include "../PowerUps/MagnetPower.h"
#include "../PowerUps/DoubleCoinPower.h"
#include "../PowerUps/JetpackPower.h"

#include "../Obstacles/Cone.h"

TrackManager::TrackManager() 
    : spawnTimer(0.0f), coinSpawnTimer(0.0f), powerUpSpawnTimer(0.0f),
      gameSpeed(2.0f), rng(std::random_device()()) {
}

TrackManager::~TrackManager() {
    // Cleanup obstacles
    for (int i = 0; i < obstacles.getSize(); i++) {
        delete obstacles.get(i);
    }
    // Coin cleanup
    for (int i = 0; i < coins.getSize(); i++) {
        delete coins.get(i);
    }
    // Power-up cleanup
    for (int i = 0; i < powerUps.getSize(); i++) {
        delete powerUps.get(i);
    }
}

void TrackManager::update(float deltaTime) {
    spawnTimer += deltaTime;
    coinSpawnTimer += deltaTime;
    powerUpSpawnTimer += deltaTime;
    
    // Spawn obstacles every 2 seconds
    if (spawnTimer >= 2.0f) {
        spawnObstacle();
        spawnTimer = 0.0f;
    }
    
    // Spawn vertical coin column every 4 seconds
    if (coinSpawnTimer >= 4.0f) {
        spawnVerticalCoinColumn();
        coinSpawnTimer = 0.0f;
    }
    
    // Spawn power-up every 10-15 seconds
    if (powerUpSpawnTimer >= 12.0f) {
        spawnPowerUp();
        powerUpSpawnTimer = 0.0f;
    }
    
    // Update obstacles
    for (int i = 0; i < obstacles.getSize(); i++) {
        obstacles.get(i)->update(deltaTime);
    }
    
    // Update coins
    for (int i = 0; i < coins.getSize(); i++) {
        coins.get(i)->update(deltaTime);
    }
    
    // Update power-ups
    for (int i = 0; i < powerUps.getSize(); i++) {
        powerUps.get(i)->update(deltaTime);
    }
    
    // Cleanup
    cleanupCollectedCoins();
    cleanupUsedPowerUps();
}

void TrackManager::spawnObstacle() {
    std::uniform_int_distribution<int> laneDist(0, 2);
    
    std::uniform_int_distribution<int> typeDist(0, 3); 
    
    int lane = laneDist(rng);
    int type = typeDist(rng);
    
    Obstacle* newObstacle = nullptr;
    
    switch (type) {
        case 0:
            newObstacle = new Train(lane, gameSpeed);
            break;
        case 1:
            newObstacle = new Barrier(lane, gameSpeed);
            break;
        case 2:
            newObstacle = new Fence(lane, gameSpeed);
            break;
        case 3:
            
            newObstacle = new Cone(lane, gameSpeed); 
            //std::cout << "Cone spawned in lane " << lane << std::endl;
            break;
    }
    
    if (newObstacle) {
        obstacles.add(newObstacle);
    }
}

void TrackManager::spawnPowerUp() {
    std::uniform_int_distribution<int> laneDist(0, 2);
    
    std::uniform_int_distribution<int> powerUpTypeDist(0, 3); // 0=Shield, 1=Magnet, 2=DoubleCoin, 3=Jetpack
    
    int lane = laneDist(rng);
    int powerUpType = powerUpTypeDist(rng);
    
    PowerUp* newPowerUp = nullptr;
    
    if (powerUpType == 0) {
        // Create shield power-up
        newPowerUp = new ShieldPower(lane, gameSpeed);
    } 
    else if (powerUpType == 2) {
        // Create Double Coin power-up
        newPowerUp = new DoubleCoinPower(lane, gameSpeed);
    }
    else if (powerUpType == 3) {
        // ðŸš€ CREATE JETPACK POWER-UP (NEW)
        newPowerUp = new JetPackPower(lane, gameSpeed);
    }
    else {
        // Create magnet power-up (type 1)
        newPowerUp = new MagnetPower(lane, gameSpeed);
    }
    
    // Check if position is safe
    if (newPowerUp && isPositionSafeForPowerUp(newPowerUp->getPosition().x, newPowerUp->getPosition().y)) {
        powerUps.add(newPowerUp);
        
        if (powerUpType == 0) {
            //std::cout << "Shield power-up spawned in lane " << lane << std::endl;
        } 
        else if (powerUpType == 2) {
            //std::cout << "Double Coin power-up spawned in lane " << lane << std::endl;
        }
        else if (powerUpType == 3) {
           
            //std::cout << "Jetpack power-up spawned in lane " << lane << std::endl;
        }
        else {
            //std::cout << "Magnet power-up spawned in lane " << lane << std::endl;
        }
    } else if (newPowerUp) {
        delete newPowerUp;
        //std::cout << "Power-up spawn position not safe, skipping" << std::endl;
    }
}
bool TrackManager::isPositionSafeForPowerUp(float x, float y) {
    // Check if there's an obstacle or coin near this position
    for (int i = 0; i < obstacles.getSize(); i++) {
        Obstacle* obstacle = obstacles.get(i);
        sf::Vector2f obsPos = obstacle->getPosition();
        
        float horizontalDist = std::abs(x - obsPos.x);
        float verticalDist = std::abs(y - obsPos.y);
        
        if (horizontalDist < 80.0f && verticalDist < 120.0f) {
            return false;
        }
    }
    
    // Also check distance from existing power-ups
    for (int i = 0; i < powerUps.getSize(); i++) {
        PowerUp* powerUp = powerUps.get(i);
        sf::Vector2f powerUpPos = powerUp->getPosition();
        
        float horizontalDist = std::abs(x - powerUpPos.x);
        float verticalDist = std::abs(y - powerUpPos.y);
        
        if (horizontalDist < 100.0f && verticalDist < 100.0f) {
            return false;
        }
    }
    
    return true;
}

void TrackManager::spawnVerticalCoinColumn() {
    std::uniform_int_distribution<int> coinCountDist(5, 10);
    std::uniform_int_distribution<int> laneDist(0, 2);
    
    int coinCount = coinCountDist(rng);
    int lane = laneDist(rng);
    
    float startY = -50.0f;
    
    std::cout << "Spawning STRAIGHT vertical coin column in lane " << lane 
              << " with " << coinCount << " coins" << std::endl;
    
    // Calculate lane center X position with RIGHT SHIFT
    float laneCenterX = 0.0f;
    float rightShiftAmount = 25.0f;
    
    switch (lane) {
        case 0: laneCenterX = 175 + rightShiftAmount; break;
        case 1: laneCenterX = 375 + rightShiftAmount; break;
        case 2: laneCenterX = 575 + rightShiftAmount; break;
    }
    
    // Perfectly straight vertical line with right shift
    for (int i = 0; i < coinCount; i++) {
        float yOffset = i * -40.0f;
        float coinX = laneCenterX;
        float coinY = startY + yOffset;
        
        // Ensure coin doesn't go outside lane boundaries
        float minX = 0.0f, maxX = 0.0f;
        switch (lane) {
            case 0: minX = 100.0f; maxX = 300.0f; break;
            case 1: minX = 300.0f; maxX = 500.0f; break;
            case 2: minX = 500.0f; maxX = 700.0f; break;
        }
        
        coinX = std::max(minX + 10.0f, std::min(maxX - 10.0f, coinX));
        
        // Check if position is safe (no obstacle at this position)
        if (isPositionSafeForCoin(coinX, coinY)) {
            Coin* newCoin = new Coin(lane, gameSpeed, coinY);
            newCoin->setPosition(coinX, coinY);
            coins.add(newCoin);
            //std::cout << "   Coin #" << (i+1) << " at X: " << coinX << ", Y: " << coinY << std::endl;
        } else {
            // If not safe, try with adjustment
            coinY += 25.0f;
            if (isPositionSafeForCoin(coinX, coinY)) {
                Coin* newCoin = new Coin(lane, gameSpeed, coinY);
                newCoin->setPosition(coinX, coinY);
                coins.add(newCoin);
                //std::cout << "    Adjusted coin #" << (i+1) << " at X: " << coinX << ", Y: " << coinY << std::endl;
            }
        }
    }
    
    //std::cout << " Straight vertical coin column created (shifted right by " << rightShiftAmount << "px)!" << std::endl;
}



// KEEP ONLY THIS ONE DEFINITION
bool TrackManager::isPositionSafeForCoin(float x, float y) {
    // Check if there's an obstacle near this position
    for (int i = 0; i < obstacles.getSize(); i++) {
        Obstacle* obstacle = obstacles.get(i);
        sf::Vector2f obsPos = obstacle->getPosition();
        
        // Check if coin is too close to obstacle
        float horizontalDist = std::abs(x - obsPos.x);
        float verticalDist = std::abs(y - obsPos.y);
        
        // For vertical columns, check both horizontal and vertical proximity
        if (horizontalDist < 60.0f && verticalDist < 100.0f) {
            return false;
        }
    }
    
    return true;
}

void TrackManager::applyMagnetEffect(sf::Vector2f playerPosition, float magnetStrength, float deltaTime) {
    // Attract coins towards player when magnet is active
    for (int i = 0; i < coins.getSize(); i++) {
        Coin* coin = coins.get(i);
        
        if (!coin->isCollected()) {
            sf::Vector2f coinPos = coin->getPosition();
            
            // Calculate distance to player
            float dx = playerPosition.x - coinPos.x;
            float dy = playerPosition.y - coinPos.y;
            float distance = std::sqrt(dx * dx + dy * dy);
            
            // Only attract coins within magnet radius (300 pixels)
            if (distance < 600.0f && distance > 10.0f) {
                // Normalize direction vector
                float invDistance = 1.0f / distance;
                dx *= invDistance;
                dy *= invDistance;
                
                // Calculate attraction force (stronger when closer)
                float attractionForce = magnetStrength * (600.0f - distance) / 600.0f;
                
                // Move coin towards player
                coinPos.x += dx * attractionForce * deltaTime * 100.0f;
                coinPos.y += dy * attractionForce * deltaTime * 100.0f;
                
                coin->setPosition(coinPos.x, coinPos.y);
            }
        }
    }
}

void TrackManager::cleanupCollectedCoins() {
    for (int i = coins.getSize() - 1; i >= 0; i--) {
        if (coins.get(i)->isCollected()) {
            delete coins.get(i);
            coins.remove(i);
        }
    }
}

void TrackManager::cleanupUsedPowerUps() {
    for (int i = powerUps.getSize() - 1; i >= 0; i--) {
        if (powerUps.get(i)->isUsed()) {  // Use the getter method
            delete powerUps.get(i);
            powerUps.remove(i);
        }
    }
}

void TrackManager::draw(sf::RenderWindow& window) {
    // Draw obstacles
    for (int i = 0; i < obstacles.getSize(); i++) {
        obstacles.get(i)->draw(window);
    }
    
    // Draw coins
    for (int i = 0; i < coins.getSize(); i++) {
        coins.get(i)->draw(window);
    }
    
    // Draw power-ups
    for (int i = 0; i < powerUps.getSize(); i++) {
        powerUps.get(i)->draw(window);
    }
}

// Getters
GameList<Obstacle*>& TrackManager::getObstacles() { return obstacles; }
GameList<Coin*>& TrackManager::getCoins() { return coins; }
GameList<PowerUp*>& TrackManager::getPowerUps() { return powerUps; }
float TrackManager::getGameSpeed() const { return gameSpeed; }
