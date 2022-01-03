/*
4248kb	892ms
对于线段，依旧是存斜率即可。
精度误差一点都不需要管啊/托腮 
就我一个人看成了mod(10^9+1)吗。。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define mp std::make_pair
#define pr std::pair<double,int>
typedef long long LL;
const int N=4e4+5;

char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int ID[S];
	double K[S],B[S];
	#undef S
	void Modify(int l,int r,int rt,int L,int R,double k,double b,int id)
	{
		if(L<=l && r<=R)
		{
			double l0=K[rt]*l+B[rt],r0=K[rt]*r+B[rt],l1=k*l+b,r1=k*r+b;
			if(l0>=l1 && r0>=r1) return;
			if(l0<l1 && r0<r1) {K[rt]=k, B[rt]=b, ID[rt]=id; return;}
			int m=l+r>>1;
			double p=(b-B[rt])/(K[rt]-k);
			if(l0>l1)
				if(p<=m) Modify(lson,L,R,K[rt],B[rt],ID[rt]), K[rt]=k, B[rt]=b, ID[rt]=id;
				else Modify(rson,L,R,k,b,id);
			else
				if(p<=m) Modify(lson,L,R,k,b,id);
				else Modify(rson,L,R,K[rt],B[rt],ID[rt]), K[rt]=k, B[rt]=b, ID[rt]=id;
			return;
		}
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,k,b,id);
		if(m<R) Modify(rson,L,R,k,b,id);
	}
	pr Query(int l,int r,int rt,double x)
	{
		if(l==r) return mp(K[rt]*x+B[rt],-ID[rt]);
		int m=l+r>>1;
		return std::max(mp(K[rt]*x+B[rt],-ID[rt]),x<=m?Query(lson,x):Query(rson,x));
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	#define n 39989
	#define mod 1000000000
	for(int Q=read(),ans=0,cnt=0; Q--; )
		switch(read())
		{
			case 0: printf("%d\n",ans=-T.Query(1,n,1,(read()+ans-1)%n+1).second); break;
			case 1:
			{
				++cnt;
				int x1=(read()+ans-1)%n+1,y1=(read()+ans-1)%mod+1,x2=(read()+ans-1)%n+1,y2=(read()+ans-1)%mod+1;
				double k,b;
				if(x1>x2) std::swap(x1,x2), std::swap(y1,y2);
				if(x1!=x2) k=1.0*(y1-y2)/(x1-x2), b=y1-k*x1;//忘转double了== 
				else k=0, b=std::max(y1,y2);
				T.Modify(1,n,1,x1,x2,k,b,cnt);
				break;
			}
		}
	return 0;
}
