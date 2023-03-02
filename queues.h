#include<iostream>
#include <queue>
#include <mutex>

class MessageQueue {
    std::queue<int> messages;
    std::mutex messageMutex;

    void addMessage() {
        
    }

    // Returns message
    std::pair<int,int> readMessage() {
        // Return <-1, 0 if nothing in the queue>

    }
};

MessageQueue messageQueue0;
MessageQueue messageQueue1;
MessageQueue messageQueue2;

MessageQueue* messageQueues[3] =  {&messageQueue0, &messageQueue1, &messageQueue2};


