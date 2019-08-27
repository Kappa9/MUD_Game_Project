#include "GameData.h";

void Goods::copy(Goods* thing)
{//������Ʒ
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
{//������������
	cout << "�������У�" << endl;
	for (int i = 0; i < cargo.size(); i++) {
		cout << cargo[i].thing->name<<" ��"<<cargo[i].num<<endl;
	}
	cout << "���:" << money;
}

void Bag::PrintEquipment()
{//�����������е����
	bool judge;
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

void Bag::AddGoods(Goods* thing,int num)
{//�򱳰��������Ʒ
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

void Bag::AbandonGoods(Goods* thing,int num)
{//�ڱ�����ɾ����Ʒ
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
				this->ReturNum(thing);
			}
			if ((cargo[i].num - num) < 0) {
				cout << "�����в�������ô�����Ʒ";
			}
		}
	}

	if (judge) {
		this->ReturNum(thing);

		cargo.erase(cargo.begin() + position);
	}
}


void Bag::ReturNum(Goods* thing)
{//�����ڱ����и���Ʒ��ʣ�����
	bool judge = false;

	for (int i = 0; i < cargo.size(); i++) {
		if (cargo[i].thing->name == thing->name) {
			judge = true;
			if (cargo[i].num != 0) {
				cout << thing->name<<"��ʣ��" << cargo[i].num << "��";
			}
		}
	}

	if (judge) {
		cout << thing->name << "�Ѳ�����";
	}
}

void Bag::Equip(Goods* thing)
{//װ�������е�װ��
	if (thing->attribute == 1)
	{
		cout << "װ����" << thing->name<<endl;

		if (equipment[thing->location] == NULL) {
			equipment[thing->location]->copy(thing);
		}
		else
		{
			this->AddGoods(equipment[thing->location]);
			cout << "ж����" << equipment[thing->location]->name;
			equipment[thing->location]->copy(thing);
		}
	}
	
	this->AbandonGoods(thing);

}

void Bag::Unload(Goods* thing)
{//ж��װ��
	this->AddGoods(equipment[thing->location]);
	equipment[thing->location] = NULL;
	cout << "��" << thing->name << "ж��";
}


void Bag::Sell(Goods* thing, int num)
{//���۱����е���Ʒ
	money +=(thing->cost)*num;
	this->AbandonGoods(thing);
	cout << "�������" << thing->name << " ��" << num << endl;
	cout<< ", �����" << (thing->cost) * num << "Ԫ";
}

void Bag::Purchase(Goods* thing,int num)
{//������Ʒ
	if (money >=(thing->cost)*num) {
		cout << "�㹺���ˣ�" << thing->name <<" ��"<<num<< endl;
		cout << "������Ϊ��" << money;
		this->AddGoods(thing,num);
	}
	else {
		cout << "�������";
	}
}


void Bag::UsingGoods(Goods* thing)
{//�ڱ�����ʹ������Ʒ
	if (thing->attribute == 0) {
		this->AbandonGoods(thing);
		cout << "��ʹ����" << thing->name ;
		this->ReturNum(thing);
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