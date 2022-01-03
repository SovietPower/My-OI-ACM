/*
题意:有m个区间，问最少要多少个区间能覆盖[1,n] 
注:区间要按原区间的顺序，不能用排序贪心做 

设dp[i]表示最右端端点为i时的最小值 
dp[e[i]]=min{dp[s[i]]~dp[e[i]-1]}+1
注意修改只需要修改右端点，不需要修改一段 
所以线段树查询区间最小值即可 
*/
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#define gc() getchar()
//#define gc() (TT==SS &&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),TT==SS)?EOF:*SS++)
const int N=5e4+5,MAXIN=1e7,INF=0x3f3f3f3f;

int n,m,f[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Seg_Tree
{
	int tot;
	struct Node
	{
		int l,r,val,ls,rs;
	}node[N<<1];
	inline void PushUp(int rt)
	{
		node[rt].val=std::min(node[node[rt].ls].val,node[node[rt].rs].val);
	}
	void Build(int l,int r)
	{
		int p=tot++;
		node[p].l=l, node[p].r=r;
		if(l==r){ node[p].ls=node[p].rs=-1,node[p].val=f[l]; return;}
		int m=l+r>>1;
		node[p].ls=tot, Build(l,m);
		node[p].rs=tot, Build(m+1,r);
		PushUp(p);
//		printf("%d:l:%d r:%d val:%d\n",p,l,r,node[p].val);
	}
	void Modify(int rt,int pos,int v)
	{
		if(node[rt].l==node[rt].r)
		{
			node[rt].val=v; return;
		}
		int m=node[rt].l+node[rt].r>>1;
		if(pos<=m) Modify(node[rt].ls,pos,v);
		else Modify(node[rt].rs,pos,v);
		PushUp(rt);
	}
	int Query(int rt,int L,int R)
	{
		if(L<=node[rt].l && node[rt].r<=R) return node[rt].val;
		int m=node[rt].l+node[rt].r>>1;
		if(L<=m)
			if(m<R) return std::min(Query(node[rt].ls,L,R),Query(node[rt].rs,L,R));
			else return Query(node[rt].ls,L,R);
		else if(m<R) return Query(node[rt].rs,L,R);
	}
}t;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	n=read(),m=read();
	memset(f,0x3f,sizeof f);
	f[1]=0;
	t.Build(1,n);
	int l,r,tmp;
	while(m--)
	{
		l=read(),r=read();
		if(f[r]>(tmp=t.Query(0,l,r-1)+1))
			f[r]=tmp, t.Modify(0,r,tmp);
	}
	printf("%d",f[n]);

	return 0;
}
