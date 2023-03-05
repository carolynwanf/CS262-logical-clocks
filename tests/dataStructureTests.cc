#include <gtest/gtest.h>
#include "../dataStructures.h"

TEST(QueueTest, OneThread) {
    MessageQueue testMessageQueue;

    int QUEUE_LENGTH = 10;

    // If nothing in queue
    std::pair<int,int> messagePair1 = testMessageQueue.readMessage();

    EXPECT_EQ(messagePair1.first, -1);
    EXPECT_EQ(messagePair1.second, 0);

    // If QUEUE_LENGTH things in queue
    for (int i = 0; i < QUEUE_LENGTH; i++) {
        testMessageQueue.addMessage(i);
    }

    for (int i = 0; i < QUEUE_LENGTH; i++) {
        std::pair<int,int> messagePair = testMessageQueue.readMessage();

        EXPECT_EQ(messagePair.first, i);
        EXPECT_EQ(messagePair.second, QUEUE_LENGTH - (i));
    }

    // Nothing in queue again
    std::pair<int,int> messagePair2 = testMessageQueue.readMessage();

    EXPECT_EQ(messagePair2.first, -1);
    EXPECT_EQ(messagePair2.second, 0);

}
void addMessageWrapper(int num, MessageQueue* messageQueuePointer, int msg) {
    for (int i = 0; i < num; i++) {
        messageQueuePointer->addMessage(msg);
    } 
}

TEST(QueueTest, MultiThreadedAdd) {
    MessageQueue testMessageQueue;

    // Testing mutual exclusion for addMessage
    std::thread t1(addMessageWrapper, 3, &testMessageQueue, 1);
    std::thread t2(addMessageWrapper, 2, &testMessageQueue, 2);
    std::thread t3(addMessageWrapper, 4, &testMessageQueue, 3);

    t1.join();
    t2.join();
    t3.join();

    // Count message values
    std::map<int, int> messageCount;
    for (int i = 0; i < 3+2+4; i++) {
        std::pair<int, int> messagePair = testMessageQueue.readMessage();
        messageCount[messagePair.first]++;
    }

    std::pair<int, int> emptyMessagePair = testMessageQueue.readMessage();
    
    // Queue should be empty now
    EXPECT_EQ(emptyMessagePair.first, -1);
    EXPECT_EQ(emptyMessagePair.second, 0);

    // Should be 3 1s, 2 2s, and 4 3s
    EXPECT_EQ(messageCount[1], 3);
    EXPECT_EQ(messageCount[2], 2);
    EXPECT_EQ(messageCount[3], 4);

}

void readMessageWrapper(MessageQueue* messageQueuePointer, std::set<int>* messageValuesPointer, std::mutex* messageValuesMutexPointer) {
    std::pair<int, int> messagePair = messageQueuePointer->readMessage();
    messageValuesMutexPointer->lock();
    ASSERT_EQ(messageValuesPointer->find(messagePair.first), messageValuesPointer->end());
    messageValuesPointer->insert(messagePair.first);
    messageValuesMutexPointer->unlock();
}

TEST(QueueTest, MultiThreadedRead) {
    MessageQueue testMessageQueue;

    // Testing mutual exclusion for readMessage()
    for (int i = 0; i < 10; i++) {
        testMessageQueue.addMessage(i);
    }

    std::set<int> messageValues;
    std::mutex messageValuesMutex;

    // Adding messages
    std::thread threads[10];
    for (int i = 0; i < 10; i++) {
        threads[i] = std::move(std::thread(readMessageWrapper, &testMessageQueue, &messageValues, &messageValuesMutex));
    }

    for (int i = 0; i < sizeof(threads)/sizeof(threads[0]); i++) {
        threads[i].join();
    }

    std::pair<int, int> emptyMessagePair = testMessageQueue.readMessage();
    
    // Queue should be empty now
    EXPECT_EQ(emptyMessagePair.first, -1);
    EXPECT_EQ(emptyMessagePair.second, 0);

    // Check that each one exists once
    for (int i = 0; i < 10; i++) {
        EXPECT_NE(messageValues.find(i), messageValues.end());
    }

}