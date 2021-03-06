#include "multi_thread_client.h"

THREAD_RESULT process_connection(void* data) {
    PCLIENT_OPTIONS pclient_options = (PCLIENT_OPTIONS)data;

    printf("Opt1 %p", pclient_options);
    printf("Opt1 %s", pclient_options->data);
    SOCKET client_socket = -1;
    CHECK_IO((client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) > 0, -1, "Can't create client socket\n");

    printf("Socket creation\n");
    sockaddr_in server_addr;
    init_inet_address(&server_addr, pclient_options->server_host, pclient_options->server_port);
    printf("Address inited\n");

    //Connect socket to the address on the server
    CHECK_IO(connect(client_socket, (sockaddr*)&server_addr, sizeof(sockaddr)) == 0, -1, "Can't connect socket to server %s:%d\n", pclient_options->server_host, pclient_options->server_port);

    printf("Connected\n");

    int sc = send(client_socket, pclient_options->data, sizeof(pclient_options->data), 0);
    if (sc <= 0) {
        char err_msg[128] = "";
        sprintf(err_msg, "Can't send data to the server %s:%d\n", pclient_options->server_host, pclient_options->server_port);
        error_msg(err_msg);
    }

    close_socket(client_socket);
    return 0;
}