#pragma once
#include<iostream>
#include<string>
#include <vector>
#include <list>

using namespace std;

class Goods {
public:
	string Name;            //����
	string Description;     //����
	int Attribute;          //����    0-�����ģ�1-װ����2-ѧϰ
	int AddAtract;          //���ӹ���
	int AddDefense;         //���ӷ���
	int AddHP;              //�ظ�Ѫ��
	int AddMaxHP;           //����Ѫ������
	int AddMP;              //�ظ�����
	int AddMaxMP;           //������������
	int AddSpeed;           //�����ٶ�
	int SkillIndex;         //��������
	int Location;           //װ��λ��  0-ͷ��1-��2-��
	int Cost;               //��ֵ
};
class Bag {
public:

	vector<Goods>m_vecItems;
 };
class NPC {
public:
	string Name = NULL;         //NPC���� 
	int HP = 0;                //Ѫ��
	int HPMAX = 0;             //��ʼѪ��
	int MP = 0;                //ħ��ֵ
	int MPMAX = 0;             //��ʼħ��ֵ
	int Speed = 0;             //�ٶ�
	int Attack = 0;            //����
	int Defence = 0;           //����
	string Skill = NULL;             //��ѧ��ļ���
};
class NPC1 :public NPC   //����   
{
public:
	string Name = ("����");
	int inf() {
		cout << Name << endl;             //���߸�����Ϣ������ս��ʱ��ʾ��
		cout << "HP:" << HPMAX << endl;
		cout << "MP:" << MPMAX << endl;
		return 0;
	}
	int elseinf() {
		cout << "������:" << Attack << endl;       //����������Ϣ���鿴���߸�����Ϣʱ��ʾ��
		cout << "������:" << Defence << endl;
		cout << "�ٶ�:" << Speed << endl;
		return 0;
	}
};
class CSkill {
public:
	string nName[50]; //����
	string nDescription[256];//��������	
	short nPower;//��������
	short nMpCost;//����MPֵ
	string nDamage;//�˺�

};