#include "Game.h";

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
	if (player->speed < enemy->speed) {
		return enemy;
	}
}

//��������˺�
void Fight::UseSkillAttrck(NPC* attacker,NPC* defender,int id)
{
	//int MPcost;
	//MPcost = attacker->skillList.list[num - 1]->MPcost;
	//if (attacker->MP < MPcost) {
	//	cout << "ħ��ֵ����";

	//}
	//else {
	//	int damage = attacker->skillList.list[num - 1]->damage * attacker->attack - defender->defense * 2;
	//	attacker->MP -= MPcost;
	//	defender->HP -= damage;
	//	cout << "��ʹ����" << attacker->skillList.list[num - 1]->name;
	//	cout << endl << "��" << defender->name << "�����" << damage << "���˺�";
	//}
}

//ʹ�ü���
void Fight::UseSkill(NPC* role)
{
	/*int num = role->skillList.list.size();
	if (num == 0) {
		cout << "�㻹δѧϰ����";
	}
	else {
		cout << "Ҫʹ��ʲô���ܣ�";
		role->skillList.Print;
		cout << role->skillList.list.size() + 2 << endl << endl;

		int input = GetUserInput(1, num + 2);
		if (input == num + 2) {

		}
		else {
			UseSkillAttrck(player, input - 1, enemy);
		}
	}*/
}

//����
void Fight::Escape(NPC* escaper,NPC* arrester)
{
	if(escaper->speed>=arrester->speed)
	{
		cout << "�ɹ�����";
	}
	else {
		cout << "����ʧ��";
	}

}

//enemy�����ж�
void Fight::DecideAct(NPC* enemy,NPC* player)
{
	/*int num=0;
	int damage=0;
	for (int i = 0; i < enemy->skillList.list.size(); i++) {
		if ((enemy->skillList.list[i]->damage * enemy->attack - player->defense * 2) > damage) {
			damage = enemy->skillList.list[i]->damage * enemy->attack - player->defense * 2;
			num = i;
		}
	}
	UseSkillAttrck(enemy, num + 1, player);*/
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

		//ѡ�񹥻�
		if (input == 1) {
		/*	Act(player, enemy);*/
		}
		else if (input == 2) {
			UseSkill(player);
		}
		else if (input == 3) {

		}
		else if (input == 4) {
			Escape(player, enemy);
		}

	}
	else {
		DecideAct(enemy, player);
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
	int size = str.size();
	for (int i = 0; i < size; i++) {
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