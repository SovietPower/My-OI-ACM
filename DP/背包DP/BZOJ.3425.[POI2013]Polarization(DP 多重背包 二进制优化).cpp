/*
13704kb	3020ms(13572kb	3216ms)
����һ�����������߸ĳ�����ߣ�����ͨ�ĵ�Ը����������Сֵ�������ͨ��Ҫôa�ܵ���b��Ҫôb�ܵ���a(n<=250000)��
��С�ɵ���������Ȼ�ǰ�һ��·���ϵı߲��Ϸ���Ҳ���Ǻڰ�Ⱦɫ���ɺڵ�ָ��׵㡣�����𰸾���$n-1$��
���ɵ��������������뵽��һ����$a$��Ȼ����������Ϊ������$x,y$��$x$�������б�ȫָ��$a$��$a$��$y$����֮��ı�ȫָ��$y$�������𰸾���$sz[x]\times sz[y]$��Ҫ��$sz[x],sz[y]$������ȡ������ľͺ��ˡ�
Ȼ��DP���󻮷�����������������С�ֱ�Ϊ$x$��$n-1-x$�Ƿ���С�
$f[i]$��ʾһ��������$sz$��Ϊ$i$�Ƿ���С�ת�ƾ��Ǹ������Ա�����������$bitset$�Ż���$\frac{n^2}{w}$�������ǲ�����
����$size\geq\sqrt{n}$����������಻�ᳬ��$\sqrt{n}$��������ֱ�ӱ���ת�ơ�
����$size<\sqrt{n}$������������$size$�����ر�����������ֱ�Ӷ����Ʋ�֡�
���Ӷ�Ϊ$O(\frac{n\sqrt{n}\log n}{w})$��
ע�⵽$\sum sz[i]=n$������$sz[i]$�����$O(\sqrt{n})$�֣�$1+2+...+\sqrt{n}\approx n$����������һ����$O(\sqrt{n})$����Ʒ�Ķ��ر������ö����Ʋ����$O(\sqrt{n}\log n)$����Ʒ��
�������Ż�����С������һ����Ʒ$x$���ֳ������Σ��Ͱ������ϲ���һ����$2x$��������Ʒ��������$O(\sqrt{n})$�ˡ�
���Ը��Ӷ�Ϊ$O(\frac{n\sqrt{n}}{w})$������Ȼʵ�ʱ��������������һ���==��
�����ڵ��������$\sqrt{n}$ʱ�����ö�����https://blog.csdn.net/neither_nor/article/details/52725690��~~���忴�˿�15������û����������� ��ϸ����~~
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=250005;

int n,Enum,H[N],nxt[N<<1],to[N<<1],sz[N],root,Max,cnt[N];
std::bitset<N> f;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void Get_root(int x,int f)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=f)
		{
			Get_root(v,x), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v];
		}
	mx=std::max(mx,n-sz[x]);
	if(mx<Max) Max=mx, root=x;
}
void DFS(int x,int f)
{
	sz[x]=1;//����һ��sz�� ��ʲô�� 
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=f) DFS(v,x), sz[x]+=sz[v];
}

int main()
{
	n=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	Max=1e9, Get_root(1,1), DFS(root,0);

//	f[0]=1;//O(n*sqrt(n)/w)
//	for(int i=H[root]; i; i=nxt[i]) ++cnt[sz[to[i]]];
//	for(int i=1; i<=n; ++i)
//		if(cnt[i]>2) cnt[i<<1]+=(cnt[i]-1)>>1, cnt[i]=1+!(cnt[i]&1);
//	for(int i=1; i<=n; ++i)
//		while(cnt[i]--) f|=f<<i;

	f[0]=1; const int lim=sqrt(n);//O(n*sqrt(n)*logn/w)
	for(int i=H[root]; i; i=nxt[i])
		if(sz[to[i]]<lim) ++cnt[sz[to[i]]];
		else f|=f<<sz[to[i]];
	for(int i=1; i<lim; ++i)
		for(int j=cnt[i],k=1; j; j-=k,k<<=1)
			if(j>k) f|=f<<i*k;
			else {f|=f<<i*j; break;}

	LL ans=0;
	for(int i=1; i<n; ++i) if(f[i]) ans=std::max(ans,1ll*i*(n-1-i));
	for(int i=1; i<=n; ++i) ans+=sz[i];
	printf("%d %lld\n",n-1,ans-n);

	return 0;
}
