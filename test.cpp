#include <sys/time.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv) // htons example
{
    int client_sockfd;
    struct sockaddr_in clientaddr;
    int data = 123456789;
    int client_len;

    client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.s_addr = inet_addr("125.129.39.250");
    clientaddr.sin_port = htons(atoi(argv[1])); // ->

    client_len = sizeof(clientaddr);

    if (connect(client_sockfd, (struct sockaddr *)&clientaddr, client_len) < 0)
    {
        perror("Connect error : ");
        exit(0);
    }
    
    // 보낼 데이터 네트워크 byte order를 따르도록 변경한다. 
    data = htonl(data); // ->
    write(client_sockfd, (void *)&data, sizeof(int));

    // 읽어들인 데이터는 호스트 byte order을 따르도록 변경한다.
    read(client_sockfd, (void *)&data, sizeof(int));
    data = ntohl(data); // ->
    close(client_sockfd);
}
