#ifndef THREAD_H
#define THREAD_H

#include <vector>
#include <thread>
#include <iostream>

#include "../constants.h"

#include "../account/account.h"
#include "../block/block.h"
#include "../utils/utils.h"
#include "../miner/miner.h"
#include "../transaction/transaction.h"

extern std::vector<std::thread> threads;

typedef void(*FunctionPrototype)(void);

void mineThreadFn(void);

class CThread {
public:
    std::thread workerThread;
    FunctionPrototype threadFunction;
    std::string threadName;
    static unsigned short threadId;

    CThread(FunctionPrototype func, std::string name);
};

#endif