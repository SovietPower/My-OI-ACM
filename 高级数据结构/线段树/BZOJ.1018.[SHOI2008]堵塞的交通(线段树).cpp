/*
5708kb	768ms
只有两行，可能的路径数不多，考虑用线段树维护各种路径的连通性。
每个节点记录luru(left_up->right_up),lurd,ldru,ldrd,luld,rurd,表示这个区间对应的连通信息。
合并时 横向道路需要用两个数组up[],down[]记录连通性；纵向道路在修改时直接单点改，再PushUp。
询问时连通的可能性有多种，都需判断。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e5+5;

int n,tot;//root=0
bool road[2][N];
struct Node
{
	int l,r,ls,rs;
	bool luru,lurd,ldru,ldrd,luld,rurd;
}node[N<<1];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
#define now node[rt]
#define nls node[ls]
#define nrs node[rs]
void Build(int l,int r)
{
	int p=tot++; node[p].l=l, node[p].r=r;
	if(l==r) node[p].luru=node[p].ldrd=1;//这个初始化要有。
	else{
		int m=l+r>>1;
		node[p].ls=tot, Build(l,m),
		node[p].rs=tot, Build(m+1,r);
	}
}
//void Print(Node rt){
//	printf("%d~%d\nluru:%d lurd:%d ldru:%d ldrd:%d luld:%d rurd:%d\n",rt.l,rt.r,rt.luru,rt.lurd,rt.ldru,rt.ldrd,rt.luld,rt.rurd);
//}
inline void Update(int rt)
{
	int ls=now.ls,rs=now.rs,p=node[ls].r;
	now.luru=(nls.luru&&road[0][p]&&nrs.luru)||(nls.lurd&&road[1][p]&&nrs.ldru);
	now.lurd=(nls.luru&&road[0][p]&&nrs.lurd)||(nls.lurd&&road[1][p]&&nrs.ldrd);
	now.ldru=(nls.ldrd&&road[1][p]&&nrs.ldru)||(nls.ldru&&road[0][p]&&nrs.luru);
	now.ldrd=(nls.ldrd&&road[1][p]&&nrs.ldrd)||(nls.ldru&&road[0][p]&&nrs.lurd);
	now.luld=nls.luld||(nls.luru&&road[0][p]&&nrs.luld&&road[1][p]&&nls.ldrd);
	now.rurd=nrs.rurd||(nrs.luru&&road[0][p]&&nls.rurd&&road[1][p]&&nrs.ldrd);
}
Node Merge(const Node &ls,const Node &rs)
{
	Node tmp;
	int p=ls.r; tmp.l=ls.l, tmp.r=rs.r;//左右端点要更新！(p)
	tmp.luru=(ls.luru&&road[0][p]&&rs.luru)||(ls.lurd&&road[1][p]&&rs.ldru);
	tmp.lurd=(ls.luru&&road[0][p]&&rs.lurd)||(ls.lurd&&road[1][p]&&rs.ldrd);
	tmp.ldru=(ls.ldrd&&road[1][p]&&rs.ldru)||(ls.ldru&&road[0][p]&&rs.luru);
	tmp.ldrd=(ls.ldrd&&road[1][p]&&rs.ldrd)||(ls.ldru&&road[0][p]&&rs.lurd);
	tmp.luld=ls.luld||(ls.luru&&road[0][p]&&rs.luld&&road[1][p]&&ls.ldrd);
	tmp.rurd=rs.rurd||(rs.luru&&road[0][p]&&ls.rurd&&road[1][p]&&rs.ldrd);
	return tmp;
}
void Modify_Row(int rt,int p,bool is_down,bool v)
{
	int m=now.l+now.r>>1;
	if(m==p){//当前区间从m处与m+1断开，所以应该在这更新！
		road[is_down][m]=v;
		if(now.l!=now.r) Update(rt);
	}
	else{
		if(p<=m) Modify_Row(now.ls,p,is_down,v);
		else Modify_Row(now.rs,p,is_down,v);
		Update(rt);
	}
}
void Modify_Col(int rt,int p,bool v)
{
	if(now.l==now.r)
		/*now.luru=now.ldrd=*/now.lurd=now.ldru=now.luld=now.rurd=v;//更新列之间的就可以了?
	else{
		int m=now.l+now.r>>1;
		if(p<=m) Modify_Col(now.ls,p,v);
		else Modify_Col(now.rs,p,v);
		Update(rt);
	}
}
Node Query(int rt,int L,int R)
{
	if(L<=now.l && now.r<=R) return now;
	int m=now.l+now.r>>1;
	if(L<=m)
		if(m<R) return Merge(Query(now.ls,L,R),Query(now.rs,L,R));
		else return Query(now.ls,L,R);
	return Query(now.rs,L,R);
}
void Ask(int r1,int c1,int r2,int c2)
{
	Node l=Query(0,1,c1),m=Query(0,c1,c2),r=Query(0,c2,n);//由这三个位置去判断 
//	Print(l), Print(m), Print(r);
	if(r1==1 && r2==1)
	{
		if ((m.luru)||
			(m.lurd&&r.luld)||
			(m.ldru&&l.rurd)||
			(l.rurd&&m.ldrd&&r.luld)) puts("Y");
		else puts("N");
	}
	else if(r1==2 && r2==2)
	{
		if ((m.ldrd)||
			(m.ldru&&r.luld)||
			(m.lurd&&l.luld)||
			(l.rurd&&m.luru&&r.luld)) puts("Y");
		else puts("N");
	}
	else if(r1==1)//r2==2
	{
		if ((m.lurd)||
			(m.luru&&r.luld)||
			(m.ldrd&&l.rurd)||
			(l.rurd&&m.ldru&&r.luld)) puts("Y");
		else puts("N");
	}
	else if(r1==2)//r2==1
	{
		if ((m.ldru)||
			(m.ldrd&&r.luld)||
			(m.luru&&l.rurd)||
			(l.rurd&&m.lurd&&r.luld)) puts("Y");
		else puts("N");
	}
}
//void Print_All(int rt){
//	if(now.ls) Print_All(now.ls);
//	Print(node[rt]);
//	if(now.rs) Print_All(now.rs);
//}

int main()
{
	n=read(), Build(1,n);
	char opt[3]; int r1,r2,c1,c2;
//	Print_All(0);
	while(scanf("%s",opt), opt[0]!='E')
	{
		r1=read(),c1=read(),r2=read(),c2=read();
		if(c1>c2) std::swap(r1,r2),std::swap(c1,c2);//不是在r1>r2的时候换。
		if(opt[0]=='C')
			if(r1==r2) Modify_Row(0,c1,r1==2,0);
			else Modify_Col(0,c1,0);
		else if(opt[0]=='O')
			if(r1==r2) Modify_Row(0,c1,r1==2,1);
			else Modify_Col(0,c1,1);
		else Ask(r1,c1,r2,c2);
//		Print_All(0);
	}
	return 0;
}
