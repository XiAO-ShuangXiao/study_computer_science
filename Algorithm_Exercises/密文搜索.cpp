/*

���⣺��������

����Ħ˹��X���յ�һ�����ϣ�ȫ����Сд��ĸ��ɡ�
���������ṩ����һ�����ϣ���೤��Ϊ8�������б�
����Ħ˹���֣���Щ�����Ǳ����Һ���������ǰ�Ƿ������еġ�

�����дһ�����򣬴ӵ�һ�������������������������λ�á�Ҫ����������������п����ԡ�

���ݸ�ʽ��

�����һ�У�һ���ַ���s��ȫ����Сд��ĸ��ɣ�����С��1024*1024
������һ����һ������n,��ʾ������n�����룬1<=n<=1000
��������n���ַ���������Сд��ĸ��ɣ����ȶ�Ϊ8

Ҫ�������
һ������, ��ʾÿ�����������������s��ƥ��������ܺ͡�

���磺
�û����룺
aaaabbbbaabbcccc
2
aaaabbbb
abcabccc

�����Ӧ�������
4

������Ϊ����һ������ƥ����3�Σ��ڶ�������ƥ����1�Σ�һ��4�Ρ�
*/
#include<iostream>
#include<algorithm>
using namespace std;
char a[20000], b[1000][10], c[10];
int ans;
void judge(char a[], char b[])
{
		for (int ii = 0; ii < strlen(b); ii++)
		{
			for (int i = 0; i < strlen(a); i++)
			{
				if (b[0] == a[i])
				{
					
					int i1 = i + 1;
					for (int iii = 1; iii < strlen(b); iii++)
					{
						if (b[iii] != a[i1])
							break;
						i1++;
						if (iii == strlen(b)-1)
						{
							ans++;
							return;
						}
					}
				}
			}
	}
	return;
}
int main()
{
	cin >> a;
	int bb;
	cin >> bb;
	ans = 0;
	for (int i = 0; i < bb; i++)
	{
		cin >> b[i];
		sort(b[i],b[i]+8);
	}
	for (int i = 0; i < bb; i++)
	{
		do
		{
			judge(a, b[i]);
		} while (next_permutation(b[i], b[i] + 8));
	}
	cout << ans << endl;
}