#pragma once
#include<iostream>
#include<string>
#include <vector>
#include <array>
#include <list>
#include<conio.h>
#include<Windows.h>
#include<fstream>
using namespace std;

//交互系统
class InteractSystem
{
public:
	InteractSystem() {}
	static int UserInput(int maxNum);
	static void PrintLog(string message);
	static void PrintMap();
	static int Dialog(int startLine);
	static vector<string> ReadFile(string fileName);
	static vector<string> SplitString(string str, string pattern);
private:
	static HANDLE handle;
	static int GetUserInput();
};

class Goods {
public:
	Goods();
	Goods(vector<string>list);//物品的构造函数   

	int index;                //编号
	string name;              //名称
	string description;       //描述
	int attribute;            //属性    0-可消耗，1-装备，2-学习
	int location;             //装备位置  0-身，1-手，2-足, 3-非装备
	int cost;                 //价值
	int addHP;                //回复血量
	int addMP;                //回复蓝量
	int addMaxHP;             //增加血量上限
	int addMaxMP;             //增加蓝量上限
	int addAttack;            //增加攻击
	int addDefense;           //增加防御
	int addSpeed;             //增加速度

	void Copy(Goods* thing);//复制物品
	void PrintDescription();//输出物品的详细描述
};

//背包的类
class Bag {
public:
	struct goods {
		Goods* thing;
		int num;

		goods() { thing = NULL; num = 0; }
		goods(Goods* entry_thing, int add_on) {
			thing = entry_thing;
			num = add_on;
		}
	};

	void Print(int page);                          //描述背包中存在的物品
	void PrintPart(int i);                         //描述背包中的部分物体
	void PrintEquipment();                         //描述武器栏中的情况
	void AddGoods(int id,int num=1);               //向背包中添加物品
	void AbandonGoods(int id, int num = 1);        //删除背包中存在的物品
	void AbandonGoods(Goods* thing,int num=1);     //删除背包中存在的物品 
	void ReturnNum(Goods* thing);                  //返回在背包中该物品的剩余情况
	void Equip(Goods* thing);                      //装备背包中的装备 
	void Unload(Goods* thing);                     //卸下武器栏中的中的装备
	void Sell(Goods* thing, int num=1);            //出售背包中的物品
	void Purchase(Goods* thing, int num=1);        //购买物品 
	int ReturnId(int num);                         //返回ID

	int money;
	vector <goods> cargo;
	Goods* equipment[3];
 };



//技能的类
class Skill {
public:
	int id;                    //技能编号
	string name;               //名称
	string description;        //技能描述	
	short MPcost;			   //消耗MP值
	int damage;			       //伤害
	float critRate;           //暴击率
	float accuracyRate;       //命中率

	Skill();                   //构造函数
	Skill(vector<string>list);
	Skill(string name, string description, short Mpcost, int damage, float critRate, float accuracyRate);
	                  
	void Copy(Skill* ability); //复制技能
	void PrintDescription();   //关于技能的详细描述
};

//技能栏的类
class SkillBar {
public:
	void Print();				             //输出技能列表
	void LearnSkill(Skill* ability);         //学习技能

	vector<Skill*>list;
};

//人物的类
class NPC {
public:
	int id;
	string name;          //NPC名称 
	int HPmax;             //最大血量
	int MPmax;             //最大魔法值
	int HP;                //血量
	int MP;                //魔法值
	int speed;             //速度
	int attack;            //攻击
	int defense;           //防御
	int experience;          //经验
	int money;             //金钱
	int talkingScript;         //

	NPC() {};
	NPC(vector<string>list);  //构造函数

	SkillBar skillBar;
	void ShowNPCState();
};


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
};

//商店的类
class store {
public:
	store();                                //构造函数
	void AddGoodsId(int id);                //添加物品的ID
	void Purchase(Hero* player, int id);    //购买物品
	vector<int>goodsIdList;
};

//场景类
class Spot {
public:
	int id;                   //场景编号
	string name;                  //场景名称
	string description;           //场景描述
	vector<int>NPCIdList;                 //包含场景中存在的NPC
	vector<int>nearSpotId;            //包含临近场景的编号

	Spot();
	Spot(vector<string>list);                   //构造函数

	void printSpotInformation();                //输出场景信息
	void printNPCs();                           //输出场景中所有NPC的信息
	void OnEnterSpot();                         //待对接，读地图对话脚本(enterScript)
};


//数据列表
class DataList {
public:
	DataList() {}
	static vector<Goods> goodsList;
	static vector<Skill> skillList;
	static vector<NPC> npcList;
	static vector<Spot> spotList;
	static vector<string> dialogList;
	static array<short, 100> trigger;
};