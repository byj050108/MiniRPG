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

- [ ] `Character` base class — unify Player and Monster via inheritance and polymorphism
- [ ] Save / load system using file I/O
- [ ] Data-driven monster definitions (load stats from a config file via a factory)
- [ ] Active skill system with MP
- [ ] UI polish — ASCII health bars, boss fights

## Tech

C++ · STL (`<vector>`, `<string>`, `<random>`, `<limits>`) · OOP · Finite State Machine
