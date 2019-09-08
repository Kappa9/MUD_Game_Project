#pragma once
#include "GameData.h"
#include<iostream>
#include<string>
#include<vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#define random(x) rand()%(x)


//ս������
class Fight {
public:
	Fight(Hero* player, NPC* enemy);          //���캯��
	~Fight();                                 //��������
	NPC* DecideWhoAct();                      //����˭����
	void UseSkillAttack(NPC* attacker,NPC* defender,int id);        //ʹ�ü�������˺� 
	int ReturnId(NPC* owner, int num);        //���ؼ��ܵı��
	void UseSkill(NPC* role);                 //ʹ�ü���
	bool Escape(NPC* escaper,NPC* arrester);  //����
	void DecideAct(NPC* ememy,NPC* player);   //ememy��ѡ��
	bool DeathOrNot(NPC* player, NPC* enemy); //�ж��Ƿ���������
	void Victory(Hero* player, NPC* enemy);   //ʤ���ж�
	void Fighting();                          //ս������
	
	Hero* player;       //���
	NPC* enemy;         //����
	vector<NPC*>list;   //���ڻغ��ж���vector
};

//̽������                       
class Explore {
public:
	Explore(Hero* hero,int id);
private:
	Hero* hero;
	int spotId;
	void ExploreSpot();
};

//��Ϸ�����࣬���ڽṹ�����
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
	void LaunchGame();

	void GetItemData(vector<string> list);
	void GetSkillData(vector<string> list);
	void GetNPCData(vector<string> list);
	void GetSpotData(vector<string> list);
	
	void NewGame();
	void SaveGame();
	void LoadGame();
};
