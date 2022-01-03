/*
18888KB	3000MS(18892kb	2536ms)
[xxy tql!](https://www.cnblogs.com/TheRoadToTheGold/p/8998774.html)

$d_i$��ͬ�Ͳ���˵�ˣ���������$DFS$һ�顣
����$d_i$��ͬ�������������ΰ���Щ����������
���ȶ����ѽ����Ľڵ�$x$���ѽ�����ָ���ڵ��Ѿ�������ĵ㣬�տ�ʼ����$fa[x]=0$��$x$����Ϊ������Ԥ��$sz[x]$��С��λ�á�
��$d_i$��С������������ö�٣�ÿ��Ҫ������$1,2,...,n$��������о��������λ����$p$��ʾ$Ans_p=d_i$����
����������С������$v$����һ����$k$����ͬ��$v$����������Ҫ�ҵ���ҵ�λ��$p$��$p$����$p\sim n$����������Ϊ$k$��Ȼ����$p$������$v$����ʱһ������$p$��$v$����Ϊ��$p$��Ŀ�λ��ȫ������Ҳ����$k$������Ȼ���$p$λ�õ�$sz[p]$ɾ����"����"$p$�Ķ��ӣ�������$son_p$��Ԥ��$sz[son_p]$�Ĵ�С�����ܲ���֮������ʱ����ŵ�ĳ��$son_p$����
Ȼ��$k$-=$1$���ظ�����Ĺ��̣���һ������...����ҵ�λ��$p$...����ֱ��$k=0$��
��Щ���������߶���ʵ�֡����Ӷ�$O(n\log n)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define eps 1e-9
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

int H[N],nxt[N],sz[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson r=m,rt=ls
	#define rson l=m+1,rt=rs
	#define S N<<2
	int sum[S];
	#undef S
	void Modify(int l,int r,int rt,int p,int v)
	{
		while(l!=r)
		{
			sum[rt]+=v;
			int m=l+r>>1;
			p<=m ? (lson) : (rson);
		}
		sum[rt]+=v;
	}
	int Query(int l,int r,int rt,int k)
	{
		while(l!=r)
		{
			int m=l+r>>1;
			sum[rs]>=k ? (rson) : (k-=sum[rs],lson);
		}
		return l;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline double readdb()
{
	double x=0,y=0.1;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);x=x*10+c-48,c=gc());
	for(c=='.'&&(c=gc());isdigit(c);x+=y*(c-48),y*=0.1,c=gc());
	return x;
}
inline void AE(int u,int v)
{
	nxt[v]=H[u], H[u]=v, sz[u]+=sz[v];
}

int main()
{
	static int A[N],Ans[N];
	const int n=read(); const double K=readdb();
	for(int i=1; i<=n; ++i) A[i]=read(), sz[i]=1;
	std::sort(A+1,A+1+n);
	for(int i=n; i; --i) AE(int(i/K+eps),i);//or floor(i/K) ��������Ҫeps...����...
	for(int v=H[0]; v; v=nxt[v]) T.Modify(1,n,1,v,sz[v]);
	for(int i=1,j=1; i<=n; i=j)
	{
		while(A[i]==A[j]) ++j;
		for(int k=j-i; k; --k)
		{
			int x=T.Query(1,n,1,k);
			Ans[x]=A[i], T.Modify(1,n,1,x,-sz[x]);
			for(int v=H[x]; v; v=nxt[v]) T.Modify(1,n,1,v,sz[v]);
		}
	}
	for(int i=1; i<=n; ++i) printf("%d ",Ans[i]);

	return 0;
}
