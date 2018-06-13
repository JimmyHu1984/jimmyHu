#pragma once
#ifndef  __MESSAGE_LIST_H__
#define  __MESSAGE_LIST_H__

#include "messages.h"
#include <list>
#include <mutex>

struct MessagePackage {
	int cmd;
	void* param1;
	void* param2;
};

class CMessagesList : public CMessages {
public:
	virtual bool Post(int cmd, void* param1, void* param2);
	virtual bool Process(const Processor& cb);
private:
	std::list<MessagePackage*> messageQueue;
	std::mutex messageQueueMutex;
};

#endif //  __MESSAGE_LIST_H__