#include "GameData.h"
Character::Character() {
	
}
Hero::Hero() {
	id = 0;
}
void Place::OnEnterPlace() {
	//���Խӣ�����ͼ�Ի��ű�(enterScript)
}
InteractSystem::InteractSystem() {
	handle = GetStdHandle(STD_OUTPUT_HANDLE); 
}
//ʵ�ֲ������Ե�����
int InteractSystem::GetUserInput() {
	char command[1];
	command[0] = _getch();
	return atoi(command);
}
//�û���������ѡ�maxNum(���Ϊ10)Ϊѡ����������ѡ����
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