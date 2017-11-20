#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
#include<WS2tcpip.h>

#define BUF_SIZE 1024
void ErrorHandling(char *message);
void CALLBACK ReadCompRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
void CALLBACK WriteComRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);

//ʹ�ô��ص�IOģ��ʵ�ֻ����������ˣ�����϶�~
typedef struct
{
	SOCKET hClntSock;
	char buf[BUF_SIZE];
	WSABUF wsaBuf;
} PER_IO_DATA, *LPEER_IO_DATA;

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
	LPWSAOVERLAPPED lpOvlp;
	DWORD recvBytes;
	LPEER_IO_DATA hbInfo;
	int mode = 1, recvAdrSz, flagInfo = 0;
	hLisnSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED); //����һ���ص�IO���׽���
	ioctlsocket(hLisnSock, FIONBIO, &mode); //����������ֲ�Ϊ0��ʱ�򣬽�����׽��ָ�Ϊ������ģʽ

	ZeroMemory(&lisnAdr, sizeof(lisnAdr));
	lisnAdr.sin_family = AF_INET;
	lisnAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	lisnAdr.sin_port = htons(atoi(argv[1]));

	if (bind(hLisnSock, (SOCKADDR*)&lisnAdr, sizeof(lisnAdr)) == -1)
		ErrorHandling("bind() error");
	if (listen(hLisnSock, 5) == -1)
		ErrorHandling("listen() error");

	recvAdrSz = sizeof(recvAdr);
	while (1)
	{
		SleepEx(100, TRUE); //Ϊ������Completion Routine��������Ҫѭ������SleepEx����
		hRecvSock = accept(hLisnSock, (SOCKADDR*)&recvAdr, &recvAdrSz);
		if (hRecvSock == INVALID_SOCKET) //������Ϊ�Ƿ������ģ�Ҫ����INVALID_SOCKET�����
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			else
				ErrorHandling("accept() error");
		}
		puts("Client connected\n");

		//�ص�IO����Ҫ�Ľṹ���ʼ������Ϊÿһ���ͻ��˶���Ҫһ���ṹ��
		//����ʹ��malloc���ж�̬����
		lpOvlp = (LPWSAOVERLAPPED)malloc(sizeof(WSAOVERLAPPED));
		memset(lpOvlp, 0, sizeof(WSAOVERLAPPED));

		//��̬����PER_IO_DATA�ṹ���ڴ�ռ䣬������д���׽��־��
		hbInfo = (LPEER_IO_DATA)malloc(sizeof(PER_IO_DATA));
		hbInfo->hClntSock = (DWORD)hRecvSock;
		(hbInfo->wsaBuf).buf = hbInfo->buf;
		(hbInfo->wsaBuf).len = BUF_SIZE;

		//WSAOVERLAPPED�ṹ�������event��Ա��д��֮ǰ����Ľṹ�����
		//����Completion Routine�������ص�IO����Ҫʱ�����
		//���event�¼��������ӱ����Ϣ
		lpOvlp->hEvent = (HANDLE)hbInfo; 
		//����WSARecv������ReadCompRoutineָ��ΪCompletion Routine
		//����lpOvlp���ݵ������У�CompletionRoutine��ʽ�ڿ��Է������IO���׽��־���ͻ���
		WSARecv(hRecvSock, &(hbInfo->wsaBuf), 1, &recvBytes, &flagInfo, lpOvlp, ReadCompRoutine);
	}
	closesocket(hRecvSock);
	closesocket(hLisnSock);
	WSACleanup();
	return 0;

}
void CALLBACK ReadCompRoutine(DWORD dwError, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverlapped, DWORD flags) //�ú���������ζ����������ݵ����룬����Ҫ�������ݸ������ͻ���
{
	LPEER_IO_DATA hbInfo = (LPEER_IO_DATA)(lpOverlapped->hEvent);
	SOCKET hSock = hbInfo->hClntSock;
	LPWSABUF bufInfo = &(hbInfo->wsaBuf);
	DWORD sendByes;

	if (szRecvBytes == 0) //�Ͽ�����
	{
		closesocket(hSock); 
		free(lpOverlapped->hEvent);
		free(lpOverlapped);
		puts("client disconnected\n");
	}
	else //��������
	{
		bufInfo->len = szRecvBytes;
		WSASend(hSock, bufInfo, 1, &sendByes, 0, lpOverlapped, WriteComRoutine); //��������WSASend�����ص�IO��Send
	}
}
void CALLBACK WriteComRoutine(DWORD dwError, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverlapped, DWORD flags)
{
	LPEER_IO_DATA hbInfo = (LPEER_IO_DATA)(lpOverlapped->hEvent);
	SOCKET hSock = hbInfo->hClntSock;
	LPWSABUF bufInfo = &(hbInfo->wsaBuf);
	DWORD recvBytes;
	int flagInfo = 0;
	WSARecv(hSock, bufInfo, 1, &recvBytes, &flagInfo, lpOverlapped, ReadCompRoutine); //������Ϣ֮�󣬷��������Լ���������Ϣ
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}