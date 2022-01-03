/*
836kb	20ms
���������[BZOJ1202](https://lydsy.com/JudgeOnline/problem.php?id=1202)��һģһ����= =����Ϊȫ����ȹ�ϵ����ʵ��ʮ������Ĳ��Լ���������ô�Ȩ���鼯����
��$fa[x]$��ʾ$x$���ڼ��ϵĸ��ڵ㣬$dis[x]$��ʾ$x$��$fa[x]$��ʵ�ʾ��롣
��ν������ָ������$r+c=k$�����$r-(-c)=k$����$r$��$-c$��$k$������$r\to -c$֮��������Ϊ$k$�ıߣ�ͬʱ��$fa[r]=-c$��
��������һ������$r,c,k$�����$r,c$����ͬһ���Ͼͺϲ�����ϴ�����������ǽ�С���������ڲ��鼯$Find$������˳��ά��һ��$dis$�������������ǣ�ע�������ֵ˳�򣩡�
���$r,c$��ͬһ���ϣ��͸���$dis$����һ�������ľ����Ƿ����$k$��
����$k$�����Ǹ�����ô��Ҳûʲô���⡣���ϻ�=v=��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2005;

int fa[N],dis[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int Find(int x)
{
	if(x==fa[x]) return x;
	int t=fa[x];
	fa[x]=Find(t), dis[x]+=dis[t];//!!!
	return fa[x];
}

int main()
{
	for(int Ts=read(); Ts--; )
	{
		const int n=read(),m=read(),tot=n+m;
		for(int i=1; i<=tot; ++i) fa[i]=i, dis[i]=0;
		bool fg=1;
		for(int u,v,w,K=read(); K--; )
		{
			u=read(),v=read()+n,w=read();
			if(!fg) continue;
			int r1=Find(u),r2=Find(v);
			if(r1!=r2) fa[r1]=r2, dis[r1]=dis[v]+w-dis[u];
			else if(dis[u]-dis[v]!=w) fg=0;
		}
		puts(fg?"Yes":"No");
	}

	return 0;
}
