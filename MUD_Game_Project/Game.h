#pragma once
#include "GameData.h"

//������
class Hero :public NPC {
public:
	Hero();
	int level;                                     //�ȼ�
	int currentSpotId;
	Bag bag;
	void LevelUp();								   //����
	void UsingGoods(int id);                       //ʹ�ñ����е�����Ʒ
	void MoveToSpot(int id);
private:
	int explist[5] = { 10,40,100,200,200 };
	void ShowHeroState();
	void LearnSkill(int id);					//ѧϰ����
	void OnEnterSpot();
	void ExploreSpot();
	void IdleInput();
	void SaveGame();
};
//�̵����
class Store {
public:
	vector<int>goodsIdList;
	Store();                                //���캯��
	void Print();
	void Purchase(Hero* player, int id);    //������Ʒ
private:
	void AddGoodsId(int id);                //�����Ʒ��ID
};
//ս������
class Fight {
public:
	Fight(Hero* player, int enemyId);          //���캯��
private:
	Hero* player;       //���
	vector<NPC*>list;   //���ڻغ��ж���vector

	int Random(int num);
	void Fighting(int id);                          //ս������
	void DecideWhoAct(NPC* enemy);                      //����˭����
	void UseSkillAttack(NPC* attacker, NPC* defender, int id);        //ʹ�ü�������˺� 
	int ReturnId(NPC* owner, int num);        //���ؼ��ܵı��
	int SearchSkill();                 //�鿴�����б�
	bool Escape(NPC* escaper, NPC* arrester);  //����
	void DecideAct(NPC* ememy, NPC* player);   //ememy��ѡ��
	bool DeathOrNot(NPC* enemy); //�ж��Ƿ���������
	void Victory(Hero* player, NPC* enemy);   //ʤ���ж�
};
//��Ϸ�����࣬���ڽṹ�����
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
