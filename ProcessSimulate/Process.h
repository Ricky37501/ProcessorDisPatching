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
	string mName = "NAN";	//������
	int mArriveTime;					//����ʱ��
	int mRunTime;						//Ԥ������ʱ��
	int mRemainTime;				//ʣ������ʱ��
	int mStartTime;					//��ʼʱ��
	int mFinishTime;					//���ʱ��
	int mTurnaroundTime;        //��תʱ��
	double mTurnaroundTime_W;   //��Ȩ��תʱ��
	bool mIsArrive;					//�Ƿ񵽴�ϵͳ
	bool mIsStart;						//�Ƿ�ʼִ��
	bool mIsDone;						//�Ƿ����
};

