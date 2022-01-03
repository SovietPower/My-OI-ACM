/*
795ms	41500KB
$Description$
有$n$个人都要参加考试，每个人可以在$ai$或$bi$天考试，同一天不能有两个人考试。求最晚考试的人的时间最早能是多少。无解输出-1。
$Solution$
把每个人向$ai,bi$连边。对于每个连通块单独考虑。
记点数为n，边数为m。可以发现当某一连通块n>m(n=m+1)时，可以有一个点不选(最大的)；
当n=m时，所有点都要选；n<m时，无解。
用并查集维护连通，顺便维护最大、次大值。当第一次出现环时，即n=m；第二次出现就无解(n<m)了。
离散化可以写个Hash省掉log。
怎么这种题还是不去想连边。。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
//#define MAXIN 200000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e6+5;

int ref[N],A[N>>1],B[N>>1],fa[N],mx[N],smx[N];
bool tag[N];
//char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
inline int Getfa(int x)
{
	return x==fa[x]?x:fa[x]=Getfa(fa[x]);
}

int main()
{
	int n=read(),t=0;
	for(int i=1; i<=n; ++i) ref[++t]=A[i]=read(),ref[++t]=B[i]=read();
	std::sort(ref+1,ref+1+t); int cnt=1;
	for(int i=2; i<=t; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];

	for(int i=1; i<=cnt; ++i) fa[i]=i,mx[i]=ref[i];
	for(int i=1,x,y,r1,r2; i<=n; ++i)
	{
		x=Find(A[i],cnt), y=Find(B[i],cnt);
		if((r1=Getfa(x))!=(r2=Getfa(y)))
		{
			fa[r2]=r1, tag[r1]|=tag[r2];//!
			if(mx[r2]>mx[r1]) smx[r1]=std::max(mx[r1],smx[r2]), mx[r1]=mx[r2];
			else smx[r1]=std::max(smx[r1],mx[r2]);
		}
		else if(tag[r1]) return puts("-1"),0;
		else tag[r1]=1;
	}
	int ans=0;
	for(int i=1; i<=cnt; ++i)
		if(fa[i]==i)
			if(tag[i]) ans=std::max(ans,mx[i]);
			else ans=std::max(ans,smx[i]);
	printf("%d\n",ans);

	return 0;
}
