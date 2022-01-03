/*
模拟退火！每次随机一个位置加给sum[]最小的组。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define D (0.99)//0.99
#define eps (1e-4)
#define Rand(x) (rand()%x+1)
const int N=22;

int n,K,A[N],sum[7],bel[N];
double Ans=1e14,Aver,Tmp;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline double Squ(double x){
	return x*x;
}
inline void Move(int fr,int to,int tar){
	sum[fr]-=A[tar], sum[bel[tar]=to]+=A[tar];
}
inline void Update(double &x){
	x=0.0; for(int i=1; i<=K; ++i) x+=Squ(sum[i]);
}

void SA()
{
	memset(sum,0,sizeof sum);
	for(int i=1; i<=n; ++i) sum[bel[i]=Rand(K)]+=A[i];
	double ans=0,nxt;
	for(int i=1; i<=K; ++i) ans+=Squ(sum[i]);
	Ans=std::min(Ans,ans+Tmp);
	for(double T=1e6/*big enough*/; T>eps; T*=D)//Times:
	{
		int tar=Rand(n), fr=bel[tar], to=std::min_element(sum+1,sum+1+K)-sum;
//		nxt=ans-Squ(sum[fr])-Squ(sum[to]);
		Move(fr,to,tar);
//		nxt+=Squ(sum[fr])+Squ(sum[to]);
		Update(nxt);
		if(nxt<ans||(exp((ans-nxt)/T)*RAND_MAX>rand())) ans=nxt;//!
		else Move(to,fr,tar);
		Ans=std::min(Ans,ans+Tmp);//这个放里头！
	}
}

int main()
{
	n=read(),K=read();
	int sum=0;
	for(int i=1; i<=n; ++i) sum+=(A[i]=read());
	Aver=1.0*sum/K, Tmp=K*Aver*Aver-2.0*sum*Aver;

//	std::random_shuffle(A+1,A+1+n);
	for(int i=1; i<=3; ++i) SA();
	printf("%.2lf",sqrt(Ans/(double)K));

	return 0;
}
