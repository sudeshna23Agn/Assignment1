#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_PATH "tpf_unix_sock.server"
#define CLIENT_PATH "tpf_unix_sock.client"

int main(void){

    int client_sock, rc, len;
    struct sockaddr_un server_sockaddr; 
    struct sockaddr_un client_sockaddr; 
    int buf;
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));
     
    client_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    client_sockaddr.sun_family = AF_UNIX;   
    strcpy(client_sockaddr.sun_path, CLIENT_PATH); 
    len = sizeof(client_sockaddr);
    
    unlink(CLIENT_PATH);
    rc = bind(client_sock, (struct sockaddr *) &client_sockaddr, len);
    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SERVER_PATH);
    rc = connect(client_sock, (struct sockaddr *) &server_sockaddr, len);
    rc = recv(client_sock, &buf, sizeof(buf),0); 
    printf("data received %d",buf);
    close(client_sock);
    return 0;
}