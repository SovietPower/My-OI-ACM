/*
467ms	65800KB
如果$i,j(i<j)$两个位置不是朋友，那么$j$永远不可能到$i$前面，否则$i$对$j$没有限制。
所以可以考虑拓扑排序。。如果两个位置$i,j(i<j)$处不是朋友，则连边$i->j$，即选完$i$后才能选$j$。
字典序最小的拓扑就是把`queue`换成`priority_queue`。
*/
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int A[N],las[N],dgr[N];
bool fri[205][205];
std::string str[222];
std::vector<int> to[N];
std::unordered_map<std::string,int> mps;

struct cmp
{
	bool operator ()(int a,int b)
	{
		return A[a]>A[b];
	}
};
std::priority_queue<int,std::vector<int>,cmp> q;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(; !isdigit(c); c=='-'&&(f=-1),c=gc());
	for(; isdigit(c); now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{	
	int S=read(),l=read(),n=read();
	for (int i=1; i<=S; ++i) std::cin>>str[i];
	std::sort(str+1,str+S+1);
	for (int i=1; i<=S; ++i) mps[str[i]]=i;

	std::string s1,s2;
	for(int i=1,x,y; i<=l; ++i) 
		std::cin>>s1>>s2, x=mps[s1], y=mps[s2], fri[x][y]=1, fri[y][x]=1;
	for(int i=1; i<=n; ++i) std::cin>>s1, A[i]=mps[s1];

	for(int i=1; i<=n; ++i)
	{
		for(int j=1,x=A[i]; j<=S; ++j)
			if(las[j] && !fri[x][j])
				to[las[j]].push_back(i), ++dgr[i];
		las[A[i]]=i;
	}

	for(int i=1; i<=n; ++i) if(!dgr[i]) q.push(i);
	while(!q.empty())
	{
		int x=q.top(); q.pop();
		std::cout<<str[A[x]]<<' ';
		for(auto j:to[x])
			if(!--dgr[j]) q.push(j);
	}

	return 0;
}
