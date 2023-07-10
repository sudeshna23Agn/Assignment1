#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <memory.h>
#include <errno.h>
#include<arpa/inet.h>

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    char* ip; uint32_t ip_addr;
    int ln = sizeof(servaddr);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    connfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("%d\n",sockfd);
    printf("%d\n",connfd);
    servaddr.sin_family = AF_INET;  //IP protocol family
    ip_addr = inet_pton(AF_INET,"192.168.1.109",&servaddr.sin_addr);
    servaddr.sin_port = htons(8080);
    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    // ip = inet_ntoa(servaddr.sin_addr);
    // printf("%s\n",ip);
    listen(sockfd,1);
    int sock = accept(sockfd,(struct sockaddr *)&servaddr,(socklen_t*)&ln);

    sleep(2);
    send(sock,"hello from sudeshnsa",strlen("hello from sudeshna"),0);
    close(sock);
    close(sockfd);


}

