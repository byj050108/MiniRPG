#include "GameManager.h"
#include "Monster.h"
#include "Battle.h"
#include <iostream>
#include <limits>
using namespace std;    

void GameManager::setupPlayer()
{
	string name;
	cout << "Please enter your name: ";
	cin >> name;
	player.setName(name);
}

void GameManager::showMenu() const
{
	cout << "==== Mini RPG ====" << endl;
	cout << "1. Show Player Info" << endl;
	cout << "2. Show Bag" << endl;
	cout << "3. Get Potion" << endl;
	cout << "4. Use Potion" << endl;
	cout << "5. Battle" << endl;
	cout << "6. Visit Shop" << endl;
	cout << "0. Exit" << endl;
	cout << "Enter your choice here: ";
}

//主程序启动
void GameManager::run()
{
	setupPlayer();
	while (running)
	{
		showMenu();
		int num;
		if (!(cin >> num))      // 读数字失败了
		{
			cin.clear();        // 清掉错误标志，让 cin 恢复能用
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ② 丢掉缓冲区里那行坏输入
			cout << "Please enter a number." << endl;
			continue;           // 跳过下面的 switch，回去重新显示菜单
		}
		switch (num)
		{
		case 1: player.show(); break;
		case 2: player.showBag(); break;
		case 3: player.addPotion(); break;
		case 4: player.usePotion(); break;
		case 5:
		{
			Monster m(randomMonsterType());
			m.show();
			bool win = battle(player, m);
			if (!win)                                   //失败则游戏结束
			{
				cout << "Game Over!\n";
				running = false;
			}
			break;
		}
		case 6: visitShop(); break;
		case 0: running = false; break;
		default: cout << "Invalid choice" << endl; break;
		}
	}
}

//商店系统
void GameManager::visitShop()
{
	const int POTION_PRICE = 30;
	bool inShop = true;
	while (inShop)
	{
		cout << "==== Store ====" << endl;
		cout << "1. Potion x1 --------- " << POTION_PRICE << " gold" << endl;
		cout << "0. Leave" << endl;
		cout << "Enter your choice here: ";
		int num;
		if (!(cin >> num))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a number." << endl;
			continue;
		}
		switch (num)
		{
		case 1:
			if (player.spendGold(POTION_PRICE)) { player.addPotion(); }
			else { cout << "You don't have enough gold!" << endl; }
			break;
		case 0: inShop = false; break;
		default: cout << "Invalid choice" << endl; break;
		}
	}
}