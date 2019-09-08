#pragma once
#include "GameData.h"

//������
class Hero :public NPC {
public:
	Hero();
	int level;                                     //�ȼ�
	int currentSpotId;
	Bag bag;
	bool LevelUp();								   //����
	void UsingGoods(int id);                       //ʹ�ñ����е�����Ʒ
	void MoveToSpot(int id);
	void ExploreSpot();
};
//�̵����
class store {
public:
	store();                                //���캯��
	void AddGoodsId(int id);                //�����Ʒ��ID
	void Purchase(Hero* player, int id);    //������Ʒ
	vector<int>goodsIdList;
};
//ս������
class Fight {
public:
	Fight(Hero* player, NPC* enemy);          //���캯��
	~Fight();                                 //��������
	NPC* DecideWhoAct();                      //����˭����
	void UseSkillAttack(NPC* attacker, NPC* defender, int id);        //ʹ�ü�������˺� 
	int ReturnId(NPC* owner, int num);        //���ؼ��ܵı��
	void UseSkill(NPC* role);                 //ʹ�ü���
	bool Escape(NPC* escaper, NPC* arrester);  //����
	void DecideAct(NPC* ememy, NPC* player);   //ememy��ѡ��
	bool DeathOrNot(NPC* player, NPC* enemy); //�ж��Ƿ���������
	void Victory(Hero* player, NPC* enemy);   //ʤ���ж�
	void Fighting();                          //ս������

	Hero* player;       //���
	NPC* enemy;         //����
	vector<NPC*>list;   //���ڻغ��ж���vector
private:
	int Random(int num);
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
	void TitleScreen();

	void GetItemData(vector<string> list);
	void GetSkillData(vector<string> list);
	void GetNPCData(vector<string> list);
	void GetSpotData(vector<string> list);
	
	void NewGame();
	void SaveGame();
	bool LoadGame();
};
