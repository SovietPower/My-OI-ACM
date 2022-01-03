#include <queue>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define pc putchar
#define mp std::make_pair
#define pr std::pair<int,int>
typedef long long LL;
const int N=1e5+5;

int A[N],B[N];
std::priority_queue<int,std::vector<int>,std::greater<int> > q[N],q2;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int n=read(),K=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; ++i) q[A[i]].push(B[i]=read());
	LL ans=0;
	for(int i=1; i<=K; ++i)
		while(q[i].size()>1)
			q2.push(q[i].top()), q[i].pop();
	for(int i=1; i<=K; ++i)
		if(!q[i].size()) ans+=q2.top(), q2.pop();
	printf("%I64d\n",ans);

	return 0;
}
