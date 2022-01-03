/*
78MS	9920Kb
$Description$
��һ��$n$���������ÿ���������$a_i$�ͼ�ֵ$b_i$�����������ֱ�Ϊ$1\sim m$ʱѡ��һ������ֵ�����������ڽڵ㲻��ͬʱѡ���ķ�������
$n\leq 50,m\leq 5000$��
$Solution$
�����ȿ�����򵥵ģ�$f[i][j][0/1]$��ʾ��ǰΪ��$i$����ѡ$j$�����ѡ/��ѡ$i$�ķ����������ϱ������Ӷ�$O(nm^2)$��
������DFS���Ż����α������������� DFS���$i$��$i+1$ʱ�������$A_i$�����������ߺܶಽ��$x$��Ȼ�������µ�$A_{i+1}$��������Ҫ��¼$x$��״̬����֪��$fa[A_{i+1}]$ѡûѡ��ͬ��DPʱҪ��һ���㵽���ڵ�·�������е��״̬��״̬���ͳ���$2^n$��
�Ż��ǣ��������ʷ�����DFS����DFS����������ض��ӡ�����$i$��$i+1$��Ҫ������ʱ��������$i$���ڵ�һ������������һ�����$fa[top[A_i]]-top[A_i]$��$i+1$��������������$i+1$����ֻ���$fa[top[A_i]]$��״̬��
ͬ��ֻ���ÿһ�����$u\to v$�ǵ�$u$��״̬��һ��Ҫ�ǵ�ǰ�㵽���ڵ�·����$O(�������)=O(\log n)$�����״̬��״̬��Ϊ$2^{\log n}=n$��
���Ӷ�$O(n^2m)$��
ϸ�ڣ��Ȱ����е�Ҫ�ǵ�����$fa[top[i]]$���������Ϊ$sta$����ת��ʱ����ö��$sta_i$���$sta_{i+1}$��״̬��Ȼ����ö��ѡ��ѡ$i+1$����$s_{i+1}$���ɡ�
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb push_back
typedef long long LL;
const int N=54,M=5004;

int A[N],B[N],fa[N],son[N],sz[N],top[N],Index,dfn[N],Ref[N];
std::vector<int> e[N],sta[N];
struct Node
{
	int val; LL cnt;
	Node(int val=0,LL cnt=0):val(val),cnt(cnt) {}
	Node operator +(const Node &x)const
	{
		return val==x.val?Node(val,cnt+x.cnt):val>x.val?*this:x;
	}
	friend void operator +=(Node &t,const Node &x)
	{
		t.val==x.val?(t.cnt+=x.cnt):t.val<x.val?(t=x,0):0;
	}
}ans[M],f[2][N<<1][M];//ʵ�ʲ���ҪN*2�ռ䣨�����Լ�Ҳ�ϸ�С�ڵ���logn����������û��ǿ�2N 

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v)
{
	e[u].pb(v), e[v].pb(u);
}
void DFS1(int x)
{
	int mx=0; sz[x]=1, son[x]=0/*!*/;
	for(auto v:e[x])
		if(v!=fa[x])
			fa[v]=x, DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
}
void DFS2(int x,int tp)
{
	Ref[dfn[x]=++Index]=x, top[x]=tp;
	for(auto v:e[x])
		if(v!=fa[x] && v!=son[x]) DFS2(v,v);
	if(son[x]) DFS2(son[x],tp);
}
void Clear(int p,int n,int m)
{
	const Node c=Node(0,0);
	for(int i=0; i<=n; ++i)
		for(int j=0; j<=m; ++j) f[p][i][j]=c;
}
void Solve()
{
	static int num[N];

	const int n=read(),m=read();
	for(int i=1; i<=n; ++i) A[i]=read(),B[i]=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS1(1), Index=0, DFS2(1,1);

	for(int i=1; i<=n; ++i)
		for(int x=i; x; sta[i].pb(x),x=fa[top[x]]);
	Clear(0,n*2,m), Clear(1,n*2,m);//����Ҫn*2 

	int now=0,nxt=1;
	f[now][0][0]=Node(0,1), f[now][1][A[1]]=Node(B[1],1);
	for(int q=2; q<=n; ++q,std::swap(now,nxt))
	{
		int x=Ref[q],y=Ref[q-1];
		int limx=(1<<sta[x].size())-1,limy=(1<<sta[y].size())-1;
		Clear(nxt,limx,m);

		int cnt=0;
		for(auto p:sta[x]) num[p]=cnt++;//�ⲻ��O(n)������Ϊɶ��Ҫn^2 

		int fa=-1,tmp=::fa[x];
		for(auto p:sta[y]) if(++fa,p==tmp) break;//fa[x]��sta[y]�� 

		for(int s=0; s<=limy; ++s)
		{
			int ss=0,i=0;
			for(auto v:sta[y])
			{
				if(s>>i&1 && num[v]) ss|=(1<<num[v]);
				++i;
			}
			for(int i=0; i<=m; ++i) // ע��sta[x][0]=x
				if(f[now][s][i].cnt)
				{
					f[nxt][ss][i]+=f[now][s][i];
					if(!(s>>fa&1) && i+A[x]<=m)
						f[nxt][ss|1][i+A[x]]+=Node(f[now][s][i].val+B[x],f[now][s][i].cnt);
				}
		}
		for(auto p:sta[x]) num[p]=0;
	}

	const Node c=Node(0,0);
	for(int i=1; i<=m; ++i) ans[i]=c;
	for(int s=0,lim=1<<sta[Ref[n]].size(); s<lim; ++s)
		for(int i=1; i<=m; ++i)
			ans[i]=ans[i]+f[now][s][i];
	for(int i=1; i<=m; ++i) printf("%lld%c",ans[i].cnt," \n"[i==m]);

	for(int i=1; i<=n; ++i) std::vector<int>().swap(e[i]);
	for(int i=1; i<=n; ++i) std::vector<int>().swap(sta[i]);
}

int main()
{
	for(int T=read(),t=1; t<=T; printf("Case %d:\n",t++),Solve());
	return 0;
}
