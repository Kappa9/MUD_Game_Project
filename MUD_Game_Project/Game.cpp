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
void Fight::UseSkillAttack(NPC* attacker,NPC* defender,int id)
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

		int input = InteractSystem::UserInput(num + 2);
		//取消
		if (input == num + 2) {
			
		}
		else {
			int id = ReturnId(player, input-1);
			UseSkillAttack(player, enemy, id);
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
	UseSkillAttack(enemy,player,num);
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

				int input = InteractSystem::UserInput(4);

				//选择攻击
				if (input == 1) {
					UseSkillAttack(player, enemy, 1);
				}
				//使用技能
				else if (input == 2) {
					UseSkill(player);
				}
				//使用物品
				else if (input == 3) {
					player->bag.Print(1);
					int input;
					input = InteractSystem::UserInput(player->bag.cargo.size() + 2);
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

GameThread::GameThread() {
	GetItemData(InteractSystem::ReadFile("Goods"));
	GetSkillData(InteractSystem::ReadFile("Skill"));
	GetNPCData(InteractSystem::ReadFile("NPC"));
	GetSpotData(InteractSystem::ReadFile("Spot"));
	DataList::dialogList = InteractSystem::ReadFile("Dialog");
	HideCursor();
	LaunchGame();
}
void GameThread::LaunchGame() {
	cout << endl << "Game Started." << endl;
}
//隐藏光标函数
void GameThread::HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//得到物品的数据
void GameThread::GetItemData(vector<string> list) {
	//逐个物品读入
	for (string str : list) {
		//将分隔字符串后的读入新的vector 
		vector<string> split(InteractSystem::SplitString(str, ","));
		Goods i(split);
		DataList::goodsList.push_back(i);
	}
}

//得到技能的数据
void GameThread::GetSkillData(vector<string> list)
{
	for (string str : list) {
		//将分隔字符串后的读入新的vector 
		vector<string> split(InteractSystem::SplitString(str, ","));
		Skill i(split);
		DataList::skillList.push_back(i);
	}
}

void GameThread::GetNPCData(vector<string> list)
{
	for (string str : list) {
		//将分隔字符串后的读入新的vector 
		vector<string> split(InteractSystem::SplitString(str, ","));
		NPC i(split);
		DataList::npcList.push_back(i);
	}
}

void GameThread::GetSpotData(vector<string> list)
{
	int lineNum = 1;
	Spot newSpot;
	vector<string> split;
	for (string str : list) {
		split = (InteractSystem::SplitString(str, ","));
		switch (lineNum) {
		case 1:
			newSpot.id = atoi(split[0].c_str());
			newSpot.name = split[1];
			newSpot.description = split[2];
			break;
		case 2:
			for (string i : split)
				newSpot.NPCIdList.push_back(atoi(i.c_str()));
			break;
		case 3:
			for (string i : split)
				newSpot.nearSpotId.push_back(atoi(i.c_str()));
			DataList::spotList.push_back(newSpot);
			lineNum = 0;
			newSpot.NPCIdList.clear();
			newSpot.nearSpotId.clear();
			break;
		default:
			break;
		}
		lineNum++;
	}
}

//储存数据
void GameThread::SaveGame(Hero* hero) {
	//先删除文件
	fstream fout("stuinfo.txt", ios::out | ios::trunc);  //具体的存档文件的名字需要改 

	fout << hero->name << endl;
	fout << hero->HP << endl;
	fout << hero->HPmax << endl;
	fout << hero->MP << endl;
	fout << hero->MPmax << endl;
	fout << hero->speed << endl;
	fout << hero->attack << endl;
	fout << hero->defense << endl;
	fout << hero->experience << endl;
	fout << hero->money<< endl;
	
	//存储背包中的物品的id
	for (int i = 0; i < hero->bag.cargo.size(); i++) {
		fout << hero->bag.cargo[i].thing->index << endl;
	}
	fout << " "<<endl;
	//存储背包中的对应物品的数量
	for (int i = 0; i < hero->bag.cargo.size(); i++) {
		fout << hero->bag.cargo[i].num << endl;
	}
	fout << " " << endl;

	for (int i = 0; i < hero->bag.cargo.size(); i++) {
		fout << hero->bag.equipment[i]->index << endl;
	}
	fout << " " << endl;

	//存储对话的开关
	for (int i = 0; i < DataList::trigger.size(); i++) {
		fout << DataList::trigger[i] << endl;
	}
	
	fout.close();
}

//读取数据
void GameThread::LoadGame(Hero* hero) {
	ifstream in;
	string line;
	in.open("filename.txt");  //需要具体改名字

	//读取关于hero的属性
	getline(in, line);
	hero->name = line;
	getline(in,line);
	hero->HP = atoi(line.c_str());
	getline(in, line);
	hero->HPmax = atoi(line.c_str());
	getline(in, line);
	hero->MP = atoi(line.c_str());
	getline(in, line);
	hero->MPmax = atoi(line.c_str());
	getline(in, line);
	hero->speed = atoi(line.c_str());
	getline(in, line);
	hero->attack = atoi(line.c_str());
	getline(in, line);
	hero->defense = atoi(line.c_str());
	getline(in, line);
	hero->experience = atoi(line.c_str());
	getline(in, line);
	hero->money = atoi(line.c_str());

	//先清空背包 
	hero->bag.cargo.clear();

	//读取背包内的物品种类
	for (int i=0; line != "";i++) {
		hero->bag.AddGoods(atoi(line.c_str()));
		getline(in, line);
	}

	getline(in, line);

	//读取背包内对应的物品种类的数量
	for (int i = 0; line != ""; i++) {
		hero->bag.cargo[i].num = atoi(line.c_str());
		getline(in, line);
	}

	getline(in, line);
	//读取关于装备栏中装备的信息
	for (int i = 0; line != ""; i++) {
		hero->bag.equipment[i]=(&(DataList::goodsList[atoi(line.c_str())]));
	}

	//读取关于对话的开关
	for (int i = 0; i < DataList::trigger.size(); i++) {
		DataList::trigger[i] = atoi(line.c_str());
	}

	in.close();
}

Explore::Explore(Hero* player, int id) {
	hero = player;
	spotId = id;
	ExploreSpot();
}
//探索场景
void Explore::ExploreSpot()
{
	Spot newSpot = DataList::spotList[spotId];
	cout << "你来到了" << newSpot.name << endl << newSpot.description << endl;
	for (int i = 0; i < newSpot.NPCIdList.size; i++) {
		cout << "你开始慢慢走向前" << endl;
		cout << "你发现了" << DataList::npcList[newSpot.NPCIdList[i]].name << endl;
		cout << "你要怎么做" << endl;
		int input;
		//这里的判断要改
		if (newSpot.id == 0) {
			cout << "1. 战斗 2. 偷听 3. 离开";
			input = InteractSystem::UserInput(3);
			if (input == 1) {
				Fight newFight(hero, &(DataList::npcList[newSpot.NPCIdList[i]]));
				newFight.Fighting();
			}
			else if (input == 2) {
				//偷听的相关剧情
			}
			else if (input == 3) {
				cout << "你离开了" << newSpot.name;
				//离开
			}

		}
		else {
			cout << "1. 战斗 2. 离开";
			input = InteractSystem::UserInput(2);
			if (input == 1) {
				Fight newFight(hero, &(DataList::npcList[newSpot.NPCIdList[i]]));
				newFight.Fighting();
			}
			else if (input == 2) {
				cout << "你离开了" << newSpot.name;
				//离开
			}
		}
	}
}
