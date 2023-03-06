  #include <gtest/gtest.h>
#include "../handleSockets.h"


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

TEST(ConnectionTest, EstablishingConnection) {
    int port0 = 8080;
    int port1 = 8081;
    int port2 = 8082;

    FileDescriptors fileDescriptors0;
    FileDescriptors fileDescriptors1;
    FileDescriptors fileDescriptors2;

    fileDescriptorsVector.push_back(fileDescriptors0);
    fileDescriptorsVector.push_back(fileDescriptors1);
    fileDescriptorsVector.push_back(fileDescriptors2);

    // Check if IP address is valid
    char* ip_addr = getIPAddress();

    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ip_addr, &(sa.sin_addr));

    EXPECT_NE(result, -1);

    // Check if server fds are valid
    int server_fd0 = bindSocketToPort(1, port0);
    int server_fd1 = bindSocketToPort(1, port1);
    int server_fd2 = bindSocketToPort(1, port2);

    EXPECT_GT(server_fd0, -1);
    EXPECT_GT(server_fd1, -1);
    EXPECT_GT(server_fd2, -1);

    // Check that client fds are valid
    std::thread t1(listenForConnections, server_fd0, 0);
    std::thread t2(listenForConnections, server_fd1, 1);
    std::thread t3(listenForConnections, server_fd2, 2);

    // Add two connections per port
    // Check that the write and read FDs are all valid
    // Connections for machine 0
    int write_fd1_m0 = getWriteFd(port1, ip_addr);
    int write_fd2_m0 = getWriteFd(port2, ip_addr);
    fileDescriptorsVector[0].addWriteFd(write_fd1_m0);
    fileDescriptorsVector[0].addWriteFd(write_fd2_m0);

    // Connections for machine 1
    int write_fd1_m1 = getWriteFd(port0, ip_addr);
    int write_fd2_m1 = getWriteFd(port2, ip_addr);
    fileDescriptorsVector[1].addWriteFd(write_fd1_m1);
    fileDescriptorsVector[1].addWriteFd(write_fd2_m1);

    // Connections for machine 2
    int write_fd1_m2 = getWriteFd(port0, ip_addr);
    int write_fd2_m2 = getWriteFd(port1, ip_addr);
    fileDescriptorsVector[2].addWriteFd(write_fd1_m2);
    fileDescriptorsVector[2].addWriteFd(write_fd2_m2);

    t1.join();
    t2.join();
    t3.join();

    // For machine 0
    EXPECT_GT(fileDescriptorsVector[0].write1Fd, -1);
    EXPECT_GT(fileDescriptorsVector[0].write2Fd, -1);
    
    EXPECT_GT(fileDescriptorsVector[0].read1Fd, -1);
    EXPECT_GT(fileDescriptorsVector[0].read2Fd, -1);

    // For machine 1
    EXPECT_GT(fileDescriptorsVector[1].write1Fd, -1);
    EXPECT_GT(fileDescriptorsVector[1].write2Fd, -1);

    EXPECT_GT(fileDescriptorsVector[1].read1Fd, -1);
    EXPECT_GT(fileDescriptorsVector[1].read2Fd, -1);

    // For machine 2
    EXPECT_GT(fileDescriptorsVector[2].write1Fd, -1);
    EXPECT_GT(fileDescriptorsVector[2].write2Fd, -1);

    EXPECT_GT(fileDescriptorsVector[2].read1Fd, -1);
    EXPECT_GT(fileDescriptorsVector[2].read2Fd, -1);

    // Try to send a messages to machine 0 (other machines should be the same)
    // Tests that read fds were added correctly, messages can be sent from two machines to the other
    int message = 262;
    send(fileDescriptorsVector[1].write1Fd, &message, sizeof(message), 0);
    send(fileDescriptorsVector[2].write1Fd, &message, sizeof(message), 0);

    int receivedMsg;
    std::vector<int> receivedMsgs;

    // Don't wait mechanism for listening for messages works (used in readFromSockets)
    while(receivedMsgs.size() < 2) {
        int valread = recv(fileDescriptorsVector[0].read1Fd, &receivedMsg, sizeof(receivedMsg), MSG_WAITALL);
        if (valread != -1) {
            receivedMsgs.push_back(receivedMsg);
        }
        valread = recv(fileDescriptorsVector[0].read2Fd, &receivedMsg, sizeof(receivedMsg), MSG_WAITALL);
        if (valread != -1) {
            receivedMsgs.push_back(receivedMsg);
        }
    }

    for (int i = 0; i < receivedMsgs.size(); i++) {
        EXPECT_EQ(receivedMsgs[i], message);
    }

}