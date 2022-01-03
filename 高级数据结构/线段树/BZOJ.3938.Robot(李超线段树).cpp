/*
66516kb	5156ms
以时间$t$为横坐标，位置$p$为纵坐标建坐标系，那每个机器人就是一条$0\sim INF$的折线。
用李超线段树维护最大最小值。对于折线分成若干条线段依次插入即可。
最好还是离线对时间离散化。
麻烦在写出来。。
复杂度$O(c\log^2m+q\log m)$？
以后李超树改用`struct`写了...学了一种写法好方便...
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,M=5e5+5;

int cnt,ref[N+M];//n+m!
char IN[MAXIN],*SS=IN,*TT=IN;
struct Line
{
	int K; LL B;
	LL f(int x)
	{
		return 1ll*K*x+B;
	}
};
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S (N+M<<2)//1~n+m!
	Line mn[S],mx[S];
	#undef S
	void ModifyMax(int l,int r,int rt,int L,int R,Line v)
	{
		int m=l+r>>1;
		if(v.f(ref[m])>mx[rt].f(ref[m])) std::swap(v,mx[rt]);
		if(l==r) return;
		if(mn[rt].f(ref[l])>=v.f(ref[l]) && mn[rt].f(ref[r])>=v.f(ref[r])) return;
//		if(std::max(mn[rt].f(ref[l]),mn[rt].f(ref[r]))>=std::min(v.f(ref[l]),v.f(ref[r]))) return;//为啥上面那种写法反而慢好多啊 不应该啊= = 
		if(v.K<mx[rt].K) ModifyMax(lson,L,R,v);
		else ModifyMax(rson,L,R,v);
	}
	void ModifyMin(int l,int r,int rt,int L,int R,Line v)
	{
		int m=l+r>>1;
		if(v.f(ref[m])<mn[rt].f(ref[m])) std::swap(v,mn[rt]);
		if(l==r) return;
		if(mn[rt].f(ref[l])<=v.f(ref[l]) && mn[rt].f(ref[r])<=v.f(ref[r])) return;
//		if(std::max(mn[rt].f(ref[l]),mn[rt].f(ref[r]))<=std::min(v.f(ref[l]),v.f(ref[r]))) return;
		if(v.K>mn[rt].K) ModifyMin(lson,L,R,v);
		else ModifyMin(rson,L,R,v);
	}
	void Modify(int l,int r,int rt,int L,int R,Line v)
	{
		if(L<=l && r<=R)
		{
			ModifyMax(l,r,rt,L,R,v), ModifyMin(l,r,rt,L,R,v);//max min分开维护.
			return;
		}
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
	}
	LL Query(int l,int r,int rt,int p,int x)//x=ref[p]
	{
		LL val=std::max(std::abs(mx[rt].f(x)),std::abs(mn[rt].f(x)));
		if(l==r) return val;
		int m=l+r>>1;
		return std::max(val,p<=m?Query(lson,p,x):Query(rson,p,x));
	}
}T;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline char GetOpt()
{
	register char c=gc();
	while(c!='c'&&c!='q') c=gc();
	return c;
}
inline int Find(int x)
{
	int l=1,r=cnt,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	static int Q[M];
	static std::vector<pr> vec[N];//每个机器人的折线 pair (time, slope)
	const int n=read(),m=read();
	for(int i=1; i<=n; ++i) vec[i].push_back(mp(0,read()));
	int cnt=1,q=0; ref[1]=0;
	for(int i=1,t,id; i<=m; ++i)
	{
		ref[i+1]=t=read();
		if(GetOpt()=='q') Q[++q]=t;
		else id=read(), vec[id].push_back(mp(t,read()));
	}

	ref[cnt=m+2]=1e9;
	for(int tmp=cnt,i=(cnt=1,2); i<=tmp; ++i)
		if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	::cnt=cnt;
	for(int i=1; i<=n; ++i) vec[i].push_back(mp(1e9,0));

	for(int i=1; i<=n; ++i)
	{
		int las=Find(vec[i][1].first);//r不需要减一啊→_→ 
		LL pos=vec[i][0].second;
		T.Modify(1,cnt,1,1,las,(Line){0,pos});
		for(int j=1,lim=vec[i].size()-2,l,r,k,now; j<=lim; ++j)//lim=size()，不要写l=size() →_→ 
		{
			l=vec[i][j].first, r=vec[i][j+1].first, k=vec[i][j].second;
			now=Find(r);
			T.Modify(1,cnt,1,las,now,(Line){k,pos-1ll*k*l});
			las=now, pos+=1ll*k*(r-l);
		}
	}
	for(int i=1; i<=q; ++i) printf("%lld\n",T.Query(1,cnt,1,Find(Q[i]),Q[i]));

	return 0;
}
