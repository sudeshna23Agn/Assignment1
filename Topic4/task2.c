#include<stdio.h>
#include<pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

pthread_mutex_t mutex;
int counter =0;

#define SOCK_PATH  "tpf_unix_sock.server"
#define SERVER_PATH "tpf_unix_sock.server"
#define CLIENT_PATH "tpf_unix_sock.client"

void *myThreadFun(void *arg)
{
    printf("inside child thread\n");
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
    while(1)
    {
        rc = recv(client_sock, &buf, sizeof(buf),0); 
        if (buf == 11)
            break;
        printf("data received %d\n",buf);
    }
    close(client_sock);
    return NULL;
}
int main()
{
    pthread_t th1, th2;
    pthread_create(&th1, NULL, myThreadFun, NULL);
    int server_sock, client_sock, len, rc;
    int bytes_rec = 0;
    struct sockaddr_un server_sockaddr;
    struct sockaddr_un client_sockaddr;     
    int buf=0;
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
    client_sock = accept(server_sock, (struct sockaddr *) &client_sockaddr, &len); 
    len = sizeof(client_sockaddr);
    rc = getpeername(client_sock, (struct sockaddr *) &client_sockaddr, &len);  
    int i=0;
    for(i=0;i<12;i++)
    {
        rc = send(client_sock, &buf, sizeof(int), 0);
        buf++;
    }
    close(server_sock);
    close(client_sock);
    pthread_join(th1, NULL);
    printf("parent thread\n");
}

