#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include "../Player/Player.h"
#include <SFML/Audio.hpp>
#include "../Managers/TrackManager.h"
#include "../Managers/ScoreManager.h"

// Game State Enum - 2 NAYE STATES ADD KIYE
enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAMEOVER,
    LEADERBOARD,      // NEW
    INSTRUCTIONS      // NEW
};

// Simple Button Structure
struct MenuButton {
    sf::RectangleShape shape;
    sf::Text text;
    sf::Color normalColor;
    sf::Color hoverColor;
    bool isHovered;
    
    MenuButton() : normalColor(sf::Color(70, 130, 180)), 
                   hoverColor(sf::Color(100, 160, 210)),
                   isHovered(false) {}
    
    bool contains(sf::Vector2f point) {
        return shape.getGlobalBounds().contains(point);
    }
    
    void updateHover(sf::Vector2f mousePos) {
        isHovered = contains(mousePos);
        shape.setFillColor(isHovered ? hoverColor : normalColor);
    }
};

class GameEngine {
private:
    sf::RenderWindow window;
    Player player;
    TrackManager trackManager;
    ScoreManager scoreManager;
    
    //Sounds 
    sf::Music backgroundMusic;
    sf::SoundBuffer collisionBuffer;
    sf::SoundBuffer coinBuffer;
    sf::SoundBuffer powerupBuffer;
    
    sf::Sound collisionSound;
    sf::Sound coinSound;
    sf::Sound powerupSound;
    
    // Game State
    GameState currentState;
    bool isGameOver;
    
    sf::Clock gameClock;
    sf::Font font;
    float gameSpeed;
    
    // Textures and Sprites
    sf::Texture laneTexture;
    sf::Sprite leftLaneSprite;
    sf::Sprite middleLaneSprite;
    sf::Sprite rightLaneSprite;
    
    // Background
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    
    // Jetpack texture (NEW)
    sf::Texture jetpackTexture;
    
    // Menu Components
    sf::Text menuTitle;
    sf::Text menuSubtitle;
    
    // MAIN MENU BUTTONS - 4 OPTIONS
    MenuButton startGameButton;      
    MenuButton leaderboardButton;    // NEW
    MenuButton instructionsButton;   // NEW
    MenuButton exitButton;           
    
    // OTHER BUTTONS
    MenuButton resumeButton;
    MenuButton menuButton;
    MenuButton backButton;           // NEW - Leaderboard aur Instructions se wapis
    
    // Game functions
    void handleEvents();
    void update(float deltaTime);
    void render();
    void checkCollisions();
    void gameOver();
    void drawHUD();
    void drawTrack();
    void drawBackground();
    void drawColoredLanesFallback();
    
    // Menu functions
    void initializeMenu();
    void handleMenuEvents();
    void handlePauseEvents();
    void handleGameOverEvents();
    void handleLeaderboardEvents();     // NEW
    void handleInstructionsEvents();    // NEW
    void renderMenu();
    void renderPauseMenu();
    void renderGameOver();
    void renderLeaderboard();           // NEW
    void renderInstructions();          // NEW
    void startGame();
    void resetGame();
    void pauseGame();
    void resumeGame();
    void returnToMenu();
    void showLeaderboard();             // NEW
    void showInstructions();            // NEW
    
    // Helper functions
    bool loadTextures();
    bool loadBackground();
    bool loadFont();
    bool fontLoaded() const;
    MenuButton createButton(float x, float y, float width, float height, const std::string& label);
    
public:
    GameEngine();
    void run();
    void playCollisionSound();
    void playCoinSound();
    void playPowerupSound();
};

#endif
