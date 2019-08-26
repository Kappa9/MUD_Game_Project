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




void Bag::AddGoods(Goods* thing)   
{//向背包中添加物品
	bool judge = true;

	struct goods sthing;
	sthing.thing = thing;

	for (int i = 0; i < cargo.size; i++) {
		if (cargo[i].thing->name == thing->name) {
			cargo[i].num++;
			judge = false;
		}
	}
	if (judge) {
		sthing.num = 1;
		this->cargo.push_back(sthing);
	 }
}

void Bag::AbandonGoods(Goods* thing)
{//在背包中删除物品
	for (int i = 0; i < cargo.size; i++) {
		if (cargo[i].thing->name == thing->name) {
			if (cargo[i].num == 1) {
				
			}
			else {
				/*for (int j = i; j < goods.size - 1; j++) {
					goods[j] = goods[j + 1];
				}*/
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