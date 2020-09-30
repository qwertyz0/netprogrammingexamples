#include "prog_launch_server.h"

void handle_connection(SOCKET socket, sockaddr_in* addr) {
    char* str_in_addr = inet_ntoa(addr->sin_addr);
    printf("[%s]>>%s\n", str_in_addr, "Establish new connection");
	int rc = 1;
    while (rc > 0) {
        /*SquareRootRequest request;
		memset(&request, sizeof(request), 0);

		SquareRootResponse response;
		memset(&request, sizeof(request), 0);

        rc = recv(socket, (char*)&request, sizeof(request), 0);
		compute(&request, &response);
		rc = send(socket, (char*)&response, sizeof(response), 0);*/ //pomenyat' SquareRootResponse i SquareRootRequest v shared tcp include

		char   psBuffer[128];
		FILE   *pPipe;

		/* Run DIR so that it writes its output to a pipe. Open this
		* pipe with read text attribute so that we can read it
		* like a text file.
		*/

		if ((pPipe = _popen("dir *.c /on /p", "r")) == NULL) {
			char err_msg[256];
			sprintf(err_msg, "Cant find programm !");
			send(socket, err_msg, sizeof(err_msg), 0);
		}
		else {
			char succ_msg[256];
			sprintf(succ_msg, "Success!");
			send(socket, succ_msg, sizeof(succ_msg), 0);

		}
			

		/* Read pipe until end of file, or an error occurs. */

		while (fgets(psBuffer, 128, pPipe))
		{
			puts(psBuffer);
		}

		/* Close pipe and print return value of pPipe. */
		if (feof(pPipe))
		{
			printf("\nProcess returned %d\n", _pclose(pPipe));
		}
		else
		{
			printf("Error: Failed to read the pipe to the end.\n");
		}


    }
    close_socket(socket);
    printf("[%s]>>%s", str_in_addr, "Close incomming connection");
}

