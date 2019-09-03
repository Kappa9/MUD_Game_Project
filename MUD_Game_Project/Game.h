#pragma once
#include "GameData.h"
#include<iostream>
#include<string>
#include<vector>
#include <fstream>
class Fight {
public:
	Fight(Hero* player, NPC* enemy);          //���캯��
	~Fight();                                 //��������
	NPC* DecideWhoAct();                      //����˭����
	void UseSkillAttrck(NPC* attacker,NPC* defender,int id);        //ʹ�ü�������˺� 
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

//��Ϸ�����࣬���ڽṹ�����
class GameThread {
public:
	GameThread();
	void LaunchGame();
private:
	InteractSystem sys;
	vector<string> ReadFile(string fileName);
	vector<string> SplitString(string str);
	void GetItemData(vector<string> list);
	void GetSkillData(vector<string> list);
	void GetNPCData(vector<string> list);
	void GetSpotData(vector<string> list);
	void SaveGame();
	void LoadGame();
};
