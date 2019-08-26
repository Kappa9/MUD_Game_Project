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
