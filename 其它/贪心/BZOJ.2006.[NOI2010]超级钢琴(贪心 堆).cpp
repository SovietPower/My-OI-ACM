/*
54620kb	1060ms
思路和[BZOJ3784]一样，用前缀和+堆维护。不赘述啦。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

int sum[N],pos[19][N],Log[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int val,si,l,r;
	bool operator <(const Node &x)const
	{
		return val<x.val;
	}
};
std::priority_queue<Node> q;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline int Max(int x,int y)
{
	return sum[x]>sum[y]?x:y;
}
inline int Query(int l,int r)
{
	int k=Log[r-l+1];
	return Max(pos[k][l],pos[k][r-(1<<k)+1]);
}

int main()
{
	const int n=read(),K=read(),L=read(),R=read();
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]+read(), pos[0][i]=i;
	for(int i=2; i<=n; ++i) Log[i]=Log[i>>1]+1;
	for(int j=1; j<=Log[n]; ++j)
		for(int t=1<<j-1,i=n-t; i; --i)
			pos[j][i]=Max(pos[j-1][i],pos[j-1][i+t]);
	for(int i=0; i+L<=n; ++i) q.push((Node){sum[Query(i+L,std::min(i+R,n))]-sum[i],sum[i],i+L,std::min(i+R,n)});
	LL ans=0;
	for(int i=1,p; i<=K; ++i)
	{
		Node tmp=q.top(); q.pop();
		ans+=tmp.val, p=Query(tmp.l,tmp.r);
		if(tmp.l<p) q.push((Node){sum[Query(tmp.l,p-1)]-tmp.si,tmp.si,tmp.l,p-1});
		if(p<tmp.r) q.push((Node){sum[Query(p+1,tmp.r)]-tmp.si,tmp.si,p+1,tmp.r});
	}
	printf("%lld\n",ans);

	return 0;
}
