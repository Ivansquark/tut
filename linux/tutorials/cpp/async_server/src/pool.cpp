#include "pool.h"


std::atomic<int> Pool::currentWaitThreadsNumber = 0;
