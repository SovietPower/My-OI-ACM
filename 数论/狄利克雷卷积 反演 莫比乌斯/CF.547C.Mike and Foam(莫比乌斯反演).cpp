//452ms	6600KB(因为要枚举因数而不是只需要枚举质数 有点慢了)
//https://www.cnblogs.com/SovietPower/p/9297375.html
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5,MAX=5e5+5;

int n,cnt,A[N],P[N],mu[MAX],have[N],num[MAX];
long long Ans;
bool not_P[MAX];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Pre(int n)
{
	mu[1]=1;
	for(int i=2; i<=n; ++i)
	{
		if(!not_P[i]) P[++cnt]=i, mu[i]=-1;
		for(int j=1; j<=cnt&&i*P[j]<=n; ++j)
		{
			not_P[i*P[j]]=1;
			if(i%P[j]) mu[i*P[j]]=-mu[i];
			else {mu[i*P[j]]=0; break;}
		}
	}
}
void Add(int x,int val)
{
	for(int i=1; i*i<=x; ++i)//包括1啊→_→
		if(!(x%i))
		{
			Ans-=1ll*mu[i]*num[i]*(num[i]-1)>>1, num[i]+=val;
			Ans+=1ll*mu[i]*num[i]*(num[i]-1)>>1;
			if(i*i!=x)
			{
				int j=x/i;
				Ans-=1ll*mu[j]*num[j]*(num[j]-1)>>1, num[j]+=val;
				Ans+=1ll*mu[j]*num[j]*(num[j]-1)>>1;
			}
		}
}

int main()
{
	n=read(); int Q=read(),mx=0;
	for(int i=1; i<=n; ++i) mx=std::max(mx,A[i]=read()), have[i]=-1;
	Pre(mx); int x;
	while(Q--)
		have[x=read()]*=-1, Add(A[x],have[x]), printf("%I64d\n",Ans);
	return 0;
}
