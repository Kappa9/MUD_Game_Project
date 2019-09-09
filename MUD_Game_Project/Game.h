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
	void IdleInput();
	void SaveGame();
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
	Fight(Hero* player, int enemyId);          //���캯��
	~Fight();                                 //��������
	void Fighting(int id);                          //ս������
	void DecideWhoAct(NPC* enemy);                      //����˭����
	void UseSkillAttack(NPC* attacker, NPC* defender, int id);        //ʹ�ü�������˺� 
	int ReturnId(NPC* owner, int num);        //���ؼ��ܵı��
	int SearchSkill();                 //�鿴�����б�
	bool Escape(NPC* escaper, NPC* arrester);  //����
	void DecideAct(NPC* ememy, NPC* player);   //ememy��ѡ��
	bool DeathOrNot(NPC* enemy); //�ж��Ƿ���������
	void Victory(Hero* player, NPC* enemy);   //ʤ���ж�

	Hero* player;       //���
	vector<NPC*>list;   //���ڻغ��ж���vector
private:
	int Random(int num);
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
