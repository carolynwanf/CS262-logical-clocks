#include "logicalClockClient.h"
#include "logicalClockServer.h"

#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#define PORT 8080

class LogicalClock {
    private:
        LogicalClockClient client;
        LogicalClockServer server;
        std::string server_addr;
        int microsecondSleep;
        int clockTime;
        int clockSpeed;
        std::string filename;
        std::ofstream filewriter;
    
    public:
        LogicalClock(int machineNum) {
            // run server?
            char host[256];
            std::string ip_addr;
            hostent *host_entry;
            int hostname;
            hostname = gethostname(host, sizeof(host)); //find the host name
            host_entry = gethostbyname(host); //find host information
            ip_addr = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0])); //Convert into IP string
            ServerBuilder builder;
            server_addr = ip_addr+":"+std::to_string(PORT+machineNum);
            builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());
            builder.RegisterService(&server);
            std::unique_ptr<Server> server(builder.BuildAndStart());
            server->Wait();


            // Generate random clockspeed from 1-6
            clockSpeed = (rand() % 6) + 1;
            // There are 1,000,000 microseconds in 1 seconds, so we divide that by clockspeed to
            //      find the number of microseconds (floored) that the machine should sleep for
            microsecondSleep = 1000000 / clockSpeed;
            filename = "machine"+std::to_string(machineNum)+"clock_speed"+std::to_string(clockSpeed)+"log.csv";
            // initialize CSV file
            filewriter.open(filename);
            filewriter << "was_die_roll,sent_message,message_received,system_time,logical_clock_time,length_of_queue\n";
        }

        ~LogicalClock() {
            filewriter.close();
        }

        int getClockTime() {
            return clockTime;
        }

        int getClockSpeed() {
            return clockSpeed;
        }

        int getSleepTime() {
            return microsecondSleep;
        }

        int getQueueLength() {
            return server.getQueueLength();
        }

        std::string getServerAddr() {
            return server_addr;
        }

        void readMessage() {
            auto globalTime = std::chrono::system_clock::now();
            std::time_t globalTime_t = std::chrono::system_clock::to_time_t(globalTime);

            int clockTimeRead = server.readMessage();

            if (clockTimeRead == -1) {
                return;
            } else {
                filewriter << std::to_string(false) << "," << std::to_string(false) << "," << std::to_string(true) 
                            << "," << std::to_string(globalTime_t) << "," << std::to_string(clockTime) << "," << std::to_string(getQueueLength()) << std::endl;
                clockTime = std::max(clockTimeRead, clockTime) + 1;
            }
        }

        void dieRoll() {
            std::string log = client.performDieRoll(clockTime);
            filewriter << log;
            clockTime++;
        }

        void addClientStub(std::string addr) {
            client.addClientStub(addr);
        }
};