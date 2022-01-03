/*
404ms	3.36MB
$Description$
给定一个无向带权连通图，每条边是黑色或白色。求一棵最小权的恰好有K条白边的生成树。
$Solution$
Kruskal是选取最小的n-1条边。而白边数有限制，考虑为其设额外边权C。
随着C增大，选的白边数应是不增的。可以二分求一个C值使得此时恰好选择K条边。选取时应优先选白边，因为多了还可以用黑边替换，少了只能减少C。
可能的问题是，C=mid时白边数>K，C=mid+1时白边数<K，因为有很多黑边与+mid后的白边权值想等。可以用这些黑边替换掉多余的白边，所以答案应是减K*mid(保留黑边)。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 100000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=5e4+5,M=1e5+5;

int n,m,K,fa[N],Ans;
char IN[MAXIN],*SS=IN,*TT=IN;
int read();
struct Edge
{
	int fr,to,val,col;
	inline void Init(){
		fr=read()+1, to=read()+1, val=read(), col=read();
	}
	bool operator <(const Edge &x)const{
		return val==x.val?col<x.col:val<x.val;
	}
}e[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int GetFa(int x){
	return x==fa[x]?x:fa[x]=GetFa(fa[x]);
}
bool Check(int x)
{
	for(int i=1; i<=m; ++i) if(!e[i].col) e[i].val+=x;
	for(int i=1; i<=n; ++i) fa[i]=i;
	std::sort(e+1,e+1+m);
	int sum=0, cnt=0;
	for(int i=1,k=0,r1,r2; i<=m; ++i)
	{
		if((r1=GetFa(e[i].fr))==(r2=GetFa(e[i].to))) continue;
		fa[r1]=r2, sum+=e[i].val;
		cnt+=e[i].col^1;
		if(++k+1==n) break;
	}
	for(int i=1; i<=m; ++i) if(!e[i].col) e[i].val-=x;
	if(cnt<K) return 0;
	Ans = sum-K*x;//不能取min！
	return 1;
}

int main()
{
	n=read(),m=read(),K=read();
	for(int i=1; i<=m; ++i) e[i].Init();
	Ans=m*101; int l=-101,r=101,mid;
	while(l<=r)//l==r时要Check一遍(或者结束时)
		if(Check(mid=l+r>>1)) l=mid+1;
		else r=mid-1;
//	Check(l);
	printf("%d",Ans);

	return 0;
}
