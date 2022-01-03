#include <map>
#include <set>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=3e5+5;

int tmp[N];
std::priority_queue<int,std::vector<int>,std::greater<int> > q;
struct Node
{
	int len,val;
	bool operator <(const Node &x)const
	{
		return val==x.val?len<x.len:val<x.val;
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
	int n=read(),k=read();
	for(int i=1; i<=n; ++i) A[i]=(Node){read(),read()};
	std::sort(A+1,A+1+n);
	LL ans=0,now=0;
	for(int i=n; i; --i)
	{
		while(q.size()>=k) now-=q.top(), q.pop();
		now+=A[i].len, q.push(A[i].len);	
		ans=std::max(ans,now*A[i].val);
	}
	printf("%I64d\n",ans);

	return 0;
}
