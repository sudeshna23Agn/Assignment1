#ifndef TCP_H_
#define TCP_H_
#include "common.h"
#include "fault_handling.h"
/**
 * @brief Struct to contain the socket fd, addr and associated subsystem
 * @details Used in the receive thread for receiving data from
 * each client subsystem
 */
typedef struct{
        int32_t socket_fd;	/**<socket file descriptor*/
        subsystem_t subsystem;	/**<Used to identify which computer on the
        vehicle this struct is associated with*/

        /*Below used only if current computer is a server*/
        struct sockaddr_in __attribute__((packed)) client_addr; /**<Stores
        internet addresses for connected client*/

        /*For multi-threaded applications*/
        thread_info receive_thread_info;	/**<Stores information about
        thread used to receive data from peers*/
}network_subsystem;

typedef struct
{
	struct sockaddr_in serv_addr;
	int client_fd;
	int sock;
}network_info_t;

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
/**
 * @brief    Connects a subsytem to any other subsytem using a socket.
 * @param    subsystem    Name of the subsystem to connect to.
 * @param    port        The port number of the listening subsytem. Kept by default at 9000.
 * @param    priority    Priority vaue (0-7). To be used with IEEE802.1Qbv.
 * @return   0 on success -1 on failure
 *
 * */
int32_t ConnectTo(subsystem_t subsystem, const char* port, uint32_t* priority);


/**
 * @brief    Creates a listening socket on the specified subsystem.
 *           This makes the subsystem a server
 * @param    socketfd            The file descriptor to keep track of the socket
 * @param    server_structure    Generic sockaddr_in structure
 * @param    ipaddr                 ip address of that subsystem
 * @param    port                 Port number of the subsystem
 * @return   valid file descriptor on success -1 on failure
 *
 * */
int32_t CreateServer(int32_t socketfd, struct sockaddr_in* server_structure,
        const char* ipaddr, const char* port);

/**
 * @brief	Identifies subsystem based on IP address
 * @details
 * @param   char* - ip address of subsystem to be identified
 * @param	network_subsytem* - network struct to  containing information of client
 * @return  FUNC_STATUS - Success / Failure
 * */
FUNC_STATUS identify_subsystem(char*, network_subsystem*);

/**
 * @brief Connects to the servar specified at ip and port.
 * 
 * @param network_info - Network info struct contains sock fd, 
 * @param ip           - IP Address of server in string format.
 * @param port         - The server port.
 * @return FUNC_STATUS - SUCCESS if connection is successful.
 * @todo Need to implement timeout function.
 */
FUNC_STATUS connect_to_server(network_info_t* network_info, const char* ip, uint16_t port);

/**
 * @brief Function to convert IP Address from String to Byte Array.
 *  - It is assumed that the "bytes" parameter memory is allocated 
 *    with 4 Bytes of memory.
 * @param str Input IP String.
 * @param bytes Bytes Array.
 * @return FUNC_STATUS 
 */
FUNC_STATUS ip_str_to_array(const char *str, uint8_t *bytes);


/**
 * @brief 
 * 
 * @param network_info 
 * @param ip 
 * @param port 
 * @param timeout_ms 
 * @return FUNC_STATUS 
 */
FUNC_STATUS connect_to_server_with_timeout(network_info_t* network_info, 
                                    char* ip, uint16_t port, uint32_t timeout_ms);
#endif /* TCP_H_ */
