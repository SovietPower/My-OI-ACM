/*
103684kb	2836ms
$Description$
����һ��$n$����Ĵ�Ȩ����������$\frac{n\times(n-1)}{2}$��·���У���������$m$��·���ĳ��ȡ�
$n\leq50000,\ m\leq\min(3\times10^5,\frac{n\times(n-1)}{2})$��
$Solution$
���� ����ο��Դ������������·�� �����ʣ���ÿ�ε���δ�������ʱ�����ǰѵ�ǰ��$root$�ͷ��ʵ��ĵ�$x$���δ浽ͬһ��������Ѵ�������$dis(x,root)$���м���$d_i$��
���ɵ���ε����ʣ������õ������鳤����$O(n\log n)$�ġ�

$x$��$root$�Լ�$root$֮ǰ�����еĵ�$y$�����γ�һ��·����������Щ�㣨$root$��$y$�������������е�λ����һ�����������䣬��Ϊ$[l,r]$��
��ô$dis(x,root)$�ܺ�$d_l,d_{l+1},...,d_r$�е�����һ������ϣ��õ�һ��·����Ϊ$dis(x,root)+d_i$��
��ô����ͱ���ˣ�����һ����Ϊ$n\log n$�������е�ÿ����$i$�������Ժ�ĳ������$[l_i,r_i]$�е���$j$��ϣ��õ�����Ϊ$d_i+d_j$��·��������Ҫѡ�����$m$����

��ô���ء�
���ÿ����$i$�϶��Ǻ�$[l_i,r_i]$��$d_j$����$j$��ϣ�RMQԤ������Ҳ���ǵ�һ���ֵ�϶��Ǵ�����$i$��$[l_i,r_i]$����$j_i$����ϣ�Ȼ��ѡ���ġ�
��������ѡ��$k$��$k$�Ͷ�Ӧ��$j_k$������$i$��$d_i+d_j$���ģ���Ȼ��֮��$k$ֻ�ܺ�$[l_k,j)\bigcup(j,r_k]$��Щ����ϡ�
���ڶ����ֵҪô�Ǵ���������Щ$(i,j_i)$��ѡ��Ҫô����$k$��$[l_k,j)\bigcup(j,r_k]$�е�����ϡ�
���������öѵõ�$k$������$k$�ֱ��$[l_k,j)$����������ϡ�$(j,r_k]$����������ϣ����ӵ�����ͺ��ˡ�
���Ӷ�$O((n\log n+m)\log(n\log n))$��

ps��**ps��**~~����������$n$��û����ô������ST���һ��ά˳��Ӱ�첻��~~�� ��������BZOJ�ϣ�Ӱ��ܴ�~~����~~��������͸������ˡ�����7252ms$\to$2896ms��
���̰�Ļ�������[�ɳ־û��ɲ���]д����
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=50005,M=N*16;

int Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1],Min,root,sz[N],tot,d[M],L[M],R[M],Ln,Rn,Log[M],pos[20][M];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int val,di,l,r;
	bool operator <(const Node &a)const
	{
		return val<a.val;
	}
};
std::priority_queue<Node> q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int w,int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
inline int Max(int x,int y)
{
	return d[x]>d[y]?x:y;
}
inline int Query(int l,int r)
{
	int k=Log[r-l+1];
	return Max(pos[k][l],pos[k][r-(1<<k)+1]);
}
void FindRoot(int x,int fa,int tot)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]] && v!=fa)
			FindRoot(v,x,tot), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v]);
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void Calc(int x,int fa,int dep)
{
	d[++tot]=dep, L[tot]=Ln, R[tot]=Rn;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]] && v!=fa) Calc(v,x,dep+len[i]);
}
void Solve(int x)
{
	vis[x]=1, d[++tot]=0, L[tot]=1, R[tot]=0, Ln=Rn=tot;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]) Calc(to[i],x,len[i]), Rn=tot;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]) Min=N, FindRoot(to[i],x,sz[to[i]]), Solve(root);
}

int main()
{
	const int n=read(),m=read();
	for(int i=1; i<n; ++i) AE(read(),read(),read());
	Min=N, FindRoot(1,1,n), Solve(root);

	pos[0][1]=1;
	for(int i=2; i<=tot; ++i) Log[i]=Log[i>>1]+1, pos[0][i]=i;
	for(int j=1; j<=Log[tot]; ++j)//д�� j<=Log[n],i=n-t�����ܹ����˵�6����������е�= =��
		for(int t=1<<j-1,i=tot-t; i; --i)
			pos[j][i]=Max(pos[j-1][i],pos[j-1][i+t]);
	for(int i=1; i<=tot; ++i)
		if(L[i]<=R[i]) q.push((Node){d[i]+d[Query(L[i],R[i])],d[i],L[i],R[i]});

	for(int i=1,p; i<=m; ++i)
	{
		Node tmp=q.top(); q.pop();
		printf("%d\n",tmp.val), p=Query(tmp.l,tmp.r);
		if(tmp.l<p) q.push((Node){tmp.di+d[Query(tmp.l,p-1)],tmp.di,tmp.l,p-1});
		if(p<tmp.r) q.push((Node){tmp.di+d[Query(p+1,tmp.r)],tmp.di,p+1,tmp.r});
	}

	return 0;
}
