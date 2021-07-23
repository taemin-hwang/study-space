#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "protocol_header.h"

using namespace std;

int main()
{
    struct sockaddr_in server,client;
    int s1,s2,len;
    char message[65536 + 1000];

    server.sin_port = htons(5000);
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    bzero(&(server.sin_zero),8);
    s1 = socket(AF_INET,SOCK_STREAM,0);
    if(s1 == -1) {
        perror("socket not created\n");
        exit(1);
    }
    if(bind(s1,(struct sockaddr *)&server,sizeof(struct sockaddr)) == -1) {
        perror("socket not binded\n");
        exit(1);
    }
    if(listen(s1,5) == -1) {
        perror("unable to listen");
        exit(1);
    }
    len = sizeof(struct sockaddr_in);
    s2 = accept(s1,(struct sockaddr *)&client, (socklen_t*)&len);
    printf("connected");
    if(s2 == -1) {
        perror("unable to accept connection");
        exit(1);
    }

    std::string msg;
    while(1) {
        cout << "[Enter message] ";
        cin >> msg;
        strcpy(message, msg.c_str());
        message[strlen(message)] = '\0';
        cout << strlen(message) << endl;
        int n = write(s2,message,strlen(message));
        if(n < 0) {
            perror("message not sent\n");
            exit(1);
        }
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    close(s1);
    close(s2);
    return 0;

}
