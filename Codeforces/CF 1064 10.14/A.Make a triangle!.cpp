#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
#define gc() getchar()
const int N=1e6+7;
using std::cin;
using std::cout;

inline int read()
{
	int now=0,f=1;
	register char c=gc();
	for(; !isdigit(c); c=='-'&&(f=-1),c=gc());
	for(; isdigit(c); now=now*10+c-'0',c=gc());
	return now*f;
}

int a[10], b, c;
bool Check()
{
	std::sort(a+0, a+3);
	return (a[0]+a[1])>a[2];
}

int main()
{
	cin>>a[0]>>a[1]>>a[2];
	int ans=0;
	while (!Check())
		++a[0], ++ans;
	cout<<ans;
	return 0;
}