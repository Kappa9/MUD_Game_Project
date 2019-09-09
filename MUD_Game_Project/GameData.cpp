#include "GameData.h"

Goods::Goods() {
	index = -1; name = "";
	description = "";
	attribute = 2; location = 3;
	cost = 0;
	addHP = 0; addMP = 0;
	addMaxHP = 0; addMaxMP = 0;
	addAttack = 0; addDefense = 0; addSpeed = 0;
}
Goods::Goods(vector<string> list) {
	if (list.size() == 13) {
		index = atoi(list[0].c_str());
		name = list[1];
		description = list[2];
		attribute = atoi(list[3].c_str());
		location = atoi(list[4].c_str());
		cost = atoi(list[5].c_str());
		addHP = atoi(list[6].c_str());
		addMP = atoi(list[7].c_str());
		addMaxHP = atoi(list[8].c_str());
		addMaxMP = atoi(list[9].c_str());
		addAttack = atoi(list[10].c_str());
		addDefense = atoi(list[11].c_str());
		addSpeed = atoi(list[12].c_str());
	}
	else Goods();
}
//������Ʒ
void Goods::Copy(Goods* thing) {
	name = thing->name;
	description = thing->description;
	attribute = thing->attribute;
	addAttack = thing->addAttack;
	addDefense = thing->addDefense;
	addHP = thing->addHP;
	addMaxHP = thing->addMaxHP;
	addMP = thing->addMP;
	addMaxMP = thing->addMaxMP;
	addSpeed = thing->addSpeed;
	index = thing->index;
	location = thing->location;
	cost = thing->cost;
}
Bag::Bag() {
	money = 0;
	equipment[0] = NULL;
	equipment[1] = NULL;
	equipment[2] = NULL;
}
//������������
void Bag::Print() {
	cout << "�������У�" << endl;
	unsigned int i = 0;
	for (i = 0; i < cargo.size(); i++) {
		cout << i + 1 << ". " << cargo[i].thing->name << "  ��" << cargo[i].num << "  " << cargo[i].thing->description << endl;
	}
	cout << i + 1 << ". " << "�뿪" << endl << endl;
	cout << "��ѡ����ʹ�õ���Ʒ��";
}
//�����������е����
void Bag::PrintEquipment() {
	bool judge = false;
	for (int i = 0; i <= 2; i++) {
		if (equipment[i] != NULL) {
			judge = true;
			switch (i) {
			case 0:
				cout << "���ף�" << equipment[i]->name << " ������" << equipment[i]->addDefense << endl;
				break;
			case 1:
				cout << "������" << equipment[i]->name << " ������" << equipment[i]->addAttack << endl;
				break;
			case 2:
				cout << "��ߣ�" << equipment[i]->name << " �ٶȣ�" << equipment[i]->addSpeed << endl;
				break;
			default:
				break;
			}
		}
	}
	if (!judge)
		cout << "��δ�����κ�װ��" << endl;
	cout << endl;
}
//�򱳰��������Ʒ
void Bag::AddGoods(int id,int num) {
	bool judge = true;
	Goods* thing = &DataList::goodsList[id];
	Cargo sthing;
	sthing.thing = thing;
	for (unsigned int i = 0; i < cargo.size(); i++) {
		if (cargo[i].thing->index == thing->index) {
			cargo[i].num+=num;
			judge = false;
			return;
		}
	}
	if (judge) {
		sthing.num = num;
		this->cargo.push_back(sthing);
	}
}
//ɾ�������е���Ʒ
bool Bag::AbandonGoods(int id, int num) {
	for (unsigned int i = 0; i < cargo.size(); i++) {
		if (cargo[i].thing->index == id) {
			if ((cargo[i].num - num) < 0) {
				cout << "�����в�������ô�����Ʒ" << endl << endl;
				return false;
			}
			else {
				cargo[i].num -= num;
				if (cargo[i].num == 0)
					cargo.erase(begin(cargo) + i);
				return true;
			}
		}
	}
	return false;
}
//�ڱ�����ɾ����Ʒ
bool Bag::AbandonGoods(Goods* thing,int num) {
	for (unsigned int i = 0; i < cargo.size(); i++) {
		if (cargo[i].thing->index == thing->index) {
			if ((cargo[i].num - num) < 0) {
				cout << "�����в�������ô�����Ʒ" << endl << endl;
				return false;
			}
			else {
				cargo[i].num -= num;
				if (cargo[i].num == 0)
					cargo.erase(begin(cargo) + i);
				return true;
			}
		}
	}
	return false;
}
//�����ڱ����и���Ʒ��ʣ�����
void Bag::ReturnNum(Goods* thing) {
	for (unsigned int i = 0; i < cargo.size(); i++) {
		if (cargo[i].thing->index == thing->index) {
			cout << thing->name << "��ʣ��" << cargo[i].num << "��";
			return;
		}
	}
}
//װ�������е�װ��
void Bag::Equip(Goods* thing) {
	if (equipment[thing->location] == NULL) {
		equipment[thing->location] = thing;
	}
	else {
		Unload(equipment[thing->location]);
		equipment[thing->location] = thing;
	}
	cout << "װ����" << thing->name << endl << endl;
	AbandonGoods(thing);
}
//ж��װ��
void Bag::Unload(Goods* thing) {
	AddGoods(equipment[thing->location]->index);
	equipment[thing->location] = NULL;
	cout << "ж����" << thing->name << endl << endl;
}
//���۱����е���Ʒ
void Bag::Sell(Goods* thing, int num) {
	money += (thing->cost) * num;
	this->AbandonGoods(thing, num);
	cout << "�������" << thing->name << " ��" << num << endl;
	cout << "�����" << (thing->cost) * num << "Ԫ" << endl << endl;
}
//������Ʒ
void Bag::Purchase(Goods* thing,int num) {
	if (money >=(thing->cost)*num) {
		cout << "�㹺���ˣ�" << thing->name <<" ��"<<num<< endl;
		cout << "������Ϊ��" << money << endl << endl;
		this->AddGoods(thing->index,num);
	}
	else {
		cout << "�������" << endl << endl;
	}
}
//���ر��
int Bag::ReturnId(int num) {
	return cargo[num - 1].thing->index;
}
//Skill�Ĺ��캯��
Skill::Skill() {
	id = -1;
	name = " ";
	description = " ";
	MPcost = 0;
	damage = 0;
	critRate = 0;
	accuracyRate = 0;
}
//����string���͵�vector�Ĺ��캯��
Skill::Skill(vector<string> list) {
	if (list.size() == 7) {
		id = atoi(list[0].c_str());
		name = list[1];
		description = list[2];
		MPcost = atoi(list[3].c_str());
		damage = atoi(list[4].c_str());
		critRate = (float)atof(list[5].c_str());
		accuracyRate = (float)atof(list[6].c_str());
	}
	else Skill();
}
//���Ƽ���
void Skill::Copy(Skill* ability) {
	this->name = ability->name;
	this->description = ability->description;
	this->MPcost = ability->MPcost;
	this->damage = ability->damage;
	this->critRate = ability->critRate;
	this->accuracyRate = ability->accuracyRate;
}
//��������б�
void SkillBar::Print() {
	if (list.size() == 0)
		cout << "��δѧ�Ἴ��" << endl << endl;
	else {
		cout << "����ѧ�Ἴ�ܣ�" << endl;
		for (unsigned int i = 0; i < list.size(); i++)
			cout << i + 1 << ". " << list[i]->name << " ����MP��" << list[i]->MPcost << " " << list[i]->description << endl;
		cout << endl;
	}
}
//ѧϰ����
void SkillBar::LearnSkill(Skill* ability) {
	this->list.push_back(ability);
}
//����
NPC::NPC() {
	id = -1;
	name = "";
	HPmax = 1;
	MPmax = 0;
	HP = HPmax; MP = MPmax;
	speed = 0;
	attack = 0;
	defense = 0;
	experience = 0;
	money = 0;
	talkingScript = -1;
}
//vector�������죬������ʱʹ��
NPC::NPC(vector<string> list) {
	if (list.size() == 10) {
		id = atoi(list[0].c_str());
		name = list[1];
		HPmax = atoi(list[2].c_str());
		MPmax = atoi(list[3].c_str());
		HP = HPmax; MP = MPmax;
		speed = atoi(list[4].c_str());
		attack = atoi(list[5].c_str());
		defense = atoi(list[6].c_str());
		experience = atoi(list[7].c_str());
		money = atoi(list[8].c_str());
		talkingScript = atoi(list[9].c_str());
	}
	else NPC();
}
//��ʾĳ��ɫ��״̬
void NPC::ShowNPCState() {
	cout << name << "HP��" << HP << "/" << HPmax << "��MP��" << MP << "/" << MPmax << endl << endl;
}
Spot::Spot() {
	id = -1;
}
//���������Ϣ
void Spot::printSpotInformation() {
	cout << "��������" << name << endl;
	cout << description << endl << endl;
}
//������ڳ���
void Spot::printNearSpots() {
	cout << "Ҫȥ���" << endl;
	int i = 1;
	for (int id : nearSpotId) {
		cout << i << "��" << DataList::spotList[id].name << endl;
		i++;
	}
}
//��ȡ�ļ���Ϣ�����NPC��Ϣ
void Spot::printNPCs() {
	if (NPCIdList.size() == 0)
		cout << "����û�п��ԶԻ���NPC��" << endl << endl;
	else {
		cout << "�ɶԻ���NPC���£�" << endl;
		int i = 1;
		for (int id : NPCIdList) {
			cout << i << "��" << DataList::npcList[id].name << endl;
			i++;
		}
		cout << endl;
	}
}
//��̬������ʼ��
vector<Goods> DataList::goodsList(0);
vector<Skill> DataList::skillList(0);
vector<NPC> DataList::npcList(0);
vector<Spot> DataList::spotList(0);
vector<string> DataList::dialogList(0);
array<short, 10> DataList::trigger = { 0 };
DataList::Gamestate DataList::state = over;
//���ļ�
vector<string> InteractSystem::ReadFile(string fileName) {
	string path = "Data\\" + fileName + ".txt";
	fstream fin;
	fin.open(path.c_str(), ios::in);
	vector<string> list;
	if (!fin.is_open()) {
		cout << "δ�ɹ���" << fileName << "�ļ���" << endl;
		return list;
	}
	string tmp;
	while (getline(fin, tmp))
		list.push_back(tmp);
	fin.close();
	return list;
}
//�ַ����ָ�
vector<string> InteractSystem::SplitString(string str, string pattern) {
	vector<string> split;
	string::size_type pos;
	str += pattern;
	unsigned int size = str.size();
	for (unsigned int i = 0; i < size; i++) {
		pos = str.find(pattern, i);
		if (pos < size) {
			string s = str.substr(i, pos - i);
			split.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return split;
}
//ʵ�ֲ������Ե�����
int InteractSystem::GetUserInput() {
	int command;
	cin >> command;
	return command;
}
//�û���������ѡ�maxNum(���Ϊ10)Ϊѡ����������ѡ����
int InteractSystem::UserInput(int maxNum) {
	int n = -1;
	while (n <= 0 || n > maxNum)
		n = GetUserInput();
	return n;
}
//�Ի�
int InteractSystem::Dialog(int id) {
	if (DataList::state != DataList::over) {
		int input = 0;
		int maxCases = 0;
		int lineIndex = 0;
		bool reading = true;
		enum DialogState {
			idle, inDialog, inDecision, inCase
		};
		DialogState state = idle;
		for (string line : DataList::dialogList) {
			if (!reading)break;
			switch (state) {
			case idle:
				//�ҵ���ʼλ��
				if (line == ("#START" + to_string(id))) {
					state = inDialog;
				}
				break;
			case inDialog:
				//ѡ����ʼ��־
				if (line == "#DECISION") {
					state = inDecision;
					for (unsigned int i = lineIndex; i < DataList::dialogList.size(); i++) {
						if (DataList::dialogList[i] == "#CASEEND") maxCases++;
						else if (DataList::dialogList[i] == "#DECISIONEND") break;
					}
					input = InteractSystem::UserInput(maxCases);
				}
				//�����ı�־
				else if (line == "#END")
					reading = false;
				else cout << line << endl;
				break;
			case inDecision:
				//����ѡ����
				if (line == "#CASE" + to_string(input))
					state = inCase;
				else if (line == "#DECISIONEND")
					state = inDialog;
				break;
			case inCase:
				//��֧�����
				if (line == "#CASEEND")
					state = inDecision;
				else cout << line << endl;
				break;
			default: break;
			}
			lineIndex++;
		}
		cout << endl;
		return input;
	}
	return 0;
}
//�����ͼ
void InteractSystem::PrintMap() {
	cout << "                       ������ħ����--------��Ů��С��" << endl;
	cout << "                           ��                   |" << endl;
	cout << "                      ���д���(Lv.5)            |" << endl;
	cout << "                           ��                  ��" << endl;
	cout << "           ����(�̵�)--��ɭ��С��--��ɽ��--����ɽ��Ѩ--���ּ�С��" << endl;
	cout << "               ��" << endl;
	cout << "         �粼������ſ�(Lv.2)" << endl << endl;
}