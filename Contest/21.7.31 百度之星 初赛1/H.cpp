/*
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=55;

int id[N],P[N][N],ok[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	for(int T=read(); T--; )
	{
		int n=read(),res=n,p=0;
		for(int i=1; i<=n; ++i) id[i]=read(), id[i]&&(p=i), ok[i]=1;
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n; ++j) P[i][j]=read();

		int die=P[p][1];
		ok[die]=0, --res;

		while(res>2 && ok[p])
		{
			for(int i=1; i<=n; ++i)
				if(ok[P[die][i]]) {die=P[die][i], ok[die]=0, --res; break;}
		}
		puts(ok[p]?"langren":"lieren");
	}

	return 0;
}
