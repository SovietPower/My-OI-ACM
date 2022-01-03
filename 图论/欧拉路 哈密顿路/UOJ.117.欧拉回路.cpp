/*
$Description$
��ͼ��ŷ����·����һ����ʹÿ����ǡ�ó���һ�Σ�����$t=1$��ͼΪ����ͼ������Ϊ����ͼ��
$n\leq 10^5,\ m\leq 2\times 10^5$��
$Solution$
�����ݡ�����ֱ�� 
���Ի����رߣ���Щ�����û������(���鼯����ʹ ��DFS��) 
��Ϊ�ر�+�Ի����ܷǳ��࣬ͬһ������ܾ���n�Σ����Ա���Ҫ���ñ�ͷH[x](���Ƶ�ǰ���Ż�) 
��������ŷ��**��·**����ŷ��·�����жϲ�Ҫ�� 
����ͼ: ���е������Ϊż��(��Ͳ���Ҫʲô��ȳ���֮����) 
����ͼ: ���е����=����(dgr = indgr-outdgr = 0) 
*/
#include <cstdio>
#include <cctype>
#include <cstdlib>
#define gc() getchar()
const int N=1e5+5,M=2e5+5;

int n,m,dgr[N],Enum,H[N],nxt[M<<1],to[M<<1],ans[M],cnt;
bool vis[M<<1];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
void DFS_u(int x)
{
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[i])
		{
			H[x]=i/*�����ظ���εĵ� ֮ǰ�ı�ֱ������*/, vis[i]=vis[i^1]=1, DFS_u(to[i]),
			ans[++cnt]=i>>1, i&1?ans[cnt]*=-1:0;
			i=H[x];//iΪ���������֮��ı�ͷ 
		}
}
void Undirect()
{
	n=read(),m=read(), Enum=1;
	for(int u,v,i=1; i<=m; ++i)
	{
		u=read(),v=read(),AddEdge(u,v),AddEdge(v,u);
		++dgr[u], ++dgr[v];
	}
	for(int i=1; i<=n; ++i)
		if(dgr[i]&1) {printf("NO"); return;}//���е������Ϊż�� 
	for(int i=1; i<=n; ++i)
		if(dgr[i]) {DFS_u(i); break;}//����һ(��ͼ��ͨ��)�� 
	if(cnt<m) printf("NO");
	else{
		puts("YES");
		for(int i=cnt; i; --i) printf("%d ",ans[i]);
	}
}
void DFS_d(int x)
{
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[i])
			H[x]=i, vis[i]=1, DFS_d(to[i]), ans[++cnt]=i, i=H[x];
}
void Direct()
{
	n=read(),m=read();
	int u=0,v;
	for(int i=1; i<=m; ++i)
	{
		u=read(),v=read(),AddEdge(u,v);
		--dgr[u], ++dgr[v];
	}
	int s=u;
	for(int i=1; i<=n; ++i)
		if(dgr[i]) {printf("NO"); return;}//���е����=���� 
//		if(dgr[i]&1 && ++t>2) {printf("NO"); return;}//WA: ����ŷ��· 
//	for(int i=1; i<=n; ++i)//WA: ���е��Ѿ�������Ϊ0�ˡ���
//		if(dgr[i]) {DFS_d(i); break;}
	DFS_d(s);
	if(cnt<m) printf("NO");
	else{
		puts("YES");
		for(int i=cnt; i; --i) printf("%d ",ans[i]);
	}
}

int main()
{
	int t=read();
	t==1 ? Undirect() : Direct();
	return 0;
}
