#include "taskpool.h"
#include "taskpoolOne.h"




CTaskPool* CTaskPool::Create(unsigned int threads) {
	return new CTaskPoolOne(threads);
}