#include<stdio.h>
#include<Windows.h>
#include<process.h>

unsigned WINAPI ThreadFunc(void *arg);

//һ���򵥵�windows�µĶ��̳߳���

int main(int argc, char *argv[])
{
	HANDLE hTread;
	unsigned threadID;
	int param = 5;
	hTread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (void*)&param, 0, &threadID); //����һ�����߳�
	Sleep(3000);
	puts("end of main\n");
	return 0;

}

unsigned WINAPI ThreadFunc(void *arg)
{
	int i;
	int cnt = *((int*)arg);
	for (i = 0; i < cnt; ++i)
	{
		Sleep(1000);
		puts("running thread");
	}
	return 0;
}