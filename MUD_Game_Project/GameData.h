#pragma once
#include<iostream>
#include<string>
using namespace std;
class NPC {
public:
	string Name=NULL;         //NPC���� 
	int HP=0;                //Ѫ��
	int HPMAX=0;             //��ʼѪ��
	int MP=0;                //ħ��ֵ
	int MPMAX=0;             //��ʼħ��ֵ
	int Speed=0;             //�ٶ�
	int Attack=0;            //����
	int Defence=0;           //����
	string Skill=NULL;             //��ѧ��ļ���
};
class NPC1 :public NPC   //����   
{
public:
	string Name = ("����");
	int inf(){
		cout << Name << endl;             //���߸�����Ϣ������ս��ʱ��ʾ��
		cout << "HP:" << HPMAX << endl;
		cout << "MP:" << MPMAX << endl;
		return 0;
	}
		int elseinf(){
			cout << "������:" << Attack << endl;       //����������Ϣ���鿴���߸�����Ϣʱ��ʾ��
			cout << "������:" << Defence << endl;
			cout << "�ٶ�:" << Speed << endl;
			return 0;
	}
};