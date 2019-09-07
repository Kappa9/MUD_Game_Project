#include "Game.h"
int main()
{
	cout << "Hello World!";
	GameThread game;




	return 0;
}



//Fight的构造函数
Fight::Fight(Hero* player, NPC* enemy)
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
	else {
		return enemy;
	}
}

//技能造成伤害(包括普通攻击）
void Fight::UseSkillAttrck(NPC* attacker,NPC* defender,int id)
{
	int MPcost;
	MPcost = DataList().skillList[id].MPcost;
	if (attacker->MP < MPcost) {
		cout << "魔法值不足";
	}
	else {
		srand((int)time(0));
		if (random(100) <= DataList::skillList[id].accuracyRate) {
			if (random(100) <= DataList::skillList[id].critRate) {
				int damage = DataList().skillList[id].damage * attacker->attack - defender->defense * 2;
				attacker->MP -= MPcost;
				defender->HP -= 2 * damage;
				if (id != 0) {
					cout << attacker->name << "使用了" << DataList().skillList[id].name << "并产生了暴击";
				}
				else {
					cout << "你攻击了" << defender->name << "，并产生了暴击";
				}
				cout << endl << "对" << defender->name << "造成了" << 2 * damage << "点伤害";
			}
			else {
				int damage = DataList().skillList[id].damage * attacker->attack - defender->defense * 2;
				attacker->MP -= MPcost;
				defender->HP -= damage;
				if (id != 0) {
					cout << attacker->name << "使用了" << DataList().skillList[id].name;
				}
				else {
					cout << "你攻击了" << defender->name;
				}
				cout << endl << "对" << defender->name << "造成了" << damage << "点伤害";
			}
		}
		else {
			cout << "你的攻击被闪避了";
		}
	}
}

//返回技能的编号
int Fight::ReturnId(NPC* owner, int num)
{
	return owner->skillBar.list[num]->id;
}

//使用技能
void Fight::UseSkill(NPC* role)
{
	int num = role->skillBar.list.size();
	if (num == 0) {
		cout << "你还未学习技能";
	}
	else {
		cout << "要使用什么技能？";
		role->skillBar.Print();
		cout << role->skillBar.list.size() + 2 <<".取消"<< endl << endl;

		int input = GetInput(1, num + 2);
		//取消
		if (input == num + 2) {
			
		}
		else {
			int id = ReturnId(player, input-1);
			UseSkillAttrck(player, enemy, id);
		}
	}
}

//逃跑
bool Fight::Escape(NPC* escaper,NPC* arrester)
{
	if(escaper->speed>=arrester->speed)
	{
		cout << "成功逃离";
		return true;
	}
	else {
		cout << "逃跑失败";
		return false;
	}

}

//enemy决定行动
void Fight::DecideAct(NPC* enemy,NPC* player)
{
	int num=0;
	int damage=0;
	for (int i = 0; i < enemy->skillBar.list.size(); i++) {
		if ((enemy->skillBar.list[i]->damage * enemy->attack - player->defense * 2) > damage) {
			damage = enemy->skillBar.list[i]->damage * enemy->attack - player->defense * 2;
			num = i;
		}
	}
	UseSkillAttrck(enemy,player,num);
}

//判定一方死亡
bool Fight::DeathOrNot(NPC* player, NPC* enemy)
{
	if ((player->HP <= 0) || (enemy->HP <= 0)) {
		return true;
	}
	else{
		return false;
	}
}

//胜负判定
void Fight::Victory(Hero* player, NPC* enemy)
{
	if (player->HP <= 0) {
		cout << "你被" << enemy->name << "打败了"<<endl;
		cout << "你失败了";
	}
	else {
		cout << "你战胜了" << enemy->name;
		cout << "你获得了" << enemy->experience << "点经验值" << "," << enemy->money << "金币";
		player->bag.money += enemy->money;
		player->experience += enemy->experience;
	}
}

//战斗过程
void Fight::Fighting()
{
	cout << "你与" << enemy->name << "斗在了一起";
	list[0] = DecideWhoAct();
	if (enemy->name == list[0]->name) {
		list[1] = player;
	}
	else {
		list[1] = enemy;
	}
	while (DeathOrNot(player, enemy)) {
		for (int i = 0; i < list.size(); i++) {
			if (list[i]->id == 0) {
				cout << "轮到你行动了！";
				player->ShowNPCState();
				cout << "1.攻击 2.技能 3.物品 4.逃走 ";

				int input = GetInput(1, 4);

				//选择攻击
				if (input == 1) {
					UseSkillAttrck(player, enemy, 0);
				}
				//使用技能
				else if (input == 2) {
					UseSkill(player);
				}
				//使用物品
				else if (input == 3) {
					player->bag.Print(1);
					int input;
					input = GetInput(1, player->bag.cargo.size() + 2);
					//Hero的使用物品 使用RetrunId返回物品的编号
					player->UsingGoods(player->bag.ReturnId(input));
				}
				//逃跑
				else if (input == 4) {
					if (Escape(player, enemy)) {
						break;
					}
					else {
						continue;
					}
				}
			}
			//enemy行动
			else {
				DecideAct(enemy, player);
			}
		}
	}
	Victory(player, enemy);
	//查看等级提升
	if (player->LevelUp()) {
		cout << "恭喜你的等级提升到"<<player->level<<"级";
	}
	else {
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

//字符串分隔
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

//得到物品的数据
void GameThread::GetItemData(vector<string> list) {
	//逐个物品读入
	for (string str : list) {
		//将分隔字符串后的读入新的vector 
		vector<string> split(SplitString(str));
		Goods i(split);
		DataList::goodsList.push_back(i);
	}
}

//得到技能的数据
void GameThread::GetSkillData(vector<string> list)
{
	for (string str : list) {
		//将分隔字符串后的读入新的vector 
		vector<string> split(SplitString(str));
		Skill i(split);
		DataList::skillList.push_back(i);
	}
}

void GameThread::GetNPCData(vector<string> list)
{
	for (string str : list) {
		//将分隔字符串后的读入新的vector 
		vector<string> split(SplitString(str));
		NPC i(split);
		DataList::npcList.push_back(i);
	}
}

void GameThread::GetSpotData(vector<string> list)
{
	for (string str : list) {
		//将分隔字符串后的读入新的vector 
		vector<string> split(SplitString(str));
		Spot i(split);
		DataList::spotList.push_back(i);
	}
}

//储存数据
void GameThread::SaveGame() {

}

//读取数据
void GameThread::LoadGame() {

}

//探索场景
void ExploreSpot(Hero* hero, int spotId)
{
	Spot newSpot = DataList::spotList[spotId];
	cout << "你来到了" << newSpot.spotName << endl << newSpot.spotDescription << endl;
	for (int i = 0; i < newSpot.NPCnumber; i++) {
		cout << "你开始慢慢走向前" << endl;
		cout << "你发现了" << DataList::npcList[newSpot.NPCIdList[i]].name << endl;
		cout << "你要怎么做" << endl;
		int input;
		//这里的判断要改
		if (newSpot.spotNumber == 0) {
			cout << "1. 战斗 2. 偷听 3. 离开";
			input = GetInput(1, 3);
			if (input == 1) {
				Fight newFight(hero, &(DataList::npcList[newSpot.NPCIdList[i]]));
				newFight.Fighting();
			}
			else if (input == 2) {
				//偷听的相关剧情
			}
			else if (input == 3) {
				cout << "你离开了" << newSpot.spotName;
				//离开
			}

		}
		else {
			cout << "1. 战斗 2. 离开";
			input = GetInput(1, 2);
			if (input == 1) {
				Fight newFight(hero, &(DataList::npcList[newSpot.NPCIdList[i]]));
				newFight.Fighting();
			}
			else if (input == 2) {
				cout << "你离开了" << newSpot.spotName;
				//离开
			}
		}


	}
}
