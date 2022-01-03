/*
78ms	1600KB
容易发现只要模拟一下按顺序合并连通块即可。可以用vector+启发式合并，也可以链表。用链表复杂度$O(n\alpha(n))$。
*/
#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=150005;

int fa[N],R[N],ed[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) fa[i]=ed[i]=i;
	for(int i=1; i<n; ++i)
	{
		int x=read(),y=read();
		int r1=Find(x),r2=Find(y);
		fa[r2]=r1, R[ed[r1]]=r2, ed[r1]=ed[r2];
	}
	for(int i=1; i<=n; ++i)
		if(fa[i]==i)
		{
			for(int x=i; x; x=R[x]) printf("%d ",x);
			break;
		}

	return 0;
}
