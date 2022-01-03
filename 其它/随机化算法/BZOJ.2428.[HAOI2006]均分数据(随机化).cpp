/*
832kb	2448ms
ʹÿ��(sum_i-Average)����ƽ��(Ҳ����ʹ��(sum_i^2)��С)�����ݷ�Χ��ôС������ֻ������λ����
������������Ѱ죬����random_shuffle()һ����������ܶ�ξͿ��Դﵽα�����������Ч���ˡ���
���壬���ǿ���~~���ְ�~~����ĳ�ֲ������֣��������ηָ���ǰsum��С���顣
�����������һֱ��һ���������������顣��
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=21;

int n,K,A[N],sum[7];
double Ans=1e15,Aver,Tmp;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Work()
{
	std::random_shuffle(A+1,A+1+n);
	memset(sum,0,sizeof sum);
	for(int i=1; i<=n; ++i)
		sum[std::min_element(sum+1,sum+1+K)-sum]+=A[i];
	double res=0;
	for(int i=1; i<=K; ++i) res+=1.0*sum[i]*sum[i];//Aver�������������
	Ans=std::min(Ans,res+Tmp);
}

int main()
{
	n=read(),K=read();
	int sum=0;
	for(int i=1; i<=n; ++i) sum+=(A[i]=read());
	Aver=1.0*sum/K, Tmp=K*Aver*Aver-2.0*sum*Aver;
	for(int i=1; i<=300000; ++i) Work();
	printf("%.2lf",sqrt(Ans/(double)K));

	return 0;
}
