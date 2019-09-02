#pragma once
#include "GameData.h"
#include <fstream>
//��Ϸ�����࣬���ڽṹ�����
class GameThread {
public:
	GameThread();
	void LaunchGame();
private:
	InteractSystem sys;
	vector<string> ReadFile(string fileName);
	vector<string> SplitString(string str);
	void GetItemData(vector<string> list);
	void SaveGame();
	void LoadGame();
};
