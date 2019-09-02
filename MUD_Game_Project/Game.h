#pragma once
#include "GameData.h"
#include<iostream>
#include<string>
#include<vector>
#include <fstream>
class Fight {
public:
	Fight(NPC* player, NPC* enemy);  //构造函数
	~Fight();                        //析构函数
	NPC* DecideWhoAct();             //决定谁先手
	int UseWhichSkill(NPC* role);
	void UseSkill(NPC* role);                 //使用技能
	void Fighting();                 //战斗过程

	NPC* player;        //玩家
	NPC* enemy;         //敌人
	vector<NPC*>list;   //关于回合判定的vector
};

//输入一个数字
int GetUserInput() {
	char str[1];
	str[0] = getchar();
	return (int)str[0];
}

//判定输入正确
int GetUserInput(int min, int max) {
	int n = GetUserInput();
	while (n<min || n>max) {
		cout << "请输入正确的数字";
		n = GetUserInput();
	}
	return n;
}
//游戏进程类，处于结构的最顶层
class GameThread {
public:
	GameThread();
	void LaunchGame();
private:
	InteractSystem sys;
	vector<string> ReadFile(string fileName);
	vector<string> SplitString(string str);
	void GetItemData(vector<string> list);
	void SaveGame();
	void LoadGame();
};
