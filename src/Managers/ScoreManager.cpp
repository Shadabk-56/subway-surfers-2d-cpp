#include "ScoreManager.h"
#include <iostream>
#include <fstream>

ScoreManager::ScoreManager() 
    : score(0), coins(0), highScore(0), scoreTimer(0.0f),
      coinMultiplier(1.0f), coinMultiplierTimer(0.0f),
      isCoinMultiplierActive(false) {
    loadHighScore();
}

void ScoreManager::update(float deltaTime) {
    // Add score over time
    scoreTimer += deltaTime;
    if (scoreTimer >= 0.1f) {
        score += 1;
        scoreTimer = 0.0f;
    }
    
    // Update coin multiplier timer
    if (isCoinMultiplierActive) {
        coinMultiplierTimer -= deltaTime;
        if (coinMultiplierTimer <= 0.0f) {
            isCoinMultiplierActive = false;
            coinMultiplier = 1.0f;
            //std::cout << "Coin multiplier ended!" << std::endl;
        }
    }
}

// KEEP ONLY THIS ONE addCoin() FUNCTION - REMOVE THE DUPLICATE
void ScoreManager::addCoin() {
    int coinsToAdd = 1;
    
    //std::cout << "Coin collection attempt:" << std::endl;
    //std::cout << "   Multiplier active: " << (isCoinMultiplierActive ? "YES" : "NO") << std::endl;
    
    // Apply multiplier if active
    if (isCoinMultiplierActive) {
        coinsToAdd = static_cast<int>(coinsToAdd * coinMultiplier);
        //std::cout << "   🚀 WITH MULTIPLIER: " << coinsToAdd << " coins!" << std::endl;
        //std::cout << "   Multiplier value: " << coinMultiplier << "x" << std::endl;
        //std::cout << "   Time left: " << coinMultiplierTimer << " seconds" << std::endl;
    } else {
        //std::cout << "   WITHOUT MULTIPLIER: " << coinsToAdd << " coin" << std::endl;
    }
    
    coins += coinsToAdd;
    
    // Add score for coin (50 points per coin)
    int coinScore = 50 * coinsToAdd;
    score += coinScore;
    
    //std::cout << "   Total coins: " << coins << std::endl;
    //std::cout << "   Score added: " << coinScore << std::endl;
}

void ScoreManager::addScore(int points) {
    score += points;
}

void ScoreManager::activateCoinMultiplier(float multiplier, float duration) {
    //std::cout << " ACTIVATING COIN MULTIPLIER!" << std::endl;
    //std::cout << "   Multiplier: " << multiplier << "x" << std::endl;
    //std::cout << "   Duration: " << duration << " seconds" << std::endl;
    
    coinMultiplier = multiplier;
    coinMultiplierTimer = duration;
    isCoinMultiplierActive = true;
    
    /*std::cout << "   Status: coinMultiplier=" << coinMultiplier 
              << ", timer=" << coinMultiplierTimer 
              << ", isActive=" << isCoinMultiplierActive << std::endl;*/
}

// Getters
int ScoreManager::getScore() const { return score; }
int ScoreManager::getCoins() const { return coins; }
int ScoreManager::getHighScore() const { return highScore; }

float ScoreManager::getCoinMultiplier() const { 
    return isCoinMultiplierActive ? coinMultiplier : 1.0f; 
}

float ScoreManager::getCoinMultiplierTimeLeft() const { 
    return std::max(0.0f, coinMultiplierTimer); 
}

bool ScoreManager::isCoinMultiplierActiveNow() const { 
    return isCoinMultiplierActive && coinMultiplierTimer > 0.0f; 
}

void ScoreManager::saveHighScore(const std::string& playerName) {
    if (score > highScore) {
        highScore = score;
        std::ofstream file("highscore.txt");
        if (file.is_open()) {
            file << playerName << std::endl;
            file << highScore << std::endl;
            file.close();
            //std::cout << "New high score saved: " << highScore << std::endl;
        }
    }
}

void ScoreManager::loadHighScore() {
    std::ifstream file("highscore.txt");
    if (file.is_open()) {
        std::string name;
        file >> name >> highScore;
        file.close();
        //std::cout << "High score loaded: " << highScore << std::endl;
    }
}
