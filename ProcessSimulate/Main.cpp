#include "Scheduling.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	bool isEnd = false;
	Scheduling s;
	while (!isEnd) {
		cout << "��ѡ������㷨��" << endl;
		cout << "1.ǿռʽ�̽������ȷ�" << endl;
		cout << "2.ʱ��Ƭ��ת��" << endl;
		int choice = -1;
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "-----��ʼִ��SJF-----" << endl;
			s.excuteSJF();
			s.print();
			cout << "1.����ѡ��  2.�˳�" << endl;
			cin >> choice;
			if (choice == 2) {
				isEnd = true;
			}
			else {
				s.restart();
			}
			break;
		case 2:
			cout << "-----��ʼִ��RR-----" << endl;
			s.excuteRR();
			s.print();
			cout << "1.����ѡ��  2.�˳�" << endl;
			cin >> choice;
			if (choice == 2) {
				isEnd = true;
			}
			else {
				s.restart();
			}
			break;
		default:
			break;
		}
	}
	system("pause");
	return 0;
}