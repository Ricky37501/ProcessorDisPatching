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
	cout << "�����������Ľ���������" << endl;
	if (!(cin >> mProcessNum)) {
		cout << "�ټ�" << endl;
		exit(0);
	}
	for (int i = 0;i < mProcessNum;i++) {
		cout << "��" << i+1 << "��������Ϊ��";
		cin >> temp.mName;
		cout << "����"<<temp.mName<<"�ĵ���ʱ���Ԥ������ʱ��ֱ�Ϊ��";
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
		//������Ľ��̷����ִ�ж���
		for (Process& p : mProcessList) {
			if (mCurrentTime >= p.mArriveTime && !p.mIsArrive) {
				p.mIsArrive = true;
				pendingQueue.push(&p);
			}
		}
		if (!pendingQueue.empty()) {
			//ִ�е�ǰ��̽���
			Process* temp = pendingQueue.top();
			//��һ�α�����
			if (!temp->mIsStart) {
				temp->mStartTime = mCurrentTime;
				temp->mIsStart = true;
			}
			cout <<"ʱ��"<<mCurrentTime<< "  ִ���߳�"<<temp->mName << endl;
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
		cout << "������ʱ��Ƭ���ȣ�" << endl;
		cin >> mTimeSlice;
		if (mTimeSlice <= 0) {
			cout << "ʱ��Ƭ���Ȳ��淶" << endl;
		}
	}
	queue<Process*> pendingQueue;
	auto cmp = [&](Process* p1, Process* p2) {
		return p1->getArriveTime() < p2->getArriveTime();
	};
	//���tempQueue�Ƿ�ֹ��������ʱ��ݼ��Ľ�����һ��ʱ��Ƭ�ڽ��뵼��ִ��˳�����
	priority_queue < Process*, vector<Process*>, decltype(cmp)> tempQueue{ cmp };

	while (mProcessNum > 0) {
		//������Ľ��̷����ִ�ж���
		for (Process& p : mProcessList) {
			if (mCurrentTime >= p.mArriveTime && !p.mIsArrive) {
				p.mIsArrive = true;
				pendingQueue.push(&p);
			}
		}//for
		if (!pendingQueue.empty()) {
			//ִ�е�ǰ��̽���
			Process* temp = pendingQueue.front();
			//��һ�α�����
			if (!temp->mIsStart) {
				temp->mStartTime = mCurrentTime;
				temp->mIsStart = true;
			}
			pendingQueue.pop();

			for (int i = 0;i < mTimeSlice;i++) {
				if (temp->mRemainTime > 0) {
					cout << "ʱ��" << mCurrentTime << "  ִ���߳�" << temp->mName << endl;
					temp->mRemainTime--;
					mCurrentTime++;
				}
				else {
					break;
				}
			}
			cout << endl;
			//�ٴμ���ڸո�ִ�����ʱ��Ƭ���Ƿ����µĽ��̵���
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
	cout << "-------------���Ƚ��-------------" << endl;
	cout << "������       ��ʼʱ��       ���ʱ��       ��תʱ��       ��Ȩ��תʱ��" << endl;
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

