#include <iostream>
#include <string>

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"

#define BUF_LEN 1024

using namespace std;

int main() {
    char buffer[BUF_LEN];
    struct sockaddr_in server_addr, client_addr;
    char temp[20];
    int server_fd, client_fd;
    int msg_size;
    socklen_t len;

    std::string ipaddr_ = "127.0.0.1";

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {// 소켓 생성
        printf("Server : Can't open stream socket\n");
        exit(0);
    }
    memset(&server_addr, 0x00, sizeof(server_addr));


    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ipaddr_.c_str());
    server_addr.sin_port = htons(13400);

    if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <0)
    {
        printf("Server : Can't bind local address.\n");
        exit(0);
    }


    if(listen(server_fd, 5) < 0)
    {
        printf("Server : Can't listening connect.\n");
        exit(0);
    }

    memset(buffer, 0x00, sizeof(buffer));
    printf("Server : wating connection request.\n");
    len = sizeof(client_addr);

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
    if(client_fd < 0)
    {
        printf("Server: accept failed.\n");
        exit(0);
    }

    inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));
    printf("Server : %s client connected.\n", temp);
    while(1)
    {

        memset(buffer, 0x00, sizeof(buffer));
        msg_size = read(client_fd, buffer, 1024);
        std::cout << buffer << std::endl;

        //write(client_fd, buffer, msg_size);
    }
    close(client_fd);
    printf("Server : %s client closed.\n", temp);

    close(server_fd);

    return 0;
}
