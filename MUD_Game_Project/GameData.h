#pragma once
#include<iostream>
#include<string>
#include <vector>
#include <list>
#include<conio.h>
#include<Windows.h>
using namespace std;

class Goods {
public:
	string name;            //����
	string description;     //����
	int attribute;          //����    0-�����ģ�1-װ����2-ѧϰ
	int addAtract;          //���ӹ���
	int addDefense;         //���ӷ���
	int addHP;              //�ظ�Ѫ��
	int addMaxHP;           //����Ѫ������
	int addMP;              //�ظ�����
	int addMaxMP;           //������������
	int addSpeed;           //�����ٶ�
	int index;              //���
	int location;           //װ��λ��  0-��1-�֣�2-��, 3-��װ��
	int cost;               //��ֵ

	void Copy(Goods* thing);//������Ʒ
	void PrintDescription();//�����Ʒ����ϸ����
};


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
	void AddGoods(Goods* thing,int num=1);         //�򱳰��������Ʒ
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




class Skill {
public:
	string name;               //����
	string description;        //��������	
	short  MPcost;			   //����MPֵ
	int damage;			       //�˺�
	float  critRate;           //������
	float  accuracyRate;       //������
	int id;                    //���ܱ��

	Skill() ;                //
	Skill(string name=" ", string description=" ", short Mpcost=0, int damage=0, float critRate=0, float accuracyRate=0) ;
	                  
	void Copy(Skill* ability); //���Ƽ���
	void PrintDescription();   //���ڼ��ܵ���ϸ����
};

class SkillBar {
public:
	void Print();				             //��������б�
	void LearnSkill(Skill* ability);         //ѧϰ����

	vector<Skill*>list;
};

class NPC {
public:
	int id;
	string name = NULL;        //NPC���� 
	int HP = 0;                //Ѫ��
	int HPmax = 0;             //��ʼѪ��
	int MP = 0;                //ħ��ֵ
	int MPmax = 0;             //��ʼħ��ֵ
	int speed = 0;             //�ٶ�
	int attack = 0;            //����
	int defense = 0;           //����
	int experience=0;          //����
	int money = 0;             //��Ǯ
	int talkingScript;
	SkillBar skillBar;
	void ShowNPCState();
};



class Hero :public NPC {
public:
	Hero();
	void UsingGoods(int id);                       //ʹ�ñ����е�����Ʒ 
	Bag bag;
};

//������
class Spot {
public:
	int spotNumber;                   //�������
	int NPCnumber;                    //NPC����
	string spotName;                  //��������
	string spotDescription;           //��������


	void readSoptInformation();                 //��ȡ������Ϣ
	void printSpotInformation();                //���������Ϣ
	void printNPCs();                           //�������������NPC����Ϣ


	vector<NPC*>list;                 //���������д��ڵ�NPC
	vector<int>nearSpotNumber;        //�����ٽ������ı��

};

//�����б�
class DataList {
public:
	DataList();
	static vector<Goods> goodsList;
	static vector<Skill> skillList;
	static vector<NPC> npcList;
	static vector<Spot> spotList;
	static short trigger[100];
	
};
//����ϵͳ
class InteractSystem
{
public:
	InteractSystem();
	int GetUserInput();
	int GetUserInput(int maxNum);
	void PrintLog(string message);
	void PrintMap();
private:
	HANDLE handle;
};