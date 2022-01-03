/*
2384kb	288ms
直接排序显然怎么都不行。
先按毁坏时间排序，优先修损坏早的，中途我们再改修的建筑。
枚举每个建筑x，如果能，就修；不能的话，从之前要修的建筑中找一个花时最大的need[top]，如果need[x]<need[top]，就替掉top，换修x。
这样每次最多也就是一个换一个，还能保证最优。
用堆维护即可。

这你怎么线性DP →_→
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define pr std::pair<int,int>
#define gc() getchar()
const int N=150007;

int n;
pr s[N];
std::priority_queue<int> q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) s[i].second=read(),s[i].first=read();
	std::sort(s+1,s+1+n);
	int now=0;
	for(int i=1; i<=n; ++i)
		if(now+s[i].second<=s[i].first) now+=s[i].second, q.push(s[i].second);
		else if(s[i].second<q.top() && now+s[i].second<=s[i].first+q.top()){
			now-=q.top(), q.pop(), q.push(s[i].second);
			now+=s[i].second;
		}
	printf("%d",q.size());

	return 0;
}
