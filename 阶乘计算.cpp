#include<stdio.h>  
#include<string.h>  
#define MAX 3000  
int main()  
{  
    int a[MAX],i,j,n;  
    int c=0;  //��λ  
    int s;  
    memset(a,0,sizeof(a));  
    scanf("%d",&n);  
    a[0]=1;  
    for(i=2;i<=n;i++)    //����   
    {  
        for(j=0;j<MAX;j++)  
        {  
            s=a[j]*i+c;  
            a[j]=s%10;  
            c=s/10;  
        }  
    }  
    for(i=MAX-1;i>=0;i--)   //�ӵ�һ����Ϊ��Ŀ�ʼ   
     if(a[i])  
        break;  
    for(j=i;j>=0;j--)  
    {  
        printf("%d",a[j]);  
    }  
    return 0;   
}  
