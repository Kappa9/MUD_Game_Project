#include "Game.h"
int main() {
	GameThread game;
	int input = 0;
	while (input != 3) {
		if(DataList::state==DataList::over)
			game.TitleScreen();
	}
	return 0;
}

GameThread::GameThread() {
	GetItemData(InteractSystem::ReadFile("Goods"));
	GetSkillData(InteractSystem::ReadFile("Skill"));
	GetNPCData(InteractSystem::ReadFile("NPC"));
	GetSpotData(InteractSystem::ReadFile("Spot"));
	DataList::dialogList = InteractSystem::ReadFile("Dialog");
}
//标题画面
int GameThread::TitleScreen() {
	system("cls");
	DataList::state == DataList::title;
	InteractSystem::PrintMap();
	cout << "MUDGAME" << endl << endl;
	cout << "1.新的开始" << endl;
	cout << "2.旧的回忆" << endl;
	cout << "3.退出游戏" << endl;
	int input = InteractSystem::UserInput(3);
	switch (input) {
	case 1:
		NewGame();
		break;
	case 2:
		if (LoadGame()) {
			DataList::state = DataList::idle;
			hero.MoveToSpot(hero.currentSpotId);
		}
		else
			cout << endl << "未找到存档文件！" << endl << endl;
		break;
	case 3:
		exit(0);
		break;
	default:
		break;
	}
	return input;
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
void GameThread::GetSkillData(vector<string> list) {
	for (string str : list) {
		//将分隔字符串后的读入新的vector 
		vector<string> split(InteractSystem::SplitString(str, ","));
		Skill i(split);
		DataList::skillList.push_back(i);
	}
}
//得到NPC的数据
void GameThread::GetNPCData(vector<string> list) {
	int lineNum = 1;
	NPC newNPC;
	vector<string> split;
	for (string str : list) {
		split = (InteractSystem::SplitString(str, ","));
		switch (lineNum) {
		case 1:
			newNPC.id = atoi(split[0].c_str());
			newNPC.name = split[1];
			newNPC.HPmax = atoi(split[2].c_str());
			newNPC.MPmax = atoi(split[3].c_str());
			newNPC.HP = newNPC.HPmax; newNPC.MP = newNPC.MPmax;
			newNPC.speed = atoi(split[4].c_str());
			newNPC.attack = atoi(split[5].c_str());
			newNPC.defense = atoi(split[6].c_str());
			newNPC.experience = atoi(split[7].c_str());
			newNPC.money = atoi(split[8].c_str());
			newNPC.talkingScript = atoi(split[9].c_str());
			break;
		case 2:
			if (str != "-1") {
				for (string i : split)
					newNPC.skillBar.list.push_back(&DataList::skillList[atoi(i.c_str())]);
				DataList::npcList.push_back(newNPC);
				lineNum = 0;
				newNPC.skillBar.list.clear();
			}
			break;
		default:
			break;
		}
		lineNum++;
	}
	int j = 0;
}
//得到地图的数据
void GameThread::GetSpotData(vector<string> list) {
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
			if (str != "-1") {
				for (string i : split)
					newSpot.NPCIdList.push_back(atoi(i.c_str()));
			}
			break;
		case 3:
			if (str != "-1") {
				for (string i : split)
					newSpot.nearSpotId.push_back(atoi(i.c_str()));
				DataList::spotList.push_back(newSpot);
				lineNum = 0;
				newSpot.NPCIdList.clear();
				newSpot.nearSpotId.clear();
			}
			break;
		default:
			break;
		}
		lineNum++;
	}
}
//新的游戏
void GameThread::NewGame() {
	DataList::state = DataList::idle;
	hero.MoveToSpot(0);
}
//储存数据
void Hero::SaveGame() {
	//先删除文件
	fstream fout("save.txt", ios::out | ios::trunc);  //具体的存档文件的名字需要改 
	fout << level << endl;
	fout << HPmax << endl;
	fout << MPmax << endl;
	fout << HP << endl;
	fout << MP << endl;
	fout << speed << endl;
	fout << attack << endl;
	fout << defense << endl;
	fout << experience << endl;
	fout << bag.money<< endl;
	fout << currentSpotId<< endl;
	
	//存储背包中的物品的id
	for (int i = 0; i < bag.cargo.size(); i++) {
		fout << bag.cargo[i].thing->index << endl;
	}
	fout << " "<<endl;
	//存储背包中的对应物品的数量
	for (int i = 0; i < bag.cargo.size(); i++) {
		fout << bag.cargo[i].num << endl;
	}
	fout << " " << endl;
	//存储装备中的对应物品的id
	for (int i = 0; i < bag.cargo.size(); i++) {
		fout << bag.equipment[i]->index << endl;
	}
	fout << " " << endl;
	//存储对话的开关
	for (int i = 0; i < DataList::trigger.size(); i++) {
		fout << DataList::trigger[i] << endl;
	}
	fout << " " << endl;
	fout.close();
}
//读取数据
bool GameThread::LoadGame() {
	ifstream in;
	string line;
	in.open("save.txt");  //需要具体改名字
	if (in.is_open()) {
		//读取关于hero的属性
		getline(in, line);
		hero.level = (atoi(line.c_str()));
		getline(in, line);
		hero.HPmax = atoi(line.c_str());
		getline(in, line);
		hero.MPmax = atoi(line.c_str());
		getline(in, line);
		hero.HP = atoi(line.c_str());
		getline(in, line);
		hero.MP = atoi(line.c_str());
		getline(in, line);
		hero.speed = atoi(line.c_str());
		getline(in, line);
		hero.attack = atoi(line.c_str());
		getline(in, line);
		hero.defense = atoi(line.c_str());
		getline(in, line);
		hero.experience = atoi(line.c_str());
		getline(in, line);
		hero.bag.money = atoi(line.c_str());
		getline(in, line);
		hero.currentSpotId = atoi(line.c_str());

		//先清空背包 
		hero.bag.cargo.clear();
		getline(in, line);
		//读取背包内的物品种类
		for (int i = 0; line != " "; i++) {
			hero.bag.AddGoods(atoi(line.c_str()));
			getline(in, line);
		}
		getline(in, line);
		//读取背包内对应的物品种类的数量
		for (int i = 0; line != " "; i++) {
			hero.bag.cargo[i].num = atoi(line.c_str());
			getline(in, line);
		}
		getline(in, line);
		//读取关于装备栏中装备的信息
		for (int i = 0; line != " "; i++) {
			hero.bag.equipment[i] = (&(DataList::goodsList[atoi(line.c_str())]));
			getline(in, line);
		}
		getline(in, line);
		//读取关于对话的开关
		for (int i = 0; i < DataList::trigger.size(); i++) {
			DataList::trigger[i] = atoi(line.c_str());
			getline(in, line);
		}
		in.close();
		return true;
	}
	else return false;
}
//Hero构造函数
Hero::Hero() {
	id = 0; name = "勇者";
	HPmax = 450; MPmax = 90;
	HP = HPmax; MP = MPmax;
	speed = 24; attack = 16; defense = 16;
	experience = 0; level = 1;
	money = 0; bag.money = 0;
	currentSpotId = -1;
}
//升级
bool Hero::LevelUp() {
	int num = level;
	int explist[4] = { 10,40,100,200 };
	while (level < 5 && experience >= explist[level - 1]) {
		level++;
		HPmax += 50;
		MPmax += 10;
		HP += 50;
		MP += 10;
		attack += 2;
		defense += 2;
		speed += 2;
	}
	if (level > num) return true;
	else return false;
}
//Hero在背包中使用消耗品
void Hero::UsingGoods(int id) {
	Goods usingGoods(DataList().goodsList[id]);
	if (bag.AbandonGoods(id)) {
		int addHp = DataList().goodsList[id].addHP;
		int addMp = DataList().goodsList[id].addMP;
		switch (usingGoods.attribute) {
		case 0:
			cout << "你使用了" << usingGoods.name << endl;
			if (addHp > 0) {
				addHp = min(addHp, HPmax - HP);
				cout << "你的HP增加了" << addHp << "点" << endl;
			}
			if (addMp > 0) {
				addHp = min(addMp, MPmax - MP);
				cout << "你的MP增加了" << addMp << "点！" << endl;
			}
			cout << endl;
			break;
		case 1:
			if (DataList::state == DataList::idle) {
				//cout << "你装备了" << usingGoods.name << endl;

			}
			else
				cout << "目前无法变更装备！" << endl << endl;
			break;
		case 2:
			cout << "选择的物品无法使用！" << endl << endl;
			break;
		default:
			break;
		}

	}
	
}
//移动到一个地点
void Hero::MoveToSpot(int id) {
	system("cls");
	cout << "new" << endl;
	currentSpotId = id;
	DataList::spotList[id].OnEnterSpot();
}
//探索场景
void Hero::ExploreSpot() {
	while (DataList::state != DataList::over) {
		switch (currentSpotId) {
		case 0:
			IdleInput();
			break;
		case 1:
			cout << "你来到了" << DataList::spotList[currentSpotId].name << endl;
			cout << DataList::spotList[currentSpotId].description << endl;
			for (int id : DataList::spotList[currentSpotId].NPCIdList) {
				cout << "你开始慢慢走向前" << endl;
				cout << "你发现了" << DataList::npcList[id].name << endl;
				cout << "你要怎么做" << endl;
				cout << "1. 战斗 2. 偷听 3. 离开" << endl << endl;
				int input = InteractSystem::UserInput(3);
				if (input == 1) {
					Fight newFight(this, id);
				}
				else if (input == 2) {
					//偷听的相关剧情
				}
			}
			break;
		default:
			break;
		}
	}
}
void Hero::IdleInput() {
	cout << "你要怎么做？" << endl;
	cout << "1. 赶路 2. 背包 3. 状态 4. 存档 5. 返回标题画面" << endl << endl;
	int input = InteractSystem::UserInput(5);
	switch (input) {
	case 1:
		DataList::spotList[currentSpotId].printNearSpots();
		cout << DataList::spotList[currentSpotId].nearSpotId.size() + 1 << ".取消" << endl << endl;
		int spotInput = InteractSystem::UserInput(DataList::spotList[currentSpotId].nearSpotId.size());
		if (spotInput != DataList::spotList[currentSpotId].nearSpotId.size() + 1) {
			int spotId = DataList::spotList[currentSpotId].nearSpotId[spotInput - 1];
			MoveToSpot(spotId);
		}
		break;
	case 2:
		bag.Print();
		int index = InteractSystem::UserInput(bag.cargo.size() + 1);
		if (index != bag.cargo.size() + 1) 
			UsingGoods(bag.ReturnId(index));
		break;
	case 3:
		ShowNPCState();
		break;
	case 4:
		SaveGame();
		break;
	case 5:
		DataList::state == DataList::over;
		break;
	default:
		break;
	}

}
//Fight的构造函数
Fight::Fight(Hero* player, int enemyId)
{
	DataList::state = DataList::battle;
	this->player = player;
	Fighting(enemyId);
}
//Fight的析构函数
Fight::~Fight() {
}
//战斗过程
void Fight::Fighting(int enemyId) {
	NPC enemy(DataList::npcList[enemyId]);
	cout << "你与" << enemy.name << "斗在了一起！";
	while (DeathOrNot(&enemy)) {
		DecideWhoAct(&enemy);
		int index = -1;
		int command = -1;
		while (command == -1) {
			index = -1;
			cout << endl;
			player->ShowNPCState();
			cout << "请选择你的行动：" << endl;
			cout << "1.攻击 2.技能 3.物品 4.逃走 " << endl << endl;
			command = InteractSystem::UserInput(4);
			switch (command) {
			case 1:
				index = 0;
				break;		//选择攻击
			case 2:		//查看技能列表
				index = SearchSkill();
				if (index == -1)command = -1;
				break;
			case 3:		//查看物品列表
				player->bag.Print();
				index = InteractSystem::UserInput(player->bag.cargo.size() + 1);
				if (index == player->bag.cargo.size() + 1) command = -1;
				break;
			case 4:		//逃跑
				if (Escape(player, &enemy)) {
					DataList::state = DataList::idle;
					return;
				}
				else {
					list.clear();
					list.push_back(&enemy);
				}
				break;
			default: break;
			}
		}
		for (int i = 0; i < list.size(); i++) {
			if (list[i]->id == 0) {
				//Hero的使用物品 使用RetrunId返回物品的编号
				if (command != 3)
					player->UsingGoods(player->bag.ReturnId(index));
				else
					UseSkillAttack(player, &enemy, index);
			}
			//enemy行动
			else
				DecideAct(&enemy, player);
			if (DeathOrNot(&enemy))break;
		}
	}
	Victory(player, &enemy);
}
//判定谁先先手
void Fight::DecideWhoAct(NPC* enemy) {
	list.clear();
	if (player->speed >= enemy->speed) {
		list.push_back(player);
		list.push_back(enemy);
	}
	else {
		list.push_back(enemy);
		list.push_back(player);
	}
}
//使用技能
int Fight::SearchSkill() {
	int num = player->skillBar.list.size();
	if (num == 0) {
		cout << "你还未学习技能" << endl << endl;
		return -1;
	}
	else {
		cout << endl << "要使用什么技能？" << endl;
		player->skillBar.Print();
		cout << player->skillBar.list.size() + 1 << ".取消" << endl << endl;
		int input = -1;
		while (input == -1) {
			input = InteractSystem::UserInput(num + 1);
			if (input == num + 1) return -1;
			else {
				int skillId = ReturnId(player, input - 1);
				if (DataList::skillList[skillId].MPcost > player->MP) {
					cout << "魔法值不足！" << endl << endl;
					input = -1;
				}
				else return skillId;
			}
		}
	}
}
//返回技能的编号
int Fight::ReturnId(NPC* owner, int num) {
	return owner->skillBar.list[num]->id;
}
//技能造成伤害(包括普通攻击）
void Fight::UseSkillAttack(NPC* attacker, NPC* defender, int id) {
	attacker->MP -= DataList::skillList[id].MPcost;
	cout << attacker->name << "使用了" << DataList::skillList[id].name << endl;
	if (Random(100) <= DataList::skillList[id].accuracyRate) {
		int damage = DataList::skillList[id].damage * attacker->attack - defender->defense * 2;
		damage = max(damage, 0);
		if (Random(100) <= DataList::skillList[id].critRate) {
			cout << "产生了暴击！" << endl;
			damage *= 2;
		}
		defender->HP -= damage;
		cout << defender->name << "受到了" << damage << "点伤害" << endl << endl;
	}
	else
		cout << "但是没有命中目标！" << endl << endl;
}
//逃跑
bool Fight::Escape(NPC* escaper, NPC* arrester) {
	if (escaper->speed >= arrester->speed)
	{
		cout << "成功逃离！" << endl << endl;
		return true;
	}
	else {
		cout << "逃跑失败！" << endl << endl;
		return false;
	}
}

//enemy决定行动
void Fight::DecideAct(NPC* enemy, NPC* player) {
	int num = 0;
	int damage = 0;
	for (int i = 0; i < enemy->skillBar.list.size(); i++) {
		if ((enemy->skillBar.list[i]->damage * enemy->attack - player->defense * 2) > damage) {
			damage = enemy->skillBar.list[i]->damage * enemy->attack - player->defense * 2;
			num = i;
		}
	}
	UseSkillAttack(enemy, player, num);
}
//判定一方死亡
bool Fight::DeathOrNot(NPC* enemy) {
	if (player->HP <= 0 || enemy->HP <= 0)
		return true;
	else 
		return false;
}
//胜负判定
void Fight::Victory(Hero* player, NPC* enemy) {
	if (player->HP <= 0) {
		cout << "你被" << enemy->name << "打败了" << endl;
		cout << "游戏结束" << endl;
		system("pause");
		DataList::state = DataList::over;
	}
	else {
		cout << "你战胜了" << enemy->name << endl;
		cout << "你获得了" << enemy->experience << "点经验值" << "与" << enemy->money << "金币" << endl;
		player->bag.money += enemy->money;
		player->experience += enemy->experience;
		//查看等级提升
		if (player->LevelUp())
			cout << "恭喜你的等级提升到" << player->level << "级" << endl;
		system("pause");
		DataList::state = DataList::idle;
	}
}
//产生随机数
int Fight::Random(int num) {
	srand((unsigned int)time(NULL));
	return rand() % num;
}
//商店构造函数
store::store() {
}
//向商店添加物品
void store::AddGoodsId(int id) {
	goodsIdList.push_back(id);
}
//购买物品
void store::Purchase(Hero* player, int id) {
	if (player->bag.money >= DataList::goodsList[id].cost) {
		player->bag.AddGoods(DataList::goodsList[id].index);
		player->bag.money -= DataList::goodsList[id].cost;
		cout << "你购买了" << DataList::goodsList[id].name << endl;
	}
	else {
		cout << "你的金币不足" << endl;
	}
}