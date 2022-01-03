/*
5592kb	1028ms
���⣺����Щ��һ�������ƥ���С�
��дһ��ɡ�
����Щ�㲻һ�������ƥ���С�������һ�����ƥ�䣬δƥ��㵱Ȼ��һ�������ƥ���С�
��һ��δƥ���ΪA��������ڱ�A-B���Ҵ���ƥ���B-C����ô����A�滻C����ƥ��߱��A-B�����ƥ��������ı䡣
����C��Ҳ������δƥ������ڵĵ��ƥ��㣬��һ�������ƥ���С�
����DFSһ������ˣ�����ĸ��Ӷ���$O(n+m)$��
�����ƥ���ʱ������������$O(nm)$�𣬾�Ȼ�ܹ�ô��������дһ����������Dinic��$O(sqrt(n)m)$�ɣ�ISAP�أ�����
ISAP��ô����ô==~~����ȻҲ��ǰ15�ɣ�~~��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e4+5,M=2e5+7+N+N/*����*/,INF=2e9;

int S,T,Enum,H[N],nxt[M],fr[M],to[M],cap[M],pre[N],lev[N],lk[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}
bool BFS()
{
	static int q[N];
	for(int i=S; i<T; ++i) lev[i]=T+1;
	int h=0,t=1; q[0]=T,lev[T]=0;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(lev[to[i]]==T+1&&cap[i^1])
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[S]<=T;
}
inline int Augment()
{
	for(int i=T; i!=S; i=fr[pre[i]])
		--cap[pre[i]], ++cap[pre[i]^1];
	return 1;
}
int ISAP()
{
	static int cur[N],num[N];
	if(!BFS()) return 0;
	int res=0,x=S;
	for(int i=S; i<=T; ++i) cur[i]=H[i],++num[lev[i]];
	while(lev[S]<=T)
	{
		if(x==T) res+=Augment(),x=S;
		bool can=0;
		for(int i=cur[x]; i; i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i])
			{
				can=1, cur[x]=i, pre[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=T;
			for(int i=H[x]; i; i=nxt[i])
				if(cap[i]) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1], cur[x]=H[x];
			if(x!=S) x=fr[pre[x]];
		}
	}
	return res;
}
void DFS(int x)
{
	vis[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[lk[to[i]]]) DFS(lk[to[i]]);
}

int main()
{
	int n=read(),m=read(),k=read(); Enum=1, S=0, T=n+m+1;
	for(int i=1; i<=n; ++i) AE(S,i,1);
	for(int i=1; i<=m; ++i) AE(i+n,T,1);
	int beg=Enum;
	for(int u; k--; ) u=read(), AE(u,read()+n,1);

	ISAP();
	for(int i=beg+1; i<=Enum; i+=2)
		if(!cap[i]) lk[fr[i]]=to[i], lk[to[i]]=fr[i];
	vis[0]=1;
	for(int i=1; i<=n+m; ++i) if(!lk[i]&&!vis[i]) DFS(i);
	for(int i=1; i<=n; ++i) if(!vis[i]) printf("%d\n",i);
	for(int i=1; i<=m; ++i) if(!vis[i+n]) printf("%d\n",i);

	return 0;
}
