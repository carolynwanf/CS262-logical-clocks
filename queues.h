#include<iostream>
#include <queue>
#include <mutex>

bool g_programRunning = true;
#define NUMBER_OF_PROCESSES  3

class MessageQueue {
    std::queue<int> messages;   // queue of send times
    std::mutex messageMutex;    // mutex!

public:
    // Add messages to data 
    void addMessage(int logicalClockTime) {
        messageMutex.lock();

        messages.push(logicalClockTime);

        messageMutex.unlock();
    }

    // Returns tuple of the message and the size of the queue
    std::pair<int,int> readMessage() {
        messageMutex.lock();

        std::pair<int,int> returnVal;

        if (messages.size() == 0) {
            returnVal.first = -1;
            returnVal.second = 0;
        } else {
            returnVal.first = messages.front();
            messages.pop();
            returnVal.second = messages.size();
        }

        messageMutex.unlock();
        return returnVal;

    }
};

MessageQueue messageQueue0;
MessageQueue messageQueue1;
MessageQueue messageQueue2;

MessageQueue* messageQueues[NUMBER_OF_PROCESSES] =  {&messageQueue0, &messageQueue1, &messageQueue2};


