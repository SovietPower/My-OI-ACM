/*
287ms	25472KB
$Description$
��������$n$����������ֱ�����$n-1$�����ߺ�$n-1$�������ɵ�������$n-1$�β������ܷ��������ɺ�����
ÿ�β����ǣ�ѡ��ǰ����һ��ֻ��������ɵļ�·��$u\to v$��ɾ��·���ϵ�����һ�����ߣ�Ȼ����·������ѡ�����㣬����������֮���һ����ߡ�
$n\leq10^5$��
$Solution$
ģ��һ�����������ͱȽ������뵽��
�����ܷ�Ӻ�����ص�������
����ÿ��Ҫ�ҵ���ǰ����һ��������ɵ�·��$u\to v$����·��������һ����$a$������·���ϵ�һ������$b$�������ǰ$a,b$֮���к����������$b$��·����ĳ��$c$���������бߣ���Ȼ�������$(a,b)$�ǿ���ͨ��ɾ��$(b,c)$����ģ�Ҳ�������������ڵ�ǰ����ɾ����$(a,b)$�������$(b,c)$��Ȼ�����������·��������չ��
��ôʵ����һ�����أ�
��������������ɵ�·��$u\to v$�����ǲ���Ҫ�ܾ�������Щ�㣬ֻ��Ҫ֪��$b$��$u\to v$֮�����һ����ߣ�Ҳ��һ�����ߣ��������������/���߰�����Ϊÿ�β�����Ҳ��һ��������Ȼ�����ǿ���ɾ��������ߣ������������ߡ��߾���������Ҳ����Ҫ�ܣ�����ֻ��Ҫ֪��$b$��������·��$u\to v$��
���ԾͿ����ò��鼯ʵ�֡�$b$���ϲ���·��$u\to v$ǰ��Ҫ����$b$���������б�����·��$u\to v$���Ĵ���㣩��ȥ������������ʽ�ϲ���
ͬʱ�к�ߺ�������·�����������������߳��������Ρ��������ǰѳ������εı��ó�����չ�ͺ��ˡ�
����չ$n-1$������У������С�
����ʽ�ϲ�Ȼ����setά�����ߣ����Ӷ�$O(n\log^2n)$�����߿���hash���$(u,v)$��ά������һ��$\log$������д�ˡ���
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int fa[N];
std::set<int> st[N];
std::pair<int,int> q[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}

int main()
{
	const int n=read();
	int h=0,t=0;
	for(int i=n-1<<1; i; --i)
	{
		int u=read(),v=read();
//		if(u>v) std::swap(u,v);
		if(!st[u].count(v)) st[u].insert(v), st[v].insert(u);
		else q[t++]=std::make_pair(u,v);
	}
	for(int i=1; i<=n; ++i) fa[i]=i;
	while(h<t)
	{
		int x=Find(q[h].first),y=Find(q[h++].second);
		if(st[x].size()<st[y].size()) std::swap(x,y);//x<-y
		for(std::set<int>::iterator it=st[y].begin(); it!=st[y].end(); ++it)
			if(*it!=x)
			{
				int u=x,v=*it;
				st[v].erase(y);
//				if(u>v) std::swap(u,v);
				if(!st[u].count(v)) st[u].insert(v), st[v].insert(u);
				else q[t++]=std::make_pair(u,v);		
			}
		st[x].erase(y), fa[y]=x;
	}
	puts(t==n-1?"YES":"NO");

	return 0;
}
