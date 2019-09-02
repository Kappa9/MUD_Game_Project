#pragma once
#include<iostream>
#include<string>
#include <vector>
#include <list>


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
	void AbandonGoods(Goods* thing,int num=1);     //ɾ�������д��ڵ���Ʒ
	void UsingGoods(Goods* thing);                 //ʹ�ñ����е�����Ʒ 
	void ReturnNum(Goods* thing);                  //�����ڱ����и���Ʒ��ʣ�����
	void Equip(Goods* thing);                      //װ�������е�װ�� 
	void Unload(Goods* thing);                     //ж���������е��е�װ��
	void Sell(Goods* thing, int num=1);            //���۱����е���Ʒ
	void Purchase(Goods* thing, int num=1);        //������Ʒ 

	int money;
	vector <goods> cargo;
	Goods* equipment[3];
 };




class Skill {
public:
	string name;               //����
	string description;        //��������	
	short  MPcost;			   //����MPֵ
	string damage;			   //�˺�
	float  critRate;           //������
	float  accuracyRate;       //������

	Skill() ;                //
	Skill(string name=" ", string description=" ", short Mpcost=0, string damage=" ", float critRate=0, float accuracyRate=0) ;
	                  
	void Copy(Skill* ability); //���Ƽ���
	void PrintDescription();   //���ڼ��ܵ���ϸ����
};

class NPC {
public:
	string name = NULL;        //NPC���� 
	int HP = 0;                //Ѫ��
	int HPmax = 0;             //��ʼѪ��
	int MP = 0;                //ħ��ֵ
	int MPmax = 0;             //��ʼħ��ֵ
	int speed = 0;             //�ٶ�
	int attack = 0;            //����
	int defence = 0;           //����

};

class SkillBar {
public:
	void Print();				             //��������б�
	void LearnSkill(Skill* ability);         //ѧϰ����

	vector<Skill*>list;
};

bool IfZero(int num) {
	if (num == 0)
		return true;
	else
		return false;
}

//������
class Spot {
public:
	int spotNumber;                   //�������
	int NPCnumber;                    //NPC����
	string spotName;                  //��������
	string spotDescription;           //��������
	

	void readSoptInformation();                 //��ȡ������Ϣ
	void printSpotInformation();                 //���������Ϣ
	void printNPCs();                            //�������������NPC����Ϣ

	
	vector<NPC*>list;                 //���������д��ڵ�NPC
	vector<int>nearSpotNumber;        //�����ٽ������ı��

};