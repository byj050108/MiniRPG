#include <iostream>
#include "Player.h"
using namespace std;

//显示用户信息
void Player::show() const
{
	cout << "==== Player Info ====" << endl;
	cout << "Name: " << name << endl;
	cout << "HP: " << hp << "/" << maxHp << endl;
	cout << "Level: " << level << endl;
	cout << "Exp: " << exp << "/" << maxExp << endl;
	cout << "Gold: " << gold << endl;
	cout << "Attack: " << atk << endl;
	cout << "Def: " << def << endl;
}

//获得药水Potion
void Player::addPotion()
{
	for (auto& x : bag)
	{
		if (x.name == "Potion")
		{
			x.count += 1;
			cout << "You got a Potion." << endl;
			return;
		}
	}
	Item I;
	I.name = "Potion";
	I.count = 1;
	bag.push_back(I);
	cout << "You got a Potion." << endl;
}

//使用药水
void Player::usePotion()
{
	for (auto& x : bag)
	{
		if (x.name == "Potion")
		{
			if (x.count <= 0)
			{
				cout << "No Potion left." << endl;
				return;
			}

			if (hp == maxHp)
			{
				cout << "The player's HP is full." << endl;
				return;
			}
			hp += 20;

			if (hp >= maxHp)
			{
				hp = maxHp;
			}
			x.count -= 1;
			cout << "Used a Potion successfully!" << endl;
			return;
		}
	}
	cout << "No Potion left." << endl;
}

//显示背包
void Player::showBag() const
{
	cout << "==== Bag ====" << endl;
	if (bag.empty())
	{
		cout << "Your bag is empty." << endl;
	}
	else {
		for (const auto& x : bag)
		{
			cout << x.name << " x " << x.count << endl;
		}
	}
}

//获得经验
void Player::gainExp(int amount)
{
	exp += amount;
	while (exp >= maxExp)                 //使用 while 防止一次战斗获取大量经验只升一级
	{
		level += 1;
		maxExp += 100;
		atk += 10;
		def += 10;
		maxHp += 100;
		hp = maxHp;
		cout << "Level up!" << endl;
	}
}

//消费金币
bool Player::spendGold(int cost)
{
	if (isEnough(cost))
	{
		gold -= cost;
		return true;
	}
	return false;
}