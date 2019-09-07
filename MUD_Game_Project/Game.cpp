#include "Game.h"
int main()
{
	cout << "Hello World!";
	GameThread game;



	return 0;
}



//Fight�Ĺ��캯��
Fight::Fight(Hero* player, NPC* enemy)
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

//��������˺�(������ͨ������
void Fight::UseSkillAttack(NPC* attacker,NPC* defender,int id)
{
	int MPcost;
	MPcost = DataList().skillList[id].MPcost;
	if (attacker->MP < MPcost) {
		cout << "ħ��ֵ����";
	}
	else {
		srand((int)time(0));
		if (random(100) <= DataList::skillList[id].accuracyRate) {
			if (random(100) <= DataList::skillList[id].critRate) {
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
int Fight::ReturnId(NPC* owner, int num)
{
	return owner->skillBar.list[num]->id;
}

//ʹ�ü���
void Fight::UseSkill(NPC* role)
{
	int num = role->skillBar.list.size();
	if (num == 0) {
		cout << "�㻹δѧϰ����";
	}
	else {
		cout << "Ҫʹ��ʲô���ܣ�";
		role->skillBar.Print();
		cout << role->skillBar.list.size() + 2 <<".ȡ��"<< endl << endl;

		int input = InteractSystem::UserInput(num + 2);
		//ȡ��
		if (input == num + 2) {
			
		}
		else {
			int id = ReturnId(player, input-1);
			UseSkillAttack(player, enemy, id);
		}
	}
}

//����
bool Fight::Escape(NPC* escaper,NPC* arrester)
{
	if(escaper->speed>=arrester->speed)
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

//�ж�һ������
bool Fight::DeathOrNot(NPC* player, NPC* enemy)
{
	if ((player->HP <= 0) || (enemy->HP <= 0)) {
		return true;
	}
	else{
		return false;
	}
}

//ʤ���ж�
void Fight::Victory(Hero* player, NPC* enemy)
{
	if (player->HP <= 0) {
		cout << "�㱻" << enemy->name << "�����"<<endl;
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
void Fight::Fighting()
{
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
		cout << "��ϲ��ĵȼ�������"<<player->level<<"��";
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
//���ع�꺯��
void GameThread::HideCursor()
{
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
void GameThread::GetSkillData(vector<string> list)
{
	for (string str : list) {
		//���ָ��ַ�����Ķ����µ�vector 
		vector<string> split(InteractSystem::SplitString(str, ","));
		Skill i(split);
		DataList::skillList.push_back(i);
	}
}

void GameThread::GetNPCData(vector<string> list)
{
	for (string str : list) {
		//���ָ��ַ�����Ķ����µ�vector 
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

//��������
void GameThread::SaveGame(Hero* hero) {
	//��ɾ���ļ�
	fstream fout("stuinfo.txt", ios::out | ios::trunc);  //����Ĵ浵�ļ���������Ҫ�� 

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
	
	//�洢�����е���Ʒ��id
	for (int i = 0; i < hero->bag.cargo.size(); i++) {
		fout << hero->bag.cargo[i].thing->index << endl;
	}
	fout << " "<<endl;
	//�洢�����еĶ�Ӧ��Ʒ������
	for (int i = 0; i < hero->bag.cargo.size(); i++) {
		fout << hero->bag.cargo[i].num << endl;
	}
	fout << " " << endl;

	for (int i = 0; i < hero->bag.cargo.size(); i++) {
		fout << hero->bag.equipment[i]->index << endl;
	}
	fout << " " << endl;

	//�洢�Ի��Ŀ���
	for (int i = 0; i < DataList::trigger.size(); i++) {
		fout << DataList::trigger[i] << endl;
	}
	
	fout.close();
}

//��ȡ����
void GameThread::LoadGame(Hero* hero) {
	ifstream in;
	string line;
	in.open("filename.txt");  //��Ҫ���������

	//��ȡ����hero������
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

	//����ձ��� 
	hero->bag.cargo.clear();

	//��ȡ�����ڵ���Ʒ����
	for (int i=0; line != "";i++) {
		hero->bag.AddGoods(atoi(line.c_str()));
		getline(in, line);
	}

	getline(in, line);

	//��ȡ�����ڶ�Ӧ����Ʒ���������
	for (int i = 0; line != ""; i++) {
		hero->bag.cargo[i].num = atoi(line.c_str());
		getline(in, line);
	}

	getline(in, line);
	//��ȡ����װ������װ������Ϣ
	for (int i = 0; line != ""; i++) {
		hero->bag.equipment[i]=(&(DataList::goodsList[atoi(line.c_str())]));
	}

	//��ȡ���ڶԻ��Ŀ���
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
//̽������
void Explore::ExploreSpot()
{
	Spot newSpot = DataList::spotList[spotId];
	cout << "��������" << newSpot.name << endl << newSpot.description << endl;
	for (int i = 0; i < newSpot.NPCIdList.size; i++) {
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
