#pragma once
#include <string>
#include "Character.h"

enum class MonsterType { Slime, Goblin, Wolf, Count };
enum class MonsterState { Aggressive, Defensive, Enraged, Dead };

class Monster : public Character
{
public:
	//函数声明
	Monster(const std::string& name, int hp, int atk, int def,
		int rewardGold, int dropChance, int rewardExp);
	void show() const;
	std::string getStateName() const;
	
	//getter
	int getAtk() const override { if (state == MonsterState::Enraged) { return atk*3/2; }return atk; }
	int getDef() const override { if (state == MonsterState::Defensive) { return def*3/2; }return def; }
	int getRewardGold() const { return rewardGold; }
	int getDropChance() const { return dropChance; }
	int getRewardExp() const { return rewardExp; }

	//行为门
	void takeDamage(int dmg) override { hp -= dmg; updateState(); }

private:
	int rewardGold;
	int dropChance;
	int rewardExp;
	void updateState();                                       
	MonsterState state = MonsterState::Aggressive;
	
};
