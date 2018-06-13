#pragma once
#ifndef __TASK_POOL_H__
#define __TASK_POOL_H__

#include <functional>

typedef std::function< void()> CallBack;

class CTaskPool {
protected: 
	CTaskPool() {};
public:
	virtual bool Execute(const CallBack& cb) = 0;
	static CTaskPool* Create(unsigned int threads);
};


#endif // !__TASK_POOL_H__
