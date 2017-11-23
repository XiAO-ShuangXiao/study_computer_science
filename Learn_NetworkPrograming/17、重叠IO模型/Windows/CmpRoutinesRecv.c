#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
#include<WS2tcpip.h>

#define BUF_SIZE 1024
void ErrorHandling(char *message);
void CALLBACK ComRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);

//����CompletionRoutine����������ص�IO����Pendingʱ�Զ����ú�����Ч�������ƻص�������
WSABUF dataBuf;
char buf[BUF_SIZE];
int recvBytes = 0;

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");
	if (argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	SOCKET hLisnSock, hRecvSock;
	SOCKADDR_IN lisnAdr, recvAdr;
	int recvAdrSz;
	int flags = 0;
	int index;

	WSABUF dataBuf;
	WSAEVENT evObj;
	WSAOVERLAPPED overlapped;

	hLisnSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);//FLAG_OVERLAPPED��������׽�����һ���ص�IO���׽���
	ZeroMemory(&lisnAdr, sizeof(lisnAdr));
	lisnAdr.sin_family = AF_INET;
	lisnAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	lisnAdr.sin_port = htons(atoi(argv[1]));

	if (bind(hLisnSock, (SOCKADDR*)&lisnAdr, sizeof(lisnAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if (listen(hLisnSock, 5) == SOCKET_ERROR)
		ErrorHandling("Listen() error");

	recvAdrSz = sizeof(recvAdr);
	hRecvSock = accept(hLisnSock, (SOCKADDR*)&recvAdr, &recvAdrSz);

	evObj = WSACreateEvent();
	ZeroMemory(&overlapped, sizeof(overlapped));
	overlapped.hEvent = evObj;
	dataBuf.len = BUF_SIZE;
	dataBuf.buf = buf;

	if (WSARecv(hRecvSock, &dataBuf, 1, &recvBytes, &flags, &overlapped, ComRoutine) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSA_IO_PENDING)//������ص���IO_PENDING�����ʾ�����Ƿ����˴��󣬶�����δ��ɣ�Pending��״̬
		{
			puts("BackGround data receive\n");
		}
	}
	//���һ������fAlertable����ΪTRUE֮���߳̿��Խ���alertable_wait״̬
	//��״̬�²��ܵ���CompletionRoutine����
	index = WSAWaitForMultipleEvents(1, &evObj, FALSE, WSA_INFINITE,TRUE);

	if (index == WAIT_IO_COMPLETION) //���óɹ���᷵��WAIT_IO_COMPLETION
	{
		puts("Overlapped IO completed\n");
	}
	else
	{
		ErrorHandling("WSARecv() error");
	}
	WSACloseEvent(evObj);
	closesocket(hRecvSock);
	closesocket(hLisnSock);
	WSACleanup();
	return 0;

}

void CALLBACK ComRoutine(DWORD dwError, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverlapped, DWORD flags)
{
	if (dwError != 0)
	{
		ErrorHandling("CompRoutine error");
	}
	else
	{
		recvBytes = szRecvBytes;
		printf("Received message:%s\n", buf);
	}
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}