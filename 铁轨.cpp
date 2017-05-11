/*
ĳ������һ����վ����N�ڳ����A����ʻ�복վ������չ˳����Ϊ1~n���������ж��Ƿ��������ǰ���ĳ���ض���˳���������һ����վ������˵��ս˳��5,4,1,2,3�ǲ����ܵģ�����5,4,3,2,1,�ǿ��Եġ� 
*/ 
#include<cstdio>
#include<stack>
using namespace std; 
int n;
const int MAXN = 1000 + 10;
int target[MAXN];
int main()
{
	while (scanf("%d", &n) == 1)
	{
		stack<int> s;
		int A = 1, B = 1;
		for (int i = 1; i <= n; i++)
			scanf("%d", &target[i]);
		int ok = 1;
		while (B <= n)
		{
			if (A == target[B])
			{
				A++;
				B++;
			}
			else if (!s. empty() && s.top() == target[B])
			{
				s.pop();
				B++;
			}
			else if (A <= n)
			{
				s.push(A++);
			}
			else
			{
				ok = 0;
				break;
			}
		}
		printf("%s\n",ok?"yes":"no");
	}
    return 0;
}


