#pragma once
#include <string>
#include <vector>
using namespace std;
class Process
{
	friend class Scheduling;
public:
	Process();
	~Process();
	int getArriveTime();
	int getRunTime();
	int getRemainTime();
private:
	string mName = "NAN";	//进程名
	int mArriveTime;					//到达时间
	int mRunTime;						//预估运行时间
	int mRemainTime;				//剩余运行时间
	int mStartTime;					//开始时间
	int mFinishTime;					//完成时间
	int mTurnaroundTime;        //周转时间
	double mTurnaroundTime_W;   //带权周转时间
	bool mIsArrive;					//是否到达系统
	bool mIsStart;						//是否开始执行
	bool mIsDone;						//是否完成
};

