/*
���ȿ������� ���˵��Ŷ�$\le K$�ıߣ���$1\sim K$��������ͼ��������������������ǹ���һ������
�����ʣ��ģ���һ����$>K$�ģ�һ�����У�ʹ$u,v$($u,v\le K$)��ͨ����ôֱ�Ӷϵ�����$u,v$·���ϵ�һ���ߣ���Ȼ����ȶϵ�$K+1\sim n$��ʹ$u,v$��ͨ��·��������߿�����Ҫ�ϵ��ܶ�ߣ���
��չһ�£�������Ӧ���ǿ�����һ����$\le K$�����бߣ���Щ��Ҫ��һ������Ȼ��ʣ��$n-K$�����������ͼ�ı�������ӵģ������Ȱ����Ǻϲ����ٶ�ǰ�ߺϲ������ǰ�߳��ֻ�������Ҫ�ϵ����ϵ�һ���ߡ��ò��鼯���ɡ�
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb push_back
typedef long long LL;
const int N=1e6+5;

int fa[N];
struct Edge
{
	int u,v;
}e[N<<1];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}

int main()
{
	int n=read(),m=read(),K=read();
	for(int i=1; i<=n; ++i) fa[i]=i;
	int ans=0;
	for(int i=1; i<=m; ++i) e[i]=(Edge){read(),read()};
	for(int i=1; i<=m; ++i)
		if(e[i].u>K && e[i].v>K) fa[Find(e[i].u)]=Find(e[i].v);
	for(int i=1; i<=m; ++i)
		if(e[i].u<=K||e[i].v<=K)
		{
			int u=Find(e[i].u),v=Find(e[i].v);
			if(u==v) ++ans;
			else fa[v]=u;
		}
	printf("%d\n",ans);

	return 0;
}
