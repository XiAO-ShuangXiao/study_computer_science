/*
时间限制：1秒
空间限制：32768K
小易将n个棋子摆放在一张无限大的棋盘上。第i个棋子放在第x[i]行y[i]列。同一个格子允许放置多个棋子。每一次操作小易可以把一个棋子拿起并将其移动到原格子的上、下、左、右的任意一个格子中。小易想知道要让棋盘上出现有一个格子中至少有i(1 ≤ i ≤ n)个棋子所需要的最少操作次数.

输入描述:
输入包括三行,第一行一个整数n(1 ≤ n ≤ 50),表示棋子的个数
第二行为n个棋子的横坐标x[i](1 ≤ x[i] ≤ 10^9)
第三行为n个棋子的纵坐标y[i](1 ≤ y[i] ≤ 10^9)


输出描述:
输出n个整数,第i个表示棋盘上有一个格子至少有i个棋子所需要的操作数,以空格分割。行末无空格

如样例所示:
对于1个棋子: 不需要操作
对于2个棋子: 将前两个棋子放在(1, 1)中
对于3个棋子: 将前三个棋子放在(2, 1)中
对于4个棋子: 将所有棋子都放在(3, 1)中

输入例子1:
4
1 2 4 9
1 1 1 1

输出例子1:
0 1 3 10
*/
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <math.h>
struct point{
    int x,y;
};
bool comp(point a,point b){
    if(a.x!=b.x)
        return a.x<b.x;
    else
        return a.y<b.y;
}
//ostream_iterator<int> out(cout," ");
int main(){
    int n;
    while(cin>>n){
        vector<point> a(n);
        int minx=1000000000,maxx=0;
        for(int i=0;i<n;i++){
            cin>>a[i].x;
        }
        int miny=1000000000,maxy=0;
        for(int i=0;i<n;i++){
            cin>>a[i].y;
        }
        vector<int> res(n,1000000000);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                vector<int> temp(n,0);
                for(int k=0;k<n;k++){
                    temp[k]=abs(a[k].x-a[i].x)+abs(a[k].y-a[j].y);
                }
                sort(temp.begin(),temp.end());
               //copy(map1[i][j].begin(),map1[i][j].end(),out);
                //cout<<"KKK"<<endl;
                for(int k=1;k<n;k++){
                    temp[k]+=temp[k-1];
                }
                for(int k=0;k<n;k++){
                    if(res[k]>temp[k]){
                        res[k]=temp[k];
                    }
                }
            }
         
        for(int i=0;i<n-1;i++){
            cout<<res[i]<<" ";
        }
        cout<<res[n-1];
    }
    return 0;
}

