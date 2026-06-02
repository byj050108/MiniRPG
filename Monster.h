#pragma once
#include <string>

enum class MonsterType { Slime, Goblin, Wolf, Count };
enum class MonsterState { Aggressive, Defensive, Enraged, Dead };

class Monster
{
public:
	//函数声明
	Monster(MonsterType type);
	void show() const;
	std::string getStateName() const;
	
	//getter
	std::string getName() const { return name; }
	int getAtk() const { if (state == MonsterState::Enraged) { return atk*3/2; }return atk; }
	int getDef() const { if (state == MonsterState::Defensive) { return def*3/2; }return def; }
	int getRewardGold() const { return rewardGold; }
	int getDropChance() const { return dropChance; }
	bool isAlive() const { return hp > 0; }
	int getRewardExp() const { return rewardExp; }

	//行为门
	void takeDamage(int dmg) { hp -= dmg; updateState(); }

private:
	std::string name;
	int hp;
	int maxHp;
	int atk;
	int def;
	int rewardGold;
	int dropChance;
	int rewardExp;
	void updateState();                                       
	MonsterState state = MonsterState::Aggressive;
};
