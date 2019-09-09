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
	srand((unsigned int)time(NULL));
	GetItemData(InteractSystem::ReadFile("Goods"));
	GetSkillData(InteractSystem::ReadFile("Skill"));
	GetNPCData(InteractSystem::ReadFile("NPC"));
	GetSpotData(InteractSystem::ReadFile("Spot"));
	DataList::dialogList = InteractSystem::ReadFile("Dialog");
}
//标题画面
int GameThread::TitleScreen() {
	system("cls");
	DataList::state = DataList::title;
	cout << "勇者之路" << endl << endl;
	cout << "1.新的开始" << endl;
	cout << "2.旧的回忆" << endl;
	cout << "3.退出游戏" << endl << endl;
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
	hero.bag.equipment[0] = &DataList::goodsList[8];
	hero.bag.equipment[1] = &DataList::goodsList[0];
	hero.bag.equipment[2] = &DataList::goodsList[4];
	hero.bag.AddGoods(12);
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
	
	unsigned int i = 0;
	//存储背包中的物品的id
	for (i = 0; i < bag.cargo.size(); i++) {
		fout << bag.cargo[i].thing->index << endl;
	}
	fout << " "<<endl;
	//存储背包中的对应物品的数量
	for (i = 0; i < bag.cargo.size(); i++) {
		fout << bag.cargo[i].num << endl;
	}
	fout << " " << endl;
	//存储装备中的对应物品的id
	for (i = 0; i < bag.cargo.size(); i++) {
		fout << bag.equipment[i]->index << endl;
	}
	fout << " " << endl;
	//存储对话的开关
	for (i = 0; i < DataList::trigger.size(); i++) {
		fout << DataList::trigger[i] << endl;
	}
	fout << " " << endl;
	cout << "游戏进度已存储" << endl << endl;
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

		unsigned int i = 0;
		//先清空背包 
		hero.bag.cargo.clear();
		getline(in, line);
		//读取背包内的物品种类
		for (i = 0; line != " "; i++) {
			hero.bag.AddGoods(atoi(line.c_str()));
			getline(in, line);
		}
		getline(in, line);
		//读取背包内对应的物品种类的数量
		for (i = 0; line != " "; i++) {
			hero.bag.cargo[i].num = atoi(line.c_str());
			getline(in, line);
		}
		getline(in, line);
		//读取关于装备栏中装备的信息
		for (i = 0; line != " "; i++) {
			hero.bag.equipment[i] = (&(DataList::goodsList[atoi(line.c_str())]));
			getline(in, line);
		}
		getline(in, line);
		//读取关于对话的开关
		for (i = 0; i < DataList::trigger.size(); i++) {
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
void Hero::ShowHeroState() {
	cout << name << endl;
	cout << "等级：" << level << endl;
	cout << "经验值：" << experience << "/" << explist[level - 1] << endl;
	cout << "金钱：" << bag.money << endl;
	cout << "生命值：" << HP << "/" << HPmax << endl;
	cout << "魔法值：" << MP << "/" << MPmax << endl;
	cout << "攻击：" << attack  << endl;
	cout << "防御：" << defense << endl;
	cout << "敏捷：" << speed << endl << endl;
}
//升级
void Hero::LevelUp() {
	while (level < 5 && experience >= explist[level - 1]) {
		level++;
		HPmax += 50;
		MPmax += 10;
		HP += 50;
		MP += 10;
		attack += 2;
		defense += 2;
		speed += 2;
		cout << "恭喜你的等级提升到" << level << "级" << endl;
		if (level == 2)LearnSkill(1);
		else if (level == 4)LearnSkill(2);
		cout << endl;
	}
}
//学习技能
void Hero::LearnSkill(int id) {
	skillBar.LearnSkill(&DataList::skillList[id]);
	cout << "你学会了" << DataList::skillList[id].name << endl;
}
//Hero在背包中使用消耗品
void Hero::UsingGoods(int id) {
	Goods usingGoods(DataList().goodsList[id]);
	system("cls");
	if (bag.AbandonGoods(id)) {
		int addHp = usingGoods.addHP;
		int addMp = usingGoods.addMP;
		switch (usingGoods.attribute) {
		case 0:
			cout << "你使用了" << usingGoods.name << endl;
			if (addHp > 0) {
				addHp = min(addHp, HPmax - HP);
				cout << "你的HP增加了" << addHp << "点" << endl;
			}
			if (addMp > 0) {
				addMp = min(addMp, MPmax - MP);
				cout << "你的MP增加了" << addMp << "点！" << endl;
			}
			HP += addHp; MP += addMp;
			cout << endl;
			break;
		case 1:
			if (DataList::state == DataList::idle) {
				attack -= bag.equipment[usingGoods.location]->addAttack;
				defense -= bag.equipment[usingGoods.location]->addDefense;
				speed -= bag.equipment[usingGoods.location]->addSpeed;
				bag.Equip(&DataList().goodsList[id]);
				attack += bag.equipment[usingGoods.location]->addAttack;
				defense += bag.equipment[usingGoods.location]->addDefense;
				speed += bag.equipment[usingGoods.location]->addSpeed;
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
	currentSpotId = id;
	DataList::spotList[currentSpotId].printSpotInformation();
	OnEnterSpot();
}
//探索场景
void Hero::OnEnterSpot() {
	int input = -1;
	while (DataList::state != DataList::over) {
		switch (currentSpotId) {
		case 0:
			if (DataList::trigger[6] == 0) {
				InteractSystem::Dialog(1);
				DataList::trigger[6] = 1;
			}
			break;
		case 3:
			if (DataList::trigger[0] == 0 && level >= 2) {
				DataList::trigger[0] = InteractSystem::Dialog(2);
				if (DataList::trigger[0] == 1) {
					bag.AddGoods(3);
					bag.AddGoods(7);
					bag.AddGoods(11);
				}
				if (DataList::trigger[0] == 2)
					Fight(this, 3);
			}
			break;
		case 5:
			if (level >= 5) {
				if (DataList::trigger[1] == 0) {
					DataList::trigger[1] = InteractSystem::Dialog(3);
					if (DataList::trigger[1] == 1) {
						DataList::trigger[1] = 0;
						MoveToSpot(7);
					}
				}
				else if (DataList::trigger[1] == 1 && DataList::trigger[2] == 1 && DataList::trigger[3] == 0) {
					DataList::trigger[3] = InteractSystem::Dialog(5);
					if (DataList::trigger[3] == 2)bag.AbandonGoods(15);
				}
			}
			break;
		case 6:
			if (DataList::trigger[5] == 0) {
				if (DataList::trigger[1] == 2 || DataList::trigger[2] == 2 || DataList::trigger[3] == 2) {
					InteractSystem::Dialog(6);
					Fight(this, 5);
					InteractSystem::Dialog(7);
					system("pause");
					DataList::state = DataList::over;
				}
				else if (DataList::trigger[4] == 1) {
					InteractSystem::Dialog(10);
					bag.AbandonGoods(16);
					DataList::trigger[5] = 1;
				}	
			}
			break;
		case 7:
			if (DataList::trigger[1] == 0) {
				DataList::trigger[1] = 1;
				Fight(this, 6);
				DataList::trigger[2] = InteractSystem::Dialog(4);
				if (DataList::trigger[2] == 1)
					bag.AddGoods(15);
				MoveToSpot(5);
			}
			break;
		case 8:
			if (DataList::trigger[1] == 1 && DataList::trigger[2] == 1 && DataList::trigger[3] == 1 && DataList::trigger[4] == 0) {
				InteractSystem::Dialog(8);
				Fight(this, 4);
				InteractSystem::Dialog(9);
				bag.AddGoods(16);
				bag.AddGoods(17);
				DataList::trigger[4] = 1;
			}
			break;
		case 9:
			if (DataList::trigger[1] == 1 && DataList::trigger[2] == 1 && DataList::trigger[3] == 1 && DataList::trigger[4] == 1 && DataList::trigger[5] == 1) {
				InteractSystem::Dialog(11);
				Fight(this, 6);
				InteractSystem::Dialog(12);
				system("pause");
				DataList::state = DataList::over;
			}
			break;
		default:
			break;
		}
		if (DataList::state != DataList::over)IdleInput();
	}
}
void Hero::ExploreSpot() {
	cout << "你尝试在此地探索" << endl;
	int input = -1;
	while (input != 0) {
		if (currentSpotId == 1 || currentSpotId == 2) {
			cout << endl << "是否继续探索？" << endl;
			cout << "1. 继续 2. 离开" << endl << endl;
			input = InteractSystem::UserInput(2);
			if (input == 1) {
				int result = rand() % 100;
				if (result < 30)
					cout << "似乎并没有发现什么" << endl;
				else if (result < 35) {
					int add= rand() % 10;
					add *= currentSpotId;
					bag.money += add;
					cout << "你发现了一些散落在地上的金币" << endl << "获得了" << add << "金币" << endl;
				}
				else if (result < 40) {
					bag.AddGoods(12);
					cout << "你发现了一颗果实" << endl << "获得了" << DataList::goodsList[12].name << " x1" << endl;
				}
				else {
					cout << "你发现一只怪物向你扑来！" << endl;
					int monster = rand() % 2 + currentSpotId;
					Fight(this, monster);
				}
			}
			else {
				cout << "你停止了探索。" << endl << endl;
				input = 0;
			}
		}
		else if (currentSpotId == 0) {
			Store store;
			cout <<endl<< "你来到了城内的商店" << endl;
			while (input != 0) {
				store.Print();
				input = InteractSystem::UserInput(store.goodsIdList.size() + 1);
				if (input != store.goodsIdList.size() + 1)
					store.Purchase(this, store.goodsIdList[input - 1]);
				else {
					system("cls");
					return;
				}
			}
		}
		else {
			input = 0;
			cout << endl << "但并没有可以探索的地方！" << endl << endl;
		}
	}
}
void Hero::IdleInput() {
	cout << "你要怎么做？" << endl;
	cout << "1. 探索 2. 赶路 3. 状态 4. 背包 5. 装备 6. 地图 7. 存档 8. 返回标题画面" << endl << endl;
	int input = InteractSystem::UserInput(8);
	system("cls");
	switch (input) {
	case 1:
		ExploreSpot();
		break;
	case 2:
		DataList::spotList[currentSpotId].printNearSpots();
		cout << DataList::spotList[currentSpotId].nearSpotId.size() + 1 << "：取消" << endl << endl;
		input = InteractSystem::UserInput(DataList::spotList[currentSpotId].nearSpotId.size() + 1);
		if (input != DataList::spotList[currentSpotId].nearSpotId.size() + 1) {
			int spotId = DataList::spotList[currentSpotId].nearSpotId[input - 1];
			MoveToSpot(spotId);
		}
		break;
	case 3:
		ShowHeroState();
		break;
	case 4:
		bag.Print();
		input = InteractSystem::UserInput(bag.cargo.size() + 1);
		system("cls");
		if (input != bag.cargo.size() + 1)
			UsingGoods(bag.ReturnId(input));
		break;
	case 5:
		bag.PrintEquipment();
		break;
	case 6:
		InteractSystem::PrintMap();
		break;
	case 7:
		SaveGame();
		break;
	case 8:
		DataList::state = DataList::over;
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
//战斗过程
void Fight::Fighting(int enemyId) {
	system("pause");
	system("cls");
	NPC enemy(DataList::npcList[enemyId - 1]);
	cout << "你与" << enemy.name << "斗在了一起！" << endl;
	while (!DeathOrNot(&enemy)) {
		DecideWhoAct(&enemy);
		int index = -1;
		int command = -1;
		while (command == -1) {
			index = -1;
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
		for (unsigned int i = 0; i < list.size(); i++) {
			if (list[i]->id == 0) {
				//Hero的使用物品 使用RetrunId返回物品的编号
				if (command == 3 && player->bag.cargo.size() > 0)
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
		system("cls");
		cout << "你还未学习技能" << endl << endl;
	}
	else {
		cout << endl << "要使用什么技能？" << endl;
		player->skillBar.Print();
		cout << player->skillBar.list.size() + 1 << ".取消" << endl << endl;
		int input = -1;
		while (input == -1) {
			input = InteractSystem::UserInput(num + 1);
			system("cls");
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
	return -1;
}
//返回技能的编号
int Fight::ReturnId(NPC* owner, int num) {
	return owner->skillBar.list[num]->id;
}
//技能造成伤害(包括普通攻击）
void Fight::UseSkillAttack(NPC* attacker, NPC* defender, int id) {
	attacker->MP -= DataList::skillList[id].MPcost;
	cout << attacker->name << "使用了" << DataList::skillList[id].name << endl;
	if (Random(100) <= DataList::skillList[id].accuracyRate * 100) {
		int damage = DataList::skillList[id].damage * attacker->attack - defender->defense * 2;
		damage = max(damage, 0);
		if (Random(100) <= DataList::skillList[id].critRate * 100) {
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
	if (escaper->speed >= arrester->speed) {
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
	unsigned int size = enemy->skillBar.list.size();
	int index = rand() % size;
	int id = enemy->skillBar.list[index]->id;
	UseSkillAttack(enemy, player, id);
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
		cout << "你被" << enemy->name << "打败了" << endl << endl;
		cout << "游戏结束" << endl << endl;
		DataList::state = DataList::over;
	}
	else {
		cout << "你战胜了" << enemy->name << endl << endl;
		cout << "你获得了" << enemy->experience << "点经验值" << "与" << enemy->money << "金币" << endl << endl;
		player->bag.money += enemy->money;
		if (player->level < 5) {
			player->experience += enemy->experience;
			player->experience = min(200, player->experience);
			//等级提升
			player->LevelUp();
		}
		DataList::state = DataList::idle;
	}
	system("pause");
	system("cls");
}
//产生随机数
int Fight::Random(int num) {
	return rand() % num;
}
//商店构造函数
Store::Store() {
	AddGoodsId(12);
	AddGoodsId(13);
	AddGoodsId(14);
	AddGoodsId(1);
	AddGoodsId(2);
	AddGoodsId(5);
	AddGoodsId(6);
	AddGoodsId(9);
	AddGoodsId(10);
}
//向商店添加物品
void Store::AddGoodsId(int id) {
	goodsIdList.push_back(id);
}
void Store::Print() {
	cout << "要购买什么东西？" << endl;
	int i = 0;
	for (int id : goodsIdList) {
		i++;
		cout << i << ". " << DataList::goodsList[id].name << endl;
	}
	cout << i + 1 << ". " << "取消" << endl << endl;
}
//购买物品
void Store::Purchase(Hero* player, int id) {
	system("cls");
	if (player->bag.money >= DataList::goodsList[id].cost) {
		player->bag.AddGoods(DataList::goodsList[id].index);
		player->bag.money -= DataList::goodsList[id].cost;
		cout << "你购买了" << DataList::goodsList[id].name << endl << endl;
	}
	else
		cout << "你的金币不足" << endl << endl;
}