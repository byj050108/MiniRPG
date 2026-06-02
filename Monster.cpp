#include "Monster.h"
#include <iostream>
using namespace std;

//怪物种类
Monster::Monster(MonsterType type)
{
	switch (type)
	{
	case MonsterType::Slime:
		name = "Slime"; hp = 30; atk = 8;  def = 2; rewardExp = 30; rewardGold = 20; dropChance = 30;
		break;
	case MonsterType::Goblin:
		name = "Goblin"; hp = 50; atk = 12; def = 4; rewardExp = 50; rewardGold = 35; dropChance = 50;
		break;
	case MonsterType::Wolf:
		name = "Wolf"; hp = 35; atk = 18; def = 1; rewardExp = 80; rewardGold = 40; dropChance = 60;
		break;
	default:
		name = "Slime"; hp = 30; atk = 8;  def = 2; rewardExp = 30; rewardGold = 20; dropChance = 30;
		break;
	}
	maxHp = hp;
}

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