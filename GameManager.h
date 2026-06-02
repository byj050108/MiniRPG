#pragma once
#include "Player.h"

class GameManager
{
public:
	void run();                 // 程序入口：跑整个游戏循环
private:
	Player player;              // GameManager "拥有" 一个玩家
	bool running = true;
	void showMenu() const;
	void setupPlayer();
	void visitShop();
};