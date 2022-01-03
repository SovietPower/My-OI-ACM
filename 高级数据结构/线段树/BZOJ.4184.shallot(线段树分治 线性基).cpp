/*
41652kb	11920ms
裸的线段树分治+线性基，就是跑的巨慢\_(:з」∠)\_ 。
不知道他们都写的什么=-=
*/
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define BIT 30
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

std::map<int,int> las;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Base
{
	int x[BIT+1];
	void Insert(int v)
	{
		for(int i=BIT; ~i; --i)
			if(v>>i&1)
				if(x[i]) v^=x[i];
				else {x[i]=v; break;}
	}
	void Query()
	{
		int res=0;
		for(int i=BIT; ~i; --i) res=std::max(res,res^x[i]);
		printf("%d\n",res);
	}
}base;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	std::vector<int> vec[S];
	#undef S
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {vec[rt].push_back(v); return;}
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
	}
	void Solve(int l,int r,int rt,Base b)
	{
		for(std::vector<int>::iterator it=vec[rt].begin(); it!=vec[rt].end(); ++it) b.Insert(*it);
		if(l==r) {b.Query(); return;}
		int m=l+r>>1; Solve(lson,b), Solve(rson,b);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	#define S 1,n,1
	const int n=read();
	for(int i=1; i<=n; ++i)
	{
		int a=read();
		if(las[a]) T.Modify(S,las[a],i-1,a), las[a]=0;
		else las[a]=i;
	}
	for(std::map<int,int>::iterator it=las.begin(); it!=las.end(); ++it)
		if((*it).second) T.Modify(S,(*it).second,n,(*it).first);
	T.Solve(S,base);

	return 0;
}
