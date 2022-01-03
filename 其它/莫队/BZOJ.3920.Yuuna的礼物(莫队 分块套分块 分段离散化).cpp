/*
$Description$
给定一个长为n的序列，每次查询区间中出现次数k1小的数里面的k2小的数。卡空间。
$Solution$
将出现次数按权值分块，这样可以实现O(1)插入，O(sqrt(n))查询第k1小的出现次数 
但是还需要知道第k2小的值，可以每个块维护点的个数棵平衡树，但这样插入复杂度会变高 
同样可以在每个块内每个节点再套一个权值分块，同样能够O(1)插入 
但是权值分块的大小是严格值域的，即出现次数为i的值都可能出现在i块里，这样空间无法承受 
于是需要分段离散化，对于块i，用出现次数>=i的Ax对其离散化。
∑tmi=n，所以空间是O(n)的；时间复杂度O(m*sqrt(n))(证明:https://www.cnblogs.com/autsky-jadek/p/4376091.html)
细节。。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define gc() getchar()
#define pb push_back
typedef unsigned short ushort;
const int N=40005;

ushort n,size,m,A[N],B[N],bel[N],Ans[N];
int sz1[N],sum1[N],tm[N];//都可能有负 
std::vector<ushort> sum2[N]/*某块中存在某数*/,ref[N],rank[N]/*某个数在某块中的位置*/,sz2[N];
struct Ask
{
	int l,r,k1,k2,id;
	bool operator <(const Ask &a)const
	{
		return bel[l]==bel[a.l]? r<a.r : bel[l]<bel[a.l];
//		return bel[l]==bel[a.l]? ((l-1)/size&1 ? r>a.r : r<a.r) : bel[l]<bel[a.l];
	}
}q[N];

inline ushort read()
{
	ushort now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Get_Pos1(int p)//找到k1所在大块、and 具体的套着的那个块
{
	int x=1;
	for(int i=1; i<=bel[n]; ++i)
		if((p-=sz1[i])<=0) {p+=sz1[x=i]; break;}
	for(int tmp=std::min((int)n,x*size-1),i=(x-1)*size; i<=tmp; ++i)
		if(!(p-=(sum1[i]>0))) return i;
}
int Get_Pos2(int id,int p)
{
	int x=1;
	for(int i=1; i<sum2[id].size(); ++i)//不能是<bel[sum2[id].size()]，不如直接<size，反正它肯定会结束 
		if((p-=sz2[id][i])<=0) {p+=sz2[id][x=i]; break;}
	for(int tmp=std::min((int)sum2[id].size(),x*size),i=(x-1)*size; i<tmp; ++i)//注意vector的边界 
		if(!(p-=sum2[id][i])) return i;
}
int Query(int k1,int k2)
{
	int id=Get_Pos1(k1);
	return ref[id][Get_Pos2(id,k2)];
}
inline void Update(int p,int delta)//仅在tm[p]>0(不是if(tm[p]))时加！ 
{//修改块内的块 
	sum1[tm[p]]+=delta;//同理 这个也要减掉 
	if(sum1[tm[p]] && delta==1) ++sz1[bel[tm[p]]];
	if(!sum1[tm[p]] && delta==-1) --sz1[bel[tm[p]]];
	int pos=rank[p][tm[p]-1];//对于相同数多次出现已是位于不同的块，so 出现次数就不用管了 
	sz2[tm[p]][bel[pos]]+=delta, sum2[tm[p]][pos]+=delta;
}
inline void Modify(int p,int delta)
{
	if(tm[p]>0) Update(p,-1);//要把原先的次数删掉 
	tm[p]+=delta;
	if(tm[p]>0) Update(p,1);
}
//inline void Add(int p)//WA: 没有把之前的sz1减掉 
//{
//	if(tm[p]>0) Update(p,-1);//要把原先的次数删掉 
//	++tm[p];
//	if(++sum1[tm[p]]==1) ++sz1[bel[tm[p]]];//对于外面的块 每个出现次数只计算一次
//	if(tm[p]>0) Update(p,1);
//}
//inline void Subd(int p)
//{
//	if(tm[p]>0) Update(p,-1);
//	if(!--sum1[tm[p]]) --sz1[bel[tm[p]]];
//	if(--tm[p]>0) Update(p,1);//次数-1后的加上 
//}

int main()
{
	n=read(), size=sqrt(n);
	bel[0]=1;//得有bel[0]给vector使 
	for(int i=1; i<=n; ++i) A[i]=B[i]=read(),++tm[A[i]],bel[i]=i/size+1;//全从0开始分块更方便 
	std::sort(B+1,B+1+n);
	for(int i=1; i<=n; ++i)//Discrete
	{
		for(int j=1; j<=tm[B[i]]; ++j)
			sum2[j].pb(0), rank[B[i]].pb(ref[j].size()), ref[j].pb(B[i]);
		tm[B[i]]=0;//去重 
	}
	for(int i=1; i<=n; ++i)
		for(int j=0; j<=bel[sum2[i].size()]; ++j) sz2[i].pb(0);//<=!
	m=read();
	for(int i=1; i<=m; ++i)
		q[i].l=read(),q[i].r=read(),q[i].k1=read(),q[i].k2=read(),q[i].id=i;
	std::sort(q+1,q+1+m);
	for(int l=1,r=0,i=1; i<=m; ++i)
	{
		while(l<q[i].l) Modify(A[l++],-1);
		while(l>q[i].l) Modify(A[--l],1);
		while(r<q[i].r) Modify(A[++r],1);
		while(r>q[i].r) Modify(A[r--],-1);
		Ans[q[i].id]=Query(q[i].k1,q[i].k2);
	}
	for(int i=1; i<=m; ++i) printf("%d\n",Ans[i]);

	return 0;
}
