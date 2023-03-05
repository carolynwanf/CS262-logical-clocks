#include "threadHandler.h"

/*
    Each thread has an associated server_fd and two fds associated with its connections with other servers 
*/

int main(void) {
    // Print host IP
    char host[256];
    char *ip_addr;
    hostent *host_entry;
    int hostname;
    hostname = gethostname(host, sizeof(host)); //find the host name
    host_entry = gethostbyname(host); //find host information
    ip_addr = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0])); //Convert into IP string
    printf("Host IP: %s\n", ip_addr);

    // Setting up server sockets
    std::vector<std::thread> listeningThreads;
    int ports[3] = {8080, 8081, 8082};

    int server_fd;
    int opt = 1;
    for (int i = 0; i < 3; i++) {
        // Creating socket file descriptor
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
        address.sin_port = htons(ports[i]);
    
        // Forcefully attaching socket to the port 8080
        if (bind(server_fd, (sockaddr*)&address,
                sizeof(address))
            < 0) {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        // If successfully connected, add to file descriptors vector
        FileDescriptors newFileDescriptors{};
        newFileDescriptors.addServerFd(server_fd);
        fileDescriptorsVector.push_back(newFileDescriptors);

        std::thread t(listenForConnections, server_fd, i);

        listeningThreads.push_back(std::move(t)); // TODO !! remember to join these
    }

    // Setting up client connections for each process
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        for (int j = 0; j< NUMBER_OF_PROCESSES; j++) {
            if (i != j) {
                int server_socket = 0;
                sockaddr_in serv_addr;
                if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                    printf("\n Socket Creation Error \n");
                }

                serv_addr.sin_family = AF_INET;
                serv_addr.sin_port = htons(ports[j]);
                inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr);

                if ((connect(server_socket, (sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
                    printf("\n Connection Failed \n");
                    continue;
                }

                fileDescriptorsVector[i].addWriteFd(server_socket);

            }
        }
    }

    // Joining threads
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        listeningThreads[i].join();
    }

    for (int i = 0; i < fileDescriptorsVector.size(); i++) {
        fileDescriptorsVector[i].printValues();
    }
     

    // Setting up process running threads, each thread takes its server_fd 
    std::vector<std::thread> threads;
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