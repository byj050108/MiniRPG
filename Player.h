#pragma once
#include <string>
#include <vector>
#include "Item.h"
#include "Character.h"

class Player : public Character
{
public:
	//函数声明
	void show() const;
	void addPotion();
	void usePotion();
	void showBag() const;
	void gainExp(int amount);

	// getter
	int getGold() const { return gold; }
	bool isEnough(int cost) const { return gold >= cost; }

	// 行为门
	void gainGold(int amount) { gold += amount; }
	void setName(const std::string& n) { name = n; }
	bool spendGold(int cost);

	Player() : Character("", 100, 15, 5) {}          //初始化
private:
	int gold = 0;
	int level = 1;
	int exp = 0;
	int maxExp = 100;
	std::vector<Item> bag;
};