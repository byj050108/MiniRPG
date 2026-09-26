#include "MonsterFactory.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
using namespace std;

// 静态成员的定义
vector<MonsterData> MonsterFactory::data;

// 工厂的随机引擎
static mt19937 rng(random_device{}());

// 从文件加载怪物表，启动时调用一次
void MonsterFactory::loadFromFile(const string& path)
{
    data.clear();                       // 防止重复调用时叠加
    ifstream file(path);
    if (!file)
    {
        cout << "[Error] Cannot open monster data file: " << path << endl;
        return;
    }

    string line;
    bool headerSkipped = false;         // CSV 第一行是表头（列名），跳过
    while (getline(file, line))
    {
        // 处理 Windows 的 \r\n 换行：去掉行尾可能残留的 '\r'
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        // 跳过空行和以 # 开头的注释行
        if (line.empty() || line[0] == '#')
            continue;

        if (!headerSkipped)             // 第一行有效行是表头，跳过它
        {
            headerSkipped = true;
            continue;
        }

        // 按逗号切出 8 个字段
        stringstream ss(line);
        MonsterData d;
        string field;
        try
        {
            getline(ss, d.name, ',');
            getline(ss, field, ','); d.hp = stoi(field);
            getline(ss, field, ','); d.atk = stoi(field);
            getline(ss, field, ','); d.def = stoi(field);
            getline(ss, field, ','); d.rewardGold = stoi(field);
            getline(ss, field, ','); d.dropChance = stoi(field);
            getline(ss, field, ','); d.rewardExp = stoi(field);
            getline(ss, field, ','); d.minLevel = stoi(field);
        }
        catch (const exception&)        // stoi 遇到非法数字会抛异常
        {
            cout << "[Warning] Skipped malformed line: " << line << endl;
            continue;
        }
        if (d.name.empty() || d.hp <= 0 || d.atk < 0 || d.def < 0 ||
            d.rewardGold < 0 || d.dropChance < 0 || d.dropChance > 100 ||
            d.rewardExp < 0 || d.minLevel < 1)
        {
            cout << "[Warning] Skipped invalid monster stats: " << line << endl;
            continue;
        }
        data.push_back(d);
    }

    cout << "Loaded " << data.size() << " monster types." << endl;
}

// 从玩家当前等级可遇到的怪物中随机造一只
Monster MonsterFactory::createRandom(int playerLevel)
{
    if (data.empty())   // 兜底：文件没读到时不崩溃，给个默认史莱姆
    {
        cout << "[Error] No monster data loaded! Using a default Slime." << endl;
        return Monster("Slime", 30, 8, 2, 20, 30, 30);
    }

    vector<const MonsterData*> eligible;
    for (const MonsterData& monster : data)
    {
        if (monster.minLevel <= playerLevel)
            eligible.push_back(&monster);
    }
    if (eligible.empty())
    {
        cout << "[Error] No monsters available for this level! Using a default Slime." << endl;
        return Monster("Slime", 30, 8, 2, 20, 30, 30);
    }

    uniform_int_distribution<size_t> dist(0, eligible.size() - 1);
    const MonsterData& d = *eligible[dist(rng)];
    return Monster(d.name, d.hp, d.atk, d.def, d.rewardGold, d.dropChance, d.rewardExp);
}
