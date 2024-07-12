#include "thread.h"

std::vector<std::thread> threads;

CThread::CThread(FunctionPrototype func, std::string name) : threadFunction(func), threadName(name) {
    std::cout << "[CTHREAD] Attempting to create '" << name << "'.\n";
    workerThread = std::thread(func);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    workerThread.detach();
    std::cout << "[CTHREAD] '" << name << "' running successfully.\n";
}