/*
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=5e6+5;

int fa[N],ok[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void Union(int x,int y)
{
	fa[Find(x)]=Find(y);
}

int main()
{
	for(int n=read(),q=n,opt,x; q--; )
		switch(opt=read(),x=read(),opt)
		{
			case 1:
				ok[x]=1, fa[x]=x;
				if(ok[x+1]) Union(x,x+1);
				if(ok[x-1]) Union(x-1,x);
				break;
			case 2:
				if(ok[x]||Find(1)!=x-1) printf("%d\n",Find(1)+1);
				else if(Find(1)==x-1)
					printf("%d\n",ok[x+1]?Find(x+1)+1:x+1);
				break;
		}

	return 0;
}
