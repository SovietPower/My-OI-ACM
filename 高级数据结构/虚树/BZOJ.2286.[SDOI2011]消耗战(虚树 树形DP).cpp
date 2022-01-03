/*
17428kb	3264ms(fread�����ð�)
����DP������ÿ������Ҫô���ɾ������Ҫɾ���ıߣ�Ҫôֱ�Ӷ����򸸽ڵ�ıߡ�
�����ǰ����Ҫɾ������ôֱ�Ӷϲ���Ҫ�ٹ�������
���Ӷ�O(m*n)��
��������Ҫɾ���ĵ� u,v ֮�������������û��������Ҫɾ�ĵ㣬��ֻ�豣�����ϵ���С��Ȩ���ɡ�
�����õĵ㰴DFS���������ι�����һ���������������������ͬ����DP��
�������ɣ�
���⽨����ʱ������ĳҪɾ����������еĵ㣬�����Ժ��ԣ���Insertʱ��LCA(sk[top],now)=sk[top]����ֱ�Ӻ���now����ջ������Ϊ�տ�ʼջ��һ���Ǹ�Ҫɾ�ĵ㣩
�����Ϳ����ñ�ͷ�Ƿ�Ϊ�����ж��Ƿ�Ҫɾ���õ��ˣ�����Ҫ��ǡ�
���⽨����ʱ����Ҫ��Ȩ��ֱ���õ�Ȩ���ɣ�ȨֵΪ����·������С��Ȩ��
����Ϊ�ǿ�������ô����ʱ�������ɣ�����Ҫ�ñ߱�(Ȼ�����������������)
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 1000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=250005,M=N<<1;

int n,m,K,A[N],Enum,H[N],nxt[M],to[M],len[M],val[N],dfn[N],Index,fa[N],tp[N],sz[N],son[N],dep[N],top,sk[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w){
	to[++Enum]=v, nxt[Enum]=H[u], len[Enum]=w, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], len[Enum]=w, H[v]=Enum;
}
inline void Add_direct(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
inline bool cmp_dfn(const int &a,const int &b){
	return dfn[a]<dfn[b];
}
void DFS1(int x,int mn)
{
	int mx=0; sz[x]=1, val[x]=mn;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v,std::min(mn,len[i])), sz[x]+=sz[v];
			if(mx<sz[v]) mx=sz[v], son[x]=v;
		}
}
void DFS2(int x,int _tp)
{
	dfn[x]=++Index, tp[x]=_tp;
	if(son[x])
	{
		DFS2(son[x],_tp);
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=fa[x]&&to[i]!=son[x]) DFS2(to[i],to[i]);
	}
}
int LCA(int u,int v)
{
	while(tp[u]!=tp[v]) dep[tp[u]]>dep[tp[v]]?u=fa[tp[u]]:v=fa[tp[v]];
	return dep[u]<dep[v]?u:v;
}
void Insert(int p)
{
	if(top==1) {sk[++top]=p; return;}//if(sk[top]==1)
	int lca=LCA(sk[top],p);
	if(lca==sk[top]) return;
//	int las=sk[top];
//	while(lca!=las)
//	{
//		if(dfn[sk[--top]]<dfn[lca])
//		{
//			Add_direct(lca,las), sk[++top]=lca;
//			break;
//		}
//		Add_direct(sk[top],las), las=sk[top];
//	}
	while(dfn[sk[top-1]]>=dfn[lca]) Add_direct(sk[top],sk[top--]);//��������˳��...
	if(lca!=sk[top] && dfn[sk[top-1]]<dfn[lca]) Add_direct(lca,sk[top]), sk[top]=lca;//++top, --top
	sk[++top]=p;
}
LL DP(int x)
{
	if(!H[x]) return val[x];
	LL sum=0;
	for(int i=H[x]; i; i=nxt[i]) sum+=DP(to[i]);
	H[x]=0;
	return std::min((LL)val[x],sum);
}

int main()
{
	n=read();
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v,read());
	DFS1(1,0x7fffffff), DFS2(1,1), Enum=0, memset(H,0,sizeof H);
	m=read();
	while(m--)
	{
		K=read();
		for(int i=1; i<=K; ++i) A[i]=read();
		std::sort(A+1,A+1+K,cmp_dfn);
		sk[top=1]=1;
		for(int i=1; i<=K; ++i) Insert(A[i]);
		while(--top) Add_direct(sk[top],sk[top+1]);

		LL res=0;
		for(int i=H[1]; i; i=nxt[i]) res+=DP(to[i]);//��1Ҫ��������Ҫ��Ӧ��val[1]��Ϊ�ܴ��longlong 
		H[1]=0;
		printf("%lld\n",res);
		Enum=0; //for(int i=1; i<=K; ++i) H[A[i]]=0;
	}
	return 0;
}
