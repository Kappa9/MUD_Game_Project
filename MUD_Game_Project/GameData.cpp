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
//复制物品
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
//描述背包内容
void Bag::Print() {
	cout << "背包内有：" << endl;
	unsigned int i = 0;
	for (i = 0; i < cargo.size(); i++) {
		cout << i + 1 << ". " << cargo[i].thing->name << "  ×" << cargo[i].num << "  " << cargo[i].thing->description << endl;
	}
	cout << i + 1 << ". " << "离开" << endl << endl;
	cout << "请选择想使用的物品：";
}
//描述武器栏中的情况
void Bag::PrintEquipment() {
	bool judge = false;
	for (int i = 0; i <= 2; i++) {
		if (equipment[i] != NULL) {
			judge = true;
			switch (i) {
			case 0:
				cout << "铠甲：" << equipment[i]->name << " 防御：" << equipment[i]->addDefense << endl;
				break;
			case 1:
				cout << "武器：" << equipment[i]->name << " 攻击：" << equipment[i]->addAttack << endl;
				break;
			case 2:
				cout << "足具：" << equipment[i]->name << " 速度：" << equipment[i]->addSpeed << endl;
				break;
			default:
				break;
			}
		}
	}
	if (!judge)
		cout << "你未穿戴任何装备" << endl;
	cout << endl;
}
//向背包中添加物品
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
//删除背包中的物品
bool Bag::AbandonGoods(int id, int num) {
	for (unsigned int i = 0; i < cargo.size(); i++) {
		if (cargo[i].thing->index == id) {
			if ((cargo[i].num - num) < 0) {
				cout << "背包中不存在这么多的物品" << endl << endl;
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
//在背包中删除物品
bool Bag::AbandonGoods(Goods* thing,int num) {
	for (unsigned int i = 0; i < cargo.size(); i++) {
		if (cargo[i].thing->index == thing->index) {
			if ((cargo[i].num - num) < 0) {
				cout << "背包中不存在这么多的物品" << endl << endl;
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
//返回在背包中该物品的剩余情况
void Bag::ReturnNum(Goods* thing) {
	for (unsigned int i = 0; i < cargo.size(); i++) {
		if (cargo[i].thing->index == thing->index) {
			cout << thing->name << "还剩余" << cargo[i].num << "件";
			return;
		}
	}
}
//装备背包中的装备
void Bag::Equip(Goods* thing) {
	if (equipment[thing->location] == NULL) {
		equipment[thing->location] = thing;
	}
	else {
		Unload(equipment[thing->location]);
		equipment[thing->location] = thing;
	}
	cout << "装备了" << thing->name << endl << endl;
	AbandonGoods(thing);
}
//卸下装备
void Bag::Unload(Goods* thing) {
	AddGoods(equipment[thing->location]->index);
	equipment[thing->location] = NULL;
	cout << "卸下了" << thing->name << endl << endl;
}
//出售背包中的物品
void Bag::Sell(Goods* thing, int num) {
	money += (thing->cost) * num;
	this->AbandonGoods(thing, num);
	cout << "你出售了" << thing->name << " ×" << num << endl;
	cout << "获得了" << (thing->cost) * num << "元" << endl << endl;
}
//购买物品
void Bag::Purchase(Goods* thing,int num) {
	if (money >=(thing->cost)*num) {
		cout << "你购买了：" << thing->name <<" ×"<<num<< endl;
		cout << "你的余额为：" << money << endl << endl;
		this->AddGoods(thing->index,num);
	}
	else {
		cout << "你的余额不足" << endl << endl;
	}
}
//返回编号
int Bag::ReturnId(int num) {
	return cargo[num - 1].thing->index;
}
//Skill的构造函数
Skill::Skill() {
	id = -1;
	name = " ";
	description = " ";
	MPcost = 0;
	damage = 0;
	critRate = 0;
	accuracyRate = 0;
}
//利用string类型的vector的构造函数
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
//复制技能
void Skill::Copy(Skill* ability) {
	this->name = ability->name;
	this->description = ability->description;
	this->MPcost = ability->MPcost;
	this->damage = ability->damage;
	this->critRate = ability->critRate;
	this->accuracyRate = ability->accuracyRate;
}
//输出技能列表
void SkillBar::Print() {
	if (list.size() == 0)
		cout << "还未学会技能" << endl << endl;
	else {
		cout << "你已学会技能：" << endl;
		for (unsigned int i = 0; i < list.size(); i++)
			cout << i + 1 << ". " << list[i]->name << " 消耗MP：" << list[i]->MPcost << " " << list[i]->description << endl;
		cout << endl;
	}
}
//学习技能
void SkillBar::LearnSkill(Skill* ability) {
	this->list.push_back(ability);
}
//构造
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
//vector参数构造，读数据时使用
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
//显示某角色的状态
void NPC::ShowNPCState() {
	cout << name << "HP：" << HP << "/" << HPmax << "，MP：" << MP << "/" << MPmax << endl << endl;
}
Spot::Spot() {
	id = -1;
}
//输出场景信息
void Spot::printSpotInformation() {
	cout << "你来到了" << name << endl;
	cout << description << endl << endl;
}
//输出相邻场景
void Spot::printNearSpots() {
	cout << "要去哪里？" << endl;
	int i = 1;
	for (int id : nearSpotId) {
		cout << i << "：" << DataList::spotList[id].name << endl;
		i++;
	}
}
//读取文件信息后输出NPC信息
void Spot::printNPCs() {
	if (NPCIdList.size() == 0)
		cout << "这里没有可以对话的NPC！" << endl << endl;
	else {
		cout << "可对话的NPC如下：" << endl;
		int i = 1;
		for (int id : NPCIdList) {
			cout << i << "：" << DataList::npcList[id].name << endl;
			i++;
		}
		cout << endl;
	}
}
//静态变量初始化
vector<Goods> DataList::goodsList(0);
vector<Skill> DataList::skillList(0);
vector<NPC> DataList::npcList(0);
vector<Spot> DataList::spotList(0);
vector<string> DataList::dialogList(0);
array<short, 10> DataList::trigger = { 0 };
DataList::Gamestate DataList::state = over;
//读文件
vector<string> InteractSystem::ReadFile(string fileName) {
	string path = "Data\\" + fileName + ".txt";
	fstream fin;
	fin.open(path.c_str(), ios::in);
	vector<string> list;
	if (!fin.is_open()) {
		cout << "未成功打开" << fileName << "文件！" << endl;
		return list;
	}
	string tmp;
	while (getline(fin, tmp))
		list.push_back(tmp);
	fin.close();
	return list;
}
//字符串分隔
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
//实现不带回显的输入
int InteractSystem::GetUserInput() {
	int command;
	cin >> command;
	return command;
}
//用户输入数字选项，maxNum(最大为10)为选项数，返回选项编号
int InteractSystem::UserInput(int maxNum) {
	int n = -1;
	while (n <= 0 || n > maxNum)
		n = GetUserInput();
	return n;
}
//对话
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
				//找到开始位置
				if (line == ("#START" + to_string(id))) {
					state = inDialog;
				}
				break;
			case inDialog:
				//选择域开始标志
				if (line == "#DECISION") {
					state = inDecision;
					for (unsigned int i = lineIndex; i < DataList::dialogList.size(); i++) {
						if (DataList::dialogList[i] == "#CASEEND") maxCases++;
						else if (DataList::dialogList[i] == "#DECISIONEND") break;
					}
					input = InteractSystem::UserInput(maxCases);
				}
				//结束的标志
				else if (line == "#END")
					reading = false;
				else cout << line << endl;
				break;
			case inDecision:
				//结束选择域
				if (line == "#CASE" + to_string(input))
					state = inCase;
				else if (line == "#DECISIONEND")
					state = inDialog;
				break;
			case inCase:
				//分支域结束
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
//输出地图
void InteractSystem::PrintMap() {
	cout << "                       废弃的魔法阵--------→女巫小屋" << endl;
	cout << "                           ↑                   |" << endl;
	cout << "                      林中村落(Lv.5)            |" << endl;
	cout << "                           ↑                  ↓" << endl;
	cout << "           王城(商店)--→森林小径--→山谷--→火山洞穴--→林间小屋" << endl;
	cout << "               ↓" << endl;
	cout << "         哥布林领地门口(Lv.2)" << endl << endl;
}