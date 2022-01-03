/*
103008kb	4564ms
$Description$
给定一棵$n$个点的有根树，$1$为根，每个点最多有两个子节点。
定义点$x$的权值为：若$x$为叶子，则在输入中给定；否则，其有$p_x$的概率是其子节点权值的最大值，有$1-p_x$的概率是其子节点权值的最小值。
设$1$号点权值有$m$种可能，其中权值第$i$小的为$V_i$，其概率为$D_i$，求$\sum_{i=1}^miV_iD_i^2$模998244353。
$n\leq 3\times 10^5,\ w_i\leq 10^9$。
$Solution$
令$f[i][j]$表示以$i$为根的子树，权值$j$作为根节点的概率。
设$i$的两棵子树分别为$x,y$，记$p_a$表示$f[x][a]$，$p_a'$表示$f[y][a]$，$P_i$表示给定的$i$取最大值作为权值的概率。
转移就是两棵树之间的权值组合，即以$x$子树中的$a$作为最小值的概率为$p_a\times\sum\limits_{v>a}p_v'\times(1-P_i)$，以$x$子树中的$a$作为最大值的概率为$p_a\times\sum\limits_{v\leq a}p_v'\times P_i$。
记$s'=\sum\limits_{v>a}p_v'$，$\sum\limits_{v\leq a}p_v'$就是$1-s'$。上面项加起来化简一下就是$p_a\times(s'+P_i-2s'\times P_i)$。
对于$y$子树中的$a$作为$i$节点的值的概率同理，是$p_a'\times(s+P_i-2s\times P_i)$。那$f[i][a]$就等于新的$p_a,p_a'$的和。
维护一下后缀和就是$O(n^2)$的了。

初始时每个叶节点只有一个初值，~~一不小心看到可以~~想到线段树合并就很简单了。
$s,s'$就是当前点的右边所有子树中的$\sum p_v$和$\sum p_v'$，合并的时候先合并右子树，累加一下所有叶节点处的$p_v$和$p_v'$就可以得到了。（当然$s,s'$在维护了区间和后也可以直接用个参数传下去。。见代码2）
当然不需要真访问到叶子处，维护一个区间和。
当$x$子树在当前节点有值而$y$子树不存在当前节点时（`merge(x,y) x!=0 && y=0`时），显然$y$对$x$当前节点的子树的贡献都统计过了，也就是$x$当前节点的子树内都会乘一个$s'+P_i-2s'\times P_i$，这个数不会变了，所以直接打个区间乘标记。顺便维护一个$x$子树内$p_v$的和$sum[x]$来直接得到该子树对$s$的贡献，即此时$s$+=$sum[x]$就可以统计所有子节点的$p_v$了。
`x=0 && y!=0`时同理。
复杂度$O(n\log n)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define mod 998244353
#define inv 796898467ll//inv(10000)
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=3e5+5;

int root[N],P[N],ref[N],son[N][2];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,l,m
	#define rson rs,m+1,r
	#define S N*19
	int tot,rk,s1,s2,son[S][2],p[S],tag[S];
	LL Ans;
	#undef S
	Segment_Tree() {tag[0]=1;}
	#define Upd(x,v) p[x]=1ll*p[x]*v%mod, tag[x]=1ll*tag[x]*v%mod
	void Insert(int &x,int l,int r,int pos)
	{
		x=++tot, p[x]=tag[x]=1;
		if(l==r) return;
		int m=l+r>>1;
		pos<=m ? Insert(lson,pos) : Insert(rson,pos);
	}
	inline void PushDown(int x)
	{
		int l=ls,r=rs;
		if(l) Upd(l,tag[x]);
		if(r) Upd(r,tag[x]);
		tag[x]=1;
	}
	int Merge(int x,int y,int P)
	{
		if(!x && !y) return 0;
		if(!x)
		{
			Add(s2,p[y]);
			int v=(s1+P-2ll*s1*P%mod+mod)%mod;//注意+mod放到后面 
			Upd(y,v);
			return y;
		}
		if(!y)
		{
			Add(s1,p[x]);
			int v=(s2+P-2ll*s2*P%mod+mod)%mod;
			Upd(x,v);
			return x;
		}
		if(tag[x]!=1) PushDown(x);
		if(tag[y]!=1) PushDown(y);
		rs=Merge(rs,son[y][1],P), ls=Merge(ls,son[y][0],P);
		p[x]=p[ls]+p[rs], Mod(p[x]);
		return x;
	}
	void GetAns(int x,int l,int r)
	{
		if(!p[x]) return;
		if(l==r)
		{
			Ans+=1ll*(++rk)*ref[l]%mod*p[x]%mod*p[x]%mod;//++rk=l
			return;
		}
		if(tag[x]!=1) PushDown(x);//...
		int m=l+r>>1;
		GetAns(lson), GetAns(rson);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void DFS(int x)
{
	if(son[x][1])
	{
		DFS(son[x][0]), DFS(son[x][1]);
		T.s1=0, T.s2=0, root[x]=T.Merge(root[son[x][0]],root[son[x][1]],P[x]);
	}
	else if(son[x][0]) DFS(son[x][0]), root[x]=root[son[x][0]];
}

int main()
{
	static std::pair<int,int> A[N];
	const int n=read();
	for(int i=1,x; i<=n; ++i) x=read(), son[x][0]?son[x][1]=i:son[x][0]=i;
	int cnt=0;
	for(int i=1; i<=n; ++i)
		if(son[i][0]) P[i]=inv*read()%mod;
		else A[++cnt]=std::make_pair(read(),i);
	std::sort(A+1,A+1+cnt);
	for(int i=1; i<=cnt; ++i) ref[i]=A[i].first, T.Insert(root[A[i].second],1,cnt,i);
	DFS(1), T.GetAns(root[1],1,cnt), printf("%lld\n",T.Ans%mod);

	return 0;
}
