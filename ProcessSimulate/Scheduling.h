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
	int mProcessNum;				//在系统的进程数量
	int mCurrentTime;				//系统当前时间
	bool mIsDone;						//所有进程执行完毕否
	//rr法专用
	int mTimeSlice;					//时间片长度
};