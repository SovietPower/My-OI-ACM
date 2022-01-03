/*
832kb	2448ms
使每组(sum_i-Average)尽量平均(也就是使Σ(sum_i^2)最小)。数据范围这么小，而且只保留两位。。
不连续分组很难办，但是random_shuffle()一下连续分组很多次就可以达到伪不连续分组的效果了。。
具体，我们可以~~随便分啊~~按照某种策略来分，比如依次分给当前sum最小的组。
被随机数种子一直卡一个点是怎样的体验。。
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
	for(int i=1; i<=K; ++i) res+=1.0*sum[i]*sum[i];//Aver可以提出来。。
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
