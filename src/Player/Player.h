#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>

class Player {
private:
    int currentLane;
    bool isJumping;
    bool isSliding;
    float jumpHeight;
    float slideTime;
    float jumpVelocity;
    sf::Vector2f position;
    
    // Animation variables - CHANGED TO VECTOR FOR 12 FRAMES
    std::vector<sf::Texture> runTextures;  // Changed from array[2] to vector
    std::vector<sf::Sprite> runSprites;    // Changed from array[2] to vector
    int currentAnimationFrame;
    float animationTimer;
    float frameDuration;
    
    // Fallback
    sf::RectangleShape fallbackShape;
    bool useTexture;
    
    // Magnet power-up
    bool hasMagnet;
    float magnetTimer;
    float magnetDuration;
    float magnetStrength;
    
    // SHIELD VISUALS
    sf::Texture shieldTexture; // Image hold karega
    sf::Sprite shieldSprite;   // Image ko display karega
 
    sf::CircleShape doubleCoinAura;
    
    // Jump physics
    float jumpPower;
    float gravity;
 
    // ============ 💰 DOUBLE COIN ADDITIONS START ============
    bool isDoubleCoinsActive; // Double coin effect on/off
    float doubleCoinTimer;    // Double coin remaining time
    // ============ 💰 DOUBLE COIN ADDITIONS END ============
    
    // Jetpack power-up (NEW)
    bool hasJetpack;
    float jetpackTimer;
    float jetpackDuration;
    float originalY;  // Player ki original Y position save karne ke liye    
    
    // Shield power-up (NEW)
    bool hasShield;
    float shieldTimer;
    float shieldDuration;
 
public:
    Player();
 
    // Movement functions
    void moveLeft();
    void moveRight();
    void jump();
    void slide();
    
    // Update and render
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    
    // Getters
    int getCurrentLane() const;
    bool getIsJumping() const;
    bool getIsSliding() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    
    // Setters
    void setPosition(const sf::Vector2f& newPosition);
    
    // Animation control
    void setAnimationSpeed(float speed);
    void resetAnimation();
    
    // Magnet functions
    void activateMagnet();
    bool hasActiveMagnet() const;
    float getMagnetStrength() const;
    float getMagnetTimeLeft() const;
    
    // Shield functions (NEW)
    void activateShield();
    void deactivateShield();
    bool isShielded() const;
    float getShieldTimeLeft() const;
 
    // ============ 💰 DOUBLE COIN ADDITIONS START ============
    void activateDoubleCoins(float duration);
    bool getIsDoubleCoinsActive() const;
    float getDoubleCoinTimeLeft() const;
    // ============ 💰 DOUBLE COIN ADDITIONS END ============
    
    bool isJumpingActive() const { return isJumping; }
    
    // Jetpack functions (NEW)
    void activateJetpack();
    void deactivateJetpack();
    bool isJetpackActive() const;
    float getJetpackTimeLeft() const;
};

#endif
