/*
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=1e5+5;



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
		int A=read(),B=read(),D=std::max(A,B)-std::min(A,B),mn=1e9,mx=0;
		if(A==B)
			mx=A==1?0:A, mn=2;
		else
		{
			for(int i=2; 1ll*i*i<=D; ++i)
				if(!(D%i)) mx=std::max(mx,D/i), mn=std::min(mn,i);
			if(D>1) mx=D, mn=std::min(mn,D);
		}
		printf("%d %d\n",mx?mn:-1,mx?mx:-1);
	}

	return 0;
}
