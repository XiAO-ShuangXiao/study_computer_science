/*
Tom�������ڸ��о�������һ�Ź��ڻ���Ŀγ̣���һ������������Ϊͷ�ۣ�һ��Ⱦɫ�����г�ǧ���������ԣ����Ǵ�0��ʼ��ţ��������򣬼�ǧ���������ڡ�
��������˵���ڶ�ѧ�������1234567009��λ���ϵļ��ʱ���⿴�������Ǻ���׼ȷ��������ġ�
�������ԣ������е���Ҫһ��ϵͳ��Ȼ��������12 3456 7009ʱ���������Ӧ�����
����ʮ������ǧ�İ���ʮ������ǧ���
�����ú���ƴ����ʾΪ
����shi er yi san qian si bai wu shi liu wan qi qian ling jiu
����������ֻ��Ҫ������Ϳ����ˡ�
������������ǰ����������һ��ϵͳ������һ�����������ִ���������������Ķ�д�Ĺ淶תΪ����ƴ���ִ������ڵ�����������һ���ո���񿪡�
����ע������ϸ��չ淶������˵��10010��������yi wan ling yi shi�������ǡ�yi wan ling shi������100000��������shi wan�������ǡ�yi shi wan������2000��������er qian�������ǡ�liang qian����
*/
#include<iostream>
using namespace std;
int main()
{
	int a, c = 0;
	int b[100];
	cin >> a;
	char* ds[] = { "ling","yi","er","san","si","wu","liu","qi","ba","jiu","liang" };
	while (a > 0)
	{
		b[c] = a % 10;
		a /= 10;
		c++;
	}
	int d;
	int e[100];
	int f = 0;
	for (d = c - 1; d >= 0; d--)
	{
		if (b[d] > 0 && d == 0)
			if (d == 0 && b[d + 1] == 0)
				cout << "ling " << ds[b[d]];
			else
				cout << ds[b[d]] << " ";
		else if ((d == 3 || d == 7 || d == 11) && b[d] > 0)
			cout << ds[b[d]] << " qian ";
		else if ((d == 2 || d == 6 || d == 10) && b[d] > 0)
			cout << ds[b[d]] << " bai ";
		else if ((d == 1 || d == 5 || d == 9) && b[d] > 0)
			if (c - 1 == d&&b[d] == 1)
				cout << "shi ";
			else if(b[d+1]==0)
				cout<<"ling "<<ds[b[d]]<<" shi ";
			else
				cout << ds[b[d]] << " shi ";
		else if (d == 4)
			cout << ds[b[d]] << " wan ";
		else if (d == 8)
			if (b[d] > 0)
				cout << ds[b[d]] << " yi ";
		else if (d == 0 && b[d] == 0)
				continue;
		else if (b[d] == 0 && d == 2)
			continue;
		else
			cout << ds[b[d]] << " ";
	}
	cout << endl;

}

