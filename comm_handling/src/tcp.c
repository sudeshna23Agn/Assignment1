#include "tcp.h"
#include <sys/socket.h>
#include <fcntl.h>
#include <poll.h>
#include <time.h>

int32_t ConnectTo(subsystem_t subsystem, const char* port, uint32_t* priority)
{

    const char* IP_ADDR;
    struct sockaddr_in ServerInfo;        /**<AF_INET structure to store server info*/

    /**<Clear and populate the server info structure*/
    memset(&ServerInfo, 0, sizeof(ServerInfo));
    ServerInfo.sin_family = AF_INET;
    ServerInfo.sin_port = htons((uint16_t)atoi(port));

    /**<Fill IP_ADDR based on known IP address of clients*/
    switch (subsystem) {
        case ECU_1:
            if(inet_pton(AF_INET, ECU1_S1_IPADDR, &ServerInfo.sin_addr.s_addr) <= 0){
            	PRINT_ERR();
            	return FAILURE;
            }
            IP_ADDR = ECU1_S1_IPADDR;
            break;

        case ECU_2:
            if(inet_pton(AF_INET, ECU2_S1_IPADDR, &ServerInfo.sin_addr.s_addr) <= 0){
            	PRINT_ERR();
            	return FAILURE;
            }
            IP_ADDR = ECU2_S1_IPADDR;
            break;

        case ECU_3:
            if(inet_pton(AF_INET, ECU3_S1_IPADDR, &ServerInfo.sin_addr.s_addr) <= 0){
            	PRINT_ERR();
            	return FAILURE;
            }
            IP_ADDR = ECU3_S1_IPADDR;
            break;

        case ECU_4:
            if(inet_pton(AF_INET, ECU4_S1_IPADDR, &ServerInfo.sin_addr.s_addr) <= 0){
            	PRINT_ERR();
            	return FAILURE;
            }
            IP_ADDR = ECU4_S1_IPADDR;
            break;

        case ECU_5:
            if(inet_pton(AF_INET, ECU5_S1_IPADDR, &ServerInfo.sin_addr.s_addr) <= 0){
            	PRINT_ERR();
            	return FAILURE;
            }
            IP_ADDR = ECU5_S1_IPADDR;
            break;

        case ECU_6:
            if(inet_pton(AF_INET, ECU6_S1_IPADDR, &ServerInfo.sin_addr.s_addr) <= 0){
            	PRINT_ERR();
            	return FAILURE;
            }
            IP_ADDR = ECU6_S1_IPADDR;
            break;

        case ECU_7:
            if(inet_pton(AF_INET, ECU7_S1_IPADDR, &ServerInfo.sin_addr.s_addr) <= 0){
            	PRINT_ERR();
            	return FAILURE;
            }
            IP_ADDR = ECU7_S1_IPADDR;
            break;

        case FC:
            if(inet_pton(AF_INET, FC_IPADDR, &ServerInfo.sin_addr.s_addr) <= 0){
            	PRINT_ERR();
            	return FAILURE;
            }
            IP_ADDR = FC_IPADDR;
            break;

        case TELEMETRY:
            if(inet_pton(AF_INET, TELEMETRY_IPADDR, &ServerInfo.sin_addr.s_addr) <= 0){
            	PRINT_ERR();
            	return FAILURE;
            }
            IP_ADDR = TELEMETRY_IPADDR;
            break;

        case LC:
            if(inet_pton(AF_INET, LC_IPADDR, &ServerInfo.sin_addr.s_addr) <= 0){
            	PRINT_ERR();
            	return FAILURE;
            }
            IP_ADDR = LC_IPADDR;
            break;

        case PC:
            if(inet_pton(AF_INET, PC_IPADDR, &ServerInfo.sin_addr.s_addr) <= 0){
            	PRINT_ERR();
            	return FAILURE;
            }
            IP_ADDR = PC_IPADDR;
            break;

        case LO:
            if(inet_pton(AF_INET, LOOPBACK_IPADDR, &ServerInfo.sin_addr.s_addr) <= 0){
            	PRINT_ERR();
            	return FAILURE;
            }
            IP_ADDR = LOOPBACK_IPADDR;
            break;

        case MCRC:
            if(inet_pton(AF_INET, MCRC_IPADDR, &ServerInfo.sin_addr.s_addr) <= 0){
            	PRINT_ERR();
            	return FAILURE;
            }
            IP_ADDR = MCRC_IPADDR;
            break;

        default:
        	PRINT_ERR("IP address of server is invalid!\n");
            return FAILURE;
        	break;
    }

    /**<create a TCP/IP socket for server comms*/
    int32_t socketfd = socket(PF_INET, SOCK_STREAM, 0);
    if(socketfd < 0){
    	PRINT_ERR();
    	return FAILURE;
    }

    /**<Set priority of the packet. To be used for 802.1Qbv*/
    if(priority != NULL){
    	if(setsockopt(socketfd, SOL_SOCKET, SO_PRIORITY, &priority, sizeof(priority)) < 0){
        	PRINT_ERR();
        	return FAILURE;
    	}
    }

    /**<Connect to server using its address*/
    printf("Connecting to %s on port %s ...\n", IP_ADDR, port);

    socklen_t len = sizeof(ServerInfo);

    if(connect(socketfd, (struct sockaddr *)&ServerInfo, len)  < 0){
    	PRINT_ERR("Connection to subsystem %d failed!\n", subsystem);
    	return FAILURE;
    }

    return socketfd;

}

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


FUNC_STATUS identify_subsystem(char* ip_addr, network_subsystem* connected_subsystem){

	/**<Based on IP address, identify which subsystem just connected*/
	if(0 == strcmp(ip_addr, ECU1_S1_IPADDR)){
		connected_subsystem->subsystem = ECU_1;
	}else if(0 == strcmp(ip_addr, ECU1_S2_IPADDR)){
		connected_subsystem->subsystem = ECU_1_2;
	}else if(0 == strcmp(ip_addr, ECU2_S1_IPADDR)){
		connected_subsystem->subsystem = ECU_2;
	}else if(0 == strcmp(ip_addr, ECU3_S1_IPADDR)){
		connected_subsystem->subsystem = ECU_3;
	}else if(0 == strcmp(ip_addr, ECU4_S1_IPADDR)){
		connected_subsystem->subsystem = ECU_4;
	}else if(0 == strcmp(ip_addr, ECU5_S1_IPADDR)){
		connected_subsystem->subsystem = ECU_5;
	}else if(0 == strcmp(ip_addr, ECU6_S1_IPADDR)){
		connected_subsystem->subsystem = ECU_6;
	}else if(0 == strcmp(ip_addr, ECU7_S1_IPADDR)){
		connected_subsystem->subsystem = ECU_7;
	}else if(0 == strcmp(ip_addr, FC_IPADDR)){
		connected_subsystem->subsystem = FC;
	}else if(0 == strcmp(ip_addr, TELEMETRY_IPADDR)){
		connected_subsystem->subsystem = TELEMETRY;
	}else if(0 == strcmp(ip_addr, LC_IPADDR)){
		connected_subsystem->subsystem = LC;
	}else if(0 == strcmp(ip_addr, MCRC_IPADDR)){
		connected_subsystem->subsystem = MCRC;
	}else{
		PRINT_ERR("Invalid IP address!\n");
		return FAILURE;
	}

	return SUCCESS;
}


FUNC_STATUS connect_to_server(network_info_t* network_info, const char* ip, uint16_t port)
{
	/**< Create the TCP IP Socket.*/
	if ((network_info->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		return FAILURE;
	}
	/**< Not a local connection*/
	network_info->serv_addr.sin_family = AF_INET;

	/**< Set the port according to the port specified in the LUT*/
	network_info->serv_addr.sin_port = htons(port);

	/**< Some more network stuff*/
	if (inet_pton(AF_INET, ip, &network_info->serv_addr.sin_addr) <= 0) 
	{
		return FAILURE;
	}
	
	/**< Establish a connection with the telemtry server with the respective address ans respective port.*/
	if (connect(network_info->sock, (struct sockaddr*)&network_info->serv_addr,
                                     sizeof(network_info->serv_addr)) < 0)
	{
		return FAILURE;
	}

    /**< Connected to the socket server. */
	return SUCCESS;
}

FUNC_STATUS connect_to_server_with_timeout(network_info_t* network_info, 
                                    char* ip, uint16_t port, uint32_t timeout_ms)
{
    /**< Create the TCP IP Socket.*/
	if ((network_info->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		return FAILURE;
	}
	/**< Not a local connection*/
	network_info->serv_addr.sin_family = AF_INET;

	/**< Set the port according to the port specified in the LUT*/
	network_info->serv_addr.sin_port = htons(port);

	/**< Some more network stuff*/
	if (inet_pton(AF_INET, ip, &network_info->serv_addr.sin_addr) <= 0) 
	{
		return FAILURE;
	}
    int rc = 0;
    int sockfd_flags_before;
    if ((sockfd_flags_before = fcntl(network_info->sock, F_GETFL, 0) < 0))
    {
        return -1;
    }
    
    if (fcntl(network_info->sock, F_SETFL, sockfd_flags_before | O_NONBLOCK) < 0)
        return -1;
    // Start connecting (asynchronously)
    do
    {
        if (connect(network_info->sock, (struct sockaddr*)&network_info->serv_addr,
                                     sizeof(network_info->serv_addr)) < 0)
        {
            // Did connect return an error? If so, we'll fail.
            if ((errno != EWOULDBLOCK) && (errno != EINPROGRESS))
            {
                rc = -1;
            }
            // Otherwise, we'll wait for it to complete.
            else
            {
                // Set a deadline timestamp 'timeout' ms from now (needed b/c poll can be interrupted)
                struct timespec now;
                if (clock_gettime(CLOCK_MONOTONIC, &now) < 0)
                {
                    rc = -1;
                    break;
                }
                struct timespec deadline = {.tv_sec = now.tv_sec,
                                            .tv_nsec = now.tv_nsec + timeout_ms * 1000000l};
                // Wait for the connection to complete.
                do
                {
                    // Calculate how long until the deadline
                    if (clock_gettime(CLOCK_MONOTONIC, &now) < 0)
                    {
                        rc = -1;
                        break;
                    }
                    int ms_until_deadline = (int)((deadline.tv_sec - now.tv_sec) * 1000l + (deadline.tv_nsec - now.tv_nsec) / 1000000l);
                    if (ms_until_deadline < 0)
                    {
                        rc = 0;
                        break;
                    }
                    // Wait for connect to complete (or for the timeout deadline)
                    struct pollfd pfds[] = {{.fd = network_info->sock, .events = POLLOUT}};
                    rc = poll(pfds, 1, ms_until_deadline);
                    // If poll 'succeeded', make sure it *really* succeeded
                    if (rc > 0)
                    {
                        int error = 0;
                        socklen_t len = sizeof(error);
                        int retval = getsockopt(network_info->sock, SOL_SOCKET, SO_ERROR, &error, &len);
                        if (retval == 0)
                            errno = error;
                        if (error != 0)
                            rc = -1;
                    }
                }
                // If poll was interrupted, try again.
                while (rc == -1 && errno == EINTR);
                // Did poll timeout? If so, fail.
                if (rc == 0)
                {
                    errno = ETIMEDOUT;
                    rc = -1;
                }
            }
        }
    } while (0);

    // Restore original O_NONBLOCK state
    if (fcntl(network_info->sock, F_SETFL, sockfd_flags_before) < 0)
        return -1;

    // Success
    return rc;
}

FUNC_STATUS ip_str_to_array(const char *input_str, uint8_t *bytes)
{
    char str[100];

    memcpy(str, input_str, strlen(input_str));
    
    char* save_ptr = NULL;
    char *p = strtok_r(str, ".", &save_ptr);

    int i = 0;

    for (int i = 0; i < 4; i++)
    {
        bytes[i] = strtol(p, NULL, 10);
        if (bytes[i] < -1)
        {
            return FAILURE;
        }
        p = strtok_r(NULL, ".", &save_ptr);
    }
    return SUCCESS;
}
