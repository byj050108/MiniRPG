#include "MonsterFactory.h"
Monster MonsterFactory::create(MonsterType type) 
{
    switch (type) 
    {
        case MonsterType::Slime: return Monster("Slime", 30, 8, 2, 20, 30, 30);
        case MonsterType::Goblin: return Monster("Goblin", 50, 12, 4, 35, 50, 50);
        case MonsterType::Wolf: return Monster("Wolf", 35, 18, 1, 40, 60, 80);
        default: return Monster("Slime", 30, 8, 2, 20, 30, 30);
    }
}