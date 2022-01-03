//http://www.cnblogs.com/SovietPower/p/8430058.html
#include<cstdio>
#include<cctype>
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;

int n,q[N];
LL dis[N],cost[N],num,S[N],W[N],f[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline LL X(int j,int k) {return S[j]-S[k];}
inline LL Y(int j,int k) {return f[j]-f[k]+W[j]-W[k];}
inline LL Calc(int i,int p) {return f[p]+dis[i]*(S[i-1]-S[p])-W[i-1]+W[p]+cost[i];}

int main()
{
	n=read();
	for(int a,i=1;i<=n;++i)
	{
		dis[i]=read(), num=read(), cost[i]=read();
		S[i]=S[i-1]+num, W[i]=W[i-1]+dis[i]*num;
	}
	int h=1,t=1; q[1]=0;
	for(int i=1;i<=n;++i)
	{
		while(h<t && Y(q[h+1],q[h])<=dis[i]*X(q[h+1],q[h])) ++h;
		f[i]=Calc(i,q[h]);
		while(h<t && Y(i,q[t])*X(q[t],q[t-1])<Y(q[t],q[t-1])*X(i,q[t])) --t;
		q[++t]=i;
	}
	printf("%lld",f[n]);

	return 0;
}
