#include "Scheduling.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	bool isEnd = false;
	Scheduling s;
	while (!isEnd) {
		cout << "请选择调度算法：" << endl;
		cout << "1.强占式短进程优先法" << endl;
		cout << "2.时间片轮转法" << endl;
		int choice = -1;
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "-----开始执行SJF-----" << endl;
			s.excuteSJF();
			s.print();
			cout << "1.重新选择  2.退出" << endl;
			cin >> choice;
			if (choice == 2) {
				isEnd = true;
			}
			else {
				s.restart();
			}
			break;
		case 2:
			cout << "-----开始执行RR-----" << endl;
			s.excuteRR();
			s.print();
			cout << "1.重新选择  2.退出" << endl;
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