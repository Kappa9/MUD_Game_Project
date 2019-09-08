#include "Game.h"
int main() {
	GameThread game;
	return 0;
}

GameThread::GameThread() {
	GetItemData(InteractSystem::ReadFile("Goods"));
	GetSkillData(InteractSystem::ReadFile("Skill"));
	//GetNPCData(InteractSystem::ReadFile("NPC"));
	GetSpotData(InteractSystem::ReadFile("Spot"));
	DataList::dialogList = InteractSystem::ReadFile("Dialog");
	HideCursor();
	TitleScreen();
}
//���⻭��
void GameThread::TitleScreen() {
	InteractSystem::PrintMap();
	cout << "MUDGAME" << endl << endl;
	cout << "1.�µĿ�ʼ" << endl;
	cout << "2.�ɵĻ���" << endl;
	cout << "3.�˳���Ϸ" << endl;
	int input = InteractSystem::UserInput(3);
	switch (input)
	{
	case 1:
		NewGame();
		break;
	case 2:
		if (LoadGame())
			hero.MoveToSpot(hero.currentSpotId);
		else
			cout << endl << "δ�ҵ��浵�ļ���" << endl;
		break;
	case 3:
		exit(0);
		break;
	default:
		break;
	}
}
//���ع�꺯��
void GameThread::HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//�õ���Ʒ������
void GameThread::GetItemData(vector<string> list) {
	//�����Ʒ����
	for (string str : list) {
		//���ָ��ַ�����Ķ����µ�vector 
		vector<string> split(InteractSystem::SplitString(str, ","));
		Goods i(split);
		DataList::goodsList.push_back(i);
	}
}
//�õ����ܵ�����
void GameThread::GetSkillData(vector<string> list) {
	for (string str : list) {
		//���ָ��ַ�����Ķ����µ�vector 
		vector<string> split(InteractSystem::SplitString(str, ","));
		Skill i(split);
		DataList::skillList.push_back(i);
	}
}
//�õ�NPC������
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
//�õ���ͼ������
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
//�µ���Ϸ
void GameThread::NewGame() {
	hero.MoveToSpot(0);
}
//��������
void GameThread::SaveGame() {
	//��ɾ���ļ�
	fstream fout("save.txt", ios::out | ios::trunc);  //����Ĵ浵�ļ���������Ҫ�� 

	fout << hero.level << endl;
	fout << hero.HPmax << endl;
	fout << hero.MPmax << endl;
	fout << hero.HP << endl;
	fout << hero.MP << endl;
	fout << hero.speed << endl;
	fout << hero.attack << endl;
	fout << hero.defense << endl;
	fout << hero.experience << endl;
	fout << hero.bag.money<< endl;
	fout << hero.currentSpotId<< endl;
	
	//�洢�����е���Ʒ��id
	for (int i = 0; i < hero.bag.cargo.size(); i++) {
		fout << hero.bag.cargo[i].thing->index << endl;
	}
	fout << " "<<endl;
	//�洢�����еĶ�Ӧ��Ʒ������
	for (int i = 0; i < hero.bag.cargo.size(); i++) {
		fout << hero.bag.cargo[i].num << endl;
	}
	fout << " " << endl;

	for (int i = 0; i < hero.bag.cargo.size(); i++) {
		fout << hero.bag.equipment[i]->index << endl;
	}
	fout << " " << endl;

	//�洢�Ի��Ŀ���
	for (int i = 0; i < DataList::trigger.size(); i++) {
		fout << DataList::trigger[i] << endl;
	}
	
	fout.close();
}
//��ȡ����
bool GameThread::LoadGame() {
	ifstream in;
	string line;
	in.open("save.txt");  //��Ҫ���������
	if (in.is_open()) {
		//��ȡ����hero������
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

		//����ձ��� 
		hero.bag.cargo.clear();

		//��ȡ�����ڵ���Ʒ����
		for (int i = 0; line != ""; i++) {
			hero.bag.AddGoods(atoi(line.c_str()));
			getline(in, line);
		}

		getline(in, line);

		//��ȡ�����ڶ�Ӧ����Ʒ���������
		for (int i = 0; line != ""; i++) {
			hero.bag.cargo[i].num = atoi(line.c_str());
			getline(in, line);
		}

		getline(in, line);
		//��ȡ����װ������װ������Ϣ
		for (int i = 0; line != ""; i++) {
			hero.bag.equipment[i] = (&(DataList::goodsList[atoi(line.c_str())]));
		}

		//��ȡ���ڶԻ��Ŀ���
		for (int i = 0; i < DataList::trigger.size(); i++) {
			DataList::trigger[i] = atoi(line.c_str());
		}
		in.close();
		return true;
	}
	else return false;
}

//Hero���캯��
Hero::Hero() {
	id = 0; name = "����";
	HPmax = 450; MPmax = 90;
	HP = HPmax; MP = MPmax;
	speed = 24; attack = 16; defense = 16;
	experience = 0; level = 1;
	money = 0; bag.money = 0;
	currentSpotId = -1;
}

//����
bool Hero::LevelUp() {
	int num = level;
	if (experience < 10) {
		level = 1;
	}
	else if (experience < 40) {
		level = 2;
	}
	else if (this->experience >= 40 && this->experience < 100) {
		this->level = 3;
	}
	else if (this->experience > 100 && this->experience < 200) {
		this->level = 4;
	}
	else if (this->experience >= 200) {
		this->level = 5;
	}
	if (level > num) {
		return true;
	}
	else {
		return false;
	}
}

//Hero�ڱ�����ʹ������Ʒ
void Hero::UsingGoods(int id) {
	Goods usingGoods = DataList().goodsList[id];
	if (usingGoods.attribute == 0) {
		this->bag.AbandonGoods(id);
		cout << "��ʹ����" << usingGoods.name;
		for (int i = 0; i < bag.cargo.size(); i++) {
			if (bag.cargo[i].thing->index == id) {
				bag.ReturnNum(bag.cargo[i].thing);
			}
		}
		if ((DataList().goodsList[id].addHP) == 0) {}
		else {
			if (DataList().goodsList[id].addHP <= (this->HPmax - this->HP))
				cout << "���HP������" << DataList().goodsList[id].addHP << "��";
			else {
				cout << "���HP������" << this->HPmax - this->HP;
			}
		}
		if ((DataList().goodsList[id].addMP) == 0) {}
		else {
			if (DataList().goodsList[id].addMP <= (this->MPmax - this->MP)) {
				cout << "���MP������" << DataList().goodsList[id].addMP << "��";
			}
			else {
				cout << "���MP������" << this->MPmax - this->MP;
			}
		}
	}
	else {
		cout << "ѡ�����Ʒ�޷�ʹ��";
	}
}

//�ƶ���һ���ص�
void Hero::MoveToSpot(int id) {
	system("cls");
	currentSpotId = id;
	DataList::spotList[id].OnEnterSpot();
}

//Fight�Ĺ��캯��
Fight::Fight(Hero* player, NPC* enemy)
{
	this->player = player;
	this->enemy = enemy;
}
//Fight����������
Fight::~Fight() {
}
//�ж�˭������
NPC* Fight::DecideWhoAct() {
	if (player->speed >= enemy->speed) {
		return player;
	}
	else {
		return enemy;
	}
}
//��������˺�(������ͨ������
void Fight::UseSkillAttack(NPC* attacker, NPC* defender, int id) {
	int MPcost;
	MPcost = DataList().skillList[id].MPcost;
	if (attacker->MP < MPcost) {
		cout << "ħ��ֵ����";
	}
	else {
		srand((int)time(0));
		if (Random(100) <= DataList::skillList[id].accuracyRate) {
			if (Random(100) <= DataList::skillList[id].critRate) {
				int damage = DataList().skillList[id].damage * attacker->attack - defender->defense * 2;
				attacker->MP -= MPcost;
				defender->HP -= 2 * damage;
				if (id != 0) {
					cout << attacker->name << "ʹ����" << DataList().skillList[id].name << "�������˱���";
				}
				else {
					cout << "�㹥����" << defender->name << "���������˱���";
				}
				cout << endl << "��" << defender->name << "�����" << 2 * damage << "���˺�";
			}
			else {
				int damage = DataList().skillList[id].damage * attacker->attack - defender->defense * 2;
				attacker->MP -= MPcost;
				defender->HP -= damage;
				if (id != 0) {
					cout << attacker->name << "ʹ����" << DataList().skillList[id].name;
				}
				else {
					cout << "�㹥����" << defender->name;
				}
				cout << endl << "��" << defender->name << "�����" << damage << "���˺�";
			}
		}
		else {
			cout << "��Ĺ�����������";
		}
	}
}
//���ؼ��ܵı��
int Fight::ReturnId(NPC* owner, int num) {
	return owner->skillBar.list[num]->id;
}
//ʹ�ü���
void Fight::UseSkill(NPC* role) {
	int num = role->skillBar.list.size();
	if (num == 0) {
		cout << "�㻹δѧϰ����";
	}
	else {
		cout << "Ҫʹ��ʲô���ܣ�";
		role->skillBar.Print();
		cout << role->skillBar.list.size() + 2 << ".ȡ��" << endl << endl;

		int input = InteractSystem::UserInput(num + 2);
		//ȡ��
		if (input == num + 2) {

		}
		else {
			int id = ReturnId(player, input - 1);
			UseSkillAttack(player, enemy, id);
		}
	}
}

//����
bool Fight::Escape(NPC* escaper, NPC* arrester) {
	if (escaper->speed >= arrester->speed)
	{
		cout << "�ɹ�����";
		return true;
	}
	else {
		cout << "����ʧ��";
		return false;
	}

}

//enemy�����ж�
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

//�ж�һ������
bool Fight::DeathOrNot(NPC* player, NPC* enemy) {
	if ((player->HP <= 0) || (enemy->HP <= 0)) {
		return true;
	}
	else {
		return false;
	}
}

//ʤ���ж�
void Fight::Victory(Hero* player, NPC* enemy) {
	if (player->HP <= 0) {
		cout << "�㱻" << enemy->name << "�����" << endl;
		cout << "��ʧ����";
	}
	else {
		cout << "��սʤ��" << enemy->name;
		cout << "������" << enemy->experience << "�㾭��ֵ" << "," << enemy->money << "���";
		player->bag.money += enemy->money;
		player->experience += enemy->experience;
	}
}

//ս������
void Fight::Fighting() {
	cout << "����" << enemy->name << "������һ��";
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
				cout << "�ֵ����ж��ˣ�";
				player->ShowNPCState();
				cout << "1.���� 2.���� 3.��Ʒ 4.���� ";

				int input = InteractSystem::UserInput(4);

				//ѡ�񹥻�
				if (input == 1) {
					UseSkillAttack(player, enemy, 1);
				}
				//ʹ�ü���
				else if (input == 2) {
					UseSkill(player);
				}
				//ʹ����Ʒ
				else if (input == 3) {
					player->bag.Print(1);
					int input;
					input = InteractSystem::UserInput(player->bag.cargo.size() + 2);
					//Hero��ʹ����Ʒ ʹ��RetrunId������Ʒ�ı��
					player->UsingGoods(player->bag.ReturnId(input));
				}
				//����
				else if (input == 4) {
					if (Escape(player, enemy)) {
						break;
					}
					else {
						continue;
					}
				}
			}
			//enemy�ж�
			else {
				DecideAct(enemy, player);
			}
		}
	}
	Victory(player, enemy);
	//�鿴�ȼ�����
	if (player->LevelUp()) {
		cout << "��ϲ��ĵȼ�������" << player->level << "��";
	}
	else {
	}

}

int Fight::Random(int num) {
	srand((unsigned int)time(NULL));
	return rand() % num;
}

Explore::Explore(Hero* player, int id) {
	hero = player;
	spotId = id;
	ExploreSpot();
}
//̽������
void Explore::ExploreSpot() {
	Spot newSpot = DataList::spotList[spotId];
	cout << "��������" << newSpot.name << endl << newSpot.description << endl;
	for (int i = 0; i < newSpot.NPCIdList.size(); i++) {
		cout << "�㿪ʼ��������ǰ" << endl;
		cout << "�㷢����" << DataList::npcList[newSpot.NPCIdList[i]].name << endl;
		cout << "��Ҫ��ô��" << endl;
		int input;
		//������ж�Ҫ��
		if (newSpot.id == 0) {
			cout << "1. ս�� 2. ͵�� 3. �뿪";
			input = InteractSystem::UserInput(3);
			if (input == 1) {
				Fight newFight(hero, &(DataList::npcList[newSpot.NPCIdList[i]]));
				newFight.Fighting();
			}
			else if (input == 2) {
				//͵������ؾ���
			}
			else if (input == 3) {
				cout << "���뿪��" << newSpot.name;
				//�뿪
			}

		}
		else {
			cout << "1. ս�� 2. �뿪";
			input = InteractSystem::UserInput(2);
			if (input == 1) {
				Fight newFight(hero, &(DataList::npcList[newSpot.NPCIdList[i]]));
				newFight.Fighting();
			}
			else if (input == 2) {
				cout << "���뿪��" << newSpot.name;
				//�뿪
			}
		}
	}
}



//���캯��
store::store()
{
}

//�����Ʒ��ID
void store::AddGoodsId(int id)
{
	goodsIdList.push_back(id);
}

//������Ʒ
void store::Purchase(Hero* player, int id)
{
	if (player->bag.money >= DataList::goodsList[id].cost) {
		player->bag.AddGoods(DataList::goodsList[id].index);
		player->bag.money -= DataList::goodsList[id].cost;
		cout << "�㹺����" << DataList::goodsList[id].name << endl;
	}
	else {
		cout << "��Ľ�Ҳ���" << endl;
	}
}


