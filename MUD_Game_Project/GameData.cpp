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

//复制物品
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

//输出物品的详细描述
void Goods::PrintDescription()
{
	cout << this->description;
}



//描述背包内容
void Bag::Print(int page)
{
	int i = (page - 1) * 7;
	int number = 1;
	PrintPart(i);

}

	/*	cin >> number;
		while (number < 0 || number>9) {
			cout << "请输入正确的数字";
			cin >> number;

			if (number == 8) {
				if (i < 7) {
					cout << "无法翻到上一页";
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
					cout << "无法翻到下一页";
				}
				else {
					PrintPart(i);
				}
			}
		}

		if (number == 8) {
			if (i < 7) {
				cout << "无法翻到上一页";
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
				cout << "无法翻到下一页";
			}
			else {
				PrintPart(i);
			}
		}
	}*/

//描述背包中的部分物体
void Bag::PrintPart(int i)
{
	int num = 0;
	cout << "背包内有：" << endl;
	for (; i < cargo.size(); i++) {
		num++;
		cout << num << ". " << cargo[i].thing->name << " ×" << cargo[i].num << " ";
		if (num == 7) {
			num = 0;
			cout << "8. 上一页 9. 下一页 ";
			break;
		}
	}
}

//描述武器栏中的情况
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
					case 0:cout << "铠甲：" << equipment[i]->name <<" 防御："<<equipment[i]->addDefense<<endl;
					case 1:cout << "武器：" << equipment[i]->name <<" 攻击："<<equipment[i]->addAtract<< endl;
					case 2:cout << "足具：" << equipment[i]->name <<" 速度："<<equipment[i]->addSpeed<<endl;
					default:
						break;
					}
			}
		}
	}
		else
		{
			cout << "你未穿戴任何装备";
		}
}


//向背包中添加物品
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

//删除背包中的物品
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
				cout << "背包中不存在这么多的物品";
			}
		}
	}
	if (judge) {
		this->ReturnNum(cargo[position].thing);

		cargo.erase(cargo.begin() + position);
	}
}

//在背包中删除物品
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
				cout << "背包中不存在这么多的物品";
			}
		}
	}

	if (judge) {
		this->ReturnNum(thing);

		cargo.erase(cargo.begin() + position);
	}
}

//返回在背包中该物品的剩余情况
void Bag::ReturnNum(Goods* thing)
{
	bool judge = false;

	for (int i = 0; i < cargo.size(); i++) {
		if (cargo[i].thing->name == thing->name) {
			if (cargo[i].num != 0) {
				cout << thing->name<<"还剩余" << cargo[i].num << "件";
			}
			else {
				judge = true;
			}
		}
	}
	if (judge) {
		cout << thing->name << "已不存在";
	}

}

//装备背包中的装备
void Bag::Equip(Goods* thing)
{
	if (thing->attribute == 1)
	{
		cout << "装备了" << thing->name<<endl;

		if (equipment[thing->location] == NULL) {
			equipment[thing->location]->Copy(thing);
		}
		else
		{
			this->AddGoods(equipment[thing->location]->index);
			cout << "卸下了" << equipment[thing->location]->name;
			equipment[thing->location]->Copy(thing);
		}
	}
	
	this->AbandonGoods(thing);

}

//卸下装备
void Bag::Unload(Goods* thing)
{
	this->AddGoods(equipment[thing->location]->index);
	equipment[thing->location] = NULL;
	cout << "将" << thing->name << "卸下";
}


//出售背包中的物品
void Bag::Sell(Goods* thing, int num)
{
	money +=(thing->cost)*num;
	this->AbandonGoods(thing,num);
	cout << "你出售了" << thing->name << " ×" << num << endl;
	cout<< ", 获得了" << (thing->cost) * num << "元";
}

//购买物品
void Bag::Purchase(Goods* thing,int num)
{
	if (money >=(thing->cost)*num) {
		cout << "你购买了：" << thing->name <<" ×"<<num<< endl;
		cout << "你的余额为：" << money;
		this->AddGoods(thing->index,num);
	}
	else {
		cout << "你的余额不足";
	}
}

//返回编号
int Bag::ReturnId(int num)
{
	return cargo[num - 1].thing->index;
}



//输出技能列表
void SkillBar::Print()
{
	if (list.size() == 0) {
		cout << "还未学会技能";
	}
	else {
		cout << "你已学会技能：";
		for (int i = 0; i < list.size(); i++) {
			cout << i+1<<". "<<list[i]->name<<" 消耗MP："<<list[i]->MPcost;
			cout << endl;
		}
	}
}

//学习技能
void SkillBar::LearnSkill(Skill* ability)
{
	this->list.push_back(ability);

}

//Skill的构造函数
Skill::Skill()
{
	name = " ";
	description = " ";
	MPcost = 0;
	damage = 0;
	critRate = 0;
	accuracyRate = 0;
}

//利用string类型的vector的构造函数
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

//Skill的构造函数
Skill::Skill(string name, string description, short MPcost, int damage, float critRate, float accuracyRate)
{
	this->name = name;
	this->description = description;
	this->MPcost = MPcost;
	this->damage = damage;
	this->critRate = critRate;
	this->accuracyRate = accuracyRate;
}

//复制技能
void Skill::Copy(Skill* ability)
{
	this->name = ability->name;
	this->description = ability->description;
	this->MPcost = ability->MPcost;
	this->damage = ability->damage;
	this->critRate = ability->critRate;
	this->accuracyRate = ability->accuracyRate;
}

//关于技能的详细描述
void Skill::PrintDescription()
{
	cout << this->description;
}

//Hero构造函数
Hero::Hero() {
	id = 0;
}

//升级
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

//Hero在背包中使用消耗品
void Hero::UsingGoods(int id)
{
	Goods usingGoods = DataList().goodsList[id];
	if (usingGoods.attribute == 0) {
		this->bag.AbandonGoods(id);
		cout << "你使用了" << usingGoods.name;
		for (int i = 0; i < bag.cargo.size(); i++) {
			if (bag.cargo[i].thing->index == id) {
				bag.ReturnNum(bag.cargo[i].thing);
			}
		}
		if ((DataList().goodsList[id].addHP)==0) {}
		else {
			if (DataList().goodsList[id].addHP<=(this->HPmax-this->HP))
				cout << "你的HP增加了" << DataList().goodsList[id].addHP << "点";
			else {
				cout << "你的HP增加了" << this->HPmax - this->HP;
			}
		}
		if ((DataList().goodsList[id].addMP)==0) {}
		else {
			if (DataList().goodsList[id].addMP <= (this->MPmax - this->MP)) {
				cout << "你的MP增加了" << DataList().goodsList[id].addMP << "点";
			}
			else {
				cout << "你的MP增加了" << this->MPmax - this->MP;
			}
		}
	}
	else {
		cout << "选择的物品无法使用";
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

//显示某角色的状态
void NPC::ShowNPCState()
{
	cout << this->name;
	cout << "（生命值:" << this->HP << "/" << this->HPmax;
	cout << "魔法值" << this->MP << "/" << this->MPmax << ")";
}

vector<Goods> DataList::goodsList(0);
vector<Skill> DataList::skillList(0);
vector<NPC> DataList::npcList(0);
vector<Spot> DataList::spotList(0);
array<short, 100> DataList::trigger = { 0 };

InteractSystem::InteractSystem() {
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
}
//实现不带回显的输入
int InteractSystem::GetUserInput() {
	char command[1];
	command[0] = _getch();
	return atoi(command);
}

//用户输入数字选项，maxNum(最大为10)为选项数，返回选项编号
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


//读取文件中的场景信息
void Spot::readSpotInformation()
{

}


//输出场景信息
void Spot::printSpotInformation() {
	cout << "你到达了" << spotName << "，" << spotDescription << "。" << endl;
	}


//读取文件信息后输出NPC信息
void Spot::printNPCs()
{
	for (int i = 0; i < NPCnumber; i++) {

	}
}

DataList::DataList() {
	for (int i : trigger) trigger[i] = 0;
}


//待对接，读地图对话脚本(enterScript)
void Spot::OnEnterSpot() {
	
}

//构造函数
store::store()
{
}

//添加物品的ID
void store::AddGoodsId(int id)
{
	goodsIdList.push_back(id);
}

//购买物品
void store::Purchase(Hero* player, int id)
{
	if (player->bag.money >= DataList::goodsList[id].cost) { 
		player->bag.AddGoods(DataList::goodsList[id].index);
		player->bag.money -= DataList::goodsList[id].cost;
		cout << "你购买了" << DataList::goodsList[id].name << endl;
	}
	else {
		cout << "你的金币不足" << endl;
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