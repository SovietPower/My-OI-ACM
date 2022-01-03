#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define mod 1000000007//998244353
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

struct Node
{
	int a,cost,id;
	bool operator <(const Node &x)const
	{
		return cost==x.cost?id<x.id:cost<x.cost;
	}
}A[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	static int id[N];
	int n=read(),m=read();
	for(int i=1; i<=n; ++i) A[i].a=read(), A[i].id=i;
	for(int i=1; i<=n; ++i) A[i].cost=read();
	std::sort(A+1,A+1+n);
	for(int i=1; i<=n; ++i) id[A[i].id]=i;
//	for(int i=1; i<=n; ++i) printf("A[%d]: a:%d cost:%d id:%d\n",i,A[i].a,A[i].cost,A[i].id);
	int now=1;
	for(int i=1; i<=m; ++i)
	{
		int type=read(),num=read(),p=id[type];
//		printf("%d:type:%d num:%d p:%d\n",i,type,num,p);
		LL ans=0;
		if(A[p].a>=num) ans=1ll*num*A[p].cost, A[p].a-=num, num=0;
		else
		{
			num-=A[p].a, ans=1ll*A[p].a*A[p].cost, A[p].a=0;
			while(num>0 && now<=n)
			{
				while(now<=n && !A[now].a) ++now;
				if(now>n) break;
				int t=std::min(num,A[now].a);
				ans+=1ll*t*A[now].cost, num-=t, A[now].a-=t;
			}
		}
		if(num) ans=0;
		printf("%I64d\n",ans);
	}
	return 0;
}
