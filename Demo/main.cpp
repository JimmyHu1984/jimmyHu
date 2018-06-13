#include <stdlib.h>
#include <stdio.h>
#include <chrono>

#include <mutex>
#include <condition_variable>

#include "messages.h"
#include "taskpool.h"

std::mutex					m;
std::condition_variable		cv;
bool						ready = false;
double						value = 0;

static void OnProcess(int cmd, void* param1, void* param2, int& total) {
	for (int i = 0; i < 10; ++i) {
		value += (rand() % 100 / 0.954763 + 1) / 1.03 * 999;
	}
	--total;
}

static void OnTask(CMessages* message, int count) {
	std::unique_lock<std::mutex> lk(m);
	cv.wait(lk, []{ return ready; });

	for (int i = 0; i < count; ++i) {
		message->Post(i, NULL, NULL);
	}
}


int main(int argc, const char** argv) {
	const int runTimes = 64;
	const int msgCount = 100000;
	CMessages* messages = CMessages::Create(MESSAGE_LIST);
	CTaskPool* taskPool = CTaskPool::Create(32);
	
	for (int i = 0; i < runTimes; ++i) {
		taskPool->Execute(std::bind(OnTask, messages, msgCount));
	}

	ready = true;
	cv.notify_all();
	auto start = std::chrono::system_clock::now();
	int total = runTimes * msgCount;
	while (total > 0) {
		messages->Process(std::bind(OnProcess,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3,
			std::ref(total)));
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = std::chrono::system_clock::now() - start;
	printf("%f \n", diff);
	system("pause");
	delete messages;
	delete taskPool;
	return 0;
}