#include "GameData.h";

void Goods::copy(Goods* thing)
{//����
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
{//�򱳰��������Ʒ
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
{//�ڱ�����ɾ����Ʒ
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
{//�����ڱ����и���Ʒ��ʣ�����
	for (int i = 0; i < cargo.size; i++) {
		if (cargo[i].thing->name == thing->name) {
			if (cargo[i].num != 0) {
				cout << "��ʣ��" << cargo[i].num << "��";
			}
			else
				cout << "����Ʒ�Ѳ�����";
		}

	}
}

void Bag::UsingGoods(Goods* thing)
{//�ڱ�����ʹ������Ʒ
	if (thing->attribute == 0) {
		this->AbandonGoods(thing);
		cout << "��ʹ����" << thing->name ;
		this->ReturNum;
		if (IfZero(thing->addHP)) {}
		else {
			cout << "���HP������" << thing->addHP << "��";
		}
		if (IfZero(thing->addMP)) {}
		else {
			cout << "���MP������" << thing->addMP << "��";
		}
	}
}