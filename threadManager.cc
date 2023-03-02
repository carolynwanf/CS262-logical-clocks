#include <thread>
#include <vector>
#include "threadHandler.h"

int main(void) {
    std::vector<std::thread> threads;
    auto startTime = std::chrono::system_clock::now();
    auto endTime = std::chrono::system_clock::now();

    for (int i = 0; i < 3; i++) {
        std::thread newThread(clockThread, i);
        threads.push_back(newThread);
    }

    for (int i = 0; i < 3; i++) {
        threads[0].join();
    }

    return;

}