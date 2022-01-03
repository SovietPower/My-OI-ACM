/*
设f[i]表示当前i往后6位没有重复ai的次数，n = ∑a[i] 
则 f[i] = a1/n * a2/(n-1) * a3/(n-2) * a4/(n-3) * a5/(n-4) * a6/(n-5) * a7/(n-6)
	   (= (a1*a2*a3*a4*a5*a6*a7)/(n*(n-1)*(n-2)*(n-3)*(n-4)*(n-5)*(n-6)) )
题目是求一个排列，所以要*7! 
由于一共有n-6个这样的位置，所以再*(n-6),正好可以把/(n-6)约掉 
*/
#include<cstdio>
using namespace std;
const int N=9;

int a[N];

int main()
{
	int sum=0;
	for(int i=1;i<=7;++i)
		scanf("%d",&a[i]), sum+=a[i];
	double res=1.0;
	for(int i=2;i<=7;++i)//7!
		res*=i;
	for(int i=1;i<=6;++i)
		res*=1.0*a[i]/(sum-i+1);
	printf("%.3lf",res*=a[7]);//约掉/(n-6) 

	return 0;
}
