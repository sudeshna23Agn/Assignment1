#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <arpa/inet.h>
#include <semaphore.h>

typedef struct
{
	struct sockaddr_in serv_addr;
	int client_fd;
	int sock;
}network_info_t;

typedef struct{
        int32_t socket_fd;
        subsystem_t subsystem;
        struct sockaddr_in __attribute__((packed)) client_addr;
        thread_info receive_thread_info
}network_subsystem;

int32_t CreateServer(int32_t socketfd, struct sockaddr_in* server_structure,
		const char* ipaddr, const char* port){

    /**<Create a TCP/IP socket */
    if( (socketfd = socket(PF_INET, SOCK_STREAM, 0) ) < 0){
    	PRINT_ERR("socket(2)\n");
    	return FAILURE;
    }

    /**<clear and populate server socket address structure*/
    memset(server_structure, 0, sizeof(struct sockaddr_in));
    server_structure->sin_family = AF_INET;
    server_structure->sin_port = (in_port_t)htons((uint16_t)strtol(port, NULL, 10));
    server_structure->sin_addr.s_addr = inet_addr(ipaddr);

    /**<Bind the server address to the created socket*/
    if((bind(socketfd, (struct sockaddr *)server_structure, (socklen_t) sizeof(*server_structure))) < 0 ){
    	PRINT_ERR("bind()\n");
    	return FAILURE;
    }

    /**<Make it a listening socket*/
    printf("Listening on port %s ...\n", port);

    if( (listen(socketfd, SERVER_MAX_CONNECTIONS) ) < 0){
    	PRINT_ERR("listen()\n");
    	return FAILURE;
    }

    return socketfd;
}
