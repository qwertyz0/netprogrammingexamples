#include "simple_http_tcp_client.h"

#define GET_CMD "GET / HTTP/1.1\r\nHost:%s\r\n\r\n"
using namespace std;

int main(int argc, char *argv[])
{
	//Буфер повідомлень
	char dataBuffer[BUFFER_SIZE];

	SOCKET clientSocket;

	struct sockaddr_in serverAddr;
	char serverNamePort[BUFFER_SIZE * 4];
	char serverName[BUFFER_SIZE * 4];
	int nPort = 80;
	cout << "Enter an URL into format <server:[port]>: ";

	cin.getline(serverNamePort, BUFFER_SIZE * 4);

	//Отримуємо адресу і порт HTTP-серверу
	getServerPort(serverNamePort, serverName, nPort);

	//Формуємо простий HTTP-запит до серверу
	char HTTPRequest[BUFFER_SIZE * 4];
	snprintf(HTTPRequest, BUFFER_SIZE * 4, GET_CMD, serverName);
	memset(&serverAddr, 0, sizeof(serverAddr));
	if (initSocketAPI())
	{
		return socketError(TRUE, "init socket API");

	}
	//Створюємо активний сокет
	if ((clientSocket = socket(AF_INET, SOCK_STREAM,
							   IPPROTO_TCP)) <= 0)
	{
		return socketError(TRUE, "create socket", TRUE);
	}
	//Заповнюємо структуру serverAddr
	serverAddr.sin_family = AF_INET;

	//Переходимо до мережевого порядку байт
	serverAddr.sin_port = htons(nPort);

	//Вказуємо адресу серверу
	struct hostent *hptr;
	if (!(hptr = gethostbyname(serverName)))
	{
		closeSocket(clientSocket);
		getchar();
		return socketError(TRUE, "address server", TRUE);
	}

	memcpy(&serverAddr.sin_addr.s_addr,
		   hptr->h_addr_list[0], hptr->h_length);

	if (connect(clientSocket, (struct sockaddr *)&serverAddr,
				sizeof(serverAddr)))
	{
		closeSocket(clientSocket);
		getchar();
		return socketError(TRUE, "connect to server", TRUE);
	}
	cout << "Connected to server: " << serverName;
	cout << ": " << nPort << endl;
	int ret = send(clientSocket, HTTPRequest,
				   strlen(HTTPRequest), 0);
	if (ret <= 0)
	{
		closeSocket(clientSocket);
		getchar();
		return socketError(TRUE, "send request", TRUE);
	}
	//Буфер 8 кБ для прийнятих даних
	char HTTPResponse[32 * BUFFER_SIZE];
	ret = recv(clientSocket, HTTPResponse, 32 * BUFFER_SIZE, 0);
	if (ret <= 0)
	{
		closeSocket(clientSocket);
		getchar();
		return socketError(TRUE, "receive request", TRUE);
	}
	else
	{
		HTTPResponse[ret] ='\0';
		cout << HTTPResponse << endl;
	}

	//Закриваємо сокет і звільняємо системні ресурси
	closeSocket(clientSocket);
	deinitSocketAPI();
	return 0;
}
