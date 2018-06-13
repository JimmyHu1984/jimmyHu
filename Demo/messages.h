#pragma once
#ifndef  __MESSAGE_H__
#define  __MESSAGE_H__

#include <functional>
typedef std::function< void(int, void*, void*)> Processor;

#define MESSAGE_LIST	0
#define MESSAGE_MAP		1

class CMessages {
protected:
	CMessages() {}
public:
	virtual bool Post(int cmd, void* param1, void* param2) = 0;
	virtual bool Process(const Processor& cb) = 0;

	static CMessages* Create(int MesssageType = 0);
};


#endif //  __MESSAGE_H__
