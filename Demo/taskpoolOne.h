#pragma once
#ifndef __TASK_POOL_ONE_H__
#define __TASK_POOL_ONE_H__

#include "taskpool.h"
#include <vector>
#include <thread>
#include <list>
#include <mutex>
using namespace std;

class CTaskPoolOne : public CTaskPool{
public:
	CTaskPoolOne(unsigned int threads);
	~CTaskPoolOne();
	virtual bool Execute(const CallBack& cb);
	mutex			taskQueueMutex;
	condition_variable cv;
	vector<thread*> threadHandle;
	list<CallBack>	taskQueue;
private:
	int run;
	void Run();
};


#endif // !__TASK_POOL_ONE_H__