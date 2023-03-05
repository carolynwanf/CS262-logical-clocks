#include "threadHandler.h"

#include <vector>

int main(void) {
    std::vector<std::thread> threads;
    auto startTime = std::chrono::system_clock::now();
    auto endTime = std::chrono::system_clock::now();

    srand(time(0));
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        std::thread newThread(clockThread, i);
        threads.push_back(std::move(newThread));
    }

    std::this_thread::sleep_for(std::chrono::seconds(60));
    g_programRunning = false;

    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        threads[i].join();
    }

    return 0;
}