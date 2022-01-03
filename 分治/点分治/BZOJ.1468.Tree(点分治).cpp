/*
2524kb	656ms
����: �������Ͼ���<=K�ĵ���� 
����֪������һ��·��Ҫô�������ڵ㣬Ҫô��ͬһ�������С�
���Ƕ�һ����x���ǿ�������ͳ��: ��������е㵽���ľ���dep[]����������O(n)���<=K�ĵ��������
������ͼ�����ǿ��Է��֣�������ͬһ�������е�·�����ظ�������ˡ���������Ans-=Calc(v)����ȥһ�������е�·���𰸣������Ⲣ����֮ǰx�����ǵ�·�������Ǹ�v��dep[]��һ����ʼֵΪw(x->v·��Ȩֵ)��
����x�Ĵ𰸾ͼ������ˣ�����һ���̼���Solve(x)��
������μ������е㡣DFS��Ч���Ǻ������йصġ�����x->vʱ������ѡȡv�����ϵ�������Ϊ�´�Solve()�Ĳ�����
ѡȡ����ÿ�ζ���ʹ���Ľڵ�������룬��˵ݹ�����(��)��logn�ġ�
�������O(nlog^2n)������⡣
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=40005,MAXIN=1e5;

int n,K,root,Min,Ans,Enum,H[N],nxt[N<<1],to[N<<1],val[N<<1],dep[N],sz[N],D[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, val[Enum]=w;	
}
void Get_Root(int x,int f,int tot)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!vis[to[i]] && to[i]!=f)
		{
			Get_Root(v=to[i],x,tot), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v];
		}
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void DFS(int x,int f)
{
	D[++D[0]]=dep[x];
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]&&to[i]!=f)
			dep[to[i]]=dep[x]+val[i], DFS(to[i],x);
}
int Calc(int x,int v)
{
	D[0]=0, dep[x]=v, DFS(x,-1);
	std::sort(D+1,D+1+D[0]);
	int l=1,r=D[0],res=0;
	while(l<r)
		if(D[l]+D[r]<=K) res+=r-l,++l;
		else --r;
	return res;
}
void Solve(int x)
{
	Ans+=Calc(x,0), vis[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!vis[to[i]])
		{
			Ans-=Calc(v=to[i],val[i]);
			Min=N, Get_Root(v,x,sz[v]), Solve(root);
		}
}

int main()
{
	n=read();
	for(int u,v,w,i=1; i<n; ++i) u=read(),v=read(),w=read(),AddEdge(u,v,w);
	K=read();
	Min=N, Get_Root(1,-1,n), Solve(root);
	printf("%d",Ans);

	return 0;
}
