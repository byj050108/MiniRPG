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
};

class MonsterFactory
{
public:
    static void loadFromFile(const std::string& path);  // 启动时调用一次，读入怪物表
    static Monster createRandom();                        // 随机抽一条数据造出一只怪

private:
    static std::vector<MonsterData> data;                 // 读进来的怪物表
};
