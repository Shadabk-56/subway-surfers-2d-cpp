#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <string>

class ScoreManager {
private:
    int score;
    int coins;
    int highScore;
    float scoreTimer;
    
    // Coin multiplier system
    float coinMultiplier;
    float coinMultiplierTimer;
    bool isCoinMultiplierActive;
    
public:
    ScoreManager();
    
    void update(float deltaTime);
    void addCoin();
    void addScore(int points);
    
    // Coin multiplier functions
    void activateCoinMultiplier(float multiplier, float duration);
    
    // Getters
    int getScore() const;
    int getCoins() const;
    int getHighScore() const;
    
    // Multiplier getters
    float getCoinMultiplier() const;
    float getCoinMultiplierTimeLeft() const;
    bool isCoinMultiplierActiveNow() const;
    
    void saveHighScore(const std::string& playerName);
    void loadHighScore();
};

#endif
