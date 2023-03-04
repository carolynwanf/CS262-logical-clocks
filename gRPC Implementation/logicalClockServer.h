#include "logicalClock.grpc.pb.h"
#include "logicalClock.pb.h"

#include <queue>

// Server stuff
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;


using logicalclockservice::LogicalClockService;
using logicalclockservice::LogicalClockTime;
using logicalclockservice::Reply;

class LogicalClockServer final : public  logicalclockservice::LogicalClockService::Service {
    private:
        std::mutex mu_;
        std::queue<int> messages;

    public:
        explicit LogicalClockServer() {}

        Status SendMessage(ServerContext* context, const LogicalClockTime* logical_clock_time, Reply* server_reply) {
            int clockTimeSent = logical_clock_time->time();

            mu_.lock();
            messages.push(clockTimeSent);
            mu_.unlock();

            return Status::OK;
        }

        int readMessage() {
            if (messages.size() == 0) {
                return -1;
            } else {
                mu_.lock();
                int message = messages.front();
                messages.pop();
                mu_.unlock();
                return message;
            }
        }

        int getQueueLength() {
            return messages.size();
        }
};