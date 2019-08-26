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
	int location;           //装备位置  0-头，1-身，2-手,3-足
	int cost;               //价值
	void copy(Goods* thing);//复制
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

	void AddGoods(Goods* thing);        //向背包中添加物品
	void AbandonGoods(Goods* thing);    //删除背包中存在的物品
	void UsingGoods(Goods* thing);      //使用背包中的消耗品 
	void ReturNum(Goods* thing);        //返回在背包中该物品的剩余情况

	std::vector <goods> cargo;
 };

class NPC {
public:
	string Name = NULL;         //NPC名称 
	int HP = 0;                //血量
	int HPMAX = 0;             //初始血量
	int MP = 0;                //魔法值
	int MPMAX = 0;             //初始魔法值
	int Speed = 0;             //速度
	int Attack = 0;            //攻击
	int Defence = 0;           //防御
	string Skill = NULL;             //已学会的技能
};

class CSkill {
public:
	string nName[50]; //名称
	string nDescription[256];//技能描述	
	short nPower;//技能威力
	short nMpCost;//消耗MP值
	string nDamage;//伤害

};

bool IfZero(int num) {
	if (num == 0)
		return true;
	else
		return false;
}