#include "GameData.h"
Character::Character() {
	
}
Hero::Hero() {
	id = 0;
}
void Place::OnEnterPlace() {
	//待对接，读地图对话脚本(enterScript)
}
InteractSystem::InteractSystem() {
	handle = GetStdHandle(STD_OUTPUT_HANDLE); 
}
//实现不带回显的输入
int InteractSystem::GetUserInput() {
	char command[1];
	command[0] = _getch();
	return atoi(command);
}
//用户输入数字选项，maxNum(最大为10)为选项数，返回选项编号
int InteractSystem::GetUserInput(int maxNum) {
	int n = -1;
	while (n <= 0 || n > maxNum) {
		n = GetUserInput();
		if (n == 0)n = 10;
	}
	return n;
}
void InteractSystem::PrintLog(string message) {
	SetConsoleTextAttribute(handle, 15 | 0);
	cout << message << endl << endl;
}
void InteractSystem::PrintMap() {
	
}