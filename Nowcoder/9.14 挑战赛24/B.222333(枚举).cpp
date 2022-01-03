/*
求m+n最小的m,n满足：2^m*3^n=1(mod p)
3^n逆元乘过去，得到2^m=(3^{P-2})^n(mod p)
预处理左边，再枚举右边。当然预处理到p就够了(0~p-1)。
*/
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=1e7+4;

int P,pos[N],vis[N];

inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%P)
		if(k&1) t=1ll*t*x%P;
	return t;
}

int main()
{
	int Time=0;
	while(~scanf("%d",&P))
	{
		++Time;
		int inv3=FP(3,P-2),inv;
		vis[inv=inv3]=Time, pos[inv3]=1;
		for(int i=2; i<=P; ++i)
		{
			inv=1ll*inv*inv3%P;
			if(vis[inv]!=Time) vis[inv]=Time, pos[inv]=i;
		}
		int a=P+1,b=P+1,pw=2;
		for(int i=1; i<=P; ++i,pw<<=1,pw>=P&&(pw-=P))
			if(vis[pw]==Time && i+pos[pw]<a+b) a=i, b=pos[pw];
		printf("%d %d\n",a,b);
	}

	return 0;
}
