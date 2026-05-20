# Subway Surfers 2D

> A 2D endless runner built in C++ with SFML, demonstrating object-oriented design through a polymorphic obstacle and power-up hierarchy, a custom templated dynamic array, real-time physics, and a full game loop with persistent high scores.

---

## Overview

This is an OOP course project — a playable 2D clone of Subway Surfers written entirely in C++17 using the SFML library. The player runs endlessly across three lanes, dodging obstacles and collecting coins while the game speed progressively increases. The project was designed around core OOP principles: every game entity is a class, obstacles and power-ups use abstract base classes with virtual dispatch, and all game objects are managed through a custom generic container written from scratch.

**Window:** 800 × 600 px  
**Language:** C++17  
**Library:** SFML 2.x (graphics, audio, window)

---

## Features

- Three-lane endless runner with scrolling background
- 12-frame sprite animation for the player with physics-based jump (velocity + gravity) and timed slide
- Four obstacle types: **Train**, **Barrier**, **Cone**, **Fence** — spawned randomly with increasing frequency
- Four power-ups: **Jetpack** (15s flight, bypasses all obstacles), **Magnet** (10s coin attraction with visible aura), **Shield** (10s, absorbs one collision), **Double Coin** (2× coin multiplier with pulsing gold aura)
- Score system: 1 point per 0.1s elapsed + 50 points per coin (doubled with Double Coin active)
- Persistent high score saved to and loaded from `highscore.txt`
- Full audio: looping background music, coin, collision, and power-up sound effects
- Complete UI flow: Main Menu → Playing → Pause → Game Over → Leaderboard → Instructions → Back

---

## OOP Design

### Inheritance Hierarchies

```
Obstacle  (abstract)
├── Train
├── Barrier
├── Cone
└── Fence

PowerUp   (base)
├── JetPackPower
├── MagnetPower
├── ShieldPower
└── DoubleCoinPower
```

Both `Obstacle` and `PowerUp` declare virtual `update()`, `draw()`, `activate()`, and `deactivate()` methods. `Obstacle::update()` is **pure virtual**, making it an abstract class. Subclasses override these to implement their own behavior and textures.

### Custom Templated Container

`GameList<T>` is a generic, heap-allocated resizable array — written without any STL containers. It is used for all three live object lists:

```cpp
GameList<Obstacle*> obstacles;   // polymorphic — holds any Obstacle subtype
GameList<Coin*>     coins;
GameList<PowerUp*>  powerUps;    // polymorphic — holds any PowerUp subtype
```

The container doubles its capacity on overflow and supports `add()`, `remove()`, `get()`, `getSize()`, and `clear()`.

### Polymorphism in Practice

Power-up collision resolution uses `dynamic_cast` to identify the concrete type at runtime and call the appropriate activation path on the `Player`:

```cpp
ShieldPower*  s = dynamic_cast<ShieldPower*>(powerUp);
JetPackPower* j = dynamic_cast<JetPackPower*>(powerUp);
MagnetPower*  m = dynamic_cast<MagnetPower*>(powerUp);
```

### Encapsulation

All class members are `private` or `protected`. State is exposed only through typed getters (e.g., `getShieldTimeLeft()`, `getMagnetStrength()`, `isJetpackActive()`) and narrow setters, keeping each class responsible for its own invariants.

### Composition

`GameEngine` owns `Player`, `TrackManager`, and `ScoreManager` by value. `TrackManager` owns and manages the three `GameList` containers. No global state is used.

---

## Project Structure

```
├── src/
│   ├── main.cpp
│   ├── GameEngine/
│   │   ├── GameEngine.h
│   │   └── GameEngine.cpp
│   ├── Player/
│   │   ├── Player.h
│   │   └── Player.cpp
│   ├── Obstacles/
│   │   ├── Obstacle.h / .cpp       ← abstract base
│   │   ├── Train.h / .cpp
│   │   ├── Barrier.h / .cpp
│   │   ├── Cone.h / .cpp
│   │   └── Fence.h / .cpp
│   ├── PowerUps/
│   │   ├── PowerUp.h / .cpp        ← base class
│   │   ├── JetpackPower.h / .cpp
│   │   ├── MagnetPower.h / .cpp
│   │   ├── ShieldPower.h / .cpp
│   │   └── DoubleCoinPower.h / .cpp
│   ├── Managers/
│   │   ├── TrackManager.h / .cpp
│   │   └── ScoreManager.h / .cpp
│   ├── Coin/
│   │   ├── Coin.h
│   │   └── Coin.cpp
│   └── Utils/
│       ├── GameList.h              ← custom templated dynamic array
│       └── GameList.tpp
├── assets/
│   ├── textures/
│   ├── sounds/
│   └── fonts/
├── docs/
│   ├── UML_Diagram.md
│   ├── Assumptions.md
│   └── Template_Explanation.md
├── highscore.txt
└── README.md
```

---

## Controls

| Key | Action |
|---|---|
| `A` / `←` | Move left |
| `D` / `→` | Move right |
| `W` / `↑` | Jump |
| `S` / `↓` | Slide |
| `ESC` | Pause / unpause |

---

## Building and Running

### Prerequisites

- g++ with C++17 support
- SFML 2.x development libraries

**Ubuntu / Debian:**
```bash
sudo apt-get install libsfml-dev
```

**Windows:** Download SFML from [sfml-dev.org](https://www.sfml-dev.org/download.php) and configure your compiler to link against it.

### Compile

```bash
g++ -std=c++17 \
  src/main.cpp \
  src/GameEngine/GameEngine.cpp \
  src/Player/Player.cpp \
  src/Obstacles/Obstacle.cpp \
  src/Obstacles/Train.cpp \
  src/Obstacles/Barrier.cpp \
  src/Obstacles/Cone.cpp \
  src/Obstacles/Fence.cpp \
  src/PowerUps/PowerUp.cpp \
  src/PowerUps/JetpackPower.cpp \
  src/PowerUps/MagnetPower.cpp \
  src/PowerUps/ShieldPower.cpp \
  src/PowerUps/DoubleCoinPower.cpp \
  src/Managers/TrackManager.cpp \
  src/Managers/ScoreManager.cpp \
  src/Coin/Coin.cpp \
  -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system \
  -o game
```

### Run

```bash
./game
```

> **Important:** Run the executable from the project root directory so that the `assets/` path resolves correctly. Do not run it from inside `src/` or `build/`.

---

## Scoring

| Event | Points |
|---|---|
| Time survived | 1 pt per 0.1 second |
| Coin collected | 50 pts |
| Coin with Double Coin active | 100 pts |

High scores are written to `highscore.txt` and reloaded on the next launch.

---

## Disclaimer

This project is for educational purposes only. Subway Surfers is a trademark of Kiloo and SYBO Games. This project is not affiliated with or endorsed by them.
