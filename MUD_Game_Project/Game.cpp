#include "Game.h";

//Fight的构造函数
Fight::Fight(NPC* player, NPC* enemy)
{
	this->player = player;
	this->enemy = enemy;
}

//Fight的析构函数
Fight::~Fight()
{
}

//判定谁先先手
NPC* Fight::DecideWhoAct()
{
	if (player->speed >= enemy->speed) {
		return player;
	}
	if (player->speed < enemy->speed) {
		return enemy;
	}
}

//技能造成伤害
void Fight::UseSkillAttrck(NPC* attacker,NPC* defender,int id)
{
	//int MPcost;
	//MPcost = attacker->skillList.list[num - 1]->MPcost;
	//if (attacker->MP < MPcost) {
	//	cout << "魔法值不足";

	//}
	//else {
	//	int damage = attacker->skillList.list[num - 1]->damage * attacker->attack - defender->defense * 2;
	//	attacker->MP -= MPcost;
	//	defender->HP -= damage;
	//	cout << "你使用了" << attacker->skillList.list[num - 1]->name;
	//	cout << endl << "对" << defender->name << "造成了" << damage << "点伤害";
	//}
}

//使用技能
void Fight::UseSkill(NPC* role)
{
	/*int num = role->skillList.list.size();
	if (num == 0) {
		cout << "你还未学习技能";
	}
	else {
		cout << "要使用什么技能？";
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

//逃跑
void Fight::Escape(NPC* escaper,NPC* arrester)
{
	if(escaper->speed>=arrester->speed)
	{
		cout << "成功逃离";
	}
	else {
		cout << "逃跑失败";
	}

}

//enemy决定行动
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

//战斗过程
void Fight::Fighting()
{
	cout << "你与" << enemy->name << "斗在了一起";
	NPC* actor = DecideWhoAct();
	if (actor->id == 0) {
		cout << "轮到你行动了！";
		player->ShowNPCState();
		cout << "1.攻击 2.技能 3.物品 4.逃走 ";

		int input = GetUserInput(1, 4);

		//选择攻击
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