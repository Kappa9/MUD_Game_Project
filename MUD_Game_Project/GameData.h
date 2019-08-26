#pragma once
#include<iostream>
#include<string>
#include <vector>
#include <list>

using namespace std;

class Goods {
public:
	string Name;            //名称
	string Description;     //描述
	int Attribute;          //属性    0-可消耗，1-装备，2-学习
	int AddAtract;          //增加攻击
	int AddDefense;         //增加防御
	int AddHP;              //回复血量
	int AddMaxHP;           //增加血量上限
	int AddMP;              //回复蓝量
	int AddMaxMP;           //增加蓝量上限
	int AddSpeed;           //增加速度
	int SkillIndex;         //技能书编号
	int Location;           //装备位置  0-头，1-身，2-手
	int Cost;               //价值
};
class Bag {
public:

	vector<Goods>m_vecItems;
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
class NPC1 :public NPC   //勇者   
{
public:
	string Name = ("勇者");
	int inf() {
		cout << Name << endl;             //勇者个人信息（初次战斗时显示）
		cout << "HP:" << HPMAX << endl;
		cout << "MP:" << MPMAX << endl;
		return 0;
	}
	int elseinf() {
		cout << "攻击力:" << Attack << endl;       //勇者其他信息（查看勇者个人信息时显示）
		cout << "防御力:" << Defence << endl;
		cout << "速度:" << Speed << endl;
		return 0;
	}
};
class CSkill {
public:
	string nName[50]; //名称
	string nDescription[256];//技能描述	
	short nPower;//技能威力
	short nMpCost;//消耗MP值
	string nDamage;//伤害

};