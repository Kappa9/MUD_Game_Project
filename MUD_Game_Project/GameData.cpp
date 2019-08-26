#include "GameData.h";

void Goods::copy(Goods* thing)
{//复制
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
	skillIndex=thing->skillIndex;         
	location=thing->location;           
	cost=thing->cost;               

}




void Bag::Print()
{//描述背包内容
	cout << "背包内有：" << endl;
	for (int i = 0; i < cargo.size; i++) {
		cout << cargo[i].thing->name<<" ×"<<cargo[i].num<<endl;
	}
}

void Bag::PrintEquipment()
{//描述武器栏中的情况
	bool judge;
	for (int i = 0; i < 3; i++) {
		if (equipment[i] != NULL) {
			judge = true;
		}
	}
		if (judge) {
			for (int i = 0; i < 3; i++) {
				if (equipment[i] != NULL) {
					switch (i)
					{
					case 0:cout << "头盔：" << equipment[i]->name << endl;
					case 1:cout << "铠甲：" << equipment[i]->name << endl;
					case 2:cout << "武器：" << equipment[i]->name << endl;
					case 3:cout << "足具：" << equipment[i]->name << endl;
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

void Bag::AddGoods(Goods* thing,int num=1)
{//向背包中添加物品
	bool judge = true;

	struct goods sthing;
	sthing.thing = thing;

	for (int i = 0; i < cargo.size; i++) {
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

void Bag::AbandonGoods(Goods* thing,int num=1)
{//在背包中删除物品
	for (int i = 0; i < cargo.size; i++) {
		if (cargo[i].thing->name == thing->name) {
			if ((cargo[i].num -num)==0) {
			cout << " ";
			}
			else{
			cargo[i].num--;
			this->ReturNum;
			}
		}
	}
	
}


void Bag::ReturNum(Goods* thing)
{//返回在背包中该物品的剩余情况
	for (int i = 0; i < cargo.size; i++) {
		if (cargo[i].thing->name == thing->name) {
			if (cargo[i].num != 0) {
				cout << "还剩余" << cargo[i].num << "件";
			}
			else
				cout << "该物品已不存在";
		}

	}
}

void Bag::Equip(Goods* thing)
{//装备背包中的装备
	if (thing->attribute == 1)
	{
		cout << "装备了" << thing->name<<endl;

		if (equipment[thing->location] == NULL) {
			equipment[thing->location]->copy(thing);
		}
		else
		{
			this->AddGoods(equipment[thing->location]);
			cout << "卸下了" << equipment[thing->location]->name;
			equipment[thing->location]->copy(thing);
		}
	}
	
	this->AbandonGoods(thing);

}

void Bag::Unload(Goods* thing)
{//卸下装备
	this->AddGoods(equipment[thing->location]);
	equipment[thing->location] = NULL;
	cout << "将" << thing->name << "卸下";
}


void Bag::Sell(Goods* thing, int num=1)
{//出售背包中的物品
	money +=(thing->cost)*num;
	this->AbandonGoods(thing);
	cout << "你出售了" << thing->name << " ×" << num << endl;
	cout<< ", 获得了" << (thing->cost) * num << "元";
}

void Bag::purchase(Goods* thing,int num=1)
{//购买物品
	if (money >=(thing->cost)*num) {
		cout << "你购买了：" << thing->name <<" ×"<<num<< endl;
		cout << "你的余额为：" << money;
		this->AddGoods(thing,num);
	}
	else {
		cout << "你的余额不足";
	}
}


void Bag::UsingGoods(Goods* thing)
{//在背包中使用消耗品
	if (thing->attribute == 0) {
		this->AbandonGoods(thing);
		cout << "你使用了" << thing->name ;
		this->ReturNum;
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