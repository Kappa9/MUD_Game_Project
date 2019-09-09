#pragma once
#include "GameData.h"

//勇者类
class Hero :public NPC {
public:
	Hero();
	int level;                                     //等级
	int currentSpotId;
	Bag bag;
	void LevelUp();								   //升级
	void UsingGoods(int id);                       //使用背包中的消耗品
	void MoveToSpot(int id);
private:
	int explist[5] = { 10,40,100,200,200 };
	void ShowHeroState();
	void LearnSkill(int id);					//学习技能
	void OnEnterSpot();
	void ExploreSpot();
	void IdleInput();
	void SaveGame();
};
//商店的类
class Store {
public:
	vector<int>goodsIdList;
	Store();                                //构造函数
	void Print();
	void Purchase(Hero* player, int id);    //购买物品
private:
	void AddGoodsId(int id);                //添加物品的ID
};
//战斗的类
class Fight {
public:
	Fight(Hero* player, int enemyId);          //构造函数
private:
	Hero* player;       //玩家
	vector<NPC*>list;   //关于回合判定的vector

	int Random(int num);
	void Fighting(int id);                          //战斗过程
	void DecideWhoAct(NPC* enemy);                      //决定谁先手
	void UseSkillAttack(NPC* attacker, NPC* defender, int id);        //使用技能造成伤害 
	int ReturnId(NPC* owner, int num);        //返回技能的编号
	int SearchSkill();                 //查看技能列表
	bool Escape(NPC* escaper, NPC* arrester);  //逃跑
	void DecideAct(NPC* ememy, NPC* player);   //ememy的选择
	bool DeathOrNot(NPC* enemy); //判定是否有人死亡
	void Victory(Hero* player, NPC* enemy);   //胜负判定
};
//游戏进程类，处于结构的最顶层
class GameThread {
public:
	GameThread();
	int TitleScreen();
private:
	Hero hero;

	void GetItemData(vector<string> list);
	void GetSkillData(vector<string> list);
	void GetNPCData(vector<string> list);
	void GetSpotData(vector<string> list);
	
	void NewGame();
	bool LoadGame();
};
