//105344kb	4528ms
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
#define Add2(x,y) (x+y>=mod?x+y-mod:x+y)
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
	int tot,son[S][2],p[S],tag[S];
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
	int Merge(int x,int y,int s1,int s2,int P)
	{
		if(!x && !y) return 0;
		if(!x)
		{
			int v=(s1+P-2ll*s1*P%mod+mod)%mod;//注意+mod放到后面 
			Upd(y,v);
			return y;
		}
		if(!y)
		{
			int v=(s2+P-2ll*s2*P%mod+mod)%mod;
			Upd(x,v);
			return x;
		}
		if(tag[x]!=1) PushDown(x);
		if(tag[y]!=1) PushDown(y);
		ls=Merge(ls,son[y][0],Add2(s1,p[rs]),Add2(s2,p[son[y][1]]),P), rs=Merge(rs,son[y][1],s1,s2,P);
		p[x]=p[ls]+p[rs], Mod(p[x]);
		return x;
	}
	void GetAns(int x,int l,int r)
	{
		if(!p[x]) return;
		if(l==r)
		{
			Ans+=1ll*l*ref[l]%mod*p[x]%mod*p[x]%mod;
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
		root[x]=T.Merge(root[son[x][0]],root[son[x][1]],0,0,P[x]);
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
