#pragma once
#include "Monster.h"
class MonsterFactory 
{
public:
    static Monster create(MonsterType type);
};