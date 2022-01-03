/*
343ms	40100KB
Ҫ��֤�𰸼����е�ÿ���㵽�����ڵ������������k�������򲻺ø��£����ǵ���
��������бߺ�ɾ����������k�ĵ㣬ÿ�ɹ�ɾһ���㣬������ڽӵ�Ҳ�ڴ𰸼����У����������һ�ٳ���ɾ��Ȼ��ɾ�����ڽӵ�...
�ڽӵ㵱ȻҪ��set�档�����Ӷ�$O(n\log n)$��
�� ����zz����
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

int n,m,K,Enum,H[N],to[N<<1],nxt[N<<1],dgr[N],Ans[N];
bool del[N];
std::set<int> ans,E[N];
std::pair<int,int> e[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int i)
{
	E[u].insert(v), E[v].insert(u);
	e[i]=std::make_pair(u,v), ++dgr[u], ++dgr[v];
}
void Delete(int x)
{
	del[x]=1, ans.erase(x);
	int v;
	for(std::set<int>::iterator it=E[x].begin(); it!=E[x].end(); ++it)
		if(!del[v=*it] && --dgr[v]<K) Delete(v);
}

int main()
{
	n=read(), m=read(), K=read();
	for(int i=1; i<=m; ++i) AddEdge(read(),read(),i);
	for(int i=1; i<=n; ++i) ans.insert(i);
	for(int i=1; i<=n; ++i) if(!del[i]/*!!*/&&dgr[i]<K) Delete(i);
	for(int i=m,u,v; i; --i)
	{
		Ans[i]=ans.size(), u=e[i].first, v=e[i].second;
		if(!del[u]&&!del[v])//��û��ɾ�����߲Ŵ��� 
		{
			if(--dgr[u]<K) Delete(u);
			else if(--dgr[v]<K) ++dgr[u]/*����pre���ظ�ɾ*/, Delete(v);
//			if(--dgr[u]<K) Delete(u,v);
//			if(--dgr[v]<K && !del[v]/*!!*/) Delete(v,u);
		}
		E[u].erase(v), E[v].erase(u);
	}
	for(int i=1; i<=m; ++i) printf("%d\n",Ans[i]);

	return 0;
}
