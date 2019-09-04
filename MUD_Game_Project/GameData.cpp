#include "GameData.h"

Goods::Goods()
{
}

Goods::Goods(vector<string> list)
{
	if (list.size() == 13) {
		name = list[0];
		description = list[1];
		attribute = atoi(list[2].c_str());
		addAtract = atoi(list[3].c_str());
		addDefense = atoi(list[4].c_str());
		addHP = atoi(list[5].c_str());
		addMaxHP = atoi(list[6].c_str());
		addMP = atoi(list[7].c_str());
		addMaxMP = atoi(list[8].c_str());
		addSpeed = atoi(list[9].c_str());
		index = atoi(list[10].c_str());
		location = atoi(list[11].c_str());
		cost = atoi(list[12].c_str());
	}
}

//������Ʒ
void Goods::Copy(Goods* thing)
{
	name=thing->name;            
	description=thing->description;     
	attribute=thing->attribute;          
	addAtract=thing->addAtract;          
	addDefense=thing->addDefense;         
	addHP=thing->addHP;              
	addMaxHP=thing->addMaxHP;           
	addMP=thing->addMP;              
	addMaxMP=thing->addMaxMP;          
	addSpeed = thing->addSpeed;           
	index=thing->index;         
	location=thing->location;           
	cost=thing->cost;               

}

//�����Ʒ����ϸ����
void Goods::PrintDescription()
{
	cout << this->description;
}



//������������
void Bag::Print(int page)
{
	int i = (page - 1) * 7;
	int number = 1;
	PrintPart(i);

}

	/*	cin >> number;
		while (number < 0 || number>9) {
			cout << "��������ȷ������";
			cin >> number;

			if (number == 8) {
				if (i < 7) {
					cout << "�޷�������һҳ";
				}
				else {
					int remainder;
					remainder = (i) % 7;
					i -= (7 + remainder);
					PrintPart(i);
				}
			}

			if (number == 9) {
				if (i == cargo.size()) {
					cout << "�޷�������һҳ";
				}
				else {
					PrintPart(i);
				}
			}
		}

		if (number == 8) {
			if (i < 7) {
				cout << "�޷�������һҳ";
			}
			else {
				int remainder;
				remainder = (i) % 7;
				i -= (7 + remainder);
				PrintPart(i);
			}
		}

		if (number == 9) {
			if (i == cargo.size()) {
				cout << "�޷�������һҳ";
			}
			else {
				PrintPart(i);
			}
		}
	}*/

//���������еĲ�������
void Bag::PrintPart(int i)
{
	int num = 0;
	cout << "�������У�" << endl;
	for (; i < cargo.size(); i++) {
		num++;
		cout << num << ". " << cargo[i].thing->name << " ��" << cargo[i].num << " ";
		if (num == 7) {
			num = 0;
			cout << "8. ��һҳ 9. ��һҳ ";
			break;
		}
	}
}

//�����������е����
void Bag::PrintEquipment()
{
	bool judge=false;

	for (int i = 0; i < 2; i++) {
		if (equipment[i] != NULL) {
			judge = true;
		}
	}
		if (judge) {
			for (int i = 0; i < 2; i++) {
				if (equipment[i] != NULL) {
					switch (i)
					{
					case 0:cout << "���ף�" << equipment[i]->name <<" ������"<<equipment[i]->addDefense<<endl;
					case 1:cout << "������" << equipment[i]->name <<" ������"<<equipment[i]->addAtract<< endl;
					case 2:cout << "��ߣ�" << equipment[i]->name <<" �ٶȣ�"<<equipment[i]->addSpeed<<endl;
					default:
						break;
					}
			}
		}
	}
		else
		{
			cout << "��δ�����κ�װ��";
		}
}


//�򱳰��������Ʒ
void Bag::AddGoods(int id,int num)
{
	bool judge = true;
	Goods* thing = &DataList::goodsList[id];
	struct goods sthing;
	sthing.thing = thing;

	for (unsigned int i = 0; i < cargo.size(); i++) {
		if (cargo[i].thing->name == thing->name) {
			cargo[i].num+=num;
			judge = false;
		}
	}
	if (judge) {
		sthing.num = num;
		this->cargo.push_back(sthing);
	 }
}

//ɾ�������е���Ʒ
void Bag::AbandonGoods(int id, int num)
{
	bool judge = false;
	int position;
	for (int i = 0; i < cargo.size(); i++) {
		if (cargo[i].thing->index == id) {
			if ((cargo[i].num - num) == 0) {
				judge = true;
				position = i;
			}
			if ((cargo[i].num - num) > 0) {
				cargo[i].num -= num;
				this->ReturnNum(cargo[i].thing);
			}
			if ((cargo[i].num - num) < 0) {
				cout << "�����в�������ô�����Ʒ";
			}
		}
	}
	if (judge) {
		this->ReturnNum(cargo[position].thing);

		cargo.erase(cargo.begin() + position);
	}
}

//�ڱ�����ɾ����Ʒ
void Bag::AbandonGoods(Goods* thing,int num)
{
	bool judge = false;
	int position;
	for (int i = 0; i < cargo.size(); i++) {
		if (cargo[i].thing->name == thing->name) {
			if ((cargo[i].num -num)==0) {
				judge = true;
				position = i;
			}
			if ((cargo[i].num-num)>0){
				cargo[i].num-=num;
				this->ReturnNum(thing);
			}
			if ((cargo[i].num - num) < 0) {
				cout << "�����в�������ô�����Ʒ";
			}
		}
	}

	if (judge) {
		this->ReturnNum(thing);

		cargo.erase(cargo.begin() + position);
	}
}

//�����ڱ����и���Ʒ��ʣ�����
void Bag::ReturnNum(Goods* thing)
{
	bool judge = false;

	for (int i = 0; i < cargo.size(); i++) {
		if (cargo[i].thing->name == thing->name) {
			if (cargo[i].num != 0) {
				cout << thing->name<<"��ʣ��" << cargo[i].num << "��";
			}
			else {
				judge = true;
			}
		}
	}
	if (judge) {
		cout << thing->name << "�Ѳ�����";
	}

}

//װ�������е�װ��
void Bag::Equip(Goods* thing)
{
	if (thing->attribute == 1)
	{
		cout << "װ����" << thing->name<<endl;

		if (equipment[thing->location] == NULL) {
			equipment[thing->location]->Copy(thing);
		}
		else
		{
			this->AddGoods(equipment[thing->location]->index);
			cout << "ж����" << equipment[thing->location]->name;
			equipment[thing->location]->Copy(thing);
		}
	}
	
	this->AbandonGoods(thing);

}

//ж��װ��
void Bag::Unload(Goods* thing)
{
	this->AddGoods(equipment[thing->location]->index);
	equipment[thing->location] = NULL;
	cout << "��" << thing->name << "ж��";
}


//���۱����е���Ʒ
void Bag::Sell(Goods* thing, int num)
{
	money +=(thing->cost)*num;
	this->AbandonGoods(thing,num);
	cout << "�������" << thing->name << " ��" << num << endl;
	cout<< ", �����" << (thing->cost) * num << "Ԫ";
}

//������Ʒ
void Bag::Purchase(Goods* thing,int num)
{
	if (money >=(thing->cost)*num) {
		cout << "�㹺���ˣ�" << thing->name <<" ��"<<num<< endl;
		cout << "������Ϊ��" << money;
		this->AddGoods(thing->index,num);
	}
	else {
		cout << "�������";
	}
}

//���ر��
int Bag::ReturnId(int num)
{
	return cargo[num - 1].thing->index;
}



//��������б�
void SkillBar::Print()
{
	if (list.size() == 0) {
		cout << "��δѧ�Ἴ��";
	}
	else {
		cout << "����ѧ�Ἴ�ܣ�";
		for (int i = 0; i < list.size(); i++) {
			cout << i+1<<". "<<list[i]->name<<" ����MP��"<<list[i]->MPcost;
			cout << endl;
		}
	}
}

//ѧϰ����
void SkillBar::LearnSkill(Skill* ability)
{
	this->list.push_back(ability);

}

//Skill�Ĺ��캯��
Skill::Skill()
{
	name = " ";
	description = " ";
	MPcost = 0;
	damage = 0;
	critRate = 0;
	accuracyRate = 0;
}

//����string���͵�vector�Ĺ��캯��
Skill::Skill(vector<string> list)
{
	if (list.size() == 7) {
		name = list[0];
		description = list[1];
		MPcost = atoi(list[2].c_str());
		damage = atoi(list[3].c_str());
		critRate = (float)atoi(list[4].c_str());
		accuracyRate = (float)atoi(list[5].c_str());
		id = atoi(list[6].c_str());
	}
}

//Skill�Ĺ��캯��
Skill::Skill(string name, string description, short MPcost, int damage, float critRate, float accuracyRate)
{
	this->name = name;
	this->description = description;
	this->MPcost = MPcost;
	this->damage = damage;
	this->critRate = critRate;
	this->accuracyRate = accuracyRate;
}

//���Ƽ���
void Skill::Copy(Skill* ability)
{
	this->name = ability->name;
	this->description = ability->description;
	this->MPcost = ability->MPcost;
	this->damage = ability->damage;
	this->critRate = ability->critRate;
	this->accuracyRate = ability->accuracyRate;
}

//���ڼ��ܵ���ϸ����
void Skill::PrintDescription()
{
	cout << this->description;
}

//Hero���캯��
Hero::Hero() {
	id = 0;
}

//����
bool Hero::LevelUp()
{
	int num = this->level;
	if ( this->experience < 10) {
		this->level = 1;
	}
	else if(this->experience<40){
		this->level = 2;
	}
	else if (this->experience>=40&&this->experience<100) {
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
void Hero::UsingGoods(int id)
{
	Goods usingGoods = DataList().goodsList[id];
	if (usingGoods.attribute == 0) {
		this->bag.AbandonGoods(id);
		cout << "��ʹ����" << usingGoods.name;
		for (int i = 0; i < bag.cargo.size(); i++) {
			if (bag.cargo[i].thing->index == id) {
				bag.ReturnNum(bag.cargo[i].thing);
			}
		}
		if ((DataList().goodsList[id].addHP)==0) {}
		else {
			if (DataList().goodsList[id].addHP<=(this->HPmax-this->HP))
				cout << "���HP������" << DataList().goodsList[id].addHP << "��";
			else {
				cout << "���HP������" << this->HPmax - this->HP;
			}
		}
		if ((DataList().goodsList[id].addMP)==0) {}
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



NPC::NPC()
{
}

NPC::NPC(vector<string> list)
{
	if (list.size() == 12) {
		id = atoi(list[0].c_str());
		name = list[1];
		HP = atoi(list[2].c_str());
		HPmax = atoi(list[3].c_str());
		MP = atoi(list[4].c_str());
		MPmax = atoi(list[5].c_str());
		speed = atoi(list[6].c_str());
		attack = atoi(list[7].c_str());
		defense = atoi(list[8].c_str());
		experience = atoi(list[9].c_str());
		money = atoi(list[10].c_str());
		talkingScript= atoi(list[11].c_str());
	}
}

//��ʾĳ��ɫ��״̬
void NPC::ShowNPCState()
{
	cout << this->name;
	cout << "������ֵ:" << this->HP << "/" << this->HPmax;
	cout << "ħ��ֵ" << this->MP << "/" << this->MPmax << ")";
}

vector<Goods> DataList::goodsList(0);
vector<Skill> DataList::skillList(0);
vector<NPC> DataList::npcList(0);
vector<Spot> DataList::spotList(0);
array<short, 100> DataList::trigger = { 0 };

InteractSystem::InteractSystem() {
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
}
//ʵ�ֲ������Ե�����
int InteractSystem::GetUserInput() {
	char command[1];
	command[0] = _getch();
	return atoi(command);
}

//�û���������ѡ�maxNum(���Ϊ10)Ϊѡ����������ѡ����
int InteractSystem::UserInput(int maxNum) {
	int n = -1;
	while (n <= 0 || n > maxNum) {
		n = GetUserInput();
		if (n == 0)n = 10;
	}
	return n;
}

void InteractSystem::PrintLog(string message) {
	SetConsoleTextAttribute(handle, 15 | 0);
	cout << message << endl << endl;
}
void InteractSystem::PrintMap() {

}


//��ȡ�ļ��еĳ�����Ϣ
void Spot::readSpotInformation()
{

}


//���������Ϣ
void Spot::printSpotInformation() {
	cout << "�㵽����" << spotName << "��" << spotDescription << "��" << endl;
	}


//��ȡ�ļ���Ϣ�����NPC��Ϣ
void Spot::printNPCs()
{
	for (int i = 0; i < NPCnumber; i++) {

	}
}

DataList::DataList() {
	for (int i : trigger) trigger[i] = 0;
}


//���Խӣ�����ͼ�Ի��ű�(enterScript)
void Spot::OnEnterSpot() {
	
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

Spot::Spot()
{
}

Spot::Spot(vector<string>list)
{
	if (list.size() == 4) {
		spotNumber = atoi(list[0].c_str());
		NPCnumber = atoi(list[1].c_str());
		spotName = list[2];
		spotDescription = list[3];
	}
}