#include "dataStructures.h"

// Accept connections, get fds that the process associated with server_fd should read from
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

// Read from two socket ends while the program is running
void readFromSockets(FileDescriptors fileDescriptors, int queueID) {
    int valread;
    int receivedMsg;
    
    while (g_programRunning) {
        valread = recv(fileDescriptors.read1Fd, &receivedMsg, sizeof(receivedMsg), MSG_DONTWAIT);
        if (valread != -1) {
            std::cout << "adding message to queue: " << std::to_string(queueID) << std::endl;
            messageQueues[queueID]->addMessage(receivedMsg);
        }
        valread = recv(fileDescriptors.read2Fd, &receivedMsg, sizeof(receivedMsg), MSG_DONTWAIT);
        if (valread != -1) {
            std::cout << "adding message to queue: " << std::to_string(queueID) << std::endl;
            messageQueues[queueID]->addMessage(receivedMsg);
        }
        
    }

    std::string threadExitReturnVal = "Thread exited";
    pthread_exit(&threadExitReturnVal);
}

// Get host IP address
char* getIPAddress() {
    char host[256];
    char *ip_addr;
    hostent *host_entry;
    int hostname;
    hostname = gethostname(host, sizeof(host)); //find the host name
    host_entry = gethostbyname(host); //find host information
    ip_addr = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0])); //Convert into IP string

    return ip_addr;
}

// Get fd associated with server socket
int bindSocketToPort(int opt, int port) {
    int server_fd;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                SO_REUSEADDR, &opt,
                sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }    

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (sockaddr*)&address,
            sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

// Get fd associated with socket end process should write to
int getWriteFd(int port, char* ip_addr) {

    int server_socket = 0;
    sockaddr_in serv_addr;
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket Creation Error \n");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr);

    if ((connect(server_socket, (sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("\n Connection Failed \n");
    }

    return server_socket;


}
