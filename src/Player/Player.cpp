#include "Player.h"
#include <iostream>
#include <cmath>
#include <algorithm>

Player::Player() 
    : currentLane(1),
      isJumping(false),
      isSliding(false),
      jumpHeight(0.0f),
      slideTime(0.0f),
      jumpVelocity(0.0f),
      position(375, 400),
      currentAnimationFrame(0),
      animationTimer(0.0f),
      frameDuration(0.1f),  // Faster animation for more frames
      useTexture(false),
      hasMagnet(false),
      magnetTimer(0.0f),
      magnetDuration(10.0f),
      magnetStrength(5.0f),
      hasShield(false),
      shieldTimer(0.0f),
      shieldDuration(10.0f),
      jumpPower(-30.0f),
      gravity(0.7f),
      isDoubleCoinsActive(false),
      doubleCoinTimer(0.0f),
      hasJetpack(false),
      jetpackTimer(0.0f),
      jetpackDuration(15.0f),
      originalY(400.0f)
{
    //std::cout << "=== Loading Player Running Animation (12 Frames) ===" << std::endl;
    
    // Reserve space for 12 frames
    runTextures.reserve(12);
    runSprites.reserve(12);
    
    bool loadedAny = false;
    int framesLoaded = 0;
    
    // Try to load 12 frames with different naming patterns
    for (int i = 1; i <= 12; i++) {
        std::vector<std::string> possiblePaths = {
            // Pattern 1: player_run1.png, player_run2.png, ...
            "assets/textures/player_run" + std::to_string(i) + ".png",
            "assets/textures/player_run_" + std::to_string(i) + ".png",
            
            // Pattern 2: run1.png, run2.png, ...
            "assets/textures/run" + std::to_string(i) + ".png",
            "assets/textures/run_" + std::to_string(i) + ".png",
            
            // Pattern 3: player1.png, player2.png, ...
            "assets/textures/player" + std::to_string(i) + ".png",
            "assets/textures/player_" + std::to_string(i) + ".png",
            
            // Pattern 4: with leading zeros (run_01.png, run_02.png, ...)
            "assets/textures/run_" + (i < 10 ? "0" + std::to_string(i) : std::to_string(i)) + ".png",
            "assets/textures/player_run_" + (i < 10 ? "0" + std::to_string(i) : std::to_string(i)) + ".png",
            
            // Pattern 5: Alternative locations
            "assets/player_run" + std::to_string(i) + ".png",
            "assets/run" + std::to_string(i) + ".png"
        };
        
        sf::Texture texture;
        bool frameLoaded = false;
        
        for (const auto& path : possiblePaths) {
            if (texture.loadFromFile(path)) {
                runTextures.push_back(texture);
                
                // Create sprite for this texture
                sf::Sprite sprite;
                sprite.setTexture(runTextures.back());
                runSprites.push_back(sprite);
                
                //std::cout << "Frame " << i << " loaded: " << path << std::endl;
                frameLoaded = true;
                framesLoaded++;
                loadedAny = true;
                break;
            }
        }
        
        if (!frameLoaded) {
            //std::cout << "Frame " << i << " not found with any naming pattern" << std::endl;
            
            // Create a placeholder texture for missing frames
            sf::Texture placeholder;
            placeholder.create(100, 150);
            runTextures.push_back(placeholder);
            
            sf::Sprite sprite;
            sprite.setTexture(runTextures.back());
            runSprites.push_back(sprite);
        }
    }
    
    if (loadedAny) {
        useTexture = true;
        
        // Set up all sprites
        for (size_t i = 0; i < runSprites.size(); i++) {
            sf::Vector2u texSize = runTextures[i].getSize();
            
            // Only scale if texture is valid
            if (texSize.x > 0 && texSize.y > 0) {
                float scaleX = 50.0f / texSize.x;
                float scaleY = 80.0f / texSize.y;
                
                runSprites[i].setScale(scaleX, scaleY);
                runSprites[i].setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
                runSprites[i].setPosition(position.x + 25, position.y + 40);
                runSprites[i].setRotation(0.0f);
            }
        }
        
        /*std::cout << "======================================" << std::endl;
        std::cout << "🎬 Animation Summary:" << std::endl;
        std::cout << "Frames attempted: 12" << std::endl;
        std::cout << "Frames loaded: " << framesLoaded << std::endl;
        std::cout << "Animation speed: " << (1.0f / frameDuration) << " fps" << std::endl;
        std::cout << "======================================" << std::endl;*/
        
        if (framesLoaded == 12) {
            std::cout << "Perfect! All 12 frames loaded!" << std::endl;
        } else if (framesLoaded >= 6) {
            std::cout << "Good! " << framesLoaded << " frames loaded" << std::endl;
        } else {
            std::cout << "Only " << framesLoaded << " frames loaded" << std::endl;
            std::cout << "   Check your PNG files naming and location" << std::endl;
        }
        
    } else {
        std::cout << "No animation frames loaded! Using fallback rectangle." << std::endl;
        useTexture = false;
        
        fallbackShape.setSize(sf::Vector2f(50, 80));
        fallbackShape.setFillColor(sf::Color::Green);
        fallbackShape.setPosition(position);
        fallbackShape.setOrigin(25, 40);
        fallbackShape.setPosition(position.x + 25, position.y + 40);
        fallbackShape.setRotation(0.0f);
    }
    
    // ============ SHIELD CODE ============
    if (shieldTexture.loadFromFile("assets/textures/shield.png")) {
        //std::cout << " Shield PNG loaded successfully!" << std::endl;
        shieldSprite.setTexture(shieldTexture);
        
        sf::Vector2u size = shieldTexture.getSize();
        shieldSprite.setOrigin(size.x / 2.0f, size.y / 2.0f);
        shieldSprite.setScale(0.6f, 0.6f);
        shieldSprite.setColor(sf::Color(255, 255, 255, 220)); 
    } else {
        //std::cout << "Shield PNG not found!" << std::endl;
    }
    
    // ============ DOUBLE COIN AURA ============
    doubleCoinAura.setRadius(55.0f); 
    doubleCoinAura.setOrigin(55.0f, 55.0f);
    doubleCoinAura.setFillColor(sf::Color(255, 215, 0, 80)); 
    doubleCoinAura.setOutlineColor(sf::Color(255, 215, 0, 200)); 
    doubleCoinAura.setOutlineThickness(3.0f);
    //std::cout << "Double Coin Aura initialized!" << std::endl;
    
    //std::cout << "Player initialized at position: " << position.x << ", " << position.y << std::endl;
}
void Player::moveLeft() {
    if (currentLane > 0 && !isJumping && !isSliding) {
        currentLane--;
        if (currentLane == 0) position.x = 175;
        else if (currentLane == 1) position.x = 375;
        else if (currentLane == 2) position.x = 575;
        
        // Update all sprite positions
        for (size_t i = 0; i < runSprites.size(); i++) {
            runSprites[i].setPosition(position.x + 25, position.y + 40);
        }
        fallbackShape.setPosition(position.x + 25, position.y + 40);
        
        //std::cout << "Player moved to lane " << currentLane << " at X: " << position.x << std::endl;
    }
}

void Player::moveRight() {
    if (currentLane < 2 && !isJumping && !isSliding) {
        currentLane++;
        if (currentLane == 0) position.x = 175;
        else if (currentLane == 1) position.x = 375;
        else if (currentLane == 2) position.x = 575;
        
        // Update all sprite positions
        for (size_t i = 0; i < runSprites.size(); i++) {
            runSprites[i].setPosition(position.x + 25, position.y + 40);
        }
        fallbackShape.setPosition(position.x + 25, position.y + 40);
        
        //std::cout << "Player moved to lane " << currentLane << " at X: " << position.x << std::endl;
    }
}
void Player::jump() {
    if (!isJumping && !isSliding) {
        isJumping = true;
        jumpVelocity = jumpPower;
        //std::cout << "JUMP FUNCTION CALLED!" << std::endl;
    }
}

void Player::slide() {
    if (!isJumping && !isSliding) {
        isSliding = true;
        slideTime = 1.0f;
        //std::cout << "Player sliding!" << std::endl;
    }
}

void Player::update(float deltaTime) {
    // Update magnet timer
    if (hasMagnet) {
        magnetTimer -= deltaTime;
        if (magnetTimer <= 0.0f) {
            hasMagnet = false;
            //std::cout << "Magnet effect ended!" << std::endl;
        }
    }
    
    // Update shield timer
    if (hasShield) {
        shieldTimer -= deltaTime;
        shieldSprite.rotate(90.0f * deltaTime);

        if (shieldTimer <= 0.0f) {
            hasShield = false;
            //std::cout << " Shield expired!" << std::endl;
        }
    }
    
    // Update jetpack timer
    if (hasJetpack) {
        jetpackTimer -= deltaTime;
        
        if (!isJumping) {
            position.y = 250.0f;  // Flying height
        }
        
        if (jetpackTimer <= 0.0f) {
            deactivateJetpack();
        }
    }
    
    // ============ DOUBLE COIN EFFECT ============
    if (isDoubleCoinsActive) {
        static float doubleCoinPulseTimer = 0.0f;
        doubleCoinPulseTimer += deltaTime * 5.0f;
        
        float pulseScale = 1.0f + sin(doubleCoinPulseTimer) * 0.1f;
        doubleCoinAura.setScale(pulseScale, pulseScale);
        doubleCoinAura.setPosition(position.x + 50, position.y + 80); 
        
        doubleCoinTimer -= deltaTime;
        
        if (doubleCoinTimer <= 0.0f) {
            isDoubleCoinsActive = false;
            //std::cout << "Double Coins power-up deactivated." << std::endl;
        }
    } else {
        doubleCoinAura.setScale(1.0f, 1.0f);
    }
    
    // ANIMATION UPDATE FOR 12 FRAMES
    if (useTexture && runTextures.size() > 1) {
        // Adjust animation speed based on player state
        float currentFrameDuration = frameDuration;
        
        if (isJumping) {
            currentFrameDuration = 0.2f;  // Slower in air
        } else if (isSliding) {
            currentFrameDuration = 0.25f; // Slower sliding
        } else if (hasJetpack) {
            currentFrameDuration = 0.15f; // Normal speed flying
        } else {
            currentFrameDuration = 0.08f; // Fast running on ground
        }
        
        // Update animation timer
        animationTimer += deltaTime;
        
        // Change frame when timer exceeds frame duration
        if (animationTimer >= currentFrameDuration) {
            currentAnimationFrame = (currentAnimationFrame + 1) % runTextures.size();
            animationTimer = 0.0f;
        }
    }
    
    // Jump physics
    if (isJumping) {
        position.y += jumpVelocity;
        jumpVelocity += gravity;
        
        if (position.y >= 400) {
            position.y = 400;
            isJumping = false;
            jumpVelocity = 0.0f;
            currentAnimationFrame = 0;
            animationTimer = 0.0f;
            //std::cout << "Player landed!" << std::endl;
        }
    }
    
    // Slide timer
    if (isSliding) {
        slideTime -= deltaTime;
        if (slideTime <= 0) {
            isSliding = false;
            currentAnimationFrame = 0;
            animationTimer = 0.0f;
        }
    }
    
    // Add subtle bobbing effect while running on ground
    if (!isJumping && !isSliding && !hasJetpack) {
        float bobOffset = std::sin(animationTimer * 20.0f) * 2.0f;
        position.y = 400 + bobOffset;
    }
    
    // Update visual positions
    if (useTexture && currentAnimationFrame < (int)runSprites.size()) {
        runSprites[currentAnimationFrame].setPosition(position.x + 25, position.y + 40);
        runSprites[currentAnimationFrame].setRotation(0.0f);
    } else if (!useTexture) {
        fallbackShape.setPosition(position.x + 25, position.y + 40);
        fallbackShape.setRotation(0.0f);
    }
}
void Player::draw(sf::RenderWindow& window) {
    // Draw Double Coin effect
    if (isDoubleCoinsActive) {
        window.draw(doubleCoinAura);
    }
    
    // Draw Shield
    if (hasShield) {
        sf::CircleShape shieldCircle(50);
        shieldCircle.setFillColor(sf::Color(0, 255, 255, 50));
        shieldCircle.setOutlineColor(sf::Color(0, 255, 255, 200));
        shieldCircle.setOutlineThickness(3);
        shieldCircle.setOrigin(50, 50);
        shieldCircle.setPosition(position.x + 25, position.y + 40);
        window.draw(shieldCircle);
    }
    
    // Draw Player
    if (useTexture && currentAnimationFrame < (int)runSprites.size()) {
        window.draw(runSprites[currentAnimationFrame]);
    } else if (!useTexture) {
        window.draw(fallbackShape);
    }
}
// Getters
int Player::getCurrentLane() const { 
    return currentLane; 
}

bool Player::getIsJumping() const { 
    return isJumping; 
}

bool Player::getIsSliding() const { 
    return isSliding; 
}

sf::Vector2f Player::getPosition() const { 
    return position; 
}

sf::FloatRect Player::getBounds() const {
    if (useTexture) {
        return runSprites[currentAnimationFrame].getGlobalBounds();
    } else {
        return fallbackShape.getGlobalBounds();
    }
}

// Setters
void Player::setPosition(const sf::Vector2f& newPosition) { 
    position = newPosition; 
    for (int i = 0; i < 2; i++) {
        runSprites[i].setPosition(position.x + 25, position.y + 40);
        runSprites[i].setRotation(0.0f);
    }
    fallbackShape.setPosition(position.x + 25, position.y + 40);
}

// Animation control
void Player::setAnimationSpeed(float speed) {
    frameDuration = 1.0f / speed;
}

void Player::resetAnimation() {
    currentAnimationFrame = 0;
    animationTimer = 0.0f;
}

// Magnet functions
void Player::activateMagnet() {
    hasMagnet = true;
    magnetTimer = magnetDuration;
    //std::cout << "Magnet activated for " << magnetDuration << " seconds!" << std::endl;
}

bool Player::hasActiveMagnet() const {
    return hasMagnet && magnetTimer > 0.0f;
}

float Player::getMagnetStrength() const {
    return magnetStrength;
}

float Player::getMagnetTimeLeft() const {
    return magnetTimer;
}

// Shield functions (NEW)
void Player::activateShield() {
    hasShield = true;
    shieldTimer = shieldDuration;
    //std::cout << "Shield activated for " << shieldDuration << " seconds!" << std::endl;
}

void Player::deactivateShield() {
    hasShield = false;
    shieldTimer = 0.0f;
    //std::cout << "Shield removed after collision!" << std::endl;
}

bool Player::isShielded() const {
    return hasShield && shieldTimer > 0.0f;
}

float Player::getShieldTimeLeft() const {
    return shieldTimer;
}

// ============ DOUBLE COIN FUNCTIONS START ============

void Player::activateDoubleCoins(float duration) {
    isDoubleCoinsActive = true;
    doubleCoinTimer = duration; // Set duration (e.g., 10 seconds)
    //std::cout << " Double Coin Power Up Activated for " << duration << " seconds!" << std::endl;
}

// Redefinition error ko theek karne ke liye yahan sirf definition rakhi hai.
bool Player::getIsDoubleCoinsActive() const {
    return isDoubleCoinsActive;
}

float Player::getDoubleCoinTimeLeft() const {
    return doubleCoinTimer;
}

// ============ DOUBLE COIN FUNCTIONS END ============

// ============ ðŸš€ JETPACK FUNCTIONS START ============
void Player::activateJetpack() {
    hasJetpack = true;
    jetpackTimer = jetpackDuration;
    originalY = position.y;  // Current position save karo
    //std::cout << "Jetpack activated for " << jetpackDuration << " seconds!" << std::endl;
}

void Player::deactivateJetpack() {
    hasJetpack = false;
    jetpackTimer = 0.0f;
    
    // Player ko wapis ground pe le jao (smoothly)
    if (!isJumping) {
        position.y = 400.0f;
    }
    
    //std::cout << "ðŸš€ Jetpack expired! Back to ground." << std::endl;
}

bool Player::isJetpackActive() const {
    return hasJetpack && jetpackTimer > 0.0f;
}

float Player::getJetpackTimeLeft() const {
    return jetpackTimer;
}
// ============ JETPACK FUNCTIONS END ============
