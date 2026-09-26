#pragma once
#include <string>
#include <vector>
#include "Monster.h"

// 一只怪物的原始数值（从文件读进来）
struct MonsterData
{
    std::string name;
    int hp;
    int atk;
    int def;
    int rewardGold;
    int dropChance;
    int rewardExp;
    int minLevel;
};

class MonsterFactory
{
public:
    static void loadFromFile(const std::string& path);  // 启动时调用一次，读入怪物表
    static Monster createRandom(int playerLevel);                        // 从当前等级可遇到的怪物中随机抽取

private:
    static std::vector<MonsterData> data;                 // 读进来的怪物表
};
