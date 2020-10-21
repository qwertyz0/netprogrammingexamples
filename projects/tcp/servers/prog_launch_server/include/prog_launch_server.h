#ifndef NETWORK_PROGRAMMING_SINGLE_THREAD_TCP_SERVER_H
#define NETWORK_PROGRAMMING_SINGLE_THREAD_TCP_SERVER_H


#include <stdio.h>
#include <stdlib.h>
#include "common_net.h"
#include "shared_tcp_structs.h"
#include "math.h"
#include <vector>
#define DEFAULT_PORT 5560
#define CONNECTION_QUEUE 100

LaunchProgResponse* compute(LaunchProgRequest*, LaunchProgResponse*);

void handle_connection(SOCKET, sockaddr_in*);
#endif //NETWORK_PROGRAMMING_SINGLE_THREAD_TCP_SERVER_H
