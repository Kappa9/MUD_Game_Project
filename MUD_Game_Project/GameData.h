#pragma once
#include<iostream>
#include<string>
using namespace std;
class NPC {
public:
	string Name=NULL;         //NPC名称 
	int HP=0;                //血量
	int HPMAX=0;             //初始血量
	int MP=0;                //魔法值
	int MPMAX=0;             //初始魔法值
	int Speed=0;             //速度
	int Attack=0;            //攻击
	int Defence=0;           //防御
	string Skill=NULL;             //已学会的技能
};
class NPC1 :public NPC   //勇者   
{
public:
	string Name = ("勇者");
	int inf(){
		cout << Name << endl;             //勇者个人信息（初次战斗时显示）
		cout << "HP:" << HPMAX << endl;
		cout << "MP:" << MPMAX << endl;
		return 0;
	}
		int elseinf(){
			cout << "攻击力:" << Attack << endl;       //勇者其他信息（查看勇者个人信息时显示）
			cout << "防御力:" << Defence << endl;
			cout << "速度:" << Speed << endl;
			return 0;
	}
};