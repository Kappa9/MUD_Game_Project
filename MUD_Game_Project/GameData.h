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
	int skillIndex;         //��������
	int location;           //װ��λ��  0-��1-�֣�2-��, 3-��װ��
	int cost;               //��ֵ
	void copy(Goods* thing);//������Ʒ
};


class Bag {
public:
	struct goods {
		Goods* thing;
		int num;
	
		goods() { thing = NULL; num = 0; }
		goods(Goods* entry_thing,int add_on) {
			thing = entry_thing;
			num = add_on;
		}
	};

	void Print();                                  //���������д��ڵ���Ʒ
	void PrintEquipment();                         //�����������е����
	void AddGoods(Goods* thing,int num=1);         //�򱳰��������Ʒ
	void AbandonGoods(Goods* thing,int num=1);     //ɾ�������д��ڵ���Ʒ
	void UsingGoods(Goods* thing);                 //ʹ�ñ����е�����Ʒ 
	void ReturNum(Goods* thing);                   //�����ڱ����и���Ʒ��ʣ�����
	void Equip(Goods* thing);                      //װ�������е�װ�� 
	void Unload(Goods* thing);                     //ж���������е��е�װ��
	void Sell(Goods* thing, int num=1);            //���۱����е���Ʒ
	void Purchase(Goods* thing, int num=1);        //������Ʒ

	int money;
	std::vector <goods> cargo;
	Goods* equipment[3];
 };




class CSkill {
public:
	string nName[50]; //����
	string nDescription[256];//��������	
	short nPower;//��������
	short nMpCost;//����MPֵ
	string nDamage;//�˺�

};
class NPC {
public:
	string Name = NULL;        //NPC���� 
	int HP = 0;                //Ѫ��
	int HPMAX = 0;             //��ʼѪ��
	int MP = 0;                //ħ��ֵ
	int MPMAX = 0;             //��ʼħ��ֵ
	int Speed = 0;             //�ٶ�
	int Attack = 0;            //����
	int Defence = 0;           //����
	CSkill skill[5];          //��ѧ��ļ���
};



bool IfZero(int num) {
	if (num == 0)
		return true;
	else
		return false;
}