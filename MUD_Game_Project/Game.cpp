#include "Game.h"
int main()
{
	cout << "Hello World!";
	GameThread game;




	return 0;
}

//����һ������
int GetUserInput() {
	char str[1];
	str[0] = getchar();
	return (int)str[0];
}

//�ж�������ȷ
int GetUserInput(int min, int max) {
	int n = GetUserInput();
	while (n<min || n>max) {
		cout << "��������ȷ������";
		n = GetUserInput();
	}
	return n;
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
void Fight::UseSkillAttrck(NPC* attacker,NPC* defender,int id)
{
	if (id != 0) {
		int MPcost;
		MPcost = DataList().skillList[id].MPcost;
		if (attacker->MP < MPcost) {
			cout << "ħ��ֵ����";
		}
		else {
			int damage = DataList().skillList[id].damage * attacker->attack - defender->defense * 2;
			attacker->MP -= MPcost;
			defender->HP -= damage;
			cout <<attacker->name<< "ʹ����" << DataList().skillList[id].name;
			cout << endl << "��" << defender->name << "�����" << damage << "���˺�";
		}
	}
	else {
		int damage = 5 * attacker->attack - defender->defense * 2;
		defender->HP -= damage;
		cout <<attacker->name<< "������" << defender->name;
		cout << "���������" << damage << "���˺�";
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

		int input = GetUserInput(1, num + 2);
		//ȡ��
		if (input == num + 2) {
			
		}
		else {
			int id = ReturnId(player, input-1);
			UseSkillAttrck(player, enemy, id);
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
	UseSkillAttrck(enemy,player,num);
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

				int input = GetUserInput(1, 4);

				//ѡ�񹥻�
				if (input == 1) {
					UseSkillAttrck(player, enemy, 0);
				}
				//ʹ�ü���
				else if (input == 2) {
					UseSkill(player);
				}
				//ʹ����Ʒ
				else if (input == 3) {
					player->bag.Print(1);
					int input;
					input = GetUserInput(1, player->bag.cargo.size() + 2);
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
void GameThread::GetItemData(vector<string> list) {
	for (string str : list) {
		vector<string> split(SplitString(str));
		Goods i;
		//
		DataList::goodsList.push_back(i);
	}
}
void GameThread::SaveGame() {

}
void GameThread::LoadGame() {

}