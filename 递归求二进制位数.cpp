//����һ��ʮ�����������������Ӧ�Ķ���������λ�������磬����ʮ������9�����Ӧ�Ķ���������1001�����λ����4�� 
#include	<iostream>
using namespace std;
int main()
{
	int a;
	cin>>a;
	int count=0;
	while(a>0)
	{
		a/=2;
		count++;
	}
	cout<<count<<endl;
}
