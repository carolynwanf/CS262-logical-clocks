#include "threadHandler.h"
#include <thread>
#include <vector>

int main(void) {
    std::vector<std::thread> threads;
    auto startTime = std::chrono::system_clock::now();
    auto endTime = std::chrono::system_clock::now();

    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        std::thread newThread(clockThread, i);
        threads.push_back(newThread);
    }

    while (true) {
        endTime = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsedSeconds = endTime-startTime;

        // Set global telling threads to run to false once a minute has elapsed
        if (elapsedSeconds.count() < (double) 60) {
            g_programRunning = false;
            break;
        }

    }

    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        threads[0].join();
    }

    return;

}