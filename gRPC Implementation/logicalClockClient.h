#include "logicalClock.grpc.pb.h"
#include "logicalClock.pb.h"

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#define SEND_MESSAGE_TO_ONE     0
#define SEND_MESSAGE_TO_OTHER   1
#define SEND_MESSAGE_TO_BOTH    2

// Client stuff
using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

using logicalclockservice::LogicalClockService;
using logicalclockservice::LogicalClockTime;
using logicalclockservice::Reply;

struct LogicalClockClient {
    private:
        std::vector<std::unique_ptr<LogicalClockService::Stub>> stubs;
    
    public:
        LogicalClockClient() {
            stubs = {};
        }

        void addClientStub(std::string addr) {
            auto channel = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
            std::unique_ptr<LogicalClockService::Stub> stub = LogicalClockService::NewStub(channel);
            stubs.push_back(stub);
        }


        std::string performDieRoll(int time) {
            ClientContext context;
            LogicalClockTime timeMessage;
            timeMessage.set_time(time);
            Reply server_reply;

            auto globalTime = std::chrono::system_clock::now();
            std::time_t globalTime_t = std::chrono::system_clock::to_time_t(globalTime);
            std::string log = std::to_string(true) + ",";
            int dieRoll = rand() % 10;
            switch (dieRoll)
            {
            case SEND_MESSAGE_TO_ONE:
                {
                    Status status = stubs[0]->SendMessage(&context, timeMessage, &server_reply);
                    if (!status.ok()) {
                        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
                    }
                    log += std::to_string(true) + "," + std::to_string(false) + "," + std::to_string(globalTime_t)
                                + "," + std::to_string(time) + "," + std::to_string(0) + "\n";
                    return log;
                }
                break;
            
            case SEND_MESSAGE_TO_OTHER:
                {
                    Status status = stubs[1]->SendMessage(&context, timeMessage, &server_reply);
                    if (!status.ok()) {
                        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
                    }
                    log += std::to_string(true) + "," + std::to_string(false) + "," + std::to_string(globalTime_t)
                                + "," + std::to_string(time) + "," + std::to_string(0) + "\n";
                    return log;
                }
                break;
            
            case SEND_MESSAGE_TO_BOTH:
                {
                    Status status = stubs[0]->SendMessage(&context, timeMessage, &server_reply);
                    if (!status.ok()) {
                        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
                    }
                    status = stubs[1]->SendMessage(&context, timeMessage, &server_reply);
                    if (!status.ok()) {
                        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
                    }
                    log += std::to_string(true) + "," + std::to_string(false) + "," + std::to_string(globalTime_t)
                                + "," + std::to_string(time) + "," + std::to_string(0) + "\n";
                    return log;
                }
                break;
            
            default:
                log += std::to_string(false) + "," + std::to_string(false) + "," + std::to_string(globalTime_t)
                            + "," + std::to_string(time) + "," + std::to_string(0) + "\n";
                return log;
                break;
            }
        }
};