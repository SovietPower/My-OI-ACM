/*
http://www.spoj.com/problems/VLATTICE/
���⣺��һ��n*n*n�ľ��壬�ж��ٵ������(0,0,0)������ֱ�ӿ����� 
ͬBZOJ.2301 
��Ŀ��Ҫ��gcd(i,j,k)=1��(i,j,k)���Ը�����1<=i,j,k<=n 
���������壬�������������ƽ��ĵ���������ϵ������������ 
*/
#include<cstdio>
#include<cctype>
#define gc() getchar()
typedef long long LL;
const int N=1e6+3;

int P[N+3],cnt,mu[N+3],sum[N+3];
bool Not_P[N+3];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Init()
{
	mu[1]=1;
	for(int i=2;i<N;++i)
	{
		if(!Not_P[i]) P[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*P[j]<N;++j)
		{
			Not_P[i*P[j]]=1;
			if(!(i%P[j])) {mu[i*P[j]]=0; break;}
			mu[i*P[j]]=-mu[i];
		}
	}
	for(int i=1;i<N;++i) sum[i]=sum[i-1]+mu[i];
}

int main()
{
	Init();
	int t=read(),n;
	while(t--)
	{
		n=read();
		LL ans=3;//�������ϵ������� 
		for(int nxt,i=1;i<=n;i=nxt+1)
			nxt=n/(n/i), ans+=1LL*(sum[nxt]-sum[i-1])*(n/i)*(n/i)*(n/i+3);//����ռ��ڵĺ�����ƽ��� 
		printf("%lld\n",ans);
	}
	return 0;
}
