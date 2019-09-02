#include "Game.h";

//Fight的构造函数
Fight::Fight(NPC* player, NPC* enemy)
{
	this->player = player;
	this->enemy = enemy;
}

//Fight的析构函数
Fight::~Fight()
{
}

//判定谁先先手
NPC* Fight::DecideWhoAct()
{
	if (player->speed >= enemy->speed) {
		return player;
	}
	if (player->speed < enemy->speed) {
		return enemy;
	}
}

//使用技能
void Fight::UseSkill(NPC* role)
{

}

//战斗过程
void Fight::Fighting()
{
	cout << "你与" << enemy->name << "斗在了一起";
	NPC* actor = DecideWhoAct();
	if (actor->index == 0) {
		cout << "轮到你行动了！";
		player->ShowNPCState();
		cout << "1.攻击 2.技能 3.物品 4.逃走 ";

		int input = GetUserInput(1, 4);

		if (input == 1) {

		}
		else if (input == 2) {

		}

	}



}
