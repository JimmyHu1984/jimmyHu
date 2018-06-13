#include "taskpoolOne.h"

CTaskPoolOne::CTaskPoolOne(unsigned int threads) {
	this->run = true;
	for (unsigned int i = 0; i < threads; ++i) {
		this->threadHandle.push_back(new thread(&CTaskPoolOne::Run, this));
	}	
}

CTaskPoolOne::~CTaskPoolOne() {
	this->run = false;
	for (thread* pThread : this->threadHandle) {
		if (pThread->joinable()) {
			pThread->join();
		}
		delete(pThread);
	}
}

bool CTaskPoolOne::Execute(const CallBack& cb) {
	unique_lock<mutex> lock(this->taskQueueMutex);
	taskQueue.push_back(cb);
	this->cv.notify_one();
	return true;
}

void CTaskPoolOne::Run() {
	while (this->run) {
		CallBack cb;
		{
			unique_lock<mutex> lock(this->taskQueueMutex);
			if (taskQueue.empty()) {
				this->cv.wait(lock);
				continue;
			}
			cb = taskQueue.front();
			taskQueue.pop_front();
		}
		cb();
	}
}

