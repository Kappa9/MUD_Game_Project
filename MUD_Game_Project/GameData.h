#pragma once
#include<iostream>
#include<string>
#include <vector>
#include <list>

using namespace std;

class Goods {
public:
	string name;            //名称
	string description;     //描述
	int attribute;          //属性    0-可消耗，1-装备，2-学习
	int addAtract;          //增加攻击
	int addDefense;         //增加防御
	int addHP;              //回复血量
	int addMaxHP;           //增加血量上限
	int addMP;              //回复蓝量
	int addMaxMP;           //增加蓝量上限
	int addSpeed;           //增加速度
	int skillIndex;         //技能书编号
	int location;           //装备位置  0-身，1-手，2-足, 3-非装备
	int cost;               //价值
	void copy(Goods* thing);//复制物品
};


class Bag {
public:
	struct goods {
		Goods* thing;
		int num;
	
		goods() { thing = NULL; num = 0; }
		goods(Goods* entry_thing,int add_on) {
			thing = entry_thing;
			num = add_on;
		}
	};

	void Print();                                  //描述背包中存在的物品
	void PrintEquipment();                         //描述武器栏中的情况
	void AddGoods(Goods* thing,int num=1);         //向背包中添加物品
	void AbandonGoods(Goods* thing,int num=1);     //删除背包中存在的物品
	void UsingGoods(Goods* thing);                 //使用背包中的消耗品 
	void ReturNum(Goods* thing);                   //返回在背包中该物品的剩余情况
	void Equip(Goods* thing);                      //装备背包中的装备 
	void Unload(Goods* thing);                     //卸下武器栏中的中的装备
	void Sell(Goods* thing, int num=1);            //出售背包中的物品
	void Purchase(Goods* thing, int num=1);        //购买物品

	int money;
	std::vector <goods> cargo;
	Goods* equipment[3];
 };




class CSkill {
public:
	string nName[50]; //名称
	string nDescription[256];//技能描述	
	short nPower;//技能威力
	short nMpCost;//消耗MP值
	string nDamage;//伤害

};
class NPC {
public:
	string Name = NULL;        //NPC名称 
	int HP = 0;                //血量
	int HPMAX = 0;             //初始血量
	int MP = 0;                //魔法值
	int MPMAX = 0;             //初始魔法值
	int Speed = 0;             //速度
	int Attack = 0;            //攻击
	int Defence = 0;           //防御
	CSkill skill[5];          //已学会的技能
};



bool IfZero(int num) {
	if (num == 0)
		return true;
	else
		return false;
}