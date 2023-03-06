#include "threadHandler.h"

/*
    Each thread has an associated server_fd and two fds associated with its connections with other servers 
*/

int main(void) {
    // Get host IP
    char* ip_addr;
    strcpy(ip_addr, getIPAddress());

    // Setting up server sockets
    std::vector<std::thread> listeningThreads;
    int ports[3] = {8080, 8081, 8082};

    int opt = 1;
    for (int i = 0; i < 3; i++) {
        // Creating socket file descriptor
        int server_fd = bindSocketToPort(opt, ports[i]);

        // If successfully connected, add to file descriptors vector
        FileDescriptors newFileDescriptors{};
        newFileDescriptors.addServerFd(server_fd);
        fileDescriptorsVector.push_back(newFileDescriptors);

        // Start thread to listen for connections
        std::thread t(listenForConnections, server_fd, i);

        listeningThreads.push_back(std::move(t));
    }

    // Setting up client connections for each process
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        for (int j = 0; j< NUMBER_OF_PROCESSES; j++) {
            if (i != j) {

                int server_socket = getWriteFd(ports[j], ip_addr);

                fileDescriptorsVector[i].addWriteFd(server_socket);

            }
        }
    }

    // Joining threads
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        listeningThreads[i].join();
    }

    // Setting up process running threads, each thread takes its fds and a process ID 
    std::vector<std::thread> threads;

    // Timing runs
    auto startTime = std::chrono::system_clock::now();
    auto endTime = std::chrono::system_clock::now();

    srand(time(0));
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        std::thread newThread(clockThread, i, fileDescriptorsVector[i]);
        threads.push_back(std::move(newThread));
    }

    std::this_thread::sleep_for(std::chrono::seconds(60));
    g_programRunning = false;

    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        threads[i].join();
    }

    return 0;
}