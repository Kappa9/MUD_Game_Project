#include "Game.h"
int main()
{
	cout << "Hello World!";
	GameThread game;




	return 0;
}

//Fight�Ĺ��캯��
Fight::Fight(NPC* player, NPC* enemy)
{
	this->player = player;
	this->enemy = enemy;
}

//Fight����������
Fight::~Fight()
{
}

//�ж�˭������
NPC* Fight::DecideWhoAct()
{
	if (player->speed >= enemy->speed) {
		return player;
	}
	else {
		return enemy;
	}
}

//ʹ�ü���
void Fight::UseSkill(NPC* role)
{

}

//ս������
void Fight::Fighting()
{
	cout << "����" << enemy->name << "������һ��";
	NPC* actor = DecideWhoAct();
	if (actor->id == 0) {
		cout << "�ֵ����ж��ˣ�";
		player->ShowNPCState();
		cout << "1.���� 2.���� 3.��Ʒ 4.���� ";

		int input = GetUserInput(1, 4);

		if (input == 1) {

		}
		else if (input == 2) {

		}

	}



}
GameThread::GameThread(){
	cout << endl << "Game Started." << endl;
}
void GameThread::LaunchGame() {
	sys.PrintMap();
}
vector<string> GameThread::ReadFile(string fileName) {
	string path = "" + fileName + ".txt";
	fstream fin;
	fin.open(path.c_str(), ios::in);
	vector<string> list;
	string tmp;
	while (getline(fin, tmp))
		list.push_back(tmp);
	return list;
}
vector<string> GameThread::SplitString(string str) {
	vector<string> split;
	string::size_type pos;
	str += ",";
	unsigned int size = str.size();
	for (unsigned int i = 0; i < size; i++) {
		pos = str.find(",", i);
		if (pos < size) {
			string s = str.substr(i, pos - i);
			split.push_back(s);
		}
	}
	return split;
}
void GameThread::GetItemData(vector<string> list) {
	for (string str : list) {
		vector<string> split(SplitString(str));
		Goods i;
		//
		DataList::goodList.push_back(i);
	}
}
void GameThread::SaveGame() {

}
void GameThread::LoadGame() {

}