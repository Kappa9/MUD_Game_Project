#include "Game.h";

//Fight�Ĺ��캯��
Fight::Fight(NPC* player, NPC* enemy)
{
	this->player = player;
	this->enemy = enemy;
}

//Fight����������
Fight::~Fight()
{
}

//�ж�˭������
NPC* Fight::DecideWhoAct()
{
	if (player->speed >= enemy->speed) {
		return player;
	}
	if (player->speed < enemy->speed) {
		return enemy;
	}
}

//ʹ�ü���
void Fight::UseSkill(NPC* role)
{

}

//ս������
void Fight::Fighting()
{
	cout << "����" << enemy->name << "������һ��";
	NPC* actor = DecideWhoAct();
	if (actor->index == 0) {
		cout << "�ֵ����ж��ˣ�";
		player->ShowNPCState();
		cout << "1.���� 2.���� 3.��Ʒ 4.���� ";

		int input = GetUserInput(1, 4);

		if (input == 1) {

		}
		else if (input == 2) {

		}

	}



}
