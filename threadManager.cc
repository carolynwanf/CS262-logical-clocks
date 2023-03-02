#include "threadHandler.h"

#include <vector>

int main(void) {
    std::vector<std::thread> threads;
    auto startTime = std::chrono::system_clock::now();
    auto endTime = std::chrono::system_clock::now();

    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        std::thread newThread(clockThread, i);
        threads.push_back(std::move(newThread));
    }

    // while (true) {
    //     endTime = std::chrono::system_clock::now();
    //     std::chrono::duration<double> elapsedSeconds = endTime-startTime;

    //     // Set global telling threads to run to false once a minute has elapsed
    //     std::cout << "We're here in main function" << std::endl;
    //     if (elapsedSeconds.count() < (double) 60) {
    //         g_programRunning = false;
    //         break;
    //     }
    //     std::cout << "We're here in main function" << std::endl;
    // }
    std::this_thread::sleep_for(std::chrono::seconds(60));
    g_programRunning = false;

    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        threads[i].join();
    }

    return 0;
}