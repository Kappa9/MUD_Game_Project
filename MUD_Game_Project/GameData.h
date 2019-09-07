#pragma once
#include<iostream>
#include<string>
#include <vector>
#include <array>
#include <list>
#include<conio.h>
#include<Windows.h>
#include<fstream>
using namespace std;

//����ϵͳ
class InteractSystem
{
public:
	InteractSystem() {}
	static int UserInput(int maxNum);
	static void PrintLog(string message);
	static void PrintMap();
	static int Dialog(int startLine);
	static vector<string> ReadFile(string fileName);
	static vector<string> SplitString(string str, string pattern);
private:
	static HANDLE handle;
	static int GetUserInput();
};

class Goods {
public:
	Goods();
	Goods(vector<string>list);//��Ʒ�Ĺ��캯��   

	int index;                //���
	string name;              //����
	string description;       //����
	int attribute;            //����    0-�����ģ�1-װ����2-ѧϰ
	int location;             //װ��λ��  0-��1-�֣�2-��, 3-��װ��
	int cost;                 //��ֵ
	int addHP;                //�ظ�Ѫ��
	int addMP;                //�ظ�����
	int addMaxHP;             //����Ѫ������
	int addMaxMP;             //������������
	int addAttack;            //���ӹ���
	int addDefense;           //���ӷ���
	int addSpeed;             //�����ٶ�

	void Copy(Goods* thing);//������Ʒ
	void PrintDescription();//�����Ʒ����ϸ����
};

//��������
class Bag {
public:
	struct goods {
		Goods* thing;
		int num;

		goods() { thing = NULL; num = 0; }
		goods(Goods* entry_thing, int add_on) {
			thing = entry_thing;
			num = add_on;
		}
	};

	void Print(int page);                          //���������д��ڵ���Ʒ
	void PrintPart(int i);                         //���������еĲ�������
	void PrintEquipment();                         //�����������е����
	void AddGoods(int id,int num=1);               //�򱳰��������Ʒ
	void AbandonGoods(int id, int num = 1);        //ɾ�������д��ڵ���Ʒ
	void AbandonGoods(Goods* thing,int num=1);     //ɾ�������д��ڵ���Ʒ 
	void ReturnNum(Goods* thing);                  //�����ڱ����и���Ʒ��ʣ�����
	void Equip(Goods* thing);                      //װ�������е�װ�� 
	void Unload(Goods* thing);                     //ж���������е��е�װ��
	void Sell(Goods* thing, int num=1);            //���۱����е���Ʒ
	void Purchase(Goods* thing, int num=1);        //������Ʒ 
	int ReturnId(int num);                         //����ID

	int money;
	vector <goods> cargo;
	Goods* equipment[3];
 };



//���ܵ���
class Skill {
public:
	int id;                    //���ܱ��
	string name;               //����
	string description;        //��������	
	short MPcost;			   //����MPֵ
	int damage;			       //�˺�
	float critRate;           //������
	float accuracyRate;       //������

	Skill();                   //���캯��
	Skill(vector<string>list);
	Skill(string name, string description, short Mpcost, int damage, float critRate, float accuracyRate);
	                  
	void Copy(Skill* ability); //���Ƽ���
	void PrintDescription();   //���ڼ��ܵ���ϸ����
};

//����������
class SkillBar {
public:
	void Print();				             //��������б�
	void LearnSkill(Skill* ability);         //ѧϰ����

	vector<Skill*>list;
};

//�������
class NPC {
public:
	int id;
	string name;          //NPC���� 
	int HPmax;             //���Ѫ��
	int MPmax;             //���ħ��ֵ
	int HP;                //Ѫ��
	int MP;                //ħ��ֵ
	int speed;             //�ٶ�
	int attack;            //����
	int defense;           //����
	int experience;          //����
	int money;             //��Ǯ
	int talkingScript;         //

	NPC() {};
	NPC(vector<string>list);  //���캯��

	SkillBar skillBar;
	void ShowNPCState();
};


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
};

//�̵����
class store {
public:
	store();                                //���캯��
	void AddGoodsId(int id);                //�����Ʒ��ID
	void Purchase(Hero* player, int id);    //������Ʒ
	vector<int>goodsIdList;
};

//������
class Spot {
public:
	int id;                   //�������
	string name;                  //��������
	string description;           //��������
	vector<int>NPCIdList;                 //���������д��ڵ�NPC
	vector<int>nearSpotId;            //�����ٽ������ı��

	Spot();
	Spot(vector<string>list);                   //���캯��

	void printSpotInformation();                //���������Ϣ
	void printNPCs();                           //�������������NPC����Ϣ
	void OnEnterSpot();                         //���Խӣ�����ͼ�Ի��ű�(enterScript)
};


//�����б�
class DataList {
public:
	DataList() {}
	static vector<Goods> goodsList;
	static vector<Skill> skillList;
	static vector<NPC> npcList;
	static vector<Spot> spotList;
	static vector<string> dialogList;
	static array<short, 100> trigger;
};