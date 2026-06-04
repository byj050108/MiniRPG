#include "Monster.h"
#include <iostream>
using namespace std;

//初始化怪物
Monster::Monster(const std::string& name, int hp, int atk, int def,
	int rewardGold, int dropChance, int rewardExp): Character(name,hp,atk,def), 
	rewardGold(rewardGold), dropChance(dropChance), rewardExp(rewardExp) { }
//更新怪物状态
void Monster::updateState()
{
	if (hp <= 0)
		state = MonsterState::Dead;
	else if (hp * 5 <= maxHp)
		state = MonsterState::Enraged;
	else if (hp * 2 <= maxHp)
		state = MonsterState::Defensive;
	else
		state = MonsterState::Aggressive;
}

//打印怪物状态
string Monster::getStateName() const
{
	switch (state)
	{
	case MonsterState::Aggressive: return "Aggressive";
	case MonsterState::Defensive: return "Defensive";
	case MonsterState::Enraged: return "Enraged";
	case MonsterState::Dead: return "Dead";
	default: return "Unknown";
	}
}

//打印怪物信息
void Monster::show() const
{
	cout << "==== Monster Info ====" << endl;
	cout << "Monster's name: " << name << endl;
	cout << "Monster's HP: " << hp << endl;
	cout << "Monster's Attack: " << atk << endl;
	cout << "Monster's Reward Gold: " << rewardGold << endl;
	cout << "Monster's Reward Exp: " << rewardExp << endl;
}