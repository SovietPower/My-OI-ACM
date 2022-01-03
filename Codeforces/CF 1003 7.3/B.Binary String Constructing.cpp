#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=10000;

int A,B,X;
char s[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	A=read(),B=read(),X=read();//A:0 B:1
	int n=A+B;
//	if(X==1)
//	{
//		for(int i=1; i<=A; ++i) putchar('0');
//		for(int i=A+1; i<=n; ++i) putchar('1');
//		return 0;
//	}
	const char f=A>=B?'1':'0', s=A>=B?'0':'1';
	if(A>B) std::swap(A,B);
	for(int i=1; i<=X; ++i)
		putchar((i&1)?s:f), --((i&1)?B:A);
	if(X&1)
	{
		for(int i=X+1; i<=X+B; ++i) putchar(s);
		for(int i=X+B+1; i<=n; ++i) putchar(f);
	}
	else
	{
		for(int i=X+1; i<=X+A; ++i) putchar(f);
		for(int i=X+A+1; i<=n; ++i) putchar(s);
	}

	return 0;
}
