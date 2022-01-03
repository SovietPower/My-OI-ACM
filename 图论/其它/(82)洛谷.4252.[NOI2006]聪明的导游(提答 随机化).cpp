/*
����һ���㿪ʼDFS��ÿ�δ�֮ǰ�õ���f[i]�����ӽڵ㿪ʼDFS��f[i]Ϊ��i��ʼ(֮ǰ)�ܵõ������𰸡�
Ҫע�����f[i]Ӧ���л���Ӹ�С�Ĵ𰸸��£�
9.10��ֱ����
����д��n�ˡ���
*/
#include <ctime>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=10005,M=2e4+5;

int n,m,Max,pos,A[N],Enum,H[N],nxt[M],to[M],f[N];
bool vis[N];
std::vector<int> ans,tmp,ANS;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x)
{
	vis[x]=1, tmp.push_back(x);
	int way=0;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]&&f[way]<f[to[i]]) way=to[i];
	if(way) DFS(way);
}
void Solve()
{
	memset(f,0,sizeof f);
	for(int t=500; t; --t)
		for(int i=1; i<=n; ++i)
		{
			memset(vis,0,sizeof vis), tmp.clear(), DFS(i);
			if(tmp.size()>ans.size()) ans=tmp;
//			if(tmp.size()>f[i])  f[i]=tmp.size();
			if(tmp.size()>f[i]||rand()%15==0)  f[i]=tmp.size();
		}
	if(ans.size()>ANS.size()) ANS=ans;
}
namespace Spec
{
	int Max,v,pre[N];

	void DFS(int x,int f,int d)
	{
		if(d>Max) Max=d, v=x;
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=f) pre[to[i]]=x, DFS(to[i],x,d+1);
	}
	void Solve()
	{
		Max=0, DFS(1,1,1);
		int u=v;
		Max=0, DFS(v,v,1);
		printf("%d\n%d\n",Max,v);
		while(v!=u) printf("%d\n",v=pre[v]);
	}
}

int main()
{
//	freopen("guide.in","r",stdin);
//	freopen("guide.out","w",stdout);

	srand(time(NULL));
	n=read(),m=read();
	for(int i=1; i<=m; ++i) AddEdge(read(),read());
//	Spec::Solve(); return 0;//9.10
	for(int T=1; T<=15; ++T) Solve();
	printf("%d\n",ANS.size());
	for(int i=0; i<ANS.size(); ++i) printf("%d\n",ANS[i]);

	return 0;
}
