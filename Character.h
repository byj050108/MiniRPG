#pragma once
#include <string>

class Character
{
public:
	Character(const std::string& name, int hp, int atk, int def)
		: name(name), hp(hp), maxHp(hp), atk(atk), def(def) {
	}
	virtual ~Character() = default;            // 虚析构

	virtual int getAtk() const { return atk; }  
	virtual int getDef() const { return def; }
	virtual void takeDamage(int dmg) { hp -= dmg; }
	bool isAlive() const { return hp > 0; }
	std::string getName() const { return name; }

protected:                                      // 子类能用，外面不能
	Character() = default;                       // 仅供子类使用（如 Monster 在函数体里赋值）
	std::string name;
	int hp;
	int maxHp;
	int atk;
	int def;
};
