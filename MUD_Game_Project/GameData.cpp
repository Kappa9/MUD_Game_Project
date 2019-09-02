#include "GameData.h";

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
	for (i ; i < cargo.size(); i++) {
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
			this->AddGoods(equipment[thing->location]);
			cout << "ж����" << equipment[thing->location]->name;
			equipment[thing->location]->Copy(thing);
		}
	}
	
	this->AbandonGoods(thing);

}

//ж��װ��
void Bag::Unload(Goods* thing)
{
	this->AddGoods(equipment[thing->location]);
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
		this->AddGoods(thing,num);
	}
	else {
		cout << "�������";
	}
}

//�ڱ�����ʹ������Ʒ
void Bag::UsingGoods(Goods* thing)
{
	if (thing->attribute == 0) {
		this->AbandonGoods(thing);
		cout << "��ʹ����" << thing->name ;
		this->ReturnNum(thing);
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
	damage = " ";
	critRate = 0;
	accuracyRate = 0;
}

//Skill�Ĺ��캯��
Skill::Skill(string name, string description, short MPcost, string damage, float critRate, float accuracyRate)
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




void Spot::readSoptInformation()
{

}

void Spot::printSpotInformation() {
		cout << "�㵽����" << spotName << "��" << "spotDescription";
	}

void Spot::printNPCs()
{
	for (int i = 0; i++; i < NPCnumber) {

	}
}


