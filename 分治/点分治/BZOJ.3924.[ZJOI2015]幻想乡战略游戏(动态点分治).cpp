/*
28972kb	35752ms
$Description$
���ϵ��е�Ȩ����ʼΪ0�������б�Ȩ��ÿ���޸�һ����ĵ�Ȩ����ѯ�ʵ�$x$ʹ$\sum_idis(x,i)*A_i$��С��$dis$ֻ�����Ȩ��
�����޸Ĳ�ѯ���ϴ�Ȩ���ġ�
$n,q\leq 10^5$��
$Solution$
���ɵ���Ρ����ǿ�����ô������xΪ����վ�Ĵ�cost[x].ֱ����cost[]����ά����������������ô�õ���
(���� x�µ�����ָ�����ʱ��xΪ���ķ��ʵ������нڵ㣬����ÿ���ҵ������Ĵ����һ������������е�����)
��v_son[x]��ʾ��xΪ����վ x�µ����������е�Ĺ��ף�v_fa[x]��ʾ��fa[x]Ϊ����վ x�����������е�Ĺ��ף�num[x]��ʾx��������������Щ���Ǻܺö�̬ά���ġ�
��ô�����ݳ⣬���ǿ������fa[x]��Χ�ڵ�cost[x]: cost[x] = v_son[x] + v_son[fa] + num[fa]*dis(x,fa) - v_fa[x] - num[x]*dis(x,fa) (����ͼ�����)
������Ϊ����������ֻ��logn���������ϣ����Ӷ���logn�ġ�
�������ͳ�ƴ𰸣�
��һ����x��ʼ���������������cost[v]С��cost[x]�ĵ㣬��ôһ����v���ţ�������v�������������ĵݹ�(��֤���Ӷ�)��ֱ��û��cost[v]<cost[x]�����cost[x]�������Ž⡣
������Ҫö��x��ԭ���еĶ��ӣ�����ÿ�������������20�������ܸ��Ӷ���O(20nlog^2n) 
˼·���� ȴ�����˰�����硣��
�߶������Ű� �Ժ���˵�� 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int n,Min,root,sz[N],H[N],fa[N],Enum,val[N<<1],to[N<<1],to_r[N<<1],nxt[N<<1],num[N];
int cnt,pos[N],dis[N],log2[N<<1],st[N<<1][18];
LL v_son[N],v_fa[N];
bool vis[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, val[Enum]=w;
}
void Get_root(int x,int f,int tot)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=f&&!vis[v])
		{
			Get_root(v,x,tot), sz[x]+=sz[v]/*©����� �����Ҵ�T��sb����*/;
			if(sz[v]>mx) mx=sz[v];
		}
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void pre_DFS(int x,int f)
{
//	int t=++tm; st[++cnt][0]=t, pos[x]=cnt, id[t]=x;
	st[++cnt][0]=dis[x]/*��ȨΪ���Ļ�����ֱ����dis[]*/, pos[x]=cnt;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f) dis[to[i]]=dis[x]+val[i], pre_DFS(to[i],x),st[++cnt][0]=dis[x];
}
void Init_RMQ()
{
	for(int i=2; i<=cnt; ++i) log2[i]=log2[i>>1]+1;
	for(int j=1; j<=log2[cnt]; ++j)
		for(int i=cnt-(1<<j-1); i; --i)
			st[i][j]=std::min(st[i][j-1],st[i+(1<<j-1)][j-1]);
}
int LCA_dis(int l,int r)
{
	l=pos[l], r=pos[r];
	if(l>r) std::swap(l,r);
	int k=log2[r-l+1];
	return std::min(st[l][k],st[r-(1<<k)+1][k]);
}
inline int Get_dis(int x,int y){
	return dis[x]+dis[y]-2*LCA_dis(x,y);
}
void Solve(int x)
{
	vis[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]])//��ʼΪ0�淽�� ��������DFS�� 
			Min=N, Get_root(to[i],x,sz[to[i]]), to_r[i]=root, fa[root]=x, Solve(root);
}
LL Calc(int x)
{
	LL res=v_son[x];
	for(int i=x; fa[i]; i=fa[i])
		res+=v_son[fa[i]]-v_fa[i]+1ll*(num[fa[i]]-num[i])*Get_dis(x,fa[i]);
	return res;
}
LL Query(int x)
{
	LL res;int bef;
	while(1)
	{
		res=Calc(x), bef=x;
		for(int i=H[x]; i; i=nxt[i])//һ����to[i]��������ϣ����÷�����ʹ�õݹ�������� 
			if(Calc(to[i])<res) {x=to_r[i]; break;}//�ⲻ��Ҫ�ݴ�Calc() 
		if(x==bef) return res;
	}
}

int main()
{
	n=read();int q=read(),x,e;
	for(int u,v,w,i=1; i<n; ++i) u=read(),v=read(),w=read(),AddEdge(u,v,w);
	Min=N, Get_root(1,-1,n);
	int rt=root;
	pre_DFS(root,-1), Init_RMQ(), Solve(root);
	while(q--)
	{
		x=read(),e=read(),num[x]+=e;
		for(int i=fa[x]; i; i=fa[i]) v_son[i]+=1ll*e*Get_dis(x,i), num[i]+=e;
		for(int i=x; fa[i]; i=fa[i]) v_fa[i]+=1ll*e*Get_dis(x,fa[i]);
		printf("%lld\n",Query(rt));
	}
	return 0;
}
