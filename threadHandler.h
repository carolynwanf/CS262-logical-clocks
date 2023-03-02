#include <cstdlib>
#include <thread>
#include <chrono>

#define SEND_MESSAGE_TO_ONE     0
#define SEND_MESSAGE_TO_OTHER   1
#define SEND_MESSAGE_TO_BOTH    2

void clockThread(int queueID) {
    // Generate random clockspeed from 1-6
    int clockSpeed = (rand() % 6) + 1;
    // There are 1,000,000 microseconds in 1 seconds, so we divide that by clockspeed to
    //      find the number of microseconds (floored) that the machine should sleep for
    int microsecondSleep = 1000000 / clockSpeed;

    int clockTime = 0;
    
    while(true) {
        std::this_thread::sleep_for (std::chrono::microseconds(microsecondSleep));

        // TODO: check message queue, if message was read then continue to next iteration of loop
        clockTime++;


        // TODO: we only make it here if there was no message in queue, send message and update clock
        int dieRoll = rand() % 10;
        switch (dieRoll)
        {
        case SEND_MESSAGE_TO_ONE:
            {
                int sendID = (queueID + 1) % 3;
            }
            break;
        
        case SEND_MESSAGE_TO_OTHER:
            {
                int sendID = (queueID + 2) % 3;
            }
            break;
        
        case SEND_MESSAGE_TO_BOTH:
            {
                int firstSendID = (queueID + 1) % 3;
                int secondSendID = (queueID + 2) % 3;
            }
            break;
        
        default:
            break;
        }

    }
}