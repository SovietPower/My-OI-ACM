/*
9068kb	10588ms
��Ŀ�����Ƽ�������һ������ֻ����ѡһ����ͨ��Ȼ������������ÿ�����ϵ���Ʒ����ȡһ�����󻨷�Ϊ$m$ʱ����ֵ��
��$f[i][j]$��ʾ�ڵ�$i$���������Ϊ$j$������ֵ��
�����Ʒ����Ϊ$1$���Ǿ���һ����������������ѡ���ӱ���ѡ���ף�����DFS���Ż�ת�ƣ�$f[i][j]=\max(f[i+1][j-v_i]+w_i,\ f[i+sz_i][j])$��ѡ�ýڵ�Ϳ��Դ���һ���㣬��������ת�ƣ�����ֻ�ܴ���һ������ת�ƣ������Ӷ�$O(nm)$��
��Ʒ������Ϊ$1$��$\max$��ǰ�벿������һ��[���������Ż����ر���]�����ˡ������Ӷ�Ҳ��$O(nm)$����ע��������ϵ����ǰ�ڵ�����ȡһ������һ��ת��λ�ü��ɣ�

Ȼ�����ö��ÿ����������ת�ƣ����Ӷ���$O(n^2m)$�ġ�
ö��������ͨ�飬�����׸�����Σ�����$dsu\ on\ tree$�������ض��ӵ�DP���顣����д$dsu$�ˣ���ò�Ƴ����ȵ����С�ܶ࣡��
Ȼ�����$O(nm\log n)$�ˡ�

����������Ϊ�������⣬�������������±ȸ��Ӷ�$O(nm\log num)$�Ķ������Ż����ر�����һЩ����
����������$num$��$100$��������������Ӱ��Ҳ������...�������ⵥ�����о������ܶ�ܶ��ˣ�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=505,M=4005;

int n,m,Ans,W[N],V[N],num[N],Enum,H[N],nxt[N<<1],to[N<<1],Min,root,sz[N],cnt,A[N],f[N][M];
bool vis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
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
void MultiplePack(int *f,int *g,int val,int v,int num)
{
	static int qn[M],qv[M];
	const int m=::m;
	for(int r=0; r<v; ++r)//����r 
		for(int now=r,k=0,h=1,t=0; now<=m; now+=v,++k)
		{
			if(qn[h]+num<k) ++h;
			if(h<=t) f[now]=std::max(f[now],qv[h]+k*val);//h<tʱת�� �Ϳ��Ա�֤ǿ������ѡһ���˰� 
			int tmp=g[now]-k*val;//������f[now]����g[now]���¶�β�� Ҫ�������ŵĻ�������� 
			while(h<=t && qv[t]<=tmp) --t;
			qv[++t]=tmp, qn[t]=k;
		}
}
void DP(const int cnt)
{
	for(int i=cnt; i; --i)
	{
		int x=A[i];
		for(int j=1,s=sz[x]; j<=m; ++j) f[i][j]=f[i+s][j];
		MultiplePack(f[i],f[i+1],W[x],V[x],num[x]);
	}
	for(int i=1; i<=m; ++i) Ans=std::max(Ans,f[1][i]);
	for(int i=1,s=m+1<<2; i<=cnt; ++i) memset(f[i],0,s);
}
void DFS(int x,int fa)
{
	sz[x]=1, A[++cnt]=x;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]] && v!=fa) DFS(v,x), sz[x]+=sz[v];
}
void Solve(int x)
{
	vis[x]=1, cnt=0, DFS(x,0), DP(cnt);
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]) Min=N, FindRoot(to[i],x,sz[to[i]]), Solve(root);
}

int main()
{
	for(int T=read(); T--; )
	{
		n=read(),m=read();
		for(int i=1; i<=n; ++i) W[i]=read();
		for(int i=1; i<=n; ++i) V[i]=read();
		for(int i=1; i<=n; ++i) num[i]=read();
		for(int i=1; i<n; ++i) AE(read(),read());
		Ans=0, Min=N, FindRoot(1,1,n), Solve(root);
		printf("%d\n",Ans);
		Enum=0, memset(H,0,n+1<<2), memset(vis,0,n+1);//bool!
	}
	return 0;
}
