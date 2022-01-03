/*
904kb	48ms
$Description$
��һ��$n\times m$�ľ��󣬳�ʼʱÿ��λ��ȨֵΪ$0$����ִ�����ֲ�����1. ʹĳ������λ�ü�1���1��2. ʹĳ������λ�ü�1���1��
����$k$������$(x,y,c)$����ʾ$(x,y)$λ�ò�������ֵ��Ϊ$c$�����Ƿ��������ɴβ����󣬾�����������������
$n,m,k\leq 1000$��
$Solution$
��$r_i$Ϊ��$i$��������˶��ٵ�Ȩֵ��$c_i$Ϊ��$i$��������˶���Ȩֵ����ô����$(i,j),k$����$r_i+c_j=k$��~~�Ҿ�Ȼ������������~~
����ǲ��Լ�������ˡ�$r_i+c_j=k\Rightarrow r_i-(-c_j)\leq k\ \&\&\ -c_j-r_i\leq -k$��
~~ע����ʽ��$x_j-x_i\leq w$=v=~~
���������·�и������ɡ�
ȥ��ȸ�ϰ��ǰ�İ��ӣ�����дDFS=-=��������DFS�и����������ˣ�~~̫�������ñ�DFS�Ĵ����ǡ�~~
�Թ�дBFS��
**��Ȩ���鼯��**
���������[BZOJ1202](https://lydsy.com/JudgeOnline/problem.php?id=1202)��һģһ����= =����Ϊȫ����ȹ�ϵ����ʵ��ʮ������Ĳ��Լ���������ô�Ȩ���鼯����
��$fa[x]$��ʾ$x$���ڼ��ϵĸ��ڵ㣬$dis[x]$��ʾ$x$��$fa[x]$��ʵ�ʾ��롣
��ν������ָ������$r+c=k$�����$r-(-c)=k$����$r$��$-c$��$k$������$r\to -c$֮��������Ϊ$k$�ıߣ�ͬʱ��$fa[r]=-c$��
��������һ������$r,c,k$�����$r,c$����ͬһ���Ͼͺϲ�����ϴ�����������ǽ�С���������ڲ��鼯$Find$������˳��ά��һ��$dis$�������������ǣ�ע�������ֵ˳�򣩡�
���$r,c$��ͬһ���ϣ��͸���$dis$����һ�������ľ����Ƿ����$k$��

����$k$�����Ǹ�����ô��Ҳûʲô���⡣���ϻ�=v=��
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2005;

int Enum,H[N],nxt[N],to[N],len[N],dis[N],dgr[N];
bool vis[N],inq[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
}
bool SPFA(int s,int n)//��ô��ֱ����n���ܵ�����=-= ǿ��֢��ʾ���� 
{
	std::queue<int> q;
	q.push(s), dis[s]=0;
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(dis[v=to[i]]>dis[x]+len[i])
			{
				if(++dgr[v]>n) return 1;
				dis[v]=dis[x]+len[i], !inq[v]&&(q.push(v),inq[v]=1);
			}
	}
	return 0;
}

int main()
{
	for(int Ts=read(); Ts--; )
	{
		int n=read(),m=read(),tot=n+m,cnt=0;
		Enum=0, memset(H,0,tot+1<<2), memset(vis,0,tot+1);
		for(int u,v,w,K=read(); K--; )
		{
			u=read(),v=read()+n,w=read();
			AE(v,u,w), AE(u,v,-w);
			if(!vis[u]) vis[u]=1, ++cnt;
			if(!vis[v]) vis[v]=1, ++cnt;
		}
		memset(dis,0x7f,tot+1<<2), memset(dgr,0,tot+1<<2), memset(inq,0,tot+1);
		bool fg=1;
		for(int i=1; i<=tot; ++i)
			if(vis[i]&&dis[i]==dis[0]&&SPFA(i,cnt)) {fg=0; break;}
		puts(fg?"Yes":"No");
	}

	return 0;
}
