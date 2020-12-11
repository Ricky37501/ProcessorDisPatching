#include "Scheduling.h"
#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;

Scheduling::Scheduling():
	mProcessNum(0),
	mCurrentTime(0),
	mTimeSlice(0),
	mIsDone(false)
{
	Process temp;
	cout << "请输入待处理的进程总数：" << endl;
	if (!(cin >> mProcessNum)) {
		cout << "再见" << endl;
		exit(0);
	}
	for (int i = 0;i < mProcessNum;i++) {
		cout << "第" << i+1 << "个进程名为：";
		cin >> temp.mName;
		cout << "进程"<<temp.mName<<"的到达时间和预期运行时间分别为：";
		cin >> temp.mArriveTime >> temp.mRunTime;
		temp.mRemainTime = temp.mRunTime;
		mProcessList.push_back(temp);
		cout << endl;
	}
}

void Scheduling::excuteSJF()
{
	auto cmp = [&](Process* p1, Process* p2) {
		return p1->getRunTime() > p2->getRunTime();
	};
	priority_queue < Process*, vector<Process*>, decltype(cmp)> pendingQueue{cmp};
	while (mProcessNum>0) {
		//将到达的进程放入待执行队列
		for (Process& p : mProcessList) {
			if (mCurrentTime >= p.mArriveTime && !p.mIsArrive) {
				p.mIsArrive = true;
				pendingQueue.push(&p);
			}
		}
		if (!pendingQueue.empty()) {
			//执行当前最短进程
			Process* temp = pendingQueue.top();
			//第一次被调度
			if (!temp->mIsStart) {
				temp->mStartTime = mCurrentTime;
				temp->mIsStart = true;
			}
			cout <<"时刻"<<mCurrentTime<< "  执行线程"<<temp->mName << endl;
			pendingQueue.pop();
			temp->mRemainTime--;
			if (temp->mRemainTime == 0) {
				temp->mIsDone = true;
				temp->mFinishTime = mCurrentTime;
				temp->mTurnaroundTime = temp->mFinishTime - temp->mArriveTime;
				temp->mTurnaroundTime_W = static_cast<double>(temp->mTurnaroundTime) /static_cast<double>( temp->mRunTime);
				mProcessNum--;
			}
			else {
				pendingQueue.push(temp);
			}
		}//if
		mCurrentTime++;
	}//while
}

void Scheduling::excuteRR()
{
	while (mTimeSlice <= 0) {
		cout << "请输入时间片长度：" << endl;
		cin >> mTimeSlice;
		if (mTimeSlice <= 0) {
			cout << "时间片长度不规范" << endl;
		}
	}
	queue<Process*> pendingQueue;
	auto cmp = [&](Process* p1, Process* p2) {
		return p1->getArriveTime() < p2->getArriveTime();
	};
	//这个tempQueue是防止两个到达时间递减的进程在一个时间片内进入导致执行顺序错误
	priority_queue < Process*, vector<Process*>, decltype(cmp)> tempQueue{ cmp };

	while (mProcessNum > 0) {
		//将到达的进程放入待执行队列
		for (Process& p : mProcessList) {
			if (mCurrentTime >= p.mArriveTime && !p.mIsArrive) {
				p.mIsArrive = true;
				pendingQueue.push(&p);
			}
		}//for
		if (!pendingQueue.empty()) {
			//执行当前最短进程
			Process* temp = pendingQueue.front();
			//第一次被调度
			if (!temp->mIsStart) {
				temp->mStartTime = mCurrentTime;
				temp->mIsStart = true;
			}
			pendingQueue.pop();

			for (int i = 0;i < mTimeSlice;i++) {
				if (temp->mRemainTime > 0) {
					cout << "时刻" << mCurrentTime << "  执行线程" << temp->mName << endl;
					temp->mRemainTime--;
					mCurrentTime++;
				}
				else {
					break;
				}
			}
			cout << endl;
			//再次检查在刚刚执行完的时间片内是否有新的进程到达
			for (Process& p : mProcessList) {
				if (mCurrentTime >= p.mArriveTime && !p.mIsArrive) {
					p.mIsArrive = true;
					tempQueue.push(&p);
				}
				while (!tempQueue.empty()) {
					Process* p = tempQueue.top();
					pendingQueue.push(p);
					tempQueue.pop();
				}
			}
			if (temp->mRemainTime == 0) {
				temp->mIsDone = true;
				temp->mFinishTime = mCurrentTime;
				temp->mTurnaroundTime = temp->mFinishTime - temp->mArriveTime;
				temp->mTurnaroundTime_W = static_cast<double>(temp->mTurnaroundTime) / static_cast<double>(temp->mRunTime);
				mProcessNum--;
			}
			else {
				pendingQueue.push(temp);
			}
		}//if
	}//while
}

void Scheduling::print()
{
	cout << "-------------调度结果-------------" << endl;
	cout << "进程名       开始时间       完成时间       周转时间       带权周转时间" << endl;
	for (Process& p : mProcessList) {
		cout << p.mName <<setw(13)<< p.mStartTime << setw(16) << p.mFinishTime << setw(16) << p.mTurnaroundTime << setw(16) << p.mTurnaroundTime_W << endl;
	}
	cout << endl;
}

void Scheduling::restart()
{
	for (auto i = mProcessList.begin();i != mProcessList.end();i++) {
		i->mIsDone = false;
		i->mIsArrive = false;
		i->mIsStart = false;
		i->mRemainTime = i->mRunTime;
		mProcessNum++;
	}
	mCurrentTime = 0;
	mIsDone = false;
}

