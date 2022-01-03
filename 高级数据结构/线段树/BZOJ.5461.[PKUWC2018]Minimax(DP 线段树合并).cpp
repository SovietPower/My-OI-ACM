/*
103008kb	4564ms
$Description$
����һ��$n$������и�����$1$Ϊ����ÿ��������������ӽڵ㡣
�����$x$��ȨֵΪ����$x$ΪҶ�ӣ����������и�������������$p_x$�ĸ��������ӽڵ�Ȩֵ�����ֵ����$1-p_x$�ĸ��������ӽڵ�Ȩֵ����Сֵ��
��$1$�ŵ�Ȩֵ��$m$�ֿ��ܣ�����Ȩֵ��$i$С��Ϊ$V_i$�������Ϊ$D_i$����$\sum_{i=1}^miV_iD_i^2$ģ998244353��
$n\leq 3\times 10^5,\ w_i\leq 10^9$��
$Solution$
��$f[i][j]$��ʾ��$i$Ϊ����������Ȩֵ$j$��Ϊ���ڵ�ĸ��ʡ�
��$i$�����������ֱ�Ϊ$x,y$����$p_a$��ʾ$f[x][a]$��$p_a'$��ʾ$f[y][a]$��$P_i$��ʾ������$i$ȡ���ֵ��ΪȨֵ�ĸ��ʡ�
ת�ƾ���������֮���Ȩֵ��ϣ�����$x$�����е�$a$��Ϊ��Сֵ�ĸ���Ϊ$p_a\times\sum\limits_{v>a}p_v'\times(1-P_i)$����$x$�����е�$a$��Ϊ���ֵ�ĸ���Ϊ$p_a\times\sum\limits_{v\leq a}p_v'\times P_i$��
��$s'=\sum\limits_{v>a}p_v'$��$\sum\limits_{v\leq a}p_v'$����$1-s'$�����������������һ�¾���$p_a\times(s'+P_i-2s'\times P_i)$��
����$y$�����е�$a$��Ϊ$i$�ڵ��ֵ�ĸ���ͬ����$p_a'\times(s+P_i-2s\times P_i)$����$f[i][a]$�͵����µ�$p_a,p_a'$�ĺ͡�
ά��һ�º�׺�;���$O(n^2)$���ˡ�

��ʼʱÿ��Ҷ�ڵ�ֻ��һ����ֵ��~~һ��С�Ŀ�������~~�뵽�߶����ϲ��ͺܼ��ˡ�
$s,s'$���ǵ�ǰ����ұ����������е�$\sum p_v$��$\sum p_v'$���ϲ���ʱ���Ⱥϲ����������ۼ�һ������Ҷ�ڵ㴦��$p_v$��$p_v'$�Ϳ��Եõ��ˡ�����Ȼ$s,s'$��ά��������ͺ�Ҳ����ֱ���ø���������ȥ����������2��
��Ȼ����Ҫ����ʵ�Ҷ�Ӵ���ά��һ������͡�
��$x$�����ڵ�ǰ�ڵ���ֵ��$y$���������ڵ�ǰ�ڵ�ʱ��`merge(x,y) x!=0 && y=0`ʱ������Ȼ$y$��$x$��ǰ�ڵ�������Ĺ��׶�ͳ�ƹ��ˣ�Ҳ����$x$��ǰ�ڵ�������ڶ����һ��$s'+P_i-2s'\times P_i$�������������ˣ�����ֱ�Ӵ������˱�ǡ�˳��ά��һ��$x$������$p_v$�ĺ�$sum[x]$��ֱ�ӵõ���������$s$�Ĺ��ף�����ʱ$s$+=$sum[x]$�Ϳ���ͳ�������ӽڵ��$p_v$�ˡ�
`x=0 && y!=0`ʱͬ��
���Ӷ�$O(n\log n)$��
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
			int v=(s1+P-2ll*s1*P%mod+mod)%mod;//ע��+mod�ŵ����� 
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
