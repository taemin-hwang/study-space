#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

class DoipPacket {
 public:
    DoipPacket() = default;
    virtual ~DoipPacket() = default;
    void SetPayloadLength(unsigned int len) { payload_.resize(len); }

    std::vector<uint8_t> payload_;
};

string uint8_vector_to_hex_string(const vector<uint8_t>& v) {
    stringstream ss;
    ss << std::hex << std::setfill('0');
    vector<uint8_t>::const_iterator it;

    for (it = v.begin(); it != v.end(); it++) {
        ss << std::setw(2) << static_cast<unsigned>(*it);
    }

    return ss.str();
}

int main()
{
    struct sockaddr_in server;
    int s1;
    char message[500];

    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    bzero(&(server.sin_zero),8);
    s1 = socket(AF_INET,SOCK_STREAM,0);
    if(s1 == -1) {
        perror("socket not created\n");
        exit(1);
    }
    if(connect(s1,(struct sockaddr *)&server,sizeof(server)) == -1) {
        perror("not able to connect\n");
        exit(1);
    }

    DoipPacket doipPacket;
    doipPacket.SetPayloadLength(500);
    while(1) {
        unsigned int bufferFill(0);
        do {
            int bytesRead = read(s1, &(doipPacket.payload_.at(bufferFill)), (doipPacket.payload_.size() - bufferFill + 1U));

            if(static_cast<bool>(bytesRead < 0)) {
                std::cout << "Error read return < 0" << std::endl;
                exit(1);
            } else {
                bufferFill += bytesRead;
            }

        } while ((bufferFill < doipPacket.payload_.size()));

        if(doipPacket.payload_.size() != bufferFill) {
            cout << "buffer size is mismatched" << endl;
            cout << "buffer size : " << bufferFill << endl;
            cout << "payload size : " << doipPacket.payload_.size() << endl;
        }
        std::cout << uint8_vector_to_hex_string(doipPacket.payload_) << std::endl;

        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    close(s1);
    return 0;

}
