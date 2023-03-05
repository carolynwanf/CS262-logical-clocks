#include "dataStructures.h"

void listenForConnections(int server_fd, int fileDescriptorsIndex) {

    // Thread listens for connections
    if (listen(server_fd, g_backlogSize) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Establishes two connections and dies
    int connections = 0;

    while (connections < 2) {
        int new_socket;

        if ((new_socket
            = accept(server_fd, (sockaddr*)&address,
                    (socklen_t*)&addrlen))
            < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        fileDescriptorsVector[fileDescriptorsIndex].addReadFd(new_socket);

        connections ++;
    }


}

void readFromSockets(FileDescriptors fileDescriptors, int queueID) {
    int valread;
    int receivedMsg;
    
    while (g_programRunning) {
        valread = recv(fileDescriptors.read1Fd, &receivedMsg, sizeof(receivedMsg), MSG_DONTWAIT);
        if (valread != -1) {
            messageQueues[queueID]->addMessage(receivedMsg);
        }
        valread = recv(fileDescriptors.read1Fd, &receivedMsg, sizeof(receivedMsg), MSG_DONTWAIT);
        if (valread != -1) {
            messageQueues[queueID]->addMessage(receivedMsg);
        }
        
    }

    std::string threadExitReturnVal = "Thread exited";
    pthread_exit(&threadExitReturnVal);
}