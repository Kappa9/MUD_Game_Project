#include "GameData.h"

Goods::Goods() {
	index = -1;
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
void Goods::Copy(Goods* thing)
{
	name=thing->name;            
	description=thing->description;     
	attribute=thing->attribute;          
	addAttack=thing->addAttack;          
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
					case 1:cout << "武器：" << equipment[i]->name <<" 攻击："<<equipment[i]->addAttack<< endl;
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
	id = -1;
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
		id = atoi(list[0].c_str());
		name = list[1];
		description = list[2];
		MPcost = atoi(list[3].c_str());
		damage = atoi(list[4].c_str());
		critRate = atof(list[5].c_str());
		accuracyRate = atof(list[6].c_str());
	}
	else Skill();
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


NPC::NPC(vector<string> list)
{
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
void NPC::ShowNPCState()
{
	cout << this->name;
	cout << "（生命值:" << this->HP << "/" << this->HPmax;
	cout << "魔法值" << this->MP << "/" << this->MPmax << ")";
}

//Hero构造函数
Hero::Hero() {
	id = 0; name = "勇者";
	HPmax = 450; MPmax = 90;
	HP = HPmax; MP = MPmax;
	speed = 24; attack = 16; defense = 16;
	experience = 0; level = 1;
	money = 0; bag.money = 0;
	currentSpotId = 0;
}

//升级
bool Hero::LevelUp()
{
	int num = this->level;
	if ( this->experience < 10) {
		this->level = 1;
	}
	else if (this->experience < 40) {
		this->level = 2;
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

//移动到一个地点
void Hero::MoveToSpot(int id)
{
	cout << "你来到了" << DataList::spotList[id].name<<endl;
	cout << DataList::spotList[id].description << endl;

}

vector<Goods> DataList::goodsList(0);
vector<Skill> DataList::skillList(0);
vector<NPC> DataList::npcList(0);
vector<Spot> DataList::spotList(0);
vector<string> DataList::dialogList(0);
array<short, 100> DataList::trigger = { 0 };

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

//对话
int InteractSystem::Dialog(int id) {
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
			if (line == ("#START" + id)) {
				state = inDialog;
			}
			break;
		case inDialog:
			//选择域开始标志
			if (line == "#DECISION") {
				state = inDecision;
				for (int i = lineIndex; i < DataList::dialogList.size(); i++) {
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
			if (line == "#CASE" + input)
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
	return input;
}

void InteractSystem::PrintMap() {
	cout << "                       废弃的魔法阵--------→女巫小屋" << endl;
	cout << "                           ↑                   |" << endl;
	cout << "                      林中村落(Lv.5)            |" << endl;
	cout << "                           ↑                  ↓" << endl;
	cout << "           王城(商店)--→森林小径--→山谷--→火山洞穴--→林间小屋" << endl;
	cout << "               ↓" << endl;
	cout << "         哥布林领地门口(Lv.2)" << endl;
	cout << "               ↓" << endl;
	cout << "            隐秘地牢" << endl;
}

Spot::Spot() {
	id = -1;
}

Spot::Spot(vector<string>list) {
	if (list.size() == 3) {
		id = atoi(list[0].c_str());
		name = list[1];
		description = list[2];
	}
}

//输出场景信息
void Spot::printSpotInformation() {
	cout << "你到达了" << name << "，" << description << "。" << endl;
}


//读取文件信息后输出NPC信息
void Spot::printNPCs()
{
	for (int i = 0; i < NPCIdList.size(); i++) {

	}
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


