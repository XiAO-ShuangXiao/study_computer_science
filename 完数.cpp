//���һ����Ȼ��������С�����������֮�͵��ڸ��������Ϊ����������㷨����ӡ1-9999֮�������������
#include<iostream>
#include<cstring>   
using namespace std;  
#define max(a,b) ((a)>(b)?(a):(b)) 
int addNum(int a)
{
	int add=0;
	for(int i=1;i<=a/2;i++)
	{
		if(a%i==0)
			add+=i;
	}
	return add;
}
int main()
{
	int a=1;
	for(;a<=9999;a++)
	{
		if(addNum(a)==a)
			cout<<a<<endl;
	}
}
