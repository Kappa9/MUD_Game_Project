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
