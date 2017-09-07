/*
进制均值
时间限制：1秒
空间限制：32768K
尽管是一个CS专业的学生，小B的数学基础很好并对数值计算有着特别的兴趣，喜欢用计算机程序来解决数学问题，现在，她正在玩一个数值变换的游戏。她发现计算机中经常用不同的进制表示一个数，如十进制数123表达为16进制时只包含两位数7、11（B），用八进制表示为三位数1、7、3，按不同进制表达时，各个位数的和也不同，如上述例子中十六进制和八进制中各位数的和分别是18和11,。 小B感兴趣的是，一个数A如果按2到A-1进制表达时，各个位数之和的均值是多少？她希望你能帮她解决这个问题？ 所有的计算均基于十进制进行，结果也用十进制表示为不可约简的分数形式。
输入描述:
输入中有多组测试数据，每组测试数据为一个整数A(1 ≤ A ≤ 5000).


输出描述:
对每组测试数据，在单独的行中以X/Y的形式输出结果。

输入例子1:
5
3

输出例子1:
7/3
2/1
*/
#include<iostream>
#include<algorithm>
int f(int a)
{
  int result=0;
  for(int i=2;i<a;i++)
  {
    int b=a;
    while(b>0)
    {
      result+=b%i;
      b/=i;
    }
  }
  return result;
}
int findgcd(int a,int b)
{
  if(!b)
  {
    return a;
  }
  else
  {
    return findgcd(b,a%b);
  }
}
int main(){

    int a;
    while(std::cin>>a)
    {
      int result=f(a);
      int bcd=findgcd(result,a-2);
      std::cout<<result/bcd<<"/"<<(a-2)/bcd<<std::endl;
    }
}
