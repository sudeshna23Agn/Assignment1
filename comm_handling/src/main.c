#include"tcp.c"

const char ipaddr[20];
const char port[5];
struct sockaddr_in* server_structure;


int main()
{
    int32_t  socket_fd = CreateServer(0,server_structure,ipaddr, port);
}
