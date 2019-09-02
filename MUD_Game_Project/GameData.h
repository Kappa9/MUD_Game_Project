#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<conio.h>
#include<Windows.h>
using namespace std;
class Character {
public:
	Character();
	int id;
	string name;
	int talkingScript;
	int hp;
	int maxHp;
	int mp;
	int maxMp;
	int attack;
	int defense;
	int speed;
};
class Hero :Character {
public:
	Hero();
	
};
class Place {
public:
	int id;
	string name;
	void OnEnterPlace();
private:
	vector<int> contactid;
	vector<Character> npc;
	int enterScript;
};
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
