#pragma once
#include "GameData.h"

//勇者类
class Hero :public NPC {
public:
	Hero();
	int level;                                     //等级
	int currentSpotId;
	Bag bag;
	bool LevelUp();								   //升级
	void UsingGoods(int id);                       //使用背包中的消耗品
	void MoveToSpot(int id);
	void ExploreSpot();
};
//商店的类
class store {
public:
	store();                                //构造函数
	void AddGoodsId(int id);                //添加物品的ID
	void Purchase(Hero* player, int id);    //购买物品
	vector<int>goodsIdList;
};
//战斗的类
class Fight {
public:
	Fight(Hero* player, NPC* enemy);          //构造函数
	~Fight();                                 //析构函数
	NPC* DecideWhoAct();                      //决定谁先手
	void UseSkillAttack(NPC* attacker, NPC* defender, int id);        //使用技能造成伤害 
	int ReturnId(NPC* owner, int num);        //返回技能的编号
	void UseSkill(NPC* role);                 //使用技能
	bool Escape(NPC* escaper, NPC* arrester);  //逃跑
	void DecideAct(NPC* ememy, NPC* player);   //ememy的选择
	bool DeathOrNot(NPC* player, NPC* enemy); //判定是否有人死亡
	void Victory(Hero* player, NPC* enemy);   //胜负判定
	void Fighting();                          //战斗过程

	Hero* player;       //玩家
	NPC* enemy;         //敌人
	vector<NPC*>list;   //关于回合判定的vector
private:
	int Random(int num);
};
//游戏进程类，处于结构的最顶层
class GameThread {
public:
	GameThread();
private:
	Hero hero;
	enum Gamestate {
		title, idle, explore, battle, shop
	};
	Gamestate state;

	void HideCursor();
	void TitleScreen();

	void GetItemData(vector<string> list);
	void GetSkillData(vector<string> list);
	void GetNPCData(vector<string> list);
	void GetSpotData(vector<string> list);
	
	void NewGame();
	void SaveGame();
	bool LoadGame();
};
