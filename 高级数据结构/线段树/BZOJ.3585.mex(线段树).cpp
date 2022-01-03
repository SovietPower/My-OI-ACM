/*
考虑[1,i]的mex[i]，显然是单调的 
而对于[l,r]与[l+1,r]，如果nxt[a[l]]>r，那么[l+1,r]中所有>a[l]的数显然要改成a[l] 
询问排序，离散化，预处理下nxt[]，剩下就是线段树的区间更新、查询了 
离散化的时候>=n的全部看做n就好了 
查询时是只需查r点的(l之前能更新r的已经更新完了，初始时是[1,r]，r点现在就是[l,r]了) 
单点即可不需要PushUp(也不好得某个区间的mex) 
非叶节点上的mex完全可以代替tag 
离散化需要注意 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
#define now node[rt]
#define lson node[node[rt].ls]
#define rson node[node[rt].rs]
const int N=2e5+5,INF=1e7;

int n,m,A[N],mex[N]/*不要和A混用*/,tmp[N],nxt[N],las[N],ans[N];
bool vis[N];
struct Ques
{
	int l,r,id;
	Ques() {}
	Ques(int l,int r,int id): l(l),r(r),id(id) {}
	bool operator <(const Ques &x)const {return l<x.l;}
}q[N];
struct Seg_Tree
{
	int tot;
	struct Node
	{
		int ls,rs,mex;
	}node[N<<1];
	inline void Upd(int &x,int v) {x=std::min(x,v);}
	inline void PushDown(int rt)
	{
		Upd(lson.mex,now.mex), Upd(rson.mex,now.mex);
		now.mex=INF;
	}
	void Build(int l,int r)
	{
		int rt=tot++;
		if(l==r) now.mex = mex[l];
		else
		{
			int m=l+r>>1; now.mex=INF;
			now.ls=tot, Build(l,m);
			now.rs=tot, Build(m+1,r);
		}
	}
	void Update(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) Upd(now.mex,v);
		else
		{
			if(now.mex<INF) PushDown(rt);
			int m=l+r>>1;
			if(L<=m) Update(l,m,now.ls,L,R,v);
			if(m<R) Update(m+1,r,now.rs,L,R,v);
		}
	}
	int Query(int l,int r,int rt,int p)
	{
		if(l==r) return now.mex;
		if(now.mex<INF) PushDown(rt);
		int m=l+r>>1;
		if(p<=m) return Query(l,m,now.ls,p);
		else return Query(m+1,r,now.rs,p);
	}
}t;
#undef now
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
int Find(int x,int r)
{
	int l=1,m;
	while(l<r)
	{
		if(tmp[(m=l+r>>1)]<x) l=m+1;
		else r=m;
	}
	return l;
}

int main()
{
	n=read(),m=read();
	for(int i=1; i<=n; ++i) tmp[i]=A[i]=std::min(n,read());
	std::sort(tmp+1,tmp+1+n);
	int cnt=1;
	for(int i=2; i<=n && !(tmp[i]==n&&tmp[i+1]==n); ++i)
		if(tmp[i]!=tmp[i-1]) tmp[++cnt]=tmp[i];
	for(int k=0,p,i=1; i<=n; ++i)
	{
		vis[p=Find(A[i],cnt)]=1;
		if(A[i]==k)//只有在当前最小值出现时才更新。。mex...
			while(vis[p])//p-1,vis[k]?
			{
				++k;
				if(tmp[++p]!=k) break;//离散化后 
			}
		mex[i]=k;
	}
	t.Build(1,n);
	for(int i=0; i<=n; ++i) las[i]=n+1;
	for(int tp,i=n; i; --i) nxt[i]=las[tp=Find(A[i],cnt)], las[tp]=i;//!
	for(int l,i=1; i<=m; ++i) l=read(), q[i]=Ques(l,read(),i);
	std::sort(q+1,q+1+m);
	for(int now=1,i=1; i<=m; ++i)
	{
		while(now<q[i].l)
			t.Update(1,n,0,now+1,nxt[now]-1,A[now]), ++now;
		ans[q[i].id]=t.Query(1,n,0,q[i].r);
	}
	for(int i=1; i<=m; ++i) printf("%d\n",ans[i]);

	return 0;
}
