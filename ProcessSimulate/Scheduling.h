#pragma once
#include <vector>
#include "Process.h"
using namespace std;

class Scheduling
{
public:
	Scheduling();
	void excuteSJF();
	void excuteRR();
	void print();
	void restart();
private:
	vector<Process> mProcessList;
	int mProcessNum;				//��ϵͳ�Ľ�������
	int mCurrentTime;				//ϵͳ��ǰʱ��
	bool mIsDone;						//���н���ִ����Ϸ�
	//rr��ר��
	int mTimeSlice;					//ʱ��Ƭ����
};