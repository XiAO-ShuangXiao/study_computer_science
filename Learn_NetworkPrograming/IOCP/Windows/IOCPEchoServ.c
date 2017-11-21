#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<Windows.h>
#include<process.h>

//����IOCP�ģ���Ϊ����ͨ�Ļ�����������

#define BUF_SIZE 100
#define READ 3
#define WRITE 5

typedef struct //��ͻ��������ӵ��׽��ֽṹ��
{
	SOCKET hClntSock;
	SOCKADDR_IN clntAdr;
} PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

//��IO��ʹ�õĻ�����ص�IO����Ҫ��OVERLAPPED�ṹ���װ��ͬһ���ṹ����
typedef struct  //buffer����Ϣ
{
	OVERLAPPED overlapped;
	WSABUF wsaBuf;
	char bufer[BUF_SIZE];
	int rwMode; //��ȡ��д��
}PER_IO_DATA, *LPPER_IO_DATA;

void ErrorHandling(char *message);
DWORD WINAPI EchoThreadMain(LPVOID CompletionPortIO);

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

	HANDLE hComPort;
	SYSTEM_INFO sysInfo;
	LPPER_IO_DATA ioInfo;
	LPPER_HANDLE_DATA handleInfo;

	SOCKET hServSock;
	SOCKADDR_IN servAdr;
	int recvBytes, i, flags = 0;
	hComPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0); //����һ��CP����
	GetSystemInfo(&sysInfo);
	printf("��ǰ����CPU������Ϊ:%d\n", sysInfo.dwNumberOfProcessors);
	for (i = 0; i < sysInfo.dwNumberOfProcessors; i++) //�����뵱ǰ����CPU������ͬ���߳�
	{
		_beginthreadex(NULL, 0, EchoThreadMain, (LPVOID)hComPort, 0, NULL);//����cp���������̣߳��߳̽�ͨ���þ������cp����
	}

	hServSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	ZeroMemory(&servAdr, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr));
	listen(hServSock, 5);

	while (1)
	{
		SOCKET hClntSock;
		SOCKADDR_IN clntAdr;
		int addrLen = sizeof(clntAdr);

		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &addrLen);

		//��̬����PER_HANDLE_DATA�ṹ�壬д��ͻ��������׽����Լ��ͻ��˵�ַ��Ϣ
		handleInfo = (LPPER_HANDLE_DATA)malloc(sizeof(PER_HANDLE_DATA));
		handleInfo->hClntSock = hClntSock;
		memcpy(&(handleInfo->clntAdr), &clntAdr, addrLen); 

		//���Ӵ�����cp����ʹ����Ŀͻ����׽���
		//��Ը��׽��ֵ��ص�io���ʱ����д�����ӵ�cp��������GetQueue...�����ķ���
		//Ҫ���ӵ��׽��־����Ҫ���ӵ�cp���󡢴�������ɵ��׽�����Ϣ
		CreateIoCompletionPort((HANDLE)hClntSock, hComPort, (DWORD)handleInfo, 0);

		//��̬����PER_IO_DATA�ṹ�������ͬʱ׼������WSARecv�������õ�OVERLAPPED�ṹ�������wsaBuf����
		ioInfo = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
		memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
		ioInfo->wsaBuf.len = BUF_SIZE;
		ioInfo->wsaBuf.buf = ioInfo->bufer;
		ioInfo->rwMode = READ;
	
		//���߸�����������OVERLAPPED�ṹ��ĵ�ֵַ����ֵҲ������GetQueue...�������صõ�
		//�ṹ������ĵ�ֵַ���һ����Ա�ĵ�ֵַ��ͬ��ʵ����Ҳ���Ǵ����˳ɸ�PER_IO_DATA�ṹ��
		WSARecv(handleInfo->hClntSock, &(ioInfo->wsaBuf), 1, &recvBytes, &flags, &(ioInfo->overlapped), NULL);
	}
	return 0;

}

DWORD WINAPI EchoThreadMain(LPVOID pComPort)
{
	//���߳�����EchoThreadMain����������GetQueue���������߳̾��Ƿ����CP������߳�
	HANDLE hComPort = (HANDLE)pComPort;
	SOCKET sock;
	DWORD bytesTrans;
	LPPER_HANDLE_DATA handleInfo;
	LPPER_IO_DATA ioInfo;
	DWORD flags = 0;

	while (1)
	{
		//����GetQueued��������IO�������ע�������Ϣʱ���أ����һ��������INFINITE��
		//����ʱ����ͨ�����������ĸ������õ�֮ǰ���ݵĽṹ����Ϣ
		GetQueuedCompletionStatus(hComPort, &bytesTrans, (LPDWORD)&handleInfo, (LPOVERLAPPED*)&ioInfo, INFINITE);
		sock = handleInfo->hClntSock;

		//���rwMode��Ա�е�ֵ�ж���������ɻ���������
		if (ioInfo->rwMode == READ)
		{
			puts("message received!\n");
			if (bytesTrans == 0) //����EOF��ʱ��
			{
				closesocket(sock);
				free(handleInfo);
				free(ioInfo);
				printf("client disconnected : %d\n", sock);
				continue;
			}

			//�����������ܵ���ֵ���͸��ͻ���
			memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
			ioInfo->wsaBuf.len = bytesTrans;
			ioInfo->rwMode = WRITE;
			WSASend(sock, &(ioInfo->wsaBuf), 1, NULL, 0, &(ioInfo->overlapped), NULL);
			ioInfo = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
			memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
			ioInfo->wsaBuf.len = BUF_SIZE;
			ioInfo->wsaBuf.buf = ioInfo->bufer;
			ioInfo->rwMode = READ;
			//������Ϣ֮����ܿͻ�����Ϣ
			WSARecv(sock, &(ioInfo->wsaBuf), 1, NULL, &flags, &(ioInfo->overlapped), NULL);
		}
		else
		{
			//���IOΪ���ʱִ��else����
			puts("message sent!\n");
			free(ioInfo);
		}
	}
	return 0;
}
void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}