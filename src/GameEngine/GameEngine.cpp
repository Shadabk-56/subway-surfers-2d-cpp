#include "GameEngine.h"
#include "../PowerUps/ShieldPower.h"
#include "../PowerUps/JetpackPower.h"
#include "../PowerUps/MagnetPower.h"
#include "../PowerUps/DoubleCoinPower.h"
#include <iostream>
#include <fstream>
#include <algorithm>

GameEngine::GameEngine() 
    : window(sf::VideoMode(800, 600), "Subway Surfers 2D"), 
      currentState(MENU),  // Start with menu
      isGameOver(false),
      gameSpeed(1.0f) {
    
    /*std::cout << "==================================" << std::endl;
    std::cout << "   SUBWAY SURFERS 2D - LOADING   " << std::endl;
    std::cout << "==================================" << std::endl;*/
    
    // Load background first
    if (loadBackground()) {
        std::cout << "Background loaded successfully!" << std::endl;
    } else {
        std::cout << "Background not loaded. Using solid color." << std::endl;
    }
    
    // Load font
    if (!loadFont()) {
        std::cout << "Font load failed! Game will run without text." << std::endl;
    }
    
    // Load textures
    if (!loadTextures()) {
        std::cout << "Lane texture failed to load! Using colored lanes." << std::endl;
    }
    
        // Load jetpack texture
    if (jetpackTexture.loadFromFile("assets/textures/jetpack.png")) {
        std::cout << "Jetpack texture loaded!" << std::endl;
    } else {
        std::cout << "Jetpack texture not found! Using fallback." << std::endl;
    }
    
    // Initialize menu
    initializeMenu();
    
    /*std::cout << "Game initialized successfully!" << std::endl;
    std::cout << "   Controls: A/D = Left/Right" << std::endl;
    std::cout << "             W = Jump, S = Slide" << std::endl;
    std::cout << "             Arrow keys also work" << std::endl;
    std::cout << "             ESC = Pause/Menu" << std::endl;
    std::cout << "==================================" << std::endl;
    
    
    std::cout << "=== Loading Sounds ===" << std::endl;*/
    
    // Background Music
    if (backgroundMusic.openFromFile("assets/sounds/background.ogg")) {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(30);
        std::cout << "Background music loaded!" << std::endl;
    }
    
    // Collision Sound
    if (collisionBuffer.loadFromFile("assets/sounds/collision.wav")) {
        collisionSound.setBuffer(collisionBuffer);
        collisionSound.setVolume(70);
        std::cout << "Collision sound loaded!" << std::endl;
    }
    
    // Coin Sound
    if (coinBuffer.loadFromFile("assets/sounds/coin.wav")) {
        coinSound.setBuffer(coinBuffer);
        coinSound.setVolume(50);
        std::cout << "Coin sound loaded!" << std::endl;
    }
    
    // Powerup Sound
    if (powerupBuffer.loadFromFile("assets/sounds/powerup.wav")) {
        powerupSound.setBuffer(powerupBuffer);
        powerupSound.setVolume(60);
        std::cout << "Powerup sound loaded!" << std::endl;
    }
    
    
}

bool GameEngine::loadBackground() {
    const std::vector<std::string> bgPaths = {
        "assets/textures/background.png",
        "assets/textures/bg.png",
        "assets/background.png",
        "assets/bg.png"
    };
    
    for (const auto& path : bgPaths) {
        if (backgroundTexture.loadFromFile(path)) {
            backgroundSprite.setTexture(backgroundTexture);
            
            sf::Vector2u bgSize = backgroundTexture.getSize();
            sf::Vector2u windowSize = window.getSize();
            
            float scaleX = (float)windowSize.x / bgSize.x;
            float scaleY = (float)windowSize.y / bgSize.y;
            backgroundSprite.setScale(scaleX, scaleY);
            
            return true;
        }
    }
    return false;
}

bool GameEngine::loadFont() {
    const std::vector<std::string> fontPaths = {
        "assets/fonts/Roboto.ttf",
        "assets/fonts/roboto.ttf", 
        "assets/fonts/Roboto-Regular.ttf",
        "assets/fonts/arial.ttf",
        "assets/fonts/LiberationSans-Regular.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
    };
    
    for (const auto& path : fontPaths) {
        if (font.loadFromFile(path)) {
            std::cout << "Font loaded: " << path << std::endl;
            return true;
        }
    }
    
    std::cout << "All font paths failed! Using fallback graphics." << std::endl;
    return false;
}

bool GameEngine::loadTextures() {
    if (!laneTexture.loadFromFile("assets/textures/lane.png")) {
        std::cout << "Failed to load lane.png!" << std::endl;
        
        const std::vector<std::string> lanePaths = {
            "assets/lane.png",
            "assets/textures/track.png",
            "assets/track.png"
        };
        
        for (const auto& path : lanePaths) {
            if (laneTexture.loadFromFile(path)) {
                std::cout << "Lane texture loaded from: " << path << std::endl;
                break;
            }
        }
        
        if (laneTexture.getSize().x == 0) {
            return false;
        }
    }
    
    leftLaneSprite.setTexture(laneTexture);
    middleLaneSprite.setTexture(laneTexture);
    rightLaneSprite.setTexture(laneTexture);
    
    int borderWidth = 100;
    int laneWidth = 200;
    int laneStartX = borderWidth;
    
    leftLaneSprite.setPosition(laneStartX, 0);
    middleLaneSprite.setPosition(laneStartX + laneWidth, 0);
    rightLaneSprite.setPosition(laneStartX + (laneWidth * 2), 0);
    
    sf::Vector2u texSize = laneTexture.getSize();
    float scaleX = (float)laneWidth / texSize.x;
    float scaleY = 600.0f / texSize.y;
    
    leftLaneSprite.setScale(scaleX, scaleY);
    middleLaneSprite.setScale(scaleX, scaleY);
    rightLaneSprite.setScale(scaleX, scaleY);
    
    /*std::cout << "Lane texture loaded: " << texSize.x << "x" << texSize.y 
              << " scaled to " << (texSize.x * scaleX) << "x" << (texSize.y * scaleY) << std::endl;*/
    
    return true;
}

// ===================== MENU INITIALIZATION =====================
void GameEngine::initializeMenu() {
    if (!fontLoaded()) return;
    
    // Menu Title
    /*menuTitle.setFont(font);
    //menuTitle.setString("SUBWAY SURFERS 2D");
    menuTitle.setCharacterSize(55);
    menuTitle.setFillColor(sf::Color::Yellow);
    menuTitle.setStyle(sf::Text::Bold);
    menuTitle.setPosition(120, 80);*/
    
    // Subtitle
    menuSubtitle.setFont(font);
    menuSubtitle.setString("Run, Jump, Slide!");
    menuSubtitle.setCharacterSize(22);
    menuSubtitle.setFillColor(sf::Color::White);
    menuSubtitle.setPosition(215, 185);
    
    // Create 4 main menu buttons
    startGameButton = createButton(200, 240, 220, 50, "START GAME");
    leaderboardButton = createButton(200, 310, 220, 50, "LEADERBOARD");
    instructionsButton = createButton(200, 380, 220, 50, "INSTRUCTIONS");
    exitButton = createButton(200, 450, 220, 50, "EXIT");
    
    // Pause menu buttons
    resumeButton = createButton(300, 250, 200, 60, "RESUME");
    menuButton = createButton(300, 330, 200, 60, "MAIN MENU");
    
    // Back button for leaderboard and instructions
    backButton = createButton(300, 500, 200, 50, "BACK");
}

MenuButton GameEngine::createButton(float x, float y, float width, float height, const std::string& label) {
    MenuButton button;
    
    button.shape.setSize(sf::Vector2f(width, height));
    button.shape.setPosition(x, y);
    button.shape.setFillColor(button.normalColor);
    button.shape.setOutlineColor(sf::Color::White);
    button.shape.setOutlineThickness(3);
    
    if (fontLoaded()) {
        button.text.setFont(font);
        button.text.setString(label);
        button.text.setCharacterSize(26);
        button.text.setFillColor(sf::Color::White);
        button.text.setStyle(sf::Text::Bold);
        
        // Center text in button
        sf::FloatRect textBounds = button.text.getLocalBounds();
        button.text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                              textBounds.top + textBounds.height / 2.0f);
        button.text.setPosition(x + width / 2.0f, y + height / 2.0f);
    }
    
    return button;
}

// ===================== MAIN GAME LOOP =====================
void GameEngine::run() {
    sf::Clock clock;
    
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        // Handle events based on state
        switch (currentState) {
            case MENU:
                handleMenuEvents();
                break;
            case PLAYING:
                handleEvents();
                if (!isGameOver) {
                    update(deltaTime);
                }
                break;
            case PAUSED:
                handlePauseEvents();
                break;
            case GAMEOVER:
                handleGameOverEvents();
                break;
            case LEADERBOARD:
                handleLeaderboardEvents();
                break;
            case INSTRUCTIONS:
                handleInstructionsEvents();
                break;
        }
        
        render();
    }
}

// ===================== MENU EVENT HANDLING =====================
void GameEngine::handleMenuEvents() {
    sf::Event event;
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    
    // Update button hover states
    startGameButton.updateHover(mousePos);
    leaderboardButton.updateHover(mousePos);
    instructionsButton.updateHover(mousePos);
    exitButton.updateHover(mousePos);
    
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (startGameButton.contains(mousePos)) {
                    //std::cout << "Starting game..." << std::endl;
                    startGame();
                }
                else if (leaderboardButton.contains(mousePos)) {
                    //std::cout << "Opening leaderboard..." << std::endl;
                    showLeaderboard();
                }
                else if (instructionsButton.contains(mousePos)) {
                    //std::cout << "Opening instructions..." << std::endl;
                    showInstructions();
                }
                else if (exitButton.contains(mousePos)) {
                    //std::cout << "Goodbye!" << std::endl;
                    window.close();
                }
            }
        }
        
        // Keyboard shortcuts
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter || 
                event.key.code == sf::Keyboard::Space) {
                startGame();
            }
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}

// ===================== LEADERBOARD EVENT HANDLING =====================
void GameEngine::handleLeaderboardEvents() {
    sf::Event event;
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    
    backButton.updateHover(mousePos);
    
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (backButton.contains(mousePos)) {
                    returnToMenu();
                }
            }
        }
        
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape || 
                event.key.code == sf::Keyboard::BackSpace) {
                returnToMenu();
            }
        }
    }
}

// ===================== INSTRUCTIONS EVENT HANDLING =====================
void GameEngine::handleInstructionsEvents() {
    sf::Event event;
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    
    backButton.updateHover(mousePos);
    
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (backButton.contains(mousePos)) {
                    returnToMenu();
                }
            }
        }
        
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape || 
                event.key.code == sf::Keyboard::BackSpace) {
                returnToMenu();
            }
        }
    }
}

// ===================== PAUSE EVENT HANDLING =====================
void GameEngine::handlePauseEvents() {
    sf::Event event;
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    
    resumeButton.updateHover(mousePos);
    menuButton.updateHover(mousePos);
    
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (resumeButton.contains(mousePos)) {
                    resumeGame();
                }
                else if (menuButton.contains(mousePos)) {
                    returnToMenu();
                }
            }
        }
        
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                resumeGame();
            }
        }
    }
}

// ===================== GAME OVER EVENT HANDLING (SIMPLIFIED) =====================
void GameEngine::handleGameOverEvents() {
    sf::Event event;
    
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        // Return to menu on ANY key press or mouse click
        if (event.type == sf::Event::KeyPressed || 
            event.type == sf::Event::MouseButtonPressed) {
            returnToMenu();
        }
    }
}

// ===================== GAMEPLAY EVENT HANDLING =====================
void GameEngine::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        if (event.type == sf::Event::KeyPressed && !isGameOver) {
            switch (event.key.code) {
                case sf::Keyboard::A:
                case sf::Keyboard::Left:
                    player.moveLeft();
                    break;
                    
                case sf::Keyboard::D:
                case sf::Keyboard::Right:
                    player.moveRight();
                    break;
                    
                case sf::Keyboard::W:
                case sf::Keyboard::Up:
                case sf::Keyboard::Space:
                    player.jump();
                    break;
                    
                case sf::Keyboard::S:
                case sf::Keyboard::Down:
                    player.slide();
                    break;
                    
                case sf::Keyboard::Escape:
                    pauseGame();
                    break;
                    
                default:
                    break;
            }
        }
    }
}

// ===================== GAME STATE TRANSITIONS =====================
void GameEngine::startGame() {
    currentState = PLAYING;
    isGameOver = false;
    //std::cout << "Game started!" << std::endl;
    
    currentState = PLAYING;
    isGameOver = false;
    backgroundMusic.play();  
    //std::cout << "Game started!" << std::endl;
}

void GameEngine::resetGame() {
    // Reset all game components (but DON'T reset textures/sprites)
    player = Player();
    trackManager = TrackManager();
    scoreManager = ScoreManager();
    gameSpeed = 1.0f;
    isGameOver = false;
    
    // DON'T reset these - they should stay loaded:
    // - backgroundTexture
    // - backgroundSprite
    // - laneTexture
    // - lane sprites
    // - font
    
    //std::cout << "Game reset!" << std::endl;
}

void GameEngine::pauseGame() {
    currentState = PAUSED;
    //std::cout << "Game paused" << std::endl;
}

void GameEngine::resumeGame() {
    currentState = PLAYING;
    //std::cout << "Game resumed" << std::endl;
}

void GameEngine::returnToMenu() {
    currentState = MENU;
    resetGame();
    //std::cout << "Returned to main menu" << std::endl;
    currentState = MENU;
    backgroundMusic.stop();  // ADD THIS LINE
    resetGame();
    //std::cout << "Returned to main menu" << std::endl;
}

void GameEngine::showLeaderboard() {
    currentState = LEADERBOARD;
    //std::cout << "Showing leaderboard" << std::endl;
}

void GameEngine::showInstructions() {
    currentState = INSTRUCTIONS;
    //std::cout << "Showing instructions" << std::endl;
}

// ===================== GAME UPDATE =====================
void GameEngine::update(float deltaTime) {
    gameSpeed += deltaTime * 0.01f;
    gameSpeed = std::min(gameSpeed, 3.0f);
    
    player.update(deltaTime);
    trackManager.update(deltaTime * gameSpeed);
    scoreManager.update(deltaTime);
    
    if (player.hasActiveMagnet()) {
        trackManager.applyMagnetEffect(player.getPosition(), player.getMagnetStrength(), deltaTime);
    }
    
    checkCollisions();
}

void GameEngine::checkCollisions() {
    auto& obstacles = trackManager.getObstacles();
    sf::FloatRect playerBounds = player.getBounds();
    
    // ============ OBSTACLE COLLISION WITH SHIELD/JETPACK CHECK ============
    for (int i = 0; i < obstacles.getSize(); i++) {
        Obstacle* obstacle = obstacles.get(i);
        
        if (obstacle->checkCollision(playerBounds)) {
            //std::cout << "COLLISION DETECTED!" << std::endl;
            
            // CHECK IF PLAYER HAS ACTIVE JETPACK (PRIORITY 1)
            if (player.isJetpackActive()) {
                //std::cout << "JETPACK FLYING OVER OBSTACLE!" << std::endl;
                // Jetpack active hai to collision ignore karo
                continue;  // Skip this obstacle
            }
            // CHECK IF PLAYER HAS ACTIVE SHIELD (PRIORITY 2)
            else if (player.isShielded()) {
                //std::cout << SHIELD PROTECTED YOU! Shield destroyed." << std::endl;
                player.deactivateShield();
                playCollisionSound();
                // Free memory and remove obstacle
                delete obstacle; 
                obstacles.remove(i); 
                
                // Exit immediately to prevent double collision
                return;
            } 
            else {
                // NO SHIELD - GAME OVER
                //std::cout << "NO SHIELD! Game Over." << std::endl;
                playCollisionSound();
                gameOver();
                return;
            }
        }
    }
    
    // ============ COIN COLLECTION ============
    auto& coins = trackManager.getCoins(); 
    for (int i = coins.getSize() - 1; i >= 0; i--) {
        Coin* coin = coins.get(i);
        
        if (!coin->isCollected() && coin->getBounds().intersects(playerBounds)) {
            //std::cout << "Coin collected! +50 points" << std::endl;
            playCoinSound();  // ADD THIS LINE
            scoreManager.addCoin();
            coin->collect();
        }
    }
    
    // ============ POWER-UP COLLECTION ============
    auto& powerUps = trackManager.getPowerUps();
    for (int i = powerUps.getSize() - 1; i >= 0; i--) {
        PowerUp* powerUp = powerUps.get(i);
        
        if (!powerUp->isUsed() && powerUp->getBounds().intersects(playerBounds)) {
            playPowerupSound();
            
            // Dynamic cast for ALL power-up types
            ShieldPower* shieldPower = dynamic_cast<ShieldPower*>(powerUp);
            JetPackPower* jetpackPower = dynamic_cast<JetPackPower*>(powerUp);
            MagnetPower* magnetPower = dynamic_cast<MagnetPower*>(powerUp);        // NEW
            DoubleCoinPower* doubleCoinPower = dynamic_cast<DoubleCoinPower*>(powerUp);  // NEW
            
            if (shieldPower != nullptr) {
                //std::cout << "SHIELD POWER-UP COLLECTED! " << std::endl;
                player.activateShield();
            } 
            else if (jetpackPower != nullptr) {
                //std::cout << "JETPACK POWER-UP COLLECTED! " << std::endl;
                player.activateJetpack();
                jetpackPower->activate();
            }
            else if (magnetPower != nullptr) {
                // MAGNET specific activation
                //std::cout << "MAGNET POWER-UP COLLECTED! " << std::endl;
                player.activateMagnet();
            }
            else if (doubleCoinPower != nullptr) {
                // DOUBLE COIN specific activation
                //std::cout << "DOUBLE COIN POWER-UP COLLECTED! " << std::endl;
                player.activateDoubleCoins(10.0f);  // 10 seconds duration
                scoreManager.activateCoinMultiplier(2.0f, 10.0f);  // 2x multiplier
            }
            else {
                // Unknown power-up type (should never happen)
                //std::cout << "Unknown power-up collected!" << std::endl;
            }
            
            powerUp->setUsed(true);
        }
    }
}

// ===================== RENDERING =====================
void GameEngine::render() {
    window.clear(sf::Color(135, 206, 235));
    
    switch (currentState) {
        case MENU:
            renderMenu();
            break;
            
        case PLAYING:
            drawBackground();
            drawTrack();
            player.draw(window);
            trackManager.draw(window);
            drawHUD();
            break;
            
        case PAUSED:
            drawBackground();
            drawTrack();
            player.draw(window);
            trackManager.draw(window);
            drawHUD();
            renderPauseMenu();
            break;
            
        case GAMEOVER:
            drawBackground();
            drawTrack();
            player.draw(window);
            trackManager.draw(window);
            drawHUD();
            renderGameOver();
            break;
            
        case LEADERBOARD:
            renderLeaderboard();
            break;
            
        case INSTRUCTIONS:
            renderInstructions();
            break;
    }
    
    window.display();
}

void GameEngine::renderMenu() {
    // Draw animated background
    drawBackground();
    
    // Semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(800, 600));
    overlay.setFillColor(sf::Color(0, 0, 0, 50));
    window.draw(overlay);
    
    if (fontLoaded()) {
        window.draw(menuTitle);
        window.draw(menuSubtitle);
        
        // Draw 4 buttons
        window.draw(startGameButton.shape);
        window.draw(startGameButton.text);
        
        window.draw(leaderboardButton.shape);
        window.draw(leaderboardButton.text);
        
        window.draw(instructionsButton.shape);
        window.draw(instructionsButton.text);
        
        window.draw(exitButton.shape);
        window.draw(exitButton.text);
        
        // Footer text
        sf::Text footer;
        footer.setFont(font);
        footer.setString("Press Enter to Start | ESC to Exit");
        footer.setCharacterSize(16);
        footer.setFillColor(sf::Color(200, 200, 200));
        footer.setPosition(260, 550);
        window.draw(footer);
    }
}

void GameEngine::renderLeaderboard() {
    // Draw background
    drawBackground();
    
    // Semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(800, 600));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(overlay);
    
    if (!fontLoaded()) return;
    
    // Title
    sf::Text title;
    title.setFont(font);
    title.setString("LEADERBOARD");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(200, 50);
    window.draw(title);
    
    // Read high scores from file
    std::ifstream file("highscore.txt");
    std::vector<std::pair<std::string, int>> scores;
    
    if (file.is_open()) {
        std::string name;
        int score;
        while (file >> name >> score) {
            scores.push_back({name, score});
        }
        file.close();
        
        // Sort by score (highest first)
        std::sort(scores.begin(), scores.end(), 
                  [](const auto& a, const auto& b) { return a.second > b.second; });
    }
    
    // Display top 5 scores
    int yPos = 150;
    int rank = 1;
    
    for (size_t i = 0; i < std::min(scores.size(), size_t(5)); i++) {
        sf::Text rankText;
        rankText.setFont(font);
        rankText.setString(std::to_string(rank) + ". " + scores[i].first);
        rankText.setCharacterSize(30);
        rankText.setFillColor(rank == 1 ? sf::Color::Yellow : sf::Color::White);
        rankText.setStyle(sf::Text::Bold);
        rankText.setPosition(200, yPos);
        window.draw(rankText);
        
        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString(std::to_string(scores[i].second));
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(rank == 1 ? sf::Color::Yellow : sf::Color::White);
        scoreText.setStyle(sf::Text::Bold);
        scoreText.setPosition(500, yPos);
        window.draw(scoreText);
        
        yPos += 60;
        rank++;
    }
    
    // If no scores yet
    if (scores.empty()) {
        sf::Text noScores;
        noScores.setFont(font);
        noScores.setString("No scores yet! Be the first!");
        noScores.setCharacterSize(25);
        noScores.setFillColor(sf::Color::White);
        noScores.setPosition(220, 250);
        window.draw(noScores);
    }
    
    // Back button
    window.draw(backButton.shape);
    window.draw(backButton.text);
    
    // Hint
    sf::Text hint;
    hint.setFont(font);
    hint.setString("Press ESC to go back");
    hint.setCharacterSize(16);
    hint.setFillColor(sf::Color(200, 200, 200));
    hint.setPosition(310, 560);
    window.draw(hint);
}

void GameEngine::renderInstructions() {
    // Draw background
    drawBackground();
    
    // Semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(800, 600));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(overlay);
    
    if (!fontLoaded()) return;
    
    // Title
    sf::Text title;
    title.setFont(font);
    title.setString("HOW TO PLAY?");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Cyan);
    title.setStyle(sf::Text::Bold);
    title.setPosition(180, 40);
    window.draw(title);
    
    // Instructions content
    std::vector<std::string> instructions = {
        "CONTROLS:",
        "A / Left Arrow  - Move Left",
        "D / Right Arrow - Move Right",
        "W / Up Arrow / Space - Jump",
        "S / Down Arrow - Slide",
        "ESC - Pause Game",
        "",
        "OBJECTIVE:",
        "Run as far as you can!",
        "Collect coins for points",
        "Avoid obstacles",
        "",
        "POWER-UPS:",
        "Magnet - Attracts coins",
        "Shield - Protects from 1 hit"
    };
    
    int yPos = 120;
    for (const auto& line : instructions) {
        sf::Text text;
        text.setFont(font);
        text.setString(line);
        
        if (line == "CONTROLS:" || line == "OBJECTIVE:" || line == "POWER-UPS:") {
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::Yellow);
            text.setStyle(sf::Text::Bold);
        } else if (line.empty()) {
            yPos += 10;
            continue;
        } else {
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::White);
        }
        
        text.setPosition(150, yPos);
        window.draw(text);
        yPos += 28;
    }
    
    // Back button
    window.draw(backButton.shape);
    window.draw(backButton.text);
    
    // Hint
    sf::Text hint;
    hint.setFont(font);
    hint.setString("Press ESC to go back");
    hint.setCharacterSize(16);
    hint.setFillColor(sf::Color(200, 200, 200));
    hint.setPosition(310, 560);
    window.draw(hint);
}

void GameEngine::renderPauseMenu() {
    // Semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(800, 600));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(overlay);
    
    if (fontLoaded()) {
        sf::Text pauseTitle;
        pauseTitle.setFont(font);
        pauseTitle.setString("PAUSED");
        pauseTitle.setCharacterSize(70);
        pauseTitle.setFillColor(sf::Color::Yellow);
        pauseTitle.setStyle(sf::Text::Bold);
        pauseTitle.setPosition(280, 120);
        window.draw(pauseTitle);
        
        window.draw(resumeButton.shape);
        window.draw(resumeButton.text);
        window.draw(menuButton.shape);
        window.draw(menuButton.text);
        
        sf::Text hint;
        hint.setFont(font);
        hint.setString("Press ESC to resume");
        hint.setCharacterSize(18);
        hint.setFillColor(sf::Color(200, 200, 200));
        hint.setPosition(300, 450);
        window.draw(hint);
    }
}

// ===================== SIMPLIFIED GAME OVER SCREEN =====================
void GameEngine::renderGameOver() {
    // Semi-transparent dark overlay
    sf::RectangleShape overlay(sf::Vector2f(800, 600));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(overlay);
    
    if (fontLoaded()) {
        // "GAME OVER!" Title - Big Red Text
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER!");
        gameOverText.setCharacterSize(70);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setStyle(sf::Text::Bold);
        
        // Center the text
        sf::FloatRect titleBounds = gameOverText.getLocalBounds();
        gameOverText.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
                               titleBounds.top + titleBounds.height / 2.0f);
        gameOverText.setPosition(400, 200);
        window.draw(gameOverText);
        
        // Final Score Display
        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Final Score: " + std::to_string(scoreManager.getScore()));
        scoreText.setCharacterSize(45);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setStyle(sf::Text::Bold);
        
        // Center the score text
        sf::FloatRect scoreBounds = scoreText.getLocalBounds();
        scoreText.setOrigin(scoreBounds.left + scoreBounds.width / 2.0f,
                            scoreBounds.top + scoreBounds.height / 2.0f);
        scoreText.setPosition(400, 300);
        window.draw(scoreText);
        
        // Hint Text at Bottom
        sf::Text hint;
        hint.setFont(font);
        hint.setString("Press any key to return to menu");
        hint.setCharacterSize(22);
        hint.setFillColor(sf::Color(200, 200, 200));
        
        // Center the hint text
        sf::FloatRect hintBounds = hint.getLocalBounds();
        hint.setOrigin(hintBounds.left + hintBounds.width / 2.0f,
                       hintBounds.top + hintBounds.height / 2.0f);
        hint.setPosition(400, 420);
        window.draw(hint);
    }
}

void GameEngine::drawBackground() {
    if (backgroundTexture.getSize().x > 0) {
        window.draw(backgroundSprite);
    }
}

void GameEngine::drawTrack() {
    int borderWidth = 100;
    sf::RectangleShape leftBorder(sf::Vector2f(borderWidth, 600));
    leftBorder.setFillColor(sf::Color(70, 130, 180, 200));
    leftBorder.setPosition(0, 0);
    
    sf::RectangleShape rightBorder(sf::Vector2f(borderWidth, 600));
    rightBorder.setFillColor(sf::Color(70, 130, 180, 200));
    rightBorder.setPosition(800 - borderWidth, 0);
    
    window.draw(leftBorder);
    window.draw(rightBorder);
    
    int laneStartX = borderWidth;
    int laneWidth = 200;
    
    if (laneTexture.getSize().x > 0) {
        window.draw(leftLaneSprite);
        window.draw(middleLaneSprite);
        window.draw(rightLaneSprite);
    } else {
        drawColoredLanesFallback();
    }
    
    for (int y = 0; y < 600; y += 30) {
        sf::RectangleShape dash1(sf::Vector2f(5, 15));
        dash1.setFillColor(sf::Color::White);
        dash1.setPosition(laneStartX + laneWidth, y);
        
        sf::RectangleShape dash2(sf::Vector2f(5, 15));
        dash2.setFillColor(sf::Color::White);
        dash2.setPosition(laneStartX + (laneWidth * 2), y);
        
        window.draw(dash1);
        window.draw(dash2);
    }
}

void GameEngine::drawColoredLanesFallback() {
    int borderWidth = 100;
    int laneStartX = borderWidth;
    int laneWidth = 200;
    
    sf::RectangleShape leftLane(sf::Vector2f(laneWidth, 600));
    leftLane.setFillColor(sf::Color(30, 144, 255, 100));
    leftLane.setPosition(laneStartX, 0);
    
    sf::RectangleShape middleLane(sf::Vector2f(laneWidth, 600));
    middleLane.setFillColor(sf::Color(220, 20, 60, 100));
    middleLane.setPosition(laneStartX + laneWidth, 0);
    
    sf::RectangleShape rightLane(sf::Vector2f(laneWidth, 600));
    rightLane.setFillColor(sf::Color(255, 215, 0, 100));
    rightLane.setPosition(laneStartX + (laneWidth * 2), 0);
    
    window.draw(leftLane);
    window.draw(middleLane);
    window.draw(rightLane);
}

void GameEngine::drawHUD() {
    if (!fontLoaded()) {
        sf::RectangleShape scoreBg(sf::Vector2f(150, 30));
        scoreBg.setFillColor(sf::Color(0, 0, 0, 150));
        scoreBg.setPosition(5, 5);
        window.draw(scoreBg);
        return;
    }
    
    // Score Display
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("SCORE: " + std::to_string(scoreManager.getScore()));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setPosition(10, 10);
    window.draw(scoreText);
    
    // Coins Display
    sf::Text coinsText;
    coinsText.setFont(font);
    coinsText.setString("COINS: " + std::to_string(scoreManager.getCoins()));
    coinsText.setCharacterSize(20);
    coinsText.setFillColor(scoreManager.isCoinMultiplierActiveNow() ? sf::Color::Green : sf::Color::Yellow);
    coinsText.setPosition(10, 40);
    window.draw(coinsText);
    
    // Speed Display
    sf::Text speedText;
    speedText.setFont(font);
    speedText.setString("SPEED: " + std::to_string((int)(gameSpeed * 100)) + "%");
    speedText.setCharacterSize(18);
    speedText.setFillColor(sf::Color::Cyan);
    speedText.setPosition(10, 70);
    window.draw(speedText);
    
    int yOffset = 95;
    
    // ============ DOUBLE COIN DISPLAY ============
    if (scoreManager.isCoinMultiplierActiveNow()) {
        sf::Text doubleCoinText;
        doubleCoinText.setFont(font);
        doubleCoinText.setString("DOUBLE COIN: " + std::to_string((int)scoreManager.getCoinMultiplierTimeLeft()) + "s");
        doubleCoinText.setCharacterSize(18);
        doubleCoinText.setFillColor(sf::Color::Green);
        doubleCoinText.setStyle(sf::Text::Bold);
        doubleCoinText.setPosition(10, yOffset);
        window.draw(doubleCoinText);
        yOffset += 25;
    }
    
    // ============ MAGNET DISPLAY ============
    if (player.hasActiveMagnet()) {
        sf::Text magnetText;
        magnetText.setFont(font);
        magnetText.setString("MAGNET: " + std::to_string((int)player.getMagnetTimeLeft()) + "s");
        magnetText.setCharacterSize(18);
        magnetText.setFillColor(sf::Color::Magenta);
        magnetText.setPosition(10, yOffset);
        window.draw(magnetText);
        
        // Magnet visual aura (jo already thi wahi rakho)
        sf::CircleShape magnetAura(150);
        magnetAura.setFillColor(sf::Color(255, 0, 255, 30));
        magnetAura.setOutlineColor(sf::Color::Magenta);
        magnetAura.setOutlineThickness(2);
        magnetAura.setOrigin(150, 150);
        magnetAura.setPosition(player.getPosition().x + 25, player.getPosition().y + 40);
        window.draw(magnetAura);
        
        yOffset += 25;
    }
    
    // ============ SHIELD DISPLAY ============
    if (player.isShielded()) {
        sf::Text shieldText;
        shieldText.setFont(font);
        shieldText.setString("SHIELD: " + std::to_string((int)player.getShieldTimeLeft()) + "s");
        shieldText.setCharacterSize(18);
        shieldText.setFillColor(sf::Color::Cyan);
        shieldText.setStyle(sf::Text::Bold);
        shieldText.setPosition(10, yOffset);
        window.draw(shieldText);
        yOffset += 25;
    }
    
    // ============ JETPACK DISPLAY ============
    if (player.isJetpackActive()) {
        sf::Text jetpackText;
        jetpackText.setFont(font);
        jetpackText.setString("JETPACK: " + std::to_string((int)player.getJetpackTimeLeft()) + "s");
        jetpackText.setCharacterSize(18);
        jetpackText.setFillColor(sf::Color::Yellow);
        jetpackText.setStyle(sf::Text::Bold);
        jetpackText.setPosition(10, yOffset);
        window.draw(jetpackText);
        
        // Jetpack flame effect (jo already thi wahi rakho)
        sf::RectangleShape jetpackFlame(sf::Vector2f(20, 40));
        jetpackFlame.setFillColor(sf::Color(255, 165, 0, 150));
        jetpackFlame.setOrigin(10, 40);
        jetpackFlame.setPosition(player.getPosition().x + 25, player.getPosition().y + 80);
        window.draw(jetpackFlame);
        
        yOffset += 25;
    }
}
bool GameEngine::fontLoaded() const {
    try {
        return !font.getInfo().family.empty();
    } catch (...) {
        return false;
    }
}

void GameEngine::gameOver() {
    isGameOver = true;
    currentState = GAMEOVER;
    scoreManager.saveHighScore("Player");
    
}

void GameEngine::playCollisionSound() {
    collisionSound.play();
}

void GameEngine::playCoinSound() {
    coinSound.play();
}

void GameEngine::playPowerupSound() {
    powerupSound.play();
}
