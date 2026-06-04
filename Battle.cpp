#include "Battle.h"
#include <iostream>
#include <algorithm>   // std::max 要用
#include <random>      // mt19937 等要用
using namespace std;

static std::mt19937 rng(std::random_device{}());   // 整个文件共享这一个引擎

//随机创建怪物
MonsterType randomMonsterType()
{
	uniform_int_distribution<int> dist(0, static_cast<int>(MonsterType::Count) - 1);   // 区间动态变化
	return static_cast<MonsterType>(dist(rng));                  // 用共享的 rng
}

//血药掉落概率
bool rollChance(int percent)
{
	uniform_int_distribution<int> dist(0, 99);   // 0~99，共 100 个数
	return dist(rng) < percent;					//使用同一个 rng
}

//多态处理伤害
int dealDamage(const Character& attacker, Character& defender)           //伤害者不变, 防御者掉血
{
	int dmg = max(1, attacker.getAtk() - defender.getDef());
	defender.takeDamage(dmg);
	return dmg;
}

//战斗框架
bool battle(Player& p, Monster& m)
{
	while (p.isAlive() && m.isAlive())
	{
		int p_dmg = dealDamage(p, m);
		cout << "You hit the " << m.getName() << ". The damage is " << p_dmg << endl;
		if (m.isAlive())
			cout << "The " << m.getName() << " is now " << m.getStateName() << "." << endl;
		//胜利分支
		if (!m.isAlive())                               
		{
			if (rollChance(m.getDropChance()))
			{
				p.addPotion();
			}
			p.gainGold(m.getRewardGold());
			p.gainExp(m.getRewardExp());
			cout << "The " << m.getName() << " is dead. You win!" << endl;
			cout << "You've got " << m.getRewardGold() << " gold." << endl;
			cout << "You've got " << m.getRewardExp() << " Exp." << endl;
			return true;
		}
		int m_dmg = dealDamage(m, p);
		cout << "The " << m.getName() << " hits you. The damage is " << m_dmg << endl;
		//失败分支
		if (!p.isAlive())
		{
			cout << "You are dead." << endl;
			return false;
		}
	}
	return !m.isAlive();
}