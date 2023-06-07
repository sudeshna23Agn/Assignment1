#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> 
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
// void chatfunc(int sockfd)
// {
// 	char buff[MAX];
// 	int n;
// 	for (;;) {
// 		bzero(buff, sizeof(buff));
// 		printf("Enter the string : ");
// 		n = 0;
// 		while ((buff[n++] = getchar()) != '\n')
// 			;
// 		write(sockfd, buff, sizeof(buff));
// 		bzero(buff, sizeof(buff));
// 		read(sockfd, buff, sizeof(buff));
// 		printf("From Server : %s", buff);
// 		if ((strncmp(buff, "exit", 4)) == 0) {
// 			printf("Client Exit...\n");
// 			break;
// 		}
// 	}
// }

int main()
{
	int sockfd, connfd;char buff[MAX];
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
		!= 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");
    struct timeval tv;
    tv.tv_sec = 5; /* Timeout in seconds */
    // setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
    bzero(buff, sizeof(buff));
	int r = read(sockfd, buff, sizeof(buff));
    if (r == -1)
    {
        printf("timeout");
    }
    else
        printf("%s\t ", buff);
	// chatfunc(sockfd);  // function for chat
	close(sockfd);
}
