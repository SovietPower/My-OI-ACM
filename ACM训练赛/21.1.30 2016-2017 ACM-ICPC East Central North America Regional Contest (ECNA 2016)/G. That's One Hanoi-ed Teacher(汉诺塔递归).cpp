/*
30ms	0KB
需要复习一下汉诺塔。汉诺塔的递归是这样的：
```cpp
void DFS(int n,int a,int b,int c)//第n个圆盘从a->c
{
	if(n==1)
	{
		printf("%d: %d->%d\n",n,a,c);
		return;
	}
	DFS(n-1,a,c,b);
	printf("%d: %d->%d\n",n,a,c);
	DFS(n-1,b,a,c);
}
```
总过程是，将圆盘$n-1$从$a$移到$b$，将圆盘$n$从$a$移到$c$，最后将圆盘$n-1$从$b$移到$c$。
所以这个题，从$n$开始判断，如果$n$仍在$a$上则还至少需$2^{n-1}-1$步将$n-1$个盘子从$b$移到$c$，和$1$步将$n$移到$c$；如果$n$在$b$上，则不是最优解；如果$n$在$c$上则再看$n-1$即可。
类似地递归一下，注意修改当前的参数$a,b,c$就可以了。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=105;

int vis[N];
LL ans;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
bool DFS(int n,int a,int b,int c)
{
	if(!n) return 1;
	if(vis[n]==a) return ans+=1ll<<(n-1),DFS(n-1,a,c,b);//n还在a，n-1从a移到b去 
	else if(vis[n]==c) return DFS(n-1,b,a,c);//n已经到c，n-1从b移回到c去 
	return 0;
}

int main()
{
	int a=read(); for(int i=1; i<=a; ++i) vis[read()]=1;
	int b=read(); for(int i=1; i<=b; ++i) vis[read()]=2;
	int c=read(); for(int i=1; i<=c; ++i) vis[read()]=3;
	if(!DFS(a+b+c,1,2,3)) puts("No");
	else printf("%lld\n",ans);

	return 0;
}
