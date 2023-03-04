#include "machineHandler.h"

int main(void) {
    std::vector<std::thread> threads;
    auto startTime = std::chrono::system_clock::now();
    auto endTime = std::chrono::system_clock::now();

    srand(time(0));

    // initialize LogicalClock instances
    std::vector<LogicalClock> machineInstances;
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        LogicalClock clock(i);
        machineInstances.push_back(clock);
    }

    // create connections between machines
    for (int idx1 = 0; idx1 < NUMBER_OF_PROCESSES; idx1++) {
        for (int idx2 = 0; idx2 < NUMBER_OF_PROCESSES; idx2++) {
            if (idx1 != idx2) {
                std::string server_addr = machineInstances[idx2].getServerAddr();
                machineInstances[idx1].addClientStub(server_addr);
            }
        }
    }

    for (LogicalClock& clock : machineInstances) {
        std::thread newThread(handleMachine, std::ref(clock));
        threads.push_back(std::move(newThread));
    }
    std::this_thread::sleep_for(std::chrono::seconds(60));
    g_programRunning = false;

    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        threads[i].join();
    }

    return 0;
}