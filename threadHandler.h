#include "queues.h"


#define SEND_MESSAGE_TO_ONE     0
#define SEND_MESSAGE_TO_OTHER   1
#define SEND_MESSAGE_TO_BOTH    2

void clockThread(int queueID) {

    // Generate random clockspeed from 1-6
    int clockSpeed = (rand() % 6) + 1;
    // There are 1,000,000 microseconds in 1 seconds, so we divide that by clockspeed to
    //      find the number of microseconds (floored) that the machine should sleep for
    const int microsecondSleep = 1000000 / clockSpeed;

    std::string filename = "machine"+std::to_string(queueID)+"clock_speed"+std::to_string(clockSpeed)+"log.csv";

    // initialize CSV file
    std::ofstream filewriter;
    filewriter.open(filename);
    filewriter << "was_die_roll,sent_message,message_received,system_time,logical_clock_time,length_of_queue\n";

    int clockTime = 0;
    
    while(g_programRunning) {
        std::this_thread::sleep_for(std::chrono::microseconds(microsecondSleep));

        std::pair<int, int> clockVal_queueLength = messageQueues[queueID]->readMessage();
        auto globalTime = std::chrono::system_clock::now();
        std::time_t globalTime_t = std::chrono::system_clock::to_time_t(globalTime);
        std::string systemTimeString = std::ctime(&globalTime_t);
        systemTimeString.pop_back();
        // if queue was not empty
        if (clockVal_queueLength.first != -1) {
            filewriter << std::to_string(false) << "," << std::to_string(false) << "," << std::to_string(true) 
                        << "," << std::to_string(globalTime_t) << "," << std::to_string(clockTime) << "," << clockVal_queueLength.second << std::endl;
            clockTime = std::max(clockVal_queueLength.first, clockTime) + 1;
            continue;
        }


        // TODO: we only make it here if there was no message in queue, send message and update clock
        int dieRoll = rand() % 10;
        filewriter << std::to_string(true) << ",";
        switch (dieRoll)
        {
        case SEND_MESSAGE_TO_ONE:
            {
                int sendID = (queueID + 1) % 3;
                messageQueues[sendID]->addMessage(clockTime);
                filewriter << std::to_string(true) << "," << std::to_string(false) << "," << std::to_string(globalTime_t)
                            << "," << std::to_string(clockTime) << "," << std::to_string(clockVal_queueLength.second) << std::endl;
                clockTime++;
            }
            break;
        
        case SEND_MESSAGE_TO_OTHER:
            {
                int sendID = (queueID + 2) % 3;
                messageQueues[sendID]->addMessage(clockTime);
                filewriter << std::to_string(true) << "," << std::to_string(false) << "," << std::to_string(globalTime_t)
                            << "," << std::to_string(clockTime) << "," << std::to_string(clockVal_queueLength.second) << std::endl;
                clockTime++;
            }
            break;
        
        case SEND_MESSAGE_TO_BOTH:
            {
                int firstSendID = (queueID + 1) % 3;
                int secondSendID = (queueID + 2) % 3;
                messageQueues[firstSendID]->addMessage(clockTime);
                messageQueues[secondSendID]->addMessage(clockTime);
                filewriter << std::to_string(true) << "," << std::to_string(false) << "," << std::to_string(globalTime_t)
                            << "," << std::to_string(clockTime) << "," << std::to_string(clockVal_queueLength.second) << std::endl;
                clockTime++;
            }
            break;
        
        default:
            filewriter << std::to_string(false) << "," << std::to_string(false) << "," << std::to_string(globalTime_t)
                        << "," << std::to_string(clockTime) << "," << std::to_string(clockVal_queueLength.second) << std::endl;
            clockTime++;
            break;
        }
    }

    filewriter.close();
    std::string threadExitReturnVal = "Thread exited";
    pthread_exit(&threadExitReturnVal);
}