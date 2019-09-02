#pragma once
#include "GameData.h"
#include<iostream>
#include<string>
#include<vector>

class Fight {
public:
	Fight(NPC* player, NPC* enemy);  //���캯��
	~Fight();                        //��������
	NPC* DecideWhoAct();             //����˭����
	int UseWhichSkill(NPC* role);
	void UseSkill(NPC* role);                 //ʹ�ü���
	void Fighting();                 //ս������

	NPC* player;        //���
	NPC* enemy;         //����
	vector<NPC*>list;   //���ڻغ��ж���vector
};

//����һ������
int GetUserInput() {
	char str[1];
	str[0] = getchar();
	return (int)str[0];
}

//�ж�������ȷ
int GetUserInput(int min, int max) {
	int n = GetUserInput();
	while (n<min || n>max) {
		cout << "��������ȷ������";
		n = GetUserInput();
	}
	return n;
}