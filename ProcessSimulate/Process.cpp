#include "Process.h"

Process::Process():
mName("NAN"),
mArriveTime(-1),
mRunTime(-1),
mRemainTime(-1),
mStartTime(-1),
mFinishTime(-1),
mTurnaroundTime(-1),
mTurnaroundTime_W(-1),
mIsArrive(false),
mIsStart(false),
mIsDone(false)
{
}

Process::~Process()
{
}

int Process::getArriveTime()
{
	return mArriveTime;
}

int Process::getRunTime()
{
	return mRunTime;
}

int Process::getRemainTime()
{
	return mRemainTime;
}
