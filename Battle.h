#pragma once
#include "Player.h"
#include "Monster.h"

bool rollChance(int percent);
bool battle(Player& p, Monster& m);
int dealDamage(const Character& attacker, Character& defender);