//贪心思路显然。
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

int n,A[N];
std::queue<int> q0,qn,qp;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	n=read(); int p=0;
	for(int i=1; i<=n; ++i)
	{
		A[i]=read();
		if(!A[i]) q0.push(i);
		else if(A[i]>0) qp.push(i);
		else
		{
			qn.push(i);
			if(!p || A[i]>A[p]) p=i;
		}
	}
	int x=0; --n;// n=1e5;
	while(!q0.empty())
	{
		int y=q0.front(); q0.pop();
		if(x)
		{
			printf("1 %d %d\n",x,y);
			if(!--n) return 0;
		}
		x=y;
	}
	bool f=0;
	if(qn.size()&1)
	{
		f=1;
		if(x)
		{
			printf("1 %d %d\n",x,p), x=0;
			if(!--n) return 0;
		}
		printf("2 %d\n",p);
		if(!--n) return 0;
	}
	else if(x)
	{
		printf("2 %d\n",x);
		if(!--n) return 0;
	}
	x=0;
	while(!qn.empty())
	{
		int y=qn.front(); qn.pop();
		if(f&&y==p) continue;
		if(x)
		{
			printf("1 %d %d\n",x,y);
			if(!--n) return 0;
		}
		x=y;
	}
	while(!qp.empty())
	{
		int y=qp.front(); qp.pop();
		if(x)
		{
			printf("1 %d %d\n",x,y);
			if(!--n) return 0;
		}
		x=y;
	}

	return 0;
}
