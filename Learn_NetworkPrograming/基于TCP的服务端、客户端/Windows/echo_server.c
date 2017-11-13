#include<WinSock2.h>
#include<stdio.h>
#include<WS2tcpip.h> 
void ErrorHandling(char *message);
#define BUF_SIZE 1024
int main(int argc, char *argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");

	SOCKET hServSock, hClntSock;
	char message[BUF_SIZE];
	int strLen, i;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSize;
	if (argc != 2)
	{
		printf("Usage %s <port>\n", argv[0]);
		exit(1);
	}
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	clntAdrSize = sizeof(clntAdr);

	for (int i = 0; i < 5; ++i)
	{
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSize);
		if (hClntSock == -1)
			ErrorHandling("acept() error");
		while ((strLen = recv(hClntSock, message, BUF_SIZE,0)) != 0)
		{
			send(hClntSock, message, strLen,0);
		}
		closesocket(hClntSock);
	}
	closesocket(hServSock);
	WSACleanup();
	return 0;

}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}