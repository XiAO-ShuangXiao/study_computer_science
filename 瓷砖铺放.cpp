/*��������
������һ����ΪN(1<=��<=10)�ĵذ壬�������ֲ�ͬ��ש��һ�ֳ���Ϊ1����һ�ֳ���Ϊ2����Ŀ���ޡ�Ҫ���������ΪN�ĵذ�������һ���ж����ֲ�ͬ���̷���
�������磬����Ϊ4�ĵ���һ��������5���̷���
����4=1+1+1+1
����4=2+1+1
����4=1+2+1
����4=1+1+2
����4=2+2
��������õݹ�ķ�������������⡣
�����ʽ
����ֻ��һ����N������ذ�ĳ���
�����ʽ
�������һ�������������в�ͬ�Ĵ�ש�̷ŷ���������
��������
4
�������
5
*/
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int ans;
int n;
int g[1000];
void cal(int count)
{
	int e;
	if (count>n)
		return;
	for (int i = 1; i < 3; i++)
	{
		g[count] = i;
		e = 0;
		for (int ii = 1; ii <= count; ii++)
		{
			e =e+g[ii];
		}
		if (e == n)
		{
			ans++;
		}
		else if (e < n)
		{
			cal(count + 1);
		}
	}
}
int main()
{
	cin >> n;
	ans = 0;
	cal(1);
	cout << ans << endl;
}

