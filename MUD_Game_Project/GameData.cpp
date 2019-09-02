#include "GameData.h";

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
	for (i ; i < cargo.size(); i++) {
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
void Bag::AddGoods(Goods* thing,int num)
{
	bool judge = true;

	struct goods sthing;
	sthing.thing = thing;

	for (int i = 0; i < cargo.size(); i++) {
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
			this->AddGoods(equipment[thing->location]);
			cout << "卸下了" << equipment[thing->location]->name;
			equipment[thing->location]->Copy(thing);
		}
	}
	
	this->AbandonGoods(thing);

}

//卸下装备
void Bag::Unload(Goods* thing)
{
	this->AddGoods(equipment[thing->location]);
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
		this->AddGoods(thing,num);
	}
	else {
		cout << "你的余额不足";
	}
}

//在背包中使用消耗品
void Bag::UsingGoods(Goods* thing)
{
	if (thing->attribute == 0) {
		this->AbandonGoods(thing);
		cout << "你使用了" << thing->name ;
		this->ReturnNum(thing);
		if (IfZero(thing->addHP)) {}
		else {
			cout << "你的HP增加了" << thing->addHP << "点";
		}
		if (IfZero(thing->addMP)) {}
		else {
			cout << "你的MP增加了" << thing->addMP << "点";
		}
	}
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
	damage = " ";
	critRate = 0;
	accuracyRate = 0;
}

//Skill的构造函数
Skill::Skill(string name, string description, short MPcost, string damage, float critRate, float accuracyRate)
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




void Spot::readSoptInformation()
{

}

void Spot::printSpotInformation() {
		cout << "你到达了" << spotName << "，" << "spotDescription";
	}

void Spot::printNPCs()
{
	for (int i = 0; i++; i < NPCnumber) {

	}
}


