#include "multi_thread_launch_server.h"


void exit_handler();

SOCKET server_socket;
std::vector<THREAD_HANDLE> connection_pool;

int main(int argc, char *argv[]) {
    atexit(common_exit_handler);
    atexit(exit_handler);
	short port = DEFAULT_PORT;
    char host[128] = "";
    bool parse_cmd_result = parse_cmd(argc, argv, host, &port);

    common_init_handler();

    CHECK_IO((server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) > 0, -1, "Can't create socket\n") ;
    // if (server_socket <= 0) {
    //     error_msg("Can't create socket");
    //     return -1;
    // }

    sockaddr_in server_addr;
    init_inet_address(&server_addr, host, port);

    //Bind socket to the address on the server

    // if (bind(server_socket, (sockaddr *) &server_addr, sizeof(sockaddr))) {
    //     char err_msg[128] = "";
    //     sprintf(err_msg, "Can't bind socket to the port %d", port);
    //     error_msg(err_msg);
    //     return -1;
    // }

    // if (listen(server_socket, CONNECTION_QUEUE)) {
    //     error_msg("Error listening socket");
    //     return -1;
    // }

    CHECK_IO(!bind(server_socket, (sockaddr *) &server_addr, sizeof(sockaddr)), -1, "Can't bind socket to the port %d \n", port);

    CHECK_IO(!listen(server_socket, CONNECTION_QUEUE), -1, "Error listening socket\n");

    printf("Server running at the port %d\n", port);

    while (true) {
        sockaddr_in incom_addr;
        memset(&incom_addr, 0, sizeof(incom_addr));
        socklen_t len = sizeof(incom_addr);
        SOCKET socket;  
        CHECK_IO((socket = accept(server_socket, (sockaddr *) &incom_addr, &len)) > 0, -1, "Can't accept connection\n");
        // if (socket <= 0) {
        //     error_msg("Can't accept connection");
        //     return -1;
        // }
        //handle_connection(socket, &incom_addr);
        connection_pool.push_back(create_thread(handle_connection, (SOCKET*)socket));
    }

    close_socket(server_socket);

    return 0;
}

void exit_handler() {
    close_socket(server_socket);
}