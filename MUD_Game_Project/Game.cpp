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
//���⻭��
int GameThread::TitleScreen() {
	system("cls");
	DataList::state = DataList::title;
	cout << "����֮·" << endl << endl;
	cout << "1.�µĿ�ʼ" << endl;
	cout << "2.�ɵĻ���" << endl;
	cout << "3.�˳���Ϸ" << endl << endl;
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
	hero.bag.equipment[0] = &DataList::goodsList[8];
	hero.bag.equipment[1] = &DataList::goodsList[0];
	hero.bag.equipment[2] = &DataList::goodsList[4];
	hero.bag.AddGoods(12);
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
	
	unsigned int i = 0;
	//�洢�����е���Ʒ��id
	for (i = 0; i < bag.cargo.size(); i++) {
		fout << bag.cargo[i].thing->index << endl;
	}
	fout << " "<<endl;
	//�洢�����еĶ�Ӧ��Ʒ������
	for (i = 0; i < bag.cargo.size(); i++) {
		fout << bag.cargo[i].num << endl;
	}
	fout << " " << endl;
	//�洢װ���еĶ�Ӧ��Ʒ��id
	for (i = 0; i < bag.cargo.size(); i++) {
		fout << bag.equipment[i]->index << endl;
	}
	fout << " " << endl;
	//�洢�Ի��Ŀ���
	for (i = 0; i < DataList::trigger.size(); i++) {
		fout << DataList::trigger[i] << endl;
	}
	fout << " " << endl;
	cout << "��Ϸ�����Ѵ洢" << endl << endl;
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

		unsigned int i = 0;
		//����ձ��� 
		hero.bag.cargo.clear();
		getline(in, line);
		//��ȡ�����ڵ���Ʒ����
		for (i = 0; line != " "; i++) {
			hero.bag.AddGoods(atoi(line.c_str()));
			getline(in, line);
		}
		getline(in, line);
		//��ȡ�����ڶ�Ӧ����Ʒ���������
		for (i = 0; line != " "; i++) {
			hero.bag.cargo[i].num = atoi(line.c_str());
			getline(in, line);
		}
		getline(in, line);
		//��ȡ����װ������װ������Ϣ
		for (i = 0; line != " "; i++) {
			hero.bag.equipment[i] = (&(DataList::goodsList[atoi(line.c_str())]));
			getline(in, line);
		}
		getline(in, line);
		//��ȡ���ڶԻ��Ŀ���
		for (i = 0; i < DataList::trigger.size(); i++) {
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
void Hero::ShowHeroState() {
	cout << name << endl;
	cout << "�ȼ���" << level << endl;
	cout << "����ֵ��" << experience << "/" << explist[level - 1] << endl;
	cout << "��Ǯ��" << bag.money << endl;
	cout << "����ֵ��" << HP << "/" << HPmax << endl;
	cout << "ħ��ֵ��" << MP << "/" << MPmax << endl;
	cout << "������" << attack  << endl;
	cout << "������" << defense << endl;
	cout << "���ݣ�" << speed << endl << endl;
}
//����
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
		cout << "��ϲ��ĵȼ�������" << level << "��" << endl;
		if (level == 2)LearnSkill(1);
		else if (level == 4)LearnSkill(2);
		cout << endl;
	}
}
//ѧϰ����
void Hero::LearnSkill(int id) {
	skillBar.LearnSkill(&DataList::skillList[id]);
	cout << "��ѧ����" << DataList::skillList[id].name << endl;
}
//Hero�ڱ�����ʹ������Ʒ
void Hero::UsingGoods(int id) {
	Goods usingGoods(DataList().goodsList[id]);
	system("cls");
	if (bag.AbandonGoods(id)) {
		int addHp = usingGoods.addHP;
		int addMp = usingGoods.addMP;
		switch (usingGoods.attribute) {
		case 0:
			cout << "��ʹ����" << usingGoods.name << endl;
			if (addHp > 0) {
				addHp = min(addHp, HPmax - HP);
				cout << "���HP������" << addHp << "��" << endl;
			}
			if (addMp > 0) {
				addMp = min(addMp, MPmax - MP);
				cout << "���MP������" << addMp << "�㣡" << endl;
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
	currentSpotId = id;
	DataList::spotList[currentSpotId].printSpotInformation();
	OnEnterSpot();
}
//̽������
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
	cout << "�㳢���ڴ˵�̽��" << endl;
	int input = -1;
	while (input != 0) {
		if (currentSpotId == 1 || currentSpotId == 2) {
			cout << endl << "�Ƿ����̽����" << endl;
			cout << "1. ���� 2. �뿪" << endl << endl;
			input = InteractSystem::UserInput(2);
			if (input == 1) {
				int result = rand() % 100;
				if (result < 30)
					cout << "�ƺ���û�з���ʲô" << endl;
				else if (result < 35) {
					int add= rand() % 10;
					add *= currentSpotId;
					bag.money += add;
					cout << "�㷢����һЩɢ���ڵ��ϵĽ��" << endl << "�����" << add << "���" << endl;
				}
				else if (result < 40) {
					bag.AddGoods(12);
					cout << "�㷢����һ�Ź�ʵ" << endl << "�����" << DataList::goodsList[12].name << " x1" << endl;
				}
				else {
					cout << "�㷢��һֻ��������������" << endl;
					int monster = rand() % 2 + currentSpotId;
					Fight(this, monster);
				}
			}
			else {
				cout << "��ֹͣ��̽����" << endl << endl;
				input = 0;
			}
		}
		else if (currentSpotId == 0) {
			Store store;
			cout <<endl<< "�������˳��ڵ��̵�" << endl;
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
			cout << endl << "����û�п���̽���ĵط���" << endl << endl;
		}
	}
}
void Hero::IdleInput() {
	cout << "��Ҫ��ô����" << endl;
	cout << "1. ̽�� 2. ��· 3. ״̬ 4. ���� 5. װ�� 6. ��ͼ 7. �浵 8. ���ر��⻭��" << endl << endl;
	int input = InteractSystem::UserInput(8);
	system("cls");
	switch (input) {
	case 1:
		ExploreSpot();
		break;
	case 2:
		DataList::spotList[currentSpotId].printNearSpots();
		cout << DataList::spotList[currentSpotId].nearSpotId.size() + 1 << "��ȡ��" << endl << endl;
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
//Fight�Ĺ��캯��
Fight::Fight(Hero* player, int enemyId)
{
	DataList::state = DataList::battle;
	this->player = player;
	Fighting(enemyId);
}
//ս������
void Fight::Fighting(int enemyId) {
	system("pause");
	system("cls");
	NPC enemy(DataList::npcList[enemyId - 1]);
	cout << "����" << enemy.name << "������һ��" << endl;
	while (!DeathOrNot(&enemy)) {
		DecideWhoAct(&enemy);
		int index = -1;
		int command = -1;
		while (command == -1) {
			index = -1;
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
		for (unsigned int i = 0; i < list.size(); i++) {
			if (list[i]->id == 0) {
				//Hero��ʹ����Ʒ ʹ��RetrunId������Ʒ�ı��
				if (command == 3 && player->bag.cargo.size() > 0)
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
		system("cls");
		cout << "�㻹δѧϰ����" << endl << endl;
	}
	else {
		cout << endl << "Ҫʹ��ʲô���ܣ�" << endl;
		player->skillBar.Print();
		cout << player->skillBar.list.size() + 1 << ".ȡ��" << endl << endl;
		int input = -1;
		while (input == -1) {
			input = InteractSystem::UserInput(num + 1);
			system("cls");
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
	return -1;
}
//���ؼ��ܵı��
int Fight::ReturnId(NPC* owner, int num) {
	return owner->skillBar.list[num]->id;
}
//��������˺�(������ͨ������
void Fight::UseSkillAttack(NPC* attacker, NPC* defender, int id) {
	attacker->MP -= DataList::skillList[id].MPcost;
	cout << attacker->name << "ʹ����" << DataList::skillList[id].name << endl;
	if (Random(100) <= DataList::skillList[id].accuracyRate * 100) {
		int damage = DataList::skillList[id].damage * attacker->attack - defender->defense * 2;
		damage = max(damage, 0);
		if (Random(100) <= DataList::skillList[id].critRate * 100) {
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
	if (escaper->speed >= arrester->speed) {
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
	unsigned int size = enemy->skillBar.list.size();
	int index = rand() % size;
	int id = enemy->skillBar.list[index]->id;
	UseSkillAttack(enemy, player, id);
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
		cout << "�㱻" << enemy->name << "�����" << endl << endl;
		cout << "��Ϸ����" << endl << endl;
		DataList::state = DataList::over;
	}
	else {
		cout << "��սʤ��" << enemy->name << endl << endl;
		cout << "������" << enemy->experience << "�㾭��ֵ" << "��" << enemy->money << "���" << endl << endl;
		player->bag.money += enemy->money;
		if (player->level < 5) {
			player->experience += enemy->experience;
			player->experience = min(200, player->experience);
			//�ȼ�����
			player->LevelUp();
		}
		DataList::state = DataList::idle;
	}
	system("pause");
	system("cls");
}
//���������
int Fight::Random(int num) {
	return rand() % num;
}
//�̵깹�캯��
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
//���̵������Ʒ
void Store::AddGoodsId(int id) {
	goodsIdList.push_back(id);
}
void Store::Print() {
	cout << "Ҫ����ʲô������" << endl;
	int i = 0;
	for (int id : goodsIdList) {
		i++;
		cout << i << ". " << DataList::goodsList[id].name << endl;
	}
	cout << i + 1 << ". " << "ȡ��" << endl << endl;
}
//������Ʒ
void Store::Purchase(Hero* player, int id) {
	system("cls");
	if (player->bag.money >= DataList::goodsList[id].cost) {
		player->bag.AddGoods(DataList::goodsList[id].index);
		player->bag.money -= DataList::goodsList[id].cost;
		cout << "�㹺����" << DataList::goodsList[id].name << endl << endl;
	}
	else
		cout << "��Ľ�Ҳ���" << endl << endl;
}