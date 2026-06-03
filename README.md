# Mini RPG Adventure

> 🚧 Actively developed — a personal learning project, iterated on over time.

A turn-based console RPG written in modern C++ (C++11 and later). Built as a hands-on project to practice object-oriented design, state machines, and clean separation of concerns.

## Features

- **Player progression** — HP, attack, defense, gold, level, and EXP. Defeating monsters grants EXP and gold; leveling up boosts stats and fully restores HP.
- **Monster state machine** — Each monster transitions between four states based on its remaining HP (checked in priority order: Dead → Enraged → Defensive → Aggressive):

  | State | Trigger | Effect |
  |-------|---------|--------|
  | Aggressive | HP > 50% | Normal stats |
  | Defensive | 20% < HP ≤ 50% | Defense ×1.5 |
  | Enraged | 0 < HP ≤ 20% | Attack ×1.5 |
  | Dead | HP ≤ 0 | Battle ends |

- **Turn-based combat** — Damage is calculated from attacker's attack minus defender's defense (minimum 1). Monster state modifiers feed directly into combat.
- **Loot & economy** — Monsters drop potions by chance and reward gold. Gold is spent in the shop.
- **Shop system** — Buy potions with gold; purchases are validated against the player's balance.
- **Inventory** — Stackable items (potions) stored in the player's bag.
- **Robust input handling** — Invalid menu input is detected, the stream is cleared, and the user is re-prompted instead of crashing.

## Project Structure

| File | Responsibility |
|------|----------------|
| `main.cpp` | Entry point |
| `GameManager.{h,cpp}` | Game loop, menus, all UI and input |
| `Player.{h,cpp}` | Player state and behavior (stats, EXP/level, inventory, gold) |
| `Monster.{h,cpp}` | Monster definitions and HP-driven state machine |
| `Battle.{h,cpp}` | Combat logic and RNG (monster spawn, drop rolls) |
| `Item.h` | Item data structure |

The design separates three concerns: **GameManager** owns all I/O, **Player/Monster** own data and behavior, and **Battle** owns the combat rules — so each layer can change without touching the others.

## Build & Run

### Visual Studio
Open `Mini RPG Adventure Demo.vcxproj` and build (Ctrl+F5).

### Command line (g++)

```bash
g++ -std=c++17 main.cpp GameManager.cpp Player.cpp Monster.cpp Battle.cpp -o MiniRPG
./MiniRPG
```

## Gameplay

```
==== Mini RPG ====
1. Show Player Info
2. Show Bag
3. Get Potion
4. Use Potion
5. Battle
6. Visit Shop
0. Exit
```

Fight monsters to earn gold and EXP, buy potions to survive tougher fights, and level up to grow stronger.

## Roadmap

The project is evolving from a hardcoded demo into an extensible, data-driven game system. Phases are ordered by value, not just difficulty.

### Phase 1 — Inheritance & Polymorphism `★★★★★`

Refactor `Player` and `Monster` (which currently duplicate `atk`/`def`/`isAlive`/`takeDamage`) under a shared abstract base class:

```
Character (abstract)
├── Player
└── Monster
```

- `Character` declares `virtual getAtk()` / `virtual getDef()`
- `Monster` overrides them to fold in its state-based modifiers (Enraged/Defensive)
- `battle()` is rewritten to take `Character&` references — combat logic runs through the base interface and dispatches dynamically

This is the highest-value step: virtual functions + runtime polymorphism are the core of C++ OOP.

### Phase 2 — Save / Load System `★★★`

Persist player state to disk with `fstream` and resume from a save on startup.

- `Player::save(const std::string& filename)` / `Player::load(const std::string& filename)`
- Serializes: name, HP, maxHP, level, EXP, gold, and inventory

### Phase 3 — Factory Pattern & Data-Driven Design `★★★★`

Replace the hardcoded `switch`-based monster creation with a factory, then move monster data out of the code entirely:

```cpp
class MonsterFactory {
public:
    static Monster create(MonsterType type);
};
```

- Load monster stats from an external CSV/text file so adding a new monster requires no code change
- Turns the project from a "fixed toy" into an extensible system

### Phase 4 — Skill System `★★★★`

Add an MP resource and a `Skill` class, and restructure the battle loop into an action menu:

```
1. Attack
2. Use Skill: Fireball (costs 20 MP)
3. Use Potion
4. Flee
```

The largest jump in complexity — combat becomes a real interaction loop.

### Phase 5 — Polish `★★`

- ASCII health bars: `[####------] 40/100`
- Screen clearing for a cleaner UI
- Unified battle-log formatting
- More monster types and boss fights

## Tech

C++ · STL (`<vector>`, `<string>`, `<random>`, `<limits>`) · OOP · Finite State Machine
