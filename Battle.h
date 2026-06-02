#pragma once
#include "Player.h"
#include "Monster.h"

MonsterType randomMonsterType();
bool rollChance(int percent);
bool battle(Player& p, Monster& m);
