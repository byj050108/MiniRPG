#pragma once
#include <string>
#include <vector>
#include "Item.h"

class Player
{
public:
	//函数声明
	void show() const;
	void addPotion();
	void usePotion();
	void showBag() const;
	void gainExp(int amount);

	// getter
	int getAtk() const { return atk; }
	int getDef() const { return def; }
	int getGold() const { return gold; }
	bool isAlive() const { return hp > 0; }
	bool isEnough(int cost) const { return gold >= cost; }

	// 行为门
	void takeDamage(int dmg) { hp -= dmg; }
	void gainGold(int amount) { gold += amount; }
	void setName(const std::string& n) { name = n; }
	bool spendGold(int cost);

private:
	std::string name;
	int hp = 100;
	int gold = 0;
	int maxHp = 100;
	int atk = 15;
	int def = 5;
	int level = 1;
	int exp = 0;
	int maxExp = 100;
	std::vector<Item> bag;
};