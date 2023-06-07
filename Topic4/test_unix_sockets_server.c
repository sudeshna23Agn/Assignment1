#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH  "tpf_unix_sock.server"

int main(void){

    int server_sock, client_sock, len, rc;
    int bytes_rec = 0;
    struct sockaddr_un server_sockaddr;
    struct sockaddr_un client_sockaddr;     
    int buf=5;
    int backlog = 10;
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));              
    server_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    server_sockaddr.sun_family = AF_UNIX;   
    strcpy(server_sockaddr.sun_path, SOCK_PATH); 
    len = sizeof(server_sockaddr);
    unlink(SOCK_PATH);
    rc = bind(server_sock, (struct sockaddr *) &server_sockaddr, len);
    rc = listen(server_sock, backlog);
    printf("socket listening...\n");
    client_sock = accept(server_sock, (struct sockaddr *) &client_sockaddr, &len); 
    len = sizeof(client_sockaddr);
    rc = getpeername(client_sock, (struct sockaddr *) &client_sockaddr, &len);  
    rc = send(client_sock, &buf, sizeof(int), 0);
    close(server_sock);
    close(client_sock);
    return 0;
}