#include "messagesList.h"
#include <iostream>

using namespace std;

bool CMessagesList::Post(int cmd, void* param1, void* param2) {
	unique_lock<mutex> lock(this->messageQueueMutex);
	MessagePackage* pTmpMessage = new MessagePackage();	
	pTmpMessage->cmd = cmd;
	pTmpMessage->param1 = param1;
	pTmpMessage->param2 = param2;
	this->messageQueue.push_back(pTmpMessage);

	return true;
}
bool CMessagesList::Process(const Processor& cb) {
	if (this->messageQueue.empty()) {
		return false;
	}
	unique_lock<mutex> lock(this->messageQueueMutex);
	MessagePackage* pMessage = this->messageQueue.front();
	cb(pMessage->cmd, pMessage->param1, pMessage->param2);
	delete(pMessage);
	this->messageQueue.pop_front();

	return true;
}