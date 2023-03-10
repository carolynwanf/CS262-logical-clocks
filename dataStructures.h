#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>

#include <netdb.h>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>

// Globals
#define NUMBER_OF_PROCESSES  3

int g_backlogSize = 20;
bool g_programRunning = true;

sockaddr_in address;
int addrlen = sizeof(address);

// File descriptors for each thread
class FileDescriptors {

    public:
        int serverFd;
        int write1Fd;
        int write2Fd;
        int read1Fd;
        int read2Fd; 

        FileDescriptors() {
            serverFd = -1;
            write1Fd = -1;
            write2Fd = -1;
            read1Fd = -1;
            read2Fd = -1;
        };

        // Adding a file descriptor for the server side of the socket
        void addReadFd(int fd) {
            std::cout << "Adding read fd " << fd << std::endl;

            if (read1Fd == -1) {
                read1Fd = fd;
            } else {
                read2Fd = fd;
            }
        }

        // Adding a file descriptor for the client side of the socket
        void addWriteFd(int fd) {
            std::cout << "Adding write fd " << fd << std::endl;
            if (write1Fd == -1) {
                write1Fd = fd;
            } else {
                write2Fd = fd;
            }
        }

        void addServerFd(int fd) {
            serverFd = fd;
        }

        // Print values for debugging
        void printValues() {
            std::cout << "Server FD: " << serverFd << std::endl;
            std::cout << "Write 1 FD: " << write1Fd << std::endl;
            std::cout << "Write 2 FD: " << write2Fd << std::endl;
            std::cout << "Read 1 FD: " << read1Fd << std::endl;
            std::cout << "Read 2 FD: " << read2Fd << std::endl;
            std::cout << std::endl;

        }
};

// Queue of messages for each thread
class MessageQueue {
    std::queue<int> messages;   // queue of send times
    std::mutex messageMutex;    // mutex!

public:
    // Add message to messages
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
            returnVal.second = messages.size();
            messages.pop();
        }

        messageMutex.unlock();
        return returnVal;

    }
};

MessageQueue messageQueue0;
MessageQueue messageQueue1;
MessageQueue messageQueue2;

MessageQueue* messageQueues[NUMBER_OF_PROCESSES] =  {&messageQueue0, &messageQueue1, &messageQueue2};

std::vector<FileDescriptors> fileDescriptorsVector;