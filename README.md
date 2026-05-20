<div align="center">

# 🚇 Subway Surfers 2D

### A 2D endless runner game built in C++ using SFML

*OOP Course Project — demonstrating inheritance, polymorphism, templates, and real-time game architecture*

<br>

![C++](https://img.shields.io/badge/C++17-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![SFML](https://img.shields.io/badge/SFML_2.x-8CC445?style=flat-square&logo=sfml&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey?style=flat-square)
![OOP](https://img.shields.io/badge/Paradigm-Object--Oriented-orange?style=flat-square)

</div>

---

## What is this?

A fully playable 2D clone of Subway Surfers written from scratch in C++. The player sprints across three lanes, vaults over obstacles, collects coins, and grabs power-ups — all while the game gradually speeds up. The project was built as an OOP course assignment to implement real-world use of inheritance hierarchies, abstract classes, runtime polymorphism, and a custom templated data structure.

---

## Gameplay

- **3 lanes** — switch left and right with `A / D` or `← / →`
- **Jump** over tall obstacles with `W / ↑`
- **Slide** under low barriers with `S / ↓`
- Game speed ramps from **100% → 300%** over time
- High score is saved between sessions

---

## Controls

| Key | Action |
|---|---|
| `A` / `←` | Move left |
| `D` / `→` | Move right |
| `W` / `↑` | Jump |
| `S` / `↓` | Slide |
| `ESC` | Pause |

---

## Obstacles

| Obstacle | Behaviour | Dodge How? |
|---|---|---|
| **Train** | Full-height blocker | Switch lane |
| **Barrier** | Low obstacle | Jump over |
| **Cone** | Low obstacle | Jump over |
| **Fence** | Low obstacle | Jump or slide |

---

## Power-Ups

| Power-Up | Effect | Duration |
|---|---|---|
| 🚀 **Jetpack** | Fly above the track — all obstacles ignored | 15 s |
| 🧲 **Magnet** | Coins within radius are pulled toward you | 10 s |
| 🛡️ **Shield** | Absorbs the next collision without dying | 10 s |
| 💰 **Double Coin** | Every coin collected counts as 2 (2× multiplier) | 10 s |

---

## Scoring

| Event | Points |
|---|---|
| Surviving | +1 per 0.1 second |
| Coin collected | +50 |
| Coin with Double Coin active | +100 |

---

## OOP Architecture

### Class Hierarchy

```
Obstacle  [abstract]          PowerUp  [base]
├── Train                     ├── JetPackPower
├── Barrier                   ├── MagnetPower
├── Cone                      ├── ShieldPower
└── Fence                     └── DoubleCoinPower
```

Every `Obstacle` subclass **must** implement `update()` (pure virtual). Every `PowerUp` subclass overrides `activate()` and `deactivate()`. At runtime the engine holds `GameList<Obstacle*>` and `GameList<PowerUp*>` — it calls `update()` and `draw()` on each without knowing the concrete type.

### Key OOP Concepts Applied

| Concept | Where |
|---|---|
| **Abstract class** | `Obstacle` — has pure virtual `update()`, cannot be instantiated |
| **Inheritance** | `Train`, `Barrier`, `Cone`, `Fence` all extend `Obstacle` |
| **Polymorphism** | `GameList<Obstacle*>` stores any subtype; virtual dispatch calls the right `update()` |
| **Encapsulation** | All members `private` / `protected`; exposed only via typed getters |
| **Templates** | `GameList<T>` — a generic resizable array used for obstacles, coins, and power-ups |
| **Composition** | `GameEngine` owns `Player`, `TrackManager`, `ScoreManager` by value |
| **File I/O** | `ScoreManager` reads and writes `highscore.txt` |
| **dynamic_cast** | Used at power-up pickup to identify concrete type and call player's activation method |

### Custom Data Structure — `GameList<T>`

All game objects are managed through `GameList<T>`, a templated dynamic array written without STL containers. It owns heap memory, doubles capacity on overflow, and supports add, remove-by-index, get, and clear.

```cpp
GameList<Obstacle*> obstacles;   // polymorphic list — any Obstacle subtype
GameList<Coin*>     coins;
GameList<PowerUp*>  powerUps;    // polymorphic list — any PowerUp subtype
```

---

## Project Structure

```
├── src/
│   ├── main.cpp
│   ├── GameEngine/         ← game loop, input, rendering, collision
│   ├── Player/             ← movement, jump/slide physics, power-up states
│   ├── Obstacles/          ← abstract base + Train, Barrier, Cone, Fence
│   ├── PowerUps/           ← base class + Jetpack, Magnet, Shield, DoubleCoin
│   ├── Managers/
│   │   ├── TrackManager    ← spawns and updates all obstacles, coins, power-ups
│   │   └── ScoreManager    ← score, coin count, multiplier, high score I/O
│   ├── Coin/
│   └── Utils/
│       └── GameList.h / .tpp   ← custom templated dynamic array
├── assets/
│   ├── textures/           ← sprites, backgrounds, lane art
│   ├── sounds/             ← background music, coin, collision, power-up SFX
│   └── fonts/
└── highscore.txt
```

---

## Getting Started

### Requirements

- **g++** with C++17 support
- **SFML 2.x** development libraries

```bash
# Ubuntu / Debian
sudo apt-get install libsfml-dev
```

For Windows, download SFML from [sfml-dev.org](https://www.sfml-dev.org/download.php) and link it in your compiler settings.

### Build

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
# Must be run from the project root — not from inside src/
./game
```

---

## Author

**Shadab Ahad** 
FAST National University of Computer and Emerging Sciences (NUCES), Islamabad  
Object-Oriented Programming — Course Project

---

## Disclaimer

Subway Surfers is a trademark of Kiloo and SYBO Games. This is an independent student project built for educational purposes and is not affiliated with or endorsed by them.

---

<div align="center">

Made with ❤️ at FAST-NUCES Islamabad

</div>
