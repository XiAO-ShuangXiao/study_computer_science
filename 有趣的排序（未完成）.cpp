/*
有趣的排序
时间限制：1秒
空间限制：32768K
度度熊有一个N个数的数组，他想将数组从小到大 排好序，但是萌萌的度度熊只会下面这个操作：
任取数组中的一个数然后将它放置在数组的最后一个位置。
问最少操作多少次可以使得数组从小到大有序？ 
输入描述:
首先输入一个正整数N，接下来的一行输入N个整数。(N <= 50, 每个数的绝对值小于等于1000)


输出描述:
输出一个整数表示最少的操作次数。

输入例子1:
4
19 7 8 25

输出例子1:
2
*/
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath> 
int main()
{
	int n;
	std::cin>>n;
	int a[n+2];
	int b[n+2];
	for(int i=0;i<n;i++)
	{
		std::cin>>a[i];
		b[i]=a[i];
	}
	std::sort(a,a+n);
	int result=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(b[j]==a[i])
			{
				result+=fabs(j-i);
			}
		}
	}
	std::cout<<result/2<<std::endl;
}