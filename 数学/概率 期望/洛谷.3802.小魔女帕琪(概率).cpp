/*
��f[i]��ʾ��ǰi����6λû���ظ�ai�Ĵ�����n = ��a[i] 
�� f[i] = a1/n * a2/(n-1) * a3/(n-2) * a4/(n-3) * a5/(n-4) * a6/(n-5) * a7/(n-6)
	   (= (a1*a2*a3*a4*a5*a6*a7)/(n*(n-1)*(n-2)*(n-3)*(n-4)*(n-5)*(n-6)) )
��Ŀ����һ�����У�����Ҫ*7! 
����һ����n-6��������λ�ã�������*(n-6),���ÿ��԰�/(n-6)Լ�� 
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
	printf("%.3lf",res*=a[7]);//Լ��/(n-6) 

	return 0;
}
