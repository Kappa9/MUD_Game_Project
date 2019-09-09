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
//���⻭��
int GameThread::TitleScreen() {
	system("cls");
	DataList::state == DataList::title;
	InteractSystem::PrintMap();
	cout << "MUDGAME" << endl << endl;
	cout << "1.�µĿ�ʼ" << endl;
	cout << "2.�ɵĻ���" << endl;
	cout << "3.�˳���Ϸ" << endl;
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
			cout << endl << "δ�ҵ��浵�ļ���" << endl << endl;
		break;
	case 3:
		exit(0);
		break;
	default:
		break;
	}
	return input;
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
	DataList::state = DataList::idle;
	hero.MoveToSpot(0);
}
//��������
void Hero::SaveGame() {
	//��ɾ���ļ�
	fstream fout("save.txt", ios::out | ios::trunc);  //����Ĵ浵�ļ���������Ҫ�� 
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
	
	//�洢�����е���Ʒ��id
	for (int i = 0; i < bag.cargo.size(); i++) {
		fout << bag.cargo[i].thing->index << endl;
	}
	fout << " "<<endl;
	//�洢�����еĶ�Ӧ��Ʒ������
	for (int i = 0; i < bag.cargo.size(); i++) {
		fout << bag.cargo[i].num << endl;
	}
	fout << " " << endl;
	//�洢װ���еĶ�Ӧ��Ʒ��id
	for (int i = 0; i < bag.cargo.size(); i++) {
		fout << bag.equipment[i]->index << endl;
	}
	fout << " " << endl;
	//�洢�Ի��Ŀ���
	for (int i = 0; i < DataList::trigger.size(); i++) {
		fout << DataList::trigger[i] << endl;
	}
	fout << " " << endl;
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
		getline(in, line);
		//��ȡ�����ڵ���Ʒ����
		for (int i = 0; line != " "; i++) {
			hero.bag.AddGoods(atoi(line.c_str()));
			getline(in, line);
		}
		getline(in, line);
		//��ȡ�����ڶ�Ӧ����Ʒ���������
		for (int i = 0; line != " "; i++) {
			hero.bag.cargo[i].num = atoi(line.c_str());
			getline(in, line);
		}
		getline(in, line);
		//��ȡ����װ������װ������Ϣ
		for (int i = 0; line != " "; i++) {
			hero.bag.equipment[i] = (&(DataList::goodsList[atoi(line.c_str())]));
			getline(in, line);
		}
		getline(in, line);
		//��ȡ���ڶԻ��Ŀ���
		for (int i = 0; i < DataList::trigger.size(); i++) {
			DataList::trigger[i] = atoi(line.c_str());
			getline(in, line);
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
//Hero�ڱ�����ʹ������Ʒ
void Hero::UsingGoods(int id) {
	Goods usingGoods(DataList().goodsList[id]);
	if (bag.AbandonGoods(id)) {
		int addHp = DataList().goodsList[id].addHP;
		int addMp = DataList().goodsList[id].addMP;
		switch (usingGoods.attribute) {
		case 0:
			cout << "��ʹ����" << usingGoods.name << endl;
			if (addHp > 0) {
				addHp = min(addHp, HPmax - HP);
				cout << "���HP������" << addHp << "��" << endl;
			}
			if (addMp > 0) {
				addHp = min(addMp, MPmax - MP);
				cout << "���MP������" << addMp << "�㣡" << endl;
			}
			cout << endl;
			break;
		case 1:
			if (DataList::state == DataList::idle) {
				//cout << "��װ����" << usingGoods.name << endl;

			}
			else
				cout << "Ŀǰ�޷����װ����" << endl << endl;
			break;
		case 2:
			cout << "ѡ�����Ʒ�޷�ʹ�ã�" << endl << endl;
			break;
		default:
			break;
		}

	}
	
}
//�ƶ���һ���ص�
void Hero::MoveToSpot(int id) {
	system("cls");
	cout << "new" << endl;
	currentSpotId = id;
	DataList::spotList[id].OnEnterSpot();
}
//̽������
void Hero::ExploreSpot() {
	while (DataList::state != DataList::over) {
		switch (currentSpotId) {
		case 0:
			IdleInput();
			break;
		case 1:
			cout << "��������" << DataList::spotList[currentSpotId].name << endl;
			cout << DataList::spotList[currentSpotId].description << endl;
			for (int id : DataList::spotList[currentSpotId].NPCIdList) {
				cout << "�㿪ʼ��������ǰ" << endl;
				cout << "�㷢����" << DataList::npcList[id].name << endl;
				cout << "��Ҫ��ô��" << endl;
				cout << "1. ս�� 2. ͵�� 3. �뿪" << endl << endl;
				int input = InteractSystem::UserInput(3);
				if (input == 1) {
					Fight newFight(this, id);
				}
				else if (input == 2) {
					//͵������ؾ���
				}
			}
			break;
		default:
			break;
		}
	}
}
void Hero::IdleInput() {
	cout << "��Ҫ��ô����" << endl;
	cout << "1. ��· 2. ���� 3. ״̬ 4. �浵 5. ���ر��⻭��" << endl << endl;
	int input = InteractSystem::UserInput(5);
	switch (input) {
	case 1:
		DataList::spotList[currentSpotId].printNearSpots();
		cout << DataList::spotList[currentSpotId].nearSpotId.size() + 1 << ".ȡ��" << endl << endl;
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
//Fight�Ĺ��캯��
Fight::Fight(Hero* player, int enemyId)
{
	DataList::state = DataList::battle;
	this->player = player;
	Fighting(enemyId);
}
//Fight����������
Fight::~Fight() {
}
//ս������
void Fight::Fighting(int enemyId) {
	NPC enemy(DataList::npcList[enemyId]);
	cout << "����" << enemy.name << "������һ��";
	while (DeathOrNot(&enemy)) {
		DecideWhoAct(&enemy);
		int index = -1;
		int command = -1;
		while (command == -1) {
			index = -1;
			cout << endl;
			player->ShowNPCState();
			cout << "��ѡ������ж���" << endl;
			cout << "1.���� 2.���� 3.��Ʒ 4.���� " << endl << endl;
			command = InteractSystem::UserInput(4);
			switch (command) {
			case 1:
				index = 0;
				break;		//ѡ�񹥻�
			case 2:		//�鿴�����б�
				index = SearchSkill();
				if (index == -1)command = -1;
				break;
			case 3:		//�鿴��Ʒ�б�
				player->bag.Print();
				index = InteractSystem::UserInput(player->bag.cargo.size() + 1);
				if (index == player->bag.cargo.size() + 1) command = -1;
				break;
			case 4:		//����
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
				//Hero��ʹ����Ʒ ʹ��RetrunId������Ʒ�ı��
				if (command != 3)
					player->UsingGoods(player->bag.ReturnId(index));
				else
					UseSkillAttack(player, &enemy, index);
			}
			//enemy�ж�
			else
				DecideAct(&enemy, player);
			if (DeathOrNot(&enemy))break;
		}
	}
	Victory(player, &enemy);
}
//�ж�˭������
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
//ʹ�ü���
int Fight::SearchSkill() {
	int num = player->skillBar.list.size();
	if (num == 0) {
		cout << "�㻹δѧϰ����" << endl << endl;
		return -1;
	}
	else {
		cout << endl << "Ҫʹ��ʲô���ܣ�" << endl;
		player->skillBar.Print();
		cout << player->skillBar.list.size() + 1 << ".ȡ��" << endl << endl;
		int input = -1;
		while (input == -1) {
			input = InteractSystem::UserInput(num + 1);
			if (input == num + 1) return -1;
			else {
				int skillId = ReturnId(player, input - 1);
				if (DataList::skillList[skillId].MPcost > player->MP) {
					cout << "ħ��ֵ���㣡" << endl << endl;
					input = -1;
				}
				else return skillId;
			}
		}
	}
}
//���ؼ��ܵı��
int Fight::ReturnId(NPC* owner, int num) {
	return owner->skillBar.list[num]->id;
}
//��������˺�(������ͨ������
void Fight::UseSkillAttack(NPC* attacker, NPC* defender, int id) {
	attacker->MP -= DataList::skillList[id].MPcost;
	cout << attacker->name << "ʹ����" << DataList::skillList[id].name << endl;
	if (Random(100) <= DataList::skillList[id].accuracyRate) {
		int damage = DataList::skillList[id].damage * attacker->attack - defender->defense * 2;
		damage = max(damage, 0);
		if (Random(100) <= DataList::skillList[id].critRate) {
			cout << "�����˱�����" << endl;
			damage *= 2;
		}
		defender->HP -= damage;
		cout << defender->name << "�ܵ���" << damage << "���˺�" << endl << endl;
	}
	else
		cout << "����û������Ŀ�꣡" << endl << endl;
}
//����
bool Fight::Escape(NPC* escaper, NPC* arrester) {
	if (escaper->speed >= arrester->speed)
	{
		cout << "�ɹ����룡" << endl << endl;
		return true;
	}
	else {
		cout << "����ʧ�ܣ�" << endl << endl;
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
bool Fight::DeathOrNot(NPC* enemy) {
	if (player->HP <= 0 || enemy->HP <= 0)
		return true;
	else 
		return false;
}
//ʤ���ж�
void Fight::Victory(Hero* player, NPC* enemy) {
	if (player->HP <= 0) {
		cout << "�㱻" << enemy->name << "�����" << endl;
		cout << "��Ϸ����" << endl;
		system("pause");
		DataList::state = DataList::over;
	}
	else {
		cout << "��սʤ��" << enemy->name << endl;
		cout << "������" << enemy->experience << "�㾭��ֵ" << "��" << enemy->money << "���" << endl;
		player->bag.money += enemy->money;
		player->experience += enemy->experience;
		//�鿴�ȼ�����
		if (player->LevelUp())
			cout << "��ϲ��ĵȼ�������" << player->level << "��" << endl;
		system("pause");
		DataList::state = DataList::idle;
	}
}
//���������
int Fight::Random(int num) {
	srand((unsigned int)time(NULL));
	return rand() % num;
}
//�̵깹�캯��
store::store() {
}
//���̵������Ʒ
void store::AddGoodsId(int id) {
	goodsIdList.push_back(id);
}
//������Ʒ
void store::Purchase(Hero* player, int id) {
	if (player->bag.money >= DataList::goodsList[id].cost) {
		player->bag.AddGoods(DataList::goodsList[id].index);
		player->bag.money -= DataList::goodsList[id].cost;
		cout << "�㹺����" << DataList::goodsList[id].name << endl;
	}
	else {
		cout << "��Ľ�Ҳ���" << endl;
	}
}