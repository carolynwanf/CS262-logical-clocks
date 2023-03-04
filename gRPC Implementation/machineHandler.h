#include "logicalClockClass.h"
#include "globals.h"

void handleMachine(LogicalClock& clock) {
    while(g_programRunning) {
        std::this_thread::sleep_for(std::chrono::microseconds(clock.getSleepTime()));
        if (clock.getQueueLength() < 1) {
            clock.dieRoll();
        } else {
            clock.readMessage();
        }
    }

    std::string threadExitReturnVal = "Thread exited";
    pthread_exit(&threadExitReturnVal);
}