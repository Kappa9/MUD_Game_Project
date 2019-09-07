#pragma once
#include "GameData.h"
#include<iostream>
#include<string>
#include<vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#define random(x) rand()%(x)


//战斗的类
class Fight {
public:
	Fight(Hero* player, NPC* enemy);          //构造函数
	~Fight();                                 //析构函数
	NPC* DecideWhoAct();                      //决定谁先手
	void UseSkillAttack(NPC* attacker,NPC* defender,int id);        //使用技能造成伤害 
	int ReturnId(NPC* owner, int num);        //返回技能的编号
	void UseSkill(NPC* role);                 //使用技能
	bool Escape(NPC* escaper,NPC* arrester);  //逃跑
	void DecideAct(NPC* ememy,NPC* player);   //ememy的选择
	bool DeathOrNot(NPC* player, NPC* enemy); //判定是否有人死亡
	void Victory(Hero* player, NPC* enemy);   //胜负判定
	void Fighting();                          //战斗过程
	
	Hero* player;       //玩家
	NPC* enemy;         //敌人
	vector<NPC*>list;   //关于回合判定的vector
};

//探索场景
void ExploreSpot(Hero* hero,int spotId);                           



//游戏进程类，处于结构的最顶层
class GameThread {
public:
	GameThread();
	void LaunchGame();
private:
	vector<string> ReadFile(string fileName);
	vector<string> SplitString(string str);
	void GetItemData(vector<string> list);
	void GetSkillData(vector<string> list);
	void GetNPCData(vector<string> list);
	void GetSpotData(vector<string> list);
	enum Gamestate {
		Title, Battle
	};
	Gamestate state;
	void SaveGame(Hero* hero);
	void LoadGame(Hero* hero);
};
